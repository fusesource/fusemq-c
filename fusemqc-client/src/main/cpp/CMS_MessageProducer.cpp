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

#include <CMS_MessageProducer.h>

#include <Config.h>
#include <types/CMS_Types.h>

#include <cms/Destination.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <memory>

////////////////////////////////////////////////////////////////////////////////
cms_status cms_createProducer(CMS_Session* session, CMS_Destination* destination, CMS_MessageProducer** producer) {

    cms_status result = CMS_SUCCESS;
    std::auto_ptr<CMS_MessageProducer> wrapper( new CMS_MessageProducer );

    try{

        if (session == NULL) {
            result = CMS_ERROR;
        } else {
            if( destination != NULL && destination->destination != NULL ) {
                wrapper->producer = session->session->createProducer(destination->destination);
            } else {
                wrapper->producer = session->session->createProducer(NULL);
            }

            *producer = wrapper.release();
        }

    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_producerSend(CMS_MessageProducer* producer, CMS_Message* message,
                            int deliveryMode, int priority, int timeToLive) {

    cms_status result = CMS_SUCCESS;

    try{

        if (producer == NULL || producer->producer == NULL || message == NULL) {
            result = CMS_ERROR;
        } else {
            producer->producer->send(message->message, deliveryMode, priority, timeToLive);
        }

    } catch(cms::CMSException& es) {
        result = CMS_ERROR;
    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_producerSendToDestination(CMS_MessageProducer* producer, CMS_Message* message, CMS_Destination* destination,
                                          int deliveryMode, int priority, int timeToLive) {

    cms_status result = CMS_SUCCESS;

    try{

        if (producer == NULL || producer->producer == NULL || message == NULL || destination == NULL) {
            result = CMS_ERROR;
        } else {
            cms::Destination* dest = destination->destination == NULL ? NULL : destination->destination;
            producer->producer->send(dest, message->message, deliveryMode, priority, timeToLive);
        }

    } catch(cms::CMSException& es) {
        result = CMS_ERROR;
    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_producerSendWithDefaults(CMS_MessageProducer* producer, CMS_Message* message) {

    cms_status result = CMS_SUCCESS;

    try{

        if (producer == NULL || message == NULL) {
            result = CMS_ERROR;
        } else {
            producer->producer->send(message->message);
        }

    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_producerSendWithTimeOut(CMS_MessageProducer* producer, CMS_Message* message, long long timeOut) {

    cms_status result = CMS_SUCCESS;

    try{

        if (producer == NULL || message == NULL) {
            result = CMS_ERROR;
        } else {
            producer->producer->send(message->message, producer->producer->getDeliveryMode(), producer->producer->getPriority(), timeOut);
        }

    } catch(...) {
        result = CMS_ERROR;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_closeProducer(CMS_MessageProducer* producer) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL) {

        try{
            producer->producer->close();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_setProducerDeliveryMode(CMS_MessageProducer* producer, int mode) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL) {

        try{
            producer->producer->setDeliveryMode(mode);
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getProducerDeliveryMode(CMS_MessageProducer* producer, int* mode) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL && mode != NULL) {

        try{
            *mode = producer->producer->getDeliveryMode();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_setProducerDisableMessageID(CMS_MessageProducer* producer, int enabled) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL) {

        try{
            producer->producer->setDisableMessageID(enabled > 0);
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getProducerDisableMessageID(CMS_MessageProducer* producer, int* enabled) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL && enabled != NULL) {

        try{
            *enabled = producer->producer->getDisableMessageID();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_setProducerDisableMessageTimeStamp(CMS_MessageProducer* producer, int enabled) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL) {

        try{
            producer->producer->setDisableMessageTimeStamp(enabled > 0);
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getProducerDisableMessageTimeStamp(CMS_MessageProducer* producer, int* enabled) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL && enabled != NULL) {

        try{
            *enabled = producer->producer->getDisableMessageTimeStamp();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_setProducerPriority(CMS_MessageProducer* producer, int priority) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL) {

        try{
            producer->producer->setPriority(priority);
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getProducerPriority(CMS_MessageProducer* producer, int* priority) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL && priority != NULL) {

        try{
            *priority = producer->producer->getPriority();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_setProducerTimeToLive(CMS_MessageProducer* producer, int timeToLive) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL) {

        try{
            producer->producer->setTimeToLive(timeToLive);
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getProducerTimeToLive(CMS_MessageProducer* producer, int* timeToLive) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL && timeToLive != NULL) {

        try{
            *timeToLive = producer->producer->getTimeToLive();
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_destroyProducer(CMS_MessageProducer* producer) {

    cms_status result = CMS_SUCCESS;

    if(producer != NULL) {

        try{
            delete producer->producer;
            delete producer;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}
