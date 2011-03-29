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

#include "TextMessageTest.h"

#include <CMS_TextMessage.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
TextMessageTest::TextMessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
TextMessageTest::~TextMessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
void TextMessageTest::testCreateTextMessage() {

	CMS_Message* txtMessage = NULL;
	const char* testString = "This is a Text Message";
	int result = -1;

	CPPUNIT_ASSERT(createTextMessage(session, &txtMessage, testString) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageType(txtMessage, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL((int)CMS_TEXT_MESSAGE, result);

	destroyMessage(txtMessage);

	CPPUNIT_ASSERT(createTextMessage(session, &txtMessage, NULL) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageType(txtMessage, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL((int)CMS_TEXT_MESSAGE, result);

	destroyMessage(txtMessage);

	CPPUNIT_ASSERT(createTextMessage(session, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(createTextMessage(NULL, &txtMessage, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(createTextMessage(NULL, NULL, NULL) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void TextMessageTest::testGetMessageText() {

	CMS_Message* txtMessage = NULL;
	const char* testString = "This is a Text Message";
	char* buffer = new char[256];
	int result = -1;

	CPPUNIT_ASSERT(createTextMessage(session, &txtMessage, testString) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageType(txtMessage, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL((int)CMS_TEXT_MESSAGE, result);

	CPPUNIT_ASSERT(getMessageText(txtMessage, buffer, 256) == CMS_SUCCESS);
	CPPUNIT_ASSERT(std::string(testString) == std::string(buffer));

	CPPUNIT_ASSERT(getMessageText(txtMessage, NULL, 256) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageText(NULL, NULL, 256) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageText(NULL, buffer, 256) == CMS_ERROR);

	destroyMessage(txtMessage);
	delete [] buffer;
}

////////////////////////////////////////////////////////////////////////////////
void TextMessageTest::testSetMessageText() {

	CMS_Message* txtMessage = NULL;
	const char* testString = "This is a Text Message";
	char* buffer = new char[256];
	int result = -1;

	CPPUNIT_ASSERT(createTextMessage(session, &txtMessage, NULL) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageType(txtMessage, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL((int)CMS_TEXT_MESSAGE, result);

	CPPUNIT_ASSERT(setMessageText(txtMessage, testString) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageText(txtMessage, buffer, 256) == CMS_SUCCESS);
	CPPUNIT_ASSERT(std::string(testString) == std::string(buffer));

	CPPUNIT_ASSERT(setMessageText(txtMessage, "") == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageText(txtMessage, buffer, 256) == CMS_SUCCESS);
	CPPUNIT_ASSERT(std::string("") == std::string(buffer));

	CPPUNIT_ASSERT(setMessageText(txtMessage, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageText(NULL, testString) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageText(NULL, NULL) == CMS_ERROR);

	destroyMessage(txtMessage);
	delete [] buffer;
}
