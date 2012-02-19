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

#include <CMS_QueueBrowser.h>

#include <Config.h>
#include <private/CMS_Types.h>
#include <private/CMS_Utils.h>

#include <cms/Destination.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <memory>

////////////////////////////////////////////////////////////////////////////////
cms_status cms_createQueueBrowser(CMS_Session* session, CMS_Destination* destination, CMS_QueueBrowser** browser, const char* selector) {

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_QueueBrowser> wrapper(new CMS_QueueBrowser);

    try{

        if (session == NULL || session->session == NULL || destination == NULL || browser == NULL) {
            result = CMS_ERROR;
        } else {

        	if (destination->type != CMS_QUEUE) {
        		return CMS_INVALID_DESTINATION;
        	}

            std::string sel = selector == NULL ? "" : std::string(selector);

			wrapper->browser = session->session->createBrowser(
					dynamic_cast<cms::Queue*>(destination->destination), sel);

        	*browser = wrapper.release();
        }

    }
    CMS_CATCH_EXCEPTION( result )

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_browserHasMoreMessages(CMS_QueueBrowser* browser, int* hasMore) {

	cms_status result = CMS_ERROR;

    if (browser != NULL && browser->browser != NULL && hasMore != NULL) {
        try {
        	*hasMore = (int) browser->browser->getEnumeration()->hasMoreMessages();
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_browserGetNextMessages(CMS_QueueBrowser* browser, CMS_Message** message) {

    cms_status result = CMS_ERROR;

    if (browser != NULL && browser->browser != NULL && message != NULL) {

        try{

            std::auto_ptr<CMS_Message> wrapper( new CMS_Message );

            cms::Message* msg = browser->browser->getEnumeration()->nextMessage();

            if(msg != NULL) {
                wrapper->message = msg;

                if(dynamic_cast<cms::TextMessage*>(msg) != NULL) {
                   wrapper->type = CMS_TEXT_MESSAGE;
                } else if(dynamic_cast<cms::BytesMessage*>(msg) != NULL) {
                    wrapper->type = CMS_BYTES_MESSAGE;
                } else if(dynamic_cast<cms::MapMessage*>(msg) != NULL) {
                    wrapper->type = CMS_MAP_MESSAGE;
                } else if(dynamic_cast<cms::StreamMessage*>(msg) != NULL) {
                    wrapper->type = CMS_STREAM_MESSAAGE;
                } else {
                    wrapper->type = CMS_MESSAGE;
                }

                *message = wrapper.release();

                result = CMS_SUCCESS;

            } else {
                *message = NULL;
            }

        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getBrowserMessageSelector(CMS_QueueBrowser* browser, char* dest, int size) {

    cms_status result = CMS_ERROR;

    if (browser != NULL && browser->browser != NULL && dest != NULL && size > 0) {

        try{

            std::string selector = browser->browser->getMessageSelector();

            if (!selector.empty()) {

                std::size_t pos = 0;
                for(; pos < selector.size() && pos < size - (std::size_t) 1; ++pos) {
                    dest[pos] = selector.at(pos);
                }

                dest[pos] = '\0';
            } else {
                dest[0] = '\0';
            }

            result = CMS_SUCCESS;

        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_destroyQueueBrowser(CMS_QueueBrowser* browser) {

    cms_status result = CMS_SUCCESS;

    if (browser != NULL) {

        try{
            delete browser->browser;
            delete browser;
        }
        CMS_CATCH_EXCEPTION( result )
    }

    return result;
}
