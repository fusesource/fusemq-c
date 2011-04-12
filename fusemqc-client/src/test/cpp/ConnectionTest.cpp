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

#include "ConnectionTest.h"

#include <cms.h>
#include <CMS_Session.h>
#include <CMS_Connection.h>
#include <CMS_ConnectionFactory.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
ConnectionTest::ConnectionTest() {
}

////////////////////////////////////////////////////////////////////////////////
ConnectionTest::~ConnectionTest() {
}

////////////////////////////////////////////////////////////////////////////////
void ConnectionTest::testConnectToNullHost() {

    CMS_ConnectionFactory* factory = NULL;

    // This will create a factory with the default Factory Broker Uri.
    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, NULL, NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void ConnectionTest::testConnectToValidHost() {

    const std::string uri = std::string("tcp://") + CMSTestCase::DEFAULT_BROKER_HOST;

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_startConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_stopConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_closeConnection(connection) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void ConnectionTest::testConnectToInvalidHost() {

    const std::string uri = std::string("tcp://unknownhost:66666");

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void ConnectionTest::testCreateSessionFromConnection() {

    const std::string uri = std::string("tcp://") + CMSTestCase::DEFAULT_BROKER_HOST;

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;
    CMS_Session* session = NULL;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createSession(connection, &session, CMS_AUTO_ACKNOWLEDGE) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createSession(connection, &session, CMS_DUPS_OK_ACKNOWLEDGE) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createSession(connection, &session, CMS_CLIENT_ACKNOWLEDGE) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createSession(connection, &session, CMS_SESSION_TRANSACTED) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createSession(connection, &session, CMS_INDIVIDUAL_ACKNOWLEDGE) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void ConnectionTest::testGetErrorString() {

    const int length = 256;
    char buffer[256] = {};

    const std::string uri = std::string("tcp://") + CMSTestCase::DEFAULT_BROKER_HOST;

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_SUCCESS);

    CPPUNIT_ASSERT_EQUAL((char*)NULL, cms_getErrorString(connection, buffer, length));

    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
}
