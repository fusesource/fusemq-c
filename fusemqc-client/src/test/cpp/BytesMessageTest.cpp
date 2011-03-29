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

#include "BytesMessageTest.h"

#include <CMS_BytesMessage.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
BytesMessageTest::BytesMessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
BytesMessageTest::~BytesMessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testCreateBytesMessage() {

	CMS_Message* message = NULL;
	int result = -1;

	CPPUNIT_ASSERT(createBytesMessage(session, &message, testString) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageType(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL((int)CMS_BYTES_MESSAGE, result);

	destroyMessage(txtMessage);

	CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageType(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL((int)CMS_BYTES_MESSAGE, result);

	destroyMessage(txtMessage);

	CPPUNIT_ASSERT(createBytesMessage(session, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(createBytesMessage(NULL, &message, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(createBytesMessage(NULL, NULL, NULL) == CMS_ERROR);
}
