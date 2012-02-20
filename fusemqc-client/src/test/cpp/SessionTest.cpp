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

#include "SessionTest.h"

#include <cms.h>
#include <CMS_QueueBrowser.h>
#include <CMS_MessageConsumer.h>
#include <CMS_MessageProducer.h>
#include <CMS_Destination.h>
#include <CMS_Session.h>
#include <CMS_Connection.h>
#include <CMS_ConnectionFactory.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
SessionTest::SessionTest() {
}

////////////////////////////////////////////////////////////////////////////////
SessionTest::~SessionTest() {
}

////////////////////////////////////////////////////////////////////////////////
void SessionTest::testCreateDestination() {

    const std::string uri = std::string("tcp://") + CMSTestCase::DEFAULT_BROKER_HOST;

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;
    CMS_Session* session = NULL;
    CMS_Destination* destination = NULL;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultSession(connection, &session) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createDestination(session, CMS_TOPIC, "cms.test.Destination", &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyDestination(destination) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void SessionTest::testCreateProducer() {

    const std::string uri = std::string("tcp://") + CMSTestCase::DEFAULT_BROKER_HOST;

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;
    CMS_Session* session = NULL;
    CMS_MessageProducer* producer = NULL;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultSession(connection, &session) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createProducer(session, NULL, &producer) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyProducer(producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void SessionTest::testCreateConsumer() {

    const std::string uri = std::string("tcp://") + CMSTestCase::DEFAULT_BROKER_HOST;

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;
    CMS_Session* session = NULL;
    CMS_Destination* destination = NULL;
    CMS_MessageConsumer* consumer = NULL;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultSession(connection, &session) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDestination(session, CMS_TOPIC, "cms.test.Destination", &destination) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createConsumer(session, destination, &consumer, NULL, false) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConsumer(consumer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_destroyDestination(destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void SessionTest::testCreateQueueBrowser() {

    const std::string uri = std::string("tcp://") + CMSTestCase::DEFAULT_BROKER_HOST;

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;
    CMS_Session* session = NULL;
    CMS_Destination* destination = NULL;
    CMS_QueueBrowser* browser = NULL;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultSession(connection, &session) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDestination(session, CMS_QUEUE, "cms.test.Destination.Queue", &destination) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createQueueBrowser(session, destination, &browser, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyQueueBrowser(browser) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_destroyDestination(destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
}
