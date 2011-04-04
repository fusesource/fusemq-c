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

#include <CMS_Message.h>

#include <Config.h>
#include <types/CMS_Types.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <memory>

////////////////////////////////////////////////////////////////////////////////
cms_status createMessage(CMS_Session* session, CMS_Message** message) {

    if(session == NULL || message == NULL) {
        return CMS_ERROR;
    }

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_Message> wrapper( new CMS_Message );

    try{

        wrapper->message = session->session->createMessage();
        wrapper->type = CMS_MESSAGE;
        *message = wrapper.release();

    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status createTextMessage(CMS_Session* session, CMS_Message** message, const char* body) {

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_Message> wrapper( new CMS_Message );

    try{

        if (session == NULL || message == NULL) {
            result = CMS_ERROR;
        } else {

            if (body == NULL) {
                wrapper->message = session->session->createTextMessage();
            } else {
                wrapper->message = session->session->createTextMessage(body);
            }

            wrapper->type = CMS_TEXT_MESSAGE;
            *message = wrapper.release();
        }

    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status createBytesMessage(CMS_Session* session, CMS_Message** message, unsigned char* body, int length) {

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_Message> wrapper( new CMS_Message );

    try{

        if (session == NULL || message == NULL) {
            result = CMS_ERROR;
        } else {

            if (body == NULL) {
                wrapper->message = session->session->createBytesMessage();
            } else {
                wrapper->message = session->session->createBytesMessage(body, length);
            }

            wrapper->type = CMS_BYTES_MESSAGE;
            *message = wrapper.release();
        }

    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status createMapMessage(CMS_Session* session, CMS_Message** message) {

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_Message> wrapper( new CMS_Message );

    try{

        if (session == NULL || message == NULL) {
            result = CMS_ERROR;
        } else {

            wrapper->message = session->session->createMapMessage();
            wrapper->type = CMS_MAP_MESSAGE;
            *message = wrapper.release();
        }

    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status createStreamMessage(CMS_Session* session, CMS_Message** message) {

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_Message> wrapper( new CMS_Message );

    try{

        if (session == NULL || message == NULL) {
            result = CMS_ERROR;
        } else {

            wrapper->message = session->session->createStreamMessage();
            wrapper->type = CMS_STREAM_MESSAAGE;
            *message = wrapper.release();
        }

    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status destroyMessage(CMS_Message* message) {

    cms_status result = CMS_SUCCESS;

    if(message != NULL) {

        try{
            delete message->message;
            delete message;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cloneMessage(CMS_Message* original, CMS_Message** clone) {

    cms_status result = CMS_SUCCESS;

    if(original != NULL && original->message != NULL) {

        std::auto_ptr<CMS_Message> wrapper( new CMS_Message );

        try{
            wrapper->message = original->message->clone();
            wrapper->type = original->type;
            *clone = wrapper.release();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageType(CMS_Message* message, int* type) {

    cms_status result = CMS_ERROR;

    if(message != NULL && type != NULL && message->message) {

        try{
            *type = message->type;
            result = CMS_SUCCESS;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status acknowledgeMessage(CMS_Message* message) {

    cms_status result = CMS_SUCCESS;

    if(message != NULL && message->message != NULL) {

        try{
            message->message->acknowledge();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status clearMessageBody(CMS_Message* message) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{
            message->message->clearBody();
            result = CMS_SUCCESS;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status clearMessageProperties(CMS_Message* message) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{
            message->message->clearProperties();
            result = CMS_SUCCESS;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getNumMessageProperties(CMS_Message* message, int* numProperties) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && numProperties != NULL) {

        try{
            *numProperties = (int) message->message->getPropertyNames().size();
            result = CMS_SUCCESS;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessagePropertyNames(CMS_Message* message, char*** names, int* size) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && names != NULL && size != NULL) {

        try{

            std::vector<std::string> keys = message->message->getPropertyNames();

            if (!keys.empty()) {

                *names = new char*[keys.size()];

                std::vector<std::string>::const_iterator iter = keys.begin();

                for (int index = 0; iter != keys.end(); ++index, ++iter) {
                    (*names)[index] = ::strdup(iter->c_str());
                }
            }

            *size = (int)keys.size();
            result = CMS_SUCCESS;

        } catch(...) {
            *size = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status messagePropertyExists(CMS_Message* message, const char* key, int* exists ) {

    cms_status result = CMS_ERROR;

    if(message != NULL && key != NULL && exists != NULL) {

        try{

            if(strlen(key) > 0) {
                *exists = (int) message->message->propertyExists(key);
            } else {
                *exists = 0;
            }

            result = CMS_SUCCESS;

        } catch(...) {
            *exists = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageBooleanProperty(CMS_Message* message, const char* key, int* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL && value != NULL) {

        try{

            if(strlen(key) > 0) {
                *value = (int) message->message->getBooleanProperty(key);
                result = CMS_SUCCESS;
            } else {
                *value = 0;
            }

        } catch(cms::MessageFormatException& ex) {
            *value = 0;
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            *value = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageByteProperty(CMS_Message* message, const char* key, unsigned char* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL && value != NULL) {

        try{

            if(strlen(key) > 0) {
                *value = message->message->getByteProperty(key);
                result = CMS_SUCCESS;
            } else {
                *value = 0;
            }

        } catch(cms::MessageFormatException& ex) {
            *value = 0;
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            *value = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageDoubleProperty(CMS_Message* message, const char* key, double* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL && value != NULL) {

        try{

            if(strlen(key) > 0) {
                *value = message->message->getDoubleProperty(key);
                result = CMS_SUCCESS;
            } else {
                *value = 0;
            }

        } catch(cms::MessageFormatException& ex) {
            *value = 0;
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            *value = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageFloatProperty(CMS_Message* message, const char* key, float* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL && value != NULL) {

        try{

            if(strlen(key) > 0) {
                *value = message->message->getFloatProperty(key);
                result = CMS_SUCCESS;
            } else {
                *value = 0;
            }

        } catch(cms::MessageFormatException& ex) {
            *value = 0;
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            *value = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageIntProperty(CMS_Message* message, const char* key, int* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL && value != NULL) {

        try{

            if(strlen(key) > 0) {
                *value = message->message->getIntProperty(key);
                result = CMS_SUCCESS;
            } else {
                *value = 0;
            }

        } catch(cms::MessageFormatException& ex) {
            *value = 0;
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            *value = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageLongProperty(CMS_Message* message, const char* key, long long* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL && value != NULL) {

        try{

            if(strlen(key) > 0) {
                *value = message->message->getLongProperty(key);
                result = CMS_SUCCESS;
            } else {
                *value = 0;
            }

        } catch(cms::MessageFormatException& ex) {
            *value = 0;
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            *value = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageShortProperty(CMS_Message* message, const char* key, short* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL && value != NULL) {

        try{

            if(strlen(key) > 0) {
                *value = message->message->getShortProperty(key);
                result = CMS_SUCCESS;
            } else {
                *value = 0;
            }

        } catch(cms::MessageFormatException& ex) {
            *value = 0;
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            *value = 0;
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getMessageStringProperty(CMS_Message* message, const char* key, char* value, int size) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL && value != NULL) {

        try{

            if(strlen(key) > 0) {
                std::string property = message->message->getStringProperty(key);

                if(!property.empty()) {

                    std::size_t pos = 0;
                    for(; pos < property.size() && pos < (std::size_t)size - 1; ++pos) {
                        value[pos] = property.at(pos);
                    }

                    value[pos] = '\0';
                } else {
                    value[0] = '\0';
                }

                result = CMS_SUCCESS;

            } else {
                *value = 0;
            }

        } catch(cms::MessageFormatException& ex) {
            value[0] = '\0';
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            value[0] = '\0';
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setMessageBooleanProperty(CMS_Message* message, const char* key, int value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL) {

        try{

            if(strlen(key) > 0) {
                message->message->setBooleanProperty(key, value > 0 ? true : false);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setMessageByteProperty(CMS_Message* message, const char* key, unsigned char value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL) {

        try{

            if(strlen(key) > 0) {
                message->message->setByteProperty(key, value);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setMessageDoubleProperty(CMS_Message* message, const char* key, double value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL) {

        try{

            if(strlen(key) > 0) {
                message->message->setDoubleProperty(key, value);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setMessageFloatProperty(CMS_Message* message, const char* key, float value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL) {

        try{

            if(strlen(key) > 0) {
                message->message->setFloatProperty(key, value);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setMessageIntProperty(CMS_Message* message, const char* key, int value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL) {

        try{

            if(strlen(key) > 0) {
                message->message->setIntProperty(key, value);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setMessageLongProperty(CMS_Message* message, const char* key, long long value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL) {

        try{

            if(strlen(key) > 0) {
                message->message->setLongProperty(key, value);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setMessageShortProperty(CMS_Message* message, const char* key, short value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL) {

        try{

            if(strlen(key) > 0) {
                message->message->setShortProperty(key, value);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setMessageStringProperty(CMS_Message* message, const char* key, const char* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && key != NULL) {

        try{

            if(strlen(key) > 0) {
                message->message->setStringProperty(key, value);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageCorrelationID(CMS_Message* message, char* correlationId, int size) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && correlationId != NULL && size > 0) {

        try{

            std::string id = message->message->getCMSCorrelationID();

            if(!id.empty()) {

                std::size_t pos = 0;
                for(; pos < id.size() && pos < (std::size_t)size - 1; ++pos) {
                    correlationId[pos] = id.at(pos);
                }

                correlationId[pos] = '\0';
            } else {
                correlationId[0] = '\0';
            }

            result = CMS_SUCCESS;

        } catch(cms::MessageFormatException& ex) {
            correlationId[0] = '\0';
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            correlationId[0] = '\0';
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageCorrelationID(CMS_Message* message, const char* correlationId) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && correlationId != NULL) {

        try{

            if(strlen(correlationId) > 0) {
                message->message->setCMSCorrelationID(correlationId);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageDeliveryMode(CMS_Message* message, int* mode) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && mode != NULL) {

        try{
            *mode = message->message->getCMSDeliveryMode();
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageDeliveryMode(CMS_Message* message, int mode) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{
            message->message->setCMSDeliveryMode(mode);
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageDestination(CMS_Message* message, CMS_Destination** destination) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && destination != NULL) {

        try{

            std::auto_ptr<CMS_Destination> wrapper( new CMS_Destination );

            const cms::Destination* dest = message->message->getCMSDestination();

            if (dest != NULL) {
                wrapper->destination = dest->clone();
                *destination = wrapper.release();
            } else {
                *destination = NULL;
            }

            result = CMS_SUCCESS;

        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageDestination(CMS_Message* message, CMS_Destination* destination) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{

            if (destination != NULL) {
                message->message->setCMSDestination(destination->destination);
            } else {
                message->message->setCMSDestination(NULL);
            }

            result = CMS_SUCCESS;

        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageExpiration(CMS_Message* message, long long* expiration) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && expiration != NULL) {

        try{
            *expiration = message->message->getCMSExpiration();
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageExpiration(CMS_Message* message, long long expiration) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{
            message->message->setCMSExpiration(expiration);
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageMessageID(CMS_Message* message, char* messageId, int size) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && messageId != NULL && size > 0) {

        try{

            std::string id = message->message->getCMSMessageID();

            if(!id.empty()) {

                std::size_t pos = 0;
                for(; pos < id.size() && pos < (std::size_t)size - 1; ++pos) {
                    messageId[pos] = id.at(pos);
                }

                messageId[pos] = '\0';
            } else {
                messageId[0] = '\0';
            }

            result = CMS_SUCCESS;

        } catch(cms::MessageFormatException& ex) {
            messageId[0] = '\0';
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            messageId[0] = '\0';
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageMessageID(CMS_Message* message, const char* messageId) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && messageId != NULL) {

        try{

            if(strlen(messageId) > 0) {
                message->message->setCMSMessageID(messageId);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessagePriority(CMS_Message* message, int* priority) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && priority != NULL) {

        try{
            *priority = message->message->getCMSPriority();
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessagePriority(CMS_Message* message, int priority) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{
            message->message->setCMSPriority(priority);
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageRedelivered(CMS_Message* message, int* redelivered) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && redelivered != NULL) {

        try{
            *redelivered = (int) message->message->getCMSRedelivered();
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageRedelivered(CMS_Message* message, int redelivered) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{
            message->message->setCMSRedelivered(redelivered == 0 ? false : true);
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageReplyTo(CMS_Message* message, CMS_Destination** destination) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{

            std::auto_ptr<CMS_Destination> wrapper( new CMS_Destination );

            const cms::Destination* dest = message->message->getCMSReplyTo();

            if (dest != NULL) {
                wrapper->destination = dest->clone();
                *destination = wrapper.release();
            } else {
                *destination = NULL;
            }

            result = CMS_SUCCESS;

        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageReplyTo(CMS_Message* message, CMS_Destination* destination) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{

            if (destination != NULL) {
                message->message->setCMSReplyTo(destination->destination);
            } else {
                message->message->setCMSReplyTo(NULL);
            }

            result = CMS_SUCCESS;

        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageTimestamp(CMS_Message* message, long long* timeStamp) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && timeStamp != NULL) {

        try{
            *timeStamp = message->message->getCMSTimestamp();
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageTimestamp(CMS_Message* message, long long timeStamp) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        try{
            message->message->setCMSTimestamp(timeStamp);
            result = CMS_SUCCESS;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status getCMSMessageType(CMS_Message* message, char* type, int size) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && type != NULL && size > 0) {

        try{

            std::string typeVal = message->message->getCMSType();

            if(!typeVal.empty()) {

                std::size_t pos = 0;
                for(; pos < typeVal.size() && pos < (std::size_t)size - 1; ++pos) {
                    type[pos] = typeVal.at(pos);
                }

                type[pos] = '\0';
            } else {
                type[0] = '\0';
            }

            result = CMS_SUCCESS;

        } catch(cms::MessageFormatException& ex) {
            type[0] = '\0';
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            type[0] = '\0';
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status setCMSMessageType(CMS_Message* message, const char* type) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && type != NULL) {

        try{

            if(strlen(type) > 0) {
                message->message->setCMSType(type);
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}
