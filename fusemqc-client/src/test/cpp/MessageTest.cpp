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

#include "MessageTest.h"

#include <CMS_Message.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
MessageTest::MessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
MessageTest::~MessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCreateMessage() {

	CMS_Message* message = NULL;
	int result = 0;

	CPPUNIT_ASSERT(createMessage(NULL, &message) == CMS_ERROR);
	CPPUNIT_ASSERT(createMessage(session, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(createMessage(NULL, NULL) == CMS_ERROR);

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	int type = -1;
	CPPUNIT_ASSERT(getMessageType(message, &type) == CMS_SUCCESS);
	CPPUNIT_ASSERT(type == CMS_MESSAGE);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);
	result = -1;
	CPPUNIT_ASSERT(messagePropertyExists(message, "some-property", &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageBooleanProperties() {

	CMS_Message* message = NULL;
	int result = 0;

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);

	result = -1;
	CPPUNIT_ASSERT(setMessageBooleanProperty(message, "boolean", 0) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageBooleanProperty(message, "boolean", &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT(result == 0);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageBooleanProperty(message, "boolean", 1) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageBooleanProperty(message, "boolean", &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT(result == 1);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageBooleanProperty(NULL, "boolean", 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageBooleanProperty(NULL, NULL, 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageBooleanProperty(message, NULL, 0) == CMS_ERROR);

	CPPUNIT_ASSERT(getMessageBooleanProperty(message, "boolean", NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageBooleanProperty(message, NULL, &result) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageBooleanProperty(message, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageBooleanProperty(NULL, "boolean", &result) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageBooleanProperty(NULL, NULL, &result) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageBooleanProperty(NULL, NULL, NULL) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageByteProperties() {

	CMS_Message* message = NULL;
	int result = 0;
	unsigned char value = 0;

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);

	result = -1;
	CPPUNIT_ASSERT(setMessageByteProperty(message, "byte", 0) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageByteProperty(message, "byte", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 0);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageByteProperty(message, "byte", 127) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageByteProperty(message, "byte", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 127);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageByteProperty(NULL, "byte", 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageByteProperty(NULL, NULL, 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageByteProperty(message, NULL, 0) == CMS_ERROR);

	CPPUNIT_ASSERT(getMessageByteProperty(message, "byte", NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageByteProperty(message, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageByteProperty(message, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageByteProperty(NULL, "byte", &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageByteProperty(NULL, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageByteProperty(NULL, NULL, NULL) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageDoubleProperties() {

	CMS_Message* message = NULL;
	int result = 0;
	double value = 0;

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);

	result = -1;
	CPPUNIT_ASSERT(setMessageDoubleProperty(message, "double", 0) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageDoubleProperty(message, "double", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 0);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageDoubleProperty(message, "double", 127) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageDoubleProperty(message, "double", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 127);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageDoubleProperty(NULL, "double", 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageDoubleProperty(NULL, NULL, 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageDoubleProperty(message, NULL, 0) == CMS_ERROR);

	CPPUNIT_ASSERT(getMessageDoubleProperty(message, "double", NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageDoubleProperty(message, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageDoubleProperty(message, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageDoubleProperty(NULL, "double", &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageDoubleProperty(NULL, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageDoubleProperty(NULL, NULL, NULL) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageFloatProperties() {

	CMS_Message* message = NULL;
	int result = 0;
	float value = 0;

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);

	result = -1;
	CPPUNIT_ASSERT(setMessageFloatProperty(message, "float", 0) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageFloatProperty(message, "float", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 0);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageFloatProperty(message, "float", 127) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageFloatProperty(message, "float", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 127);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageFloatProperty(NULL, "float", 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageFloatProperty(NULL, NULL, 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageFloatProperty(message, NULL, 0) == CMS_ERROR);

	CPPUNIT_ASSERT(getMessageFloatProperty(message, "float", NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageFloatProperty(message, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageFloatProperty(message, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageFloatProperty(NULL, "float", &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageFloatProperty(NULL, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageFloatProperty(NULL, NULL, NULL) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageLongProperties() {

	CMS_Message* message = NULL;
	int result = 0;
	long long value = 0;

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);

	result = -1;
	CPPUNIT_ASSERT(setMessageLongProperty(message, "long", 0) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageLongProperty(message, "long", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 0);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageLongProperty(message, "long", 127) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageLongProperty(message, "long", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 127);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageLongProperty(NULL, "long", 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageLongProperty(NULL, NULL, 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageLongProperty(message, NULL, 0) == CMS_ERROR);

	CPPUNIT_ASSERT(getMessageLongProperty(message, "long", NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageLongProperty(message, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageLongProperty(message, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageLongProperty(NULL, "long", &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageLongProperty(NULL, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageLongProperty(NULL, NULL, NULL) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageIntProperties() {

	CMS_Message* message = NULL;
	int result = 0;
	int value = 0;

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);

	result = -1;
	CPPUNIT_ASSERT(setMessageIntProperty(message, "int", 0) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageIntProperty(message, "int", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 0);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageIntProperty(message, "int", 127) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageIntProperty(message, "int", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 127);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageIntProperty(NULL, "int", 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageIntProperty(NULL, NULL, 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageIntProperty(message, NULL, 0) == CMS_ERROR);

	CPPUNIT_ASSERT(getMessageIntProperty(message, "int", NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageIntProperty(message, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageIntProperty(message, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageIntProperty(NULL, "int", &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageIntProperty(NULL, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageIntProperty(NULL, NULL, NULL) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageShortProperties() {

	CMS_Message* message = NULL;
	int result = 0;
	short value = 0;

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);

	result = -1;
	CPPUNIT_ASSERT(setMessageShortProperty(message, "short", 0) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageShortProperty(message, "short", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 0);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageShortProperty(message, "short", 127) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageShortProperty(message, "short", &value) == CMS_SUCCESS);
	CPPUNIT_ASSERT(value == 127);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageShortProperty(NULL, "short", 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageShortProperty(NULL, NULL, 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageShortProperty(message, NULL, 0) == CMS_ERROR);

	CPPUNIT_ASSERT(getMessageShortProperty(message, "short", NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageShortProperty(message, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageShortProperty(message, NULL, NULL) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageShortProperty(NULL, "short", &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageShortProperty(NULL, NULL, &value) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageShortProperty(NULL, NULL, NULL) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageStringProperties() {

	CMS_Message* message = NULL;
	int result = 0;
	const char* inValue1 = "Test String 1";
	const char* inValue2 = "Test String 2";
	char* outValue = new char[256];

	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(0, result);

	result = -1;
	CPPUNIT_ASSERT(setMessageStringProperty(message, "string", inValue1) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageStringProperty(message, "string", outValue, 256) == CMS_SUCCESS);
	CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageStringProperty(message, "string", inValue2) == CMS_SUCCESS);
	CPPUNIT_ASSERT(getMessageStringProperty(message, "string", outValue, 256) == CMS_SUCCESS);
	CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));

	result = -1;
	CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
	CPPUNIT_ASSERT_EQUAL(1, result);

	CPPUNIT_ASSERT(setMessageStringProperty(NULL, "string", 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageStringProperty(NULL, NULL, 0) == CMS_ERROR);
	CPPUNIT_ASSERT(setMessageStringProperty(message, NULL, 0) == CMS_ERROR);

	CPPUNIT_ASSERT(getMessageStringProperty(message, "string", NULL, 255) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageStringProperty(message, NULL, outValue, 256) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageStringProperty(message, NULL, NULL, 255) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageStringProperty(NULL, "string", outValue, 256) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageStringProperty(NULL, NULL, outValue, 256) == CMS_ERROR);
	CPPUNIT_ASSERT(getMessageStringProperty(NULL, NULL, NULL, 256) == CMS_ERROR);
}

