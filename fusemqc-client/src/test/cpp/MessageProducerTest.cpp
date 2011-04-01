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

#include "MessageProducerTest.h"

#include <cms.h>
#include <CMS_Connection.h>
#include <CMS_Session.h>
#include <CMS_Destination.h>
#include <CMS_TextMessage.h>
#include <CMS_MessageProducer.h>
#include <CMS_MessageConsumer.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
MessageProducerTest::MessageProducerTest() {
}

////////////////////////////////////////////////////////////////////////////////
MessageProducerTest::~MessageProducerTest() {
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testCreateProducer() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;

    CPPUNIT_ASSERT(createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(destroyProducer(producer) == CMS_SUCCESS);

    destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetDeliveryMode() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int mode = -1;

    CPPUNIT_ASSERT(createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerDeliveryMode(producer, &mode) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_PERSISTENT, mode);

    CPPUNIT_ASSERT(setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerDeliveryMode(producer, &mode) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_NON_PERSISTENT, mode);

    CPPUNIT_ASSERT(destroyProducer(producer) == CMS_SUCCESS);

    destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetDisableTimestamps() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int disable = -1;

    CPPUNIT_ASSERT(createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerDisableMessageTimeStamp(producer, &disable) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, disable);

    CPPUNIT_ASSERT(setProducerDisableMessageTimeStamp(producer, 1) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerDisableMessageTimeStamp(producer, &disable) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, disable);

    CPPUNIT_ASSERT(destroyProducer(producer) == CMS_SUCCESS);

    destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetDisableMessageId() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int disable = -1;

    CPPUNIT_ASSERT(createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerDisableMessageID(producer, &disable) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, disable);

    CPPUNIT_ASSERT(setProducerDisableMessageID(producer, 1) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerDisableMessageID(producer, &disable) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, disable);

    CPPUNIT_ASSERT(destroyProducer(producer) == CMS_SUCCESS);

    destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetPriority() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int priority = -1;

    CPPUNIT_ASSERT(createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerPriority(producer, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(4, priority);

    CPPUNIT_ASSERT(setProducerPriority(producer, 1) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerPriority(producer, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, priority);

    CPPUNIT_ASSERT(destroyProducer(producer) == CMS_SUCCESS);

    destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetTimeToLive() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int ttl = -1;

    CPPUNIT_ASSERT(createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerTimeToLive(producer, &ttl) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, ttl);

    CPPUNIT_ASSERT(setProducerTimeToLive(producer, 1000) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getProducerTimeToLive(producer, &ttl) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1000, ttl);

    CPPUNIT_ASSERT(destroyProducer(producer) == CMS_SUCCESS);

    destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testSendWithDefaults() {

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

    producerSendWithDefaults(producer, message);

    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);

    int priority = -1;
    int deliveryMode = -1;
    long long expiration = -1;

    CPPUNIT_ASSERT(getCMSMessagePriority(received, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageDeliveryMode(received, &deliveryMode) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageExpiration(received, &expiration) == CMS_SUCCESS);

    CPPUNIT_ASSERT_EQUAL(4, priority);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_NON_PERSISTENT, deliveryMode);
    CPPUNIT_ASSERT_EQUAL(0LL, expiration);

    destroyMessage(received);
    destroyMessage(message);
    destroyConsumer(consumer);
    destroyProducer(producer);
    destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testSendToDestination() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;

    createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    createDefaultConsumer(session, destination, &consumer);

    CPPUNIT_ASSERT(createProducer(session, NULL, &producer) == CMS_SUCCESS);

    startConnection(connection);

    createTextMessage(session, &message, NULL);

    CPPUNIT_ASSERT(producerSendToDestination(producer, message, NULL, CMS_MSG_NON_PERSISTENT, 5, 5000) == CMS_ERROR);
    CPPUNIT_ASSERT(producerSendToDestination(producer, message, destination, CMS_MSG_NON_PERSISTENT, 5, 5000) == CMS_SUCCESS);

    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);

    int priority = -1;
    int deliveryMode = -1;
    long long expiration = -1;

    CPPUNIT_ASSERT(getCMSMessagePriority(received, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageDeliveryMode(received, &deliveryMode) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageExpiration(received, &expiration) == CMS_SUCCESS);

    CPPUNIT_ASSERT_EQUAL(5, priority);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_NON_PERSISTENT, deliveryMode);
    CPPUNIT_ASSERT(expiration > 0);

    destroyMessage(received);
    destroyMessage(message);
    destroyConsumer(consumer);
    destroyProducer(producer);
    destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testSend() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;

    createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    createDefaultConsumer(session, destination, &consumer);

    CPPUNIT_ASSERT(createProducer(session, destination, &producer) == CMS_SUCCESS);

    startConnection(connection);

    createTextMessage(session, &message, NULL);

    CPPUNIT_ASSERT(producerSend(producer, NULL, CMS_MSG_NON_PERSISTENT, 5, 5000) == CMS_ERROR);
    CPPUNIT_ASSERT(producerSend(producer, message, CMS_MSG_NON_PERSISTENT, 5, 5000) == CMS_SUCCESS);

    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);

    int priority = -1;
    int deliveryMode = -1;
    long long expiration = -1;

    CPPUNIT_ASSERT(getCMSMessagePriority(received, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageDeliveryMode(received, &deliveryMode) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageExpiration(received, &expiration) == CMS_SUCCESS);

    CPPUNIT_ASSERT_EQUAL(5, priority);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_NON_PERSISTENT, deliveryMode);
    CPPUNIT_ASSERT(expiration > 0);

    destroyMessage(received);
    destroyMessage(message);
    destroyConsumer(consumer);
    destroyProducer(producer);
    destroyDestination(destination);
}
