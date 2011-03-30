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

#include "MessageConsumerTest.h"

#include <cms.h>
#include <CMS_Connection.h>
#include <CMS_Destination.h>
#include <CMS_TextMessage.h>
#include <CMS_MessageProducer.h>
#include <CMS_MessageConsumer.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
MessageConsumerTest::MessageConsumerTest() {
}

////////////////////////////////////////////////////////////////////////////////
MessageConsumerTest::~MessageConsumerTest() {
}

////////////////////////////////////////////////////////////////////////////////
void MessageConsumerTest::testCreateConsumer() {

    CMS_Destination* destination = NULL;
    CMS_MessageConsumer* consumer = NULL;

    CPPUNIT_ASSERT(createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(createDefaultConsumer(session, destination, &consumer) == CMS_SUCCESS);

    char* selector = new char[256];
    CPPUNIT_ASSERT(getConsumerMessageSelector(consumer, selector, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string("") == std::string(selector));
    delete [] selector;

    CPPUNIT_ASSERT(destroyConsumer(consumer) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void MessageConsumerTest::testAutoAckConsumerReceive() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;

    createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    createDefaultConsumer(session, destination, &consumer);
    createProducer(session, destination, &producer);
    setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT);

    startConnection(connection);

    createTextMessage(session, &message, NULL);

    for( unsigned int i = 0; i < 256; ++i ) {
        producerSendWithDefaults(producer, message);
    }

    for( unsigned int i = 0; i < 256; ++i ) {
        CMS_Message* received = NULL;
        CPPUNIT_ASSERT(consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);
        destroyMessage(received);
    }

    destroyConsumer(consumer);
    destroyProducer(producer);
    destroyDestination(destination);
}
