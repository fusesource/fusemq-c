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
#include <CMS_Destination.h>
#include <CMS_BytesMessage.h>

#include <decaf/lang/Integer.h>

using namespace cms;
using namespace decaf;
using namespace decaf::lang;

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

    CPPUNIT_ASSERT(cms_createMessage(NULL, &message) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_createMessage(session, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_createMessage(NULL, NULL) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    int type = -1;
    CPPUNIT_ASSERT(cms_getMessageType(message, &type) == CMS_SUCCESS);
    CPPUNIT_ASSERT(type == CMS_MESSAGE);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);
    result = -1;
    CPPUNIT_ASSERT(cms_messagePropertyExists(message, "some-property", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testGetNumMessageProperties() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "1", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "2", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "3", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "4", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "5", 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(5, result);

    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getNumMessageProperties(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getNumMessageProperties(NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testGetMessagePropertyNames() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "1", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "2", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "3", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "4", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "5", 0) == CMS_SUCCESS);

    char** names = NULL;
    int size = 0;

    CPPUNIT_ASSERT(cms_getMessagePropertyNames(message, &names, &size) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(5, size);

    for(int i = 0; i < size; ++i) {
        CPPUNIT_ASSERT(std::string(Integer::toString(i+1)) == std::string(names[i]) );
        delete names[i];
    }

    delete names;

    CPPUNIT_ASSERT(cms_getMessagePropertyNames(NULL, &names, &size) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessagePropertyNames(message, NULL, &size) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessagePropertyNames(message, &names, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessagePropertyNames(NULL, &names, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessagePropertyNames(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessagePropertyNames(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessagePropertyExists() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "1", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "2", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "3", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "4", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "5", 0) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_messagePropertyExists(message, "2", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    result = -1;
    CPPUNIT_ASSERT(cms_messagePropertyExists(message, "8", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(cms_messagePropertyExists(NULL, "2", &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_messagePropertyExists(message, NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_messagePropertyExists(message, "2", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_messagePropertyExists(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_messagePropertyExists(NULL, "2", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_messagePropertyExists(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testClearMessageProperties() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "1", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "2", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "3", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "4", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "5", 0) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(5, result);

    CPPUNIT_ASSERT(cms_clearMessageProperties(message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(cms_clearMessageProperties(NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testClearMessageBody() {

    CMS_Message* message = NULL;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    int length = -1;

    const int count = 10;

    CPPUNIT_ASSERT(cms_createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    for( int i = 0; i < count; i++ ) {
        CPPUNIT_ASSERT(cms_writeLongToBytesMessage(message, 5LL) == CMS_SUCCESS);
    }

    CPPUNIT_ASSERT(cms_resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getBytesMessageBodyLength(message, &length) == CMS_SUCCESS);
    CPPUNIT_ASSERT(length == (count * 8));

    CPPUNIT_ASSERT(cms_clearMessageBody(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getBytesMessageBodyLength(message, &length) == CMS_SUCCESS);
    CPPUNIT_ASSERT(length == 0);

    CPPUNIT_ASSERT(cms_clearMessageBody(NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageBooleanProperties() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "boolean", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageBooleanProperty(message, "boolean", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 0);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, "boolean", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageBooleanProperty(message, "boolean", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 1);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(NULL, "boolean", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageBooleanProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getMessageBooleanProperty(message, "boolean", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageBooleanProperty(message, NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageBooleanProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageBooleanProperty(NULL, "boolean", &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageBooleanProperty(NULL, NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageBooleanProperty(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageByteProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    unsigned char value = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(cms_setMessageByteProperty(message, "byte", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageByteProperty(message, "byte", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageByteProperty(message, "byte", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageByteProperty(message, "byte", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageByteProperty(NULL, "byte", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageByteProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageByteProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getMessageByteProperty(message, "byte", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageByteProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageByteProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageByteProperty(NULL, "byte", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageByteProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageByteProperty(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageDoubleProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    double value = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(cms_setMessageDoubleProperty(message, "double", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageDoubleProperty(message, "double", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageDoubleProperty(message, "double", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageDoubleProperty(message, "double", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageDoubleProperty(NULL, "double", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageDoubleProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageDoubleProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getMessageDoubleProperty(message, "double", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageDoubleProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageDoubleProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageDoubleProperty(NULL, "double", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageDoubleProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageDoubleProperty(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageFloatProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    float value = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(cms_setMessageFloatProperty(message, "float", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageFloatProperty(message, "float", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageFloatProperty(message, "float", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageFloatProperty(message, "float", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageFloatProperty(NULL, "float", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageFloatProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageFloatProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getMessageFloatProperty(message, "float", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageFloatProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageFloatProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageFloatProperty(NULL, "float", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageFloatProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageFloatProperty(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageLongProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    long long value = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(cms_setMessageLongProperty(message, "long", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageLongProperty(message, "long", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageLongProperty(message, "long", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageLongProperty(message, "long", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageLongProperty(NULL, "long", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageLongProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageLongProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getMessageLongProperty(message, "long", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageLongProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageLongProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageLongProperty(NULL, "long", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageLongProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageLongProperty(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageIntProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    int value = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(cms_setMessageIntProperty(message, "int", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageIntProperty(message, "int", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageIntProperty(message, "int", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageIntProperty(message, "int", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageIntProperty(NULL, "int", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageIntProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageIntProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getMessageIntProperty(message, "int", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageIntProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageIntProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageIntProperty(NULL, "int", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageIntProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageIntProperty(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageShortProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    short value = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(cms_setMessageShortProperty(message, "short", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageShortProperty(message, "short", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageShortProperty(message, "short", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageShortProperty(message, "short", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageShortProperty(NULL, "short", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageShortProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageShortProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getMessageShortProperty(message, "short", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageShortProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageShortProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageShortProperty(NULL, "short", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageShortProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageShortProperty(NULL, NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageStringProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    const char* inValue1 = "Test String 1";
    const char* inValue2 = "Test String 2";
    char* outValue = new char[256];

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(cms_setMessageStringProperty(message, "string", inValue1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageStringProperty(message, "string", outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageStringProperty(message, "string", inValue2) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getMessageStringProperty(message, "string", outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));

    result = -1;
    CPPUNIT_ASSERT(cms_getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(cms_setMessageStringProperty(NULL, "string", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageStringProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setMessageStringProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getMessageStringProperty(message, "string", NULL, 255) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageStringProperty(message, NULL, outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageStringProperty(message, NULL, NULL, 255) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageStringProperty(NULL, "string", outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageStringProperty(NULL, NULL, outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getMessageStringProperty(NULL, NULL, NULL, 256) == CMS_ERROR);

    cms_destroyMessage(message);
    delete [] outValue;
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageCorrelationID() {

    CMS_Message* message = NULL;
    const char* inValue1 = "Test String 1";
    const char* inValue2 = "Test String 2";
    char* outValue = new char[256];

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_setCMSMessageCorrelationID(message, inValue1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageCorrelationID(message, outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));

    CPPUNIT_ASSERT(cms_setCMSMessageCorrelationID(message, inValue2) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageCorrelationID(message, outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));

    CPPUNIT_ASSERT(cms_setCMSMessageCorrelationID(NULL, inValue1) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setCMSMessageCorrelationID(NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setCMSMessageCorrelationID(message, NULL) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getCMSMessageCorrelationID(message, NULL, 255) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageCorrelationID(message, outValue, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageCorrelationID(message, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageCorrelationID(NULL, outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageCorrelationID(NULL, outValue, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageCorrelationID(NULL, NULL, 256) == CMS_ERROR);

    cms_destroyMessage(message);
    delete [] outValue;
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageDeliveryMode() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_setCMSMessageDeliveryMode(message, CMS_MSG_PERSISTENT) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageDeliveryMode(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == CMS_MSG_PERSISTENT);

    CPPUNIT_ASSERT(cms_setCMSMessageDeliveryMode(message, CMS_MSG_NON_PERSISTENT) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageDeliveryMode(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == CMS_MSG_NON_PERSISTENT);

    CPPUNIT_ASSERT(cms_setCMSMessageDeliveryMode(NULL, 2) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getCMSMessageDeliveryMode(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageDeliveryMode(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageDeliveryMode(NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageDestination() {

    CMS_Message* message = NULL;
    CMS_Destination* destination = 0;
    CMS_Destination* result = 0;
    int equals = 0;

    CPPUNIT_ASSERT(cms_createDestination(session, CMS_TEMPORARY_TOPIC, NULL, &destination) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_setCMSMessageDestination(message, destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageDestination(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_compareDestinations(result, destination, &equals) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, equals);

    CPPUNIT_ASSERT(cms_setCMSMessageDestination(NULL, destination) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getCMSMessageDestination(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageDestination(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageDestination(NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
    cms_destroyDestination(destination);
    cms_destroyDestination(result);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageExpiration() {

    CMS_Message* message = NULL;
    long long result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_setCMSMessageExpiration(message, 55) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageExpiration(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 55);

    CPPUNIT_ASSERT(cms_setCMSMessageExpiration(message, 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageExpiration(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 127);

    CPPUNIT_ASSERT(cms_setCMSMessageExpiration(NULL, 2) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getCMSMessageExpiration(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageExpiration(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageExpiration(NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageMessageID() {

    // TODO - Not working in AMQ-CPP Yet
//	CMS_Message* message = NULL;
//	const char* inValue1 = "Test String 1";
//	const char* inValue2 = "Test String 2";
//	char* outValue = new char[256];
//
//	CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);
//
//	CPPUNIT_ASSERT(cms_setCMSMessageMessageID(message, inValue1) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(cms_getCMSMessageMessageID(message, outValue, 256) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));
//
//	CPPUNIT_ASSERT(cms_setCMSMessageMessageID(message, inValue2) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(cms_getCMSMessageMessageID(message, outValue, 256) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));
//
//	CPPUNIT_ASSERT(cms_setCMSMessageMessageID(NULL, inValue1) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_setCMSMessageMessageID(NULL, NULL) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_setCMSMessageMessageID(message, NULL) == CMS_ERROR);
//
//	CPPUNIT_ASSERT(cms_getCMSMessageMessageID(message, NULL, 255) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_getCMSMessageMessageID(message, outValue, 0) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_getCMSMessageMessageID(message, NULL, 0) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_getCMSMessageMessageID(NULL, outValue, 256) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_getCMSMessageMessageID(NULL, outValue, 0) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_getCMSMessageMessageID(NULL, NULL, 256) == CMS_ERROR);
//
//	cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessagePriority() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_setCMSMessagePriority(message, 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessagePriority(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 1);

    CPPUNIT_ASSERT(cms_setCMSMessagePriority(message, 4) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessagePriority(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 4);

    CPPUNIT_ASSERT(cms_setCMSMessagePriority(NULL, 2) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getCMSMessagePriority(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessagePriority(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessagePriority(NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageRedelivered() {

// TODO - Not working in AMQ-CPP Yet
//	CMS_Message* message = NULL;
//	int result = 0;
//
//	CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);
//
//	CPPUNIT_ASSERT(cms_setCMSMessageRedelivered(message, 1) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(cms_getCMSMessageRedelivered(message, &result) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(result == 1);
//
//	CPPUNIT_ASSERT(cms_setCMSMessageRedelivered(message, 0) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(cms_getCMSMessageRedelivered(message, &result) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(result == 0);
//
//	CPPUNIT_ASSERT(cms_setCMSMessageRedelivered(NULL, 2) == CMS_ERROR);
//
//	CPPUNIT_ASSERT(cms_getCMSMessageRedelivered(message, NULL) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_getCMSMessageRedelivered(NULL, &result) == CMS_ERROR);
//	CPPUNIT_ASSERT(cms_getCMSMessageRedelivered(NULL, NULL) == CMS_ERROR);
//
//	cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageReplyTo() {

}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageTimestamp() {

    CMS_Message* message = NULL;
    long long result = 0;

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_setCMSMessageTimestamp(message, 55) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageTimestamp(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 55);

    CPPUNIT_ASSERT(cms_setCMSMessageTimestamp(message, 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageTimestamp(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 127);

    CPPUNIT_ASSERT(cms_setCMSMessageTimestamp(NULL, 2) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getCMSMessageTimestamp(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageTimestamp(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageTimestamp(NULL, NULL) == CMS_ERROR);

    cms_destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageType() {

    CMS_Message* message = NULL;
    const char* inValue1 = "Test String 1";
    const char* inValue2 = "Test String 2";
    char* outValue = new char[256];

    CPPUNIT_ASSERT(cms_createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_setCMSMessageType(message, inValue1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageType(message, outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));

    CPPUNIT_ASSERT(cms_setCMSMessageType(message, inValue2) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageType(message, outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));

    CPPUNIT_ASSERT(cms_setCMSMessageType(NULL, inValue1) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setCMSMessageType(NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_setCMSMessageType(message, NULL) == CMS_ERROR);

    CPPUNIT_ASSERT(cms_getCMSMessageType(message, NULL, 255) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageType(message, outValue, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageType(message, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageType(NULL, outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageType(NULL, outValue, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_getCMSMessageType(NULL, NULL, 256) == CMS_ERROR);

    cms_destroyMessage(message);
    delete [] outValue;
}
