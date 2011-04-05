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

#ifndef _CMS_MESSAGECONSUMER_WRAPPER_H_
#define _CMS_MESSAGECONSUMER_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Given a Session instance, create a new Consumer with the default settings.
 *
 * @param session
 *      The Session that is to be used to create the new Consumer.
 * @param destination
 *      The Destination that this consumer will subscribe to.
 * @param consumer
 *      The memory location where the newly allocated Consumer instance is to be stored.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_createDefaultConsumer(CMS_Session* session, CMS_Destination* destination, CMS_MessageConsumer** consumer);

/**
 * Given a Session instance, create a new Consumer with the specified Consumer
 * ack mode.
 *
 * @param session
 *      The Session that is to be used to create the new Consumer.
 * @param destination
 *      The Destination that this consumer will subscribe to.
 * @param consumer
 *      The memory location where the newly allocated Consumer instance is to be stored.
 * @param selector
 *      The selector used to filter Messages on this Consumer, can be NULL.
 * @param noLocal
 *      Boolean indicating whether locally produced Messages are delivered to this Consumer.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_createConsumer(CMS_Session* session,
                                CMS_Destination* destination,
                                CMS_MessageConsumer** consumer,
                                const char* selector,
                                int noLocal);

/**
 * Given a Session instance, create a new Consumer with the specified Consumer
 * ack mode.
 *
 * @param session
 *      The Session that is to be used to create the new Consumer.
 * @param destination
 *      The Destination that this consumer will subscribe to.
 * @param consumer
 *      The memory location where the newly allocated Consumer instance is to be stored.
 * @param subscriptionName
 *      The name to assign the durable subscription.
 * @param selector
 *      The selector used to filter Messages on this Consumer, can be NULL.
 * @param noLocal
 *      Boolean indicating whether locally produced Messages are delivered to this Consumer.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_createDurableConsumer(CMS_Session* session,
                                      CMS_Destination* destination,
                                      CMS_MessageConsumer** consumer,
                                      const char* subscriptionName,
                                      const char* selector,
                                      int noLocal);

/**
 * Waits for a Message to become available and stores it in the Location passed to this
 * method.  The client will block indefinitely waiting for a Message, to interrupt the
 * client call another thread must call the closeConsumer method.
 *
 * @param consumer
 *      The MessageConsumer that will be used to receive the Message.
 * @param message
 *      The Memory location where a newly received message is to be stored.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_consumerReceive(CMS_MessageConsumer* consumer, CMS_Message** message);

/**
 * Waits for a Message to become available and stores it in the Location passed to this
 * method.  The client will block until the timeout elapses waiting for a Message, to interrupt
 * the client call another thread must call the closeConsumer method.
 *
 * @param consumer
 *      The MessageConsumer that will be used to receive the Message.
 * @param message
 *      The Memory location where a newly received message is to be stored.
 * @param timeout
 *      The time in milliseconds to wait for a Message to arrive.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_consumerReceiveWithTimeout(CMS_MessageConsumer* consumer, CMS_Message** message, int timeout);

/**
 * Checks for a Message that's available and stores it in the Location passed to this
 * method.  If a message is not immediately available then this method returns and the
 * message store location is set to null.
 *
 * @param consumer
 *      The MessageConsumer that will be used to receive the Message.
 * @param message
 *      The Memory location where a newly received message is to be stored.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_consumerReceiveNoWait(CMS_MessageConsumer* consumer, CMS_Message** message);

/**
 * Closes the MessageConsumer, interrupting any currently blocked receive calls.
 *
 * @param consumer
 *      The Consumer that is to be closed.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_closeConsumer(CMS_MessageConsumer* consumer);

/**
 * Gets the Message Selector that is assigned to the given MessageConsumer if there is one.
 * The method will copy the Selector into the provided char array.  The copied string is
 * always null terminate so if the selector is larger than the provided size the number
 * of chars copied will be size - 1.
 *
 * @param consumer
 *      The Consumer whose selector string is to be retrieved.
 * @param dest
 *      The character array to copy the selector string to.
 * @param size
 *      The size of the provided character array.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_getConsumerMessageSelector(CMS_MessageConsumer* consumer, char* dest, int size);

/**
 * Destroys the given Consumer instance.
 *
 * @param consumer
 *      The Consumer that is to be destroyed.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_destroyConsumer(CMS_MessageConsumer* consumer);

#ifdef __cplusplus
}
#endif

#endif /* _CMS_MESSAGECONSUMER_WRAPPER_H_ */
