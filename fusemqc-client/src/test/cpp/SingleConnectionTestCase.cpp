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

#include "SingleConnectionTestCase.h"

#include <CMS_MessageConsumer.h>
#include <CMS_MessageProducer.h>
#include <CMS_Destination.h>
#include <CMS_Session.h>
#include <CMS_Connection.h>
#include <CMS_ConnectionFactory.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
SingleConnectionTestCase::SingleConnectionTestCase() :
    CMSTestCase(), factory(NULL), connection(NULL), session(NULL) {
}

////////////////////////////////////////////////////////////////////////////////
SingleConnectionTestCase::~SingleConnectionTestCase() {
}

////////////////////////////////////////////////////////////////////////////////
void SingleConnectionTestCase::setUp() {

    const std::string uri = std::string("tcp://") + CMSTestCase::DEFAULT_BROKER_HOST;

    CPPUNIT_ASSERT(cms_createConnectionFactory(&factory, uri.c_str(), NULL, NULL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConnection(factory, &connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultSession(connection, &session) == CMS_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
void SingleConnectionTestCase::tearDown() {

    CPPUNIT_ASSERT(cms_destroySession(session) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_stopConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_closeConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnection(connection) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_destroyConnectionFactory(factory) == CMS_SUCCESS);
}
