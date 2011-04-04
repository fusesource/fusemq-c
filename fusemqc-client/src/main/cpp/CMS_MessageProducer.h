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

#ifndef _CMS_MESSAGEPRODUCER_WRAPPER_H_
#define _CMS_MESSAGEPRODUCER_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Given a Session instance, create a new Producer with the default settings.
 *
 * @param session
 *      The Session that is to be used to create the new Producer.
 * @param destination
 *      The Destination that this Producer will publish to.
 * @param producer
 *      The memory location where the newly allocated Producer instance is to be stored.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status createProducer(CMS_Session* session, CMS_Destination* destination, CMS_MessageProducer** producer);

/**
 * Given a Message Producer, send the given Message using that Producer applying the
 * values given to the send operation.
 *
 * @param producer
 *      The Message Producer to use for this send operation.
 * @param message
 *      The Message to send via the given Message Producer.
 * @param deliveryMode
 * 		The deliveryMode to use when sending this Message.
 * @param priority
 * 		The priority value to use for this Message.
 * @param timeToLive
 *      The time in milliseconds that this Message is allowed to remain active.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status producerSend(CMS_MessageProducer* producer, CMS_Message* message,
                        int deliveryMode, int priority, int timeToLive);

/**
 * Given a Message Producer, send the given Message using that Producer applying the
 * values given to the send operation.  Typically you create a Producer with a specific
 * destination to send to however you can create one with a NULL Destination.  When the
 * producer is created with a NULL Destination this send method must be used to specify
 * the Destination that the Message is to be sent to.  If the Destination is NULL this
 * method returns CMS_ERROR.
 *
 * @param producer
 *      The Message Producer to use for this send operation.
 * @param message
 *      The Message to send via the given Message Producer.
 * @param destination
 * 		The destination where the Message is to be sent.
 * @param deliveryMode
 * 		The deliveryMode to use when sending this Message.
 * @param priority
 * 		The priority value to use for this Message.
 * @param timeToLive
 *      The time in milliseconds that this Message is allowed to remain active.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status producerSendToDestination(CMS_MessageProducer* producer, CMS_Message* message, CMS_Destination* destination,
                                     int deliveryMode, int priority, int timeToLive);

/**
 * Given a Message Producer, send the given Message using that Producer.  This method
 * uses the currently set values for priority, persistence, and message time to live.
 *
 * @param producer
 *      The Message Producer to use for this send operation.
 * @param message
 *      The Message to send via the given Message Producer.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status producerSendWithDefaults(CMS_MessageProducer* producer, CMS_Message* message);

/**
 * Given a Message Producer, send the given Message using that Producer.  Assign the sent
 * message the time to live value specified and uses the currently set values for priority,
 * and message persistence.
 *
 * @param producer
 *      The Message Producer to use for this send operation.
 * @param message
 *      The Message to send via the given Message Producer.
 * @param timeToLive
 *      The time in milliseconds to live for the message.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status producerSendWithTimeOut(CMS_MessageProducer* producer, CMS_Message* message, long long timeToLive);

/**
 * Sets the delivery mode used by the given producer.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param mode
 *      The new delivery mode to assign to the Producer.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status setProducerDeliveryMode(CMS_MessageProducer* producer, int mode);

/**
 * Gets the delivery mode used by the given producer.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param mode
 *      The address where the delivery mode value is to be written.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status getProducerDeliveryMode(CMS_MessageProducer* producer, int* mode);

/**
 * Sets the value of the Producer's disable Message Id setting.  A value of zero indicates
 * that the disable message Id option is disabled, otherwise its enabled.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param enabled
 *      The new disable message id setting for the given MessageProducer.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status setProducerDisableMessageID(CMS_MessageProducer* producer, int enabled);

/**
 * Gets the value of the Producer's disable Message Id setting.  A value of zero indicates
 * that the disable message Id option is disabled, otherwise its enabled.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param enabled
 *      The address where the disable message id setting is to be written.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status getProducerDisableMessageID(CMS_MessageProducer* producer, int* enabled);

/**
 * Sets the value of the Producer's disable time stamp setting.  A value of zero indicates
 * that the disable time stamp option is disabled, otherwise its enabled.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param enabled
 *      The new disable time stamp setting for the given MessageProducer.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status setProducerDisableMessageTimeStamp(CMS_MessageProducer* producer, int enabled);

/**
 * Gets the value of the Producer's disable time stamps setting.  A value of zero indicates
 * that the disable time stamp option is disabled, otherwise its enabled.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param enabled
 *      The address where the disable time stamp setting is to be written.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status getProducerDisableMessageTimeStamp(CMS_MessageProducer* producer, int* enabled);

/**
 * Sets the value of the Producer's Message Priority setting.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param priority
 *      The new message priority setting for the given MessageProducer.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status setProducerPriority(CMS_MessageProducer* producer, int priority);

/**
 * Gets the value of the Producer's Message Priority setting.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param priority
 *      The address where the message priority setting is to be written.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status getProducerPriority(CMS_MessageProducer* producer, int* priority);

/**
 * Sets the value of the Producer's Message Time to Live setting.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param priority
 *      The new message time to live for the given MessageProducer.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status setProducerTimeToLive(CMS_MessageProducer* producer, int timeToLive);

/**
 * Gets the value of the Producer's Message Time to Live setting.
 *
 * @param producer
 *      The Message Producer to use for this operation.
 * @param priority
 *      The address where the message time to live setting is to be written.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status getProducerTimeToLive(CMS_MessageProducer* producer, int* timeToLive);

/**
 * Closes the MessageProducer.
 *
 * @param producer
 *      The Producer that is to be closed.
 *
  * @return result code indicating the success or failure of the operation.
 */
cms_status closeProducer(CMS_MessageProducer* producer);

/**
 * Destroys the given Producer instance.
 *
 * @param producer
 *      The Producer that is to be destroyed.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status destroyProducer(CMS_MessageProducer* producer);

#ifdef __cplusplus
}
#endif

#endif /* _CMS_MESSAGEPRODUCER_WRAPPER_H_ */
