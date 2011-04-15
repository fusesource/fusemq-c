/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <CMS_Session.h>

#include <Config.h>
#include <private/CMS_Types.h>
#include <private/CMS_Utils.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <memory>

////////////////////////////////////////////////////////////////////////////////
cms_status cms_createDefaultSession(CMS_Connection* connection, CMS_Session** session) {

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_Session> wrapper( new CMS_Session );

    try{

        if (connection == NULL) {
            result = CMS_ERROR;
        } else {
            wrapper->session = connection->connection->createSession();
            *session = wrapper.release();
        }

    }
    CMS_CATCH_EXCEPTION( result )

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_createSession(CMS_Connection* connection, CMS_Session** session, CMS_ACKNOWLEDGMENT_MODE ackMode) {

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_Session> wrapper( new CMS_Session );

    try{

        if (connection == NULL) {
            result = CMS_ERROR;
        } else {

            cms::Session::AcknowledgeMode cmsAckType = cms::Session::AUTO_ACKNOWLEDGE;

            switch(ackMode) {
                case CMS_AUTO_ACKNOWLEDGE:
                    break;
                case CMS_DUPS_OK_ACKNOWLEDGE:
                    cmsAckType = cms::Session::DUPS_OK_ACKNOWLEDGE;
                    break;
                case CMS_CLIENT_ACKNOWLEDGE:
                    cmsAckType = cms::Session::CLIENT_ACKNOWLEDGE;
                    break;
                case CMS_SESSION_TRANSACTED:
                    cmsAckType = cms::Session::SESSION_TRANSACTED;
                    break;
                case CMS_INDIVIDUAL_ACKNOWLEDGE:
                    cmsAckType = cms::Session::INDIVIDUAL_ACKNOWLEDGE;
                    break;
                default:
                    return CMS_UNKNOWN_ACKTYPE;
            }
            wrapper->session = connection->connection->createSession(cmsAckType);
            *session = wrapper.release();
        }

    }
    CMS_CATCH_EXCEPTION( result )

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_destroySession(CMS_Session* session) {

    cms_status result = CMS_SUCCESS;

    if(session != NULL) {

        try{
            delete session->session;
            delete session;
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_closeSession(CMS_Session* session) {

    cms_status result = CMS_SUCCESS;

    if(session != NULL) {

        try{
            session->session->close();
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_commitSession(CMS_Session* session) {

    cms_status result = CMS_SUCCESS;

    if(session != NULL) {

        try{
            session->session->commit();
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_rollbackSession(CMS_Session* session) {

    cms_status result = CMS_SUCCESS;

    if(session != NULL) {

        try{
            session->session->rollback();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_recoverSession(CMS_Session* session) {

    cms_status result = CMS_SUCCESS;

    if(session != NULL) {

        try{
            session->session->recover();
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getSessionAcknowledgeMode(CMS_Session* session, int* mode) {

    cms_status result = CMS_SUCCESS;

    if(session != NULL && mode != NULL) {

        try{
            *mode = (int) session->session->getAcknowledgeMode();
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_isSessionTransacted(CMS_Session* session, int* transacted) {

    cms_status result = CMS_SUCCESS;

    if(session != NULL && result != NULL) {

        try{
            *transacted = (int) session->session->isTransacted();
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_unsubscribeSessionDurableConsumer(CMS_Session* session, const char* subscription) {

    cms_status result = CMS_SUCCESS;

    if(session != NULL && subscription != NULL) {

        try{
            session->session->unsubscribe(subscription);
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}
