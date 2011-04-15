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

#include <CMS_Connection.h>

#include <Config.h>
#include <private/CMS_Types.h>
#include <private/CMS_Utils.h>

#include <activemq/core/ActiveMQConnection.h>

#include <cms/IllegalStateException.h>
#include <cms/InvalidClientIdException.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <memory>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
cms_status cms_createDefaultConnection(CMS_ConnectionFactory* factory, CMS_Connection** connection) {

    cms_status result = CMS_ERROR;
    std::auto_ptr<CMS_Connection> wrapper( new CMS_Connection );

    try{

        if (factory != NULL && connection != NULL) {
            wrapper->connection = factory->factory->createConnection();
            wrapper->lastException = NULL;
            *connection = wrapper.release();
            result = CMS_SUCCESS;
        }
    }
    CMS_CATCH_EXCEPTION( result )

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_createConnection(CMS_ConnectionFactory* factory,
                                CMS_Connection** connection,
                                const char* username,
                                const char* password,
                                const char* clientId) {

    cms_status result = CMS_ERROR;
    std::auto_ptr<CMS_Connection> wrapper( new CMS_Connection );

    try{

        if (factory != NULL && connection != NULL) {

            std::string user = username == NULL ? "" : std::string(username);
            std::string pass = password == NULL ? "" : std::string(password);
            std::string id = clientId == NULL ? "" : std::string(clientId);

            wrapper->connection = factory->factory->createConnection(user, pass, id);
            wrapper->lastException = NULL;
            *connection = wrapper.release();
            result = CMS_SUCCESS;
        }
    }
    CMS_CATCH_EXCEPTION( result )

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_destroyConnection(CMS_Connection* connection) {

    cms_status result = CMS_ERROR;

    if (connection != NULL) {

        try{
            delete connection->connection;
            delete connection;
            result = CMS_SUCCESS;
        }
        CMS_CATCH_EXCEPTION( result )

    } else {
        result = CMS_SUCCESS;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_startConnection(CMS_Connection* connection) {

    cms_status result = CMS_ERROR;

    if (connection != NULL && connection->connection != NULL) {

        try{
            connection->connection->start();
            result = CMS_SUCCESS;
        }
        CMS_CATCH_CONNECTION_EXCEPTION( connection, result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_stopConnection(CMS_Connection* connection) {

    cms_status result = CMS_ERROR;

    if (connection != NULL && connection->connection != NULL) {

        try{
            connection->connection->stop();
            result = CMS_SUCCESS;
        }
        CMS_CATCH_CONNECTION_EXCEPTION( connection, result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_closeConnection(CMS_Connection* connection) {

    cms_status result = CMS_ERROR;

    if (connection != NULL && connection->connection != NULL) {

        try{
            connection->connection->close();
            result = CMS_SUCCESS;
        }
        CMS_CATCH_CONNECTION_EXCEPTION( connection, result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_setConnectionClientId(CMS_Connection* connection, const char* clientId) {

    cms_status result = CMS_ERROR;

    if (connection != NULL && clientId != NULL) {

        try{
            connection->connection->setClientID(clientId);
            result = CMS_SUCCESS;
        }
        CMS_CATCH_CONNECTION_EXCEPTION( connection, result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getConnectionClientId(CMS_Connection* connection, char* clientId, int size) {

    cms_status result = CMS_ERROR;

    if (connection != NULL && connection->connection && clientId != NULL && size > 0) {

        try{
            std::string theClientId = connection->connection->getClientID();

            if(theClientId.size() < (std::size_t)size) {

                for(std::size_t i = 0; i < theClientId.size(); ++i) {
                    clientId[i] = theClientId.at(i);
                }

                clientId[theClientId.size()] = '\0';

                result = CMS_SUCCESS;
            }
        }
        CMS_CATCH_CONNECTION_EXCEPTION( connection, result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
char* cms_getErrorString(CMS_Connection* connection, char* buffer, int length) {

    char* result = NULL;

    if (buffer != NULL && length > 0 && connection->lastException != NULL) {

        cms::CMSException* ex = connection->lastException;

        std::string message = ex->getMessage();

        if(!message.empty()) {

            std::size_t pos = 0;
            for(; pos < message.size() && pos < (std::size_t)length - 1; ++pos) {
                buffer[pos] = message.at(pos);
            }

            buffer[pos] = '\0';
        } else {
            buffer[0] = '\0';
        }

    }

    return result;
}
