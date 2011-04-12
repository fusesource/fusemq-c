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

#include <cms.h>

#ifndef _CMS_CONNECTION_WRAPPER_H_
#define _CMS_CONNECTION_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new Connection from the given ConnectionFactory instance using the defaults
 * that are configured in the given Connection Factory.
 *
 * @param factory
 *      The ConnectionFactory to use to create a new Connection.
 * @param connection
 *      The address of the location to store the new Connection instance.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_createDefaultConnection(CMS_ConnectionFactory* factory, CMS_Connection** connection);

/**
 * Creates a new Connection from the given ConnectionFactory instance.  The caller can specify
 * the user name, password and client Id that will be used in the newly created Connection.
 *
 * @param factory
 *      The ConnectionFactory to use to create a new Connection.
 * @param connection
 *      The address of the location to store the new Connection instance.
 * @param username
 *      The user name that will be sent to the Broker for Authentication (can be NULL).
 * @param password
 *      The password that will be sent to the Broker for Authentication (can be NULL).
 * @param clientId
 *      The clientId that will be assigned to the newly allocated Connection (can be NULL).
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_createConnection(CMS_ConnectionFactory* factory,
                                CMS_Connection** connection,
                                const char* username,
                                const char* password,
                                const char* clientId);

/**
 * Destroys the given Connection instance, all Connection Resources should have been
 * deallocated at this point.
 *
 * @param connection
 *      The Connection that is to be destroyed.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_destroyConnection(CMS_Connection* connection);

/**
 * Starts the Connection instance.  Until a Connection is started any Message Consumers
 * created by Sessions linked to the Connection will not be able to receive Messages.
 *
 * @param connection
 *      The Connection that is to be started.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_startConnection(CMS_Connection* connection);

/**
 * Stops the Connection instance.  Until a Connection is started any Message Consumers
 * created by Sessions linked to the Connection will not be able to receive Messages.
 * By stopping the connection you stop message delivery to all currently active consumers.
 *
 * @param connection
 *      The Connection that is to be stopped.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_stopConnection(CMS_Connection* connection);

/**
 * Closes the Connection instance.  Once closed a Connection cannot be restarted.  All the
 * resources allocated from this connection will be closed as well, they must still be
 * destroyed by the client.
 *
 * @param connection
 *      The Connection that is to be closed.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_closeConnection(CMS_Connection* connection);

/**
 * Sets the Client Id for the given Connection instance.  The client Id must be
 * set before a call to start the Connection or creation of any Sessions by the
 * specified connection otherwise an error status is returned.
 *
 * @param connection
 *      The Connection whose client id is to be set.
 * @param clientId
 *      The new client Id to assign to the connection.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_setConnectionClientId(CMS_Connection* connection, const char* clientId);

/**
 * Gets the Client Id for the given Connection instance.  The caller passes an array that
 * the client id is copied into, if the array is not large enough to accommodate the client
 * Id then an error status is returned.
 *
 * @param connection
 *      The Connection whose client id is to be set.
 * @param clientId
 *      The new client Id to assign to the connection.
 * @param size
 *      The size of the character array that is to receive the client Id.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_getConnectionClientId(CMS_Connection* connection, char* clientId, int size);

/**
 * Returns a human readable error message that describes the last error that was encounted.
 * The caller provides a buffer for the error string and the client will fill the buffer up
 * to length bytes.  If there is no current error for this connection then method returns
 * NULL otherwise the filled buffer is returned.
 *
 * @param connection
 * 		The connection whose error being probed.
 * @param buffer
 * 		Pointer to a string buffer to write the error string.
 * @param length
 * 		the length in bytes of the provided buffer.
 *
 * @returns the error string or NULL if the connection has no associated error currently.
 */
char* cms_getErrorString(CMS_Connection* connection, char* buffer, int length);

#ifdef __cplusplus
}
#endif

#endif /* _CMS_CONNECTION_WRAPPER_H_ */
