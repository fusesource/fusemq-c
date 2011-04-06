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

#ifndef _CMS_DESTINATION_WRAPPER_H_
#define _CMS_DESTINATION_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a Destination from the Given Session instance.  The type of Destination is
 * given by the DESTINATION_TYPE parameter.
 *
 * @param session
 *      The Session to use to create the new Destination.
 * @param type
 *      The Type of Destination that is to be created.
 * @param name
 *      The name to assign the Destination, in the case of Temporary Destinations
 *      this parameter is ignored.
 * @param destination
 *      The address of the location to store the new Destination instance.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_createDestination(CMS_Session* session, CMS_DESTINATION_TYPE type, const char* name, CMS_Destination** destination);

/**
 * Creates a Temporary Destination from the Given Session instance.  The type of
 * Destination is given by the DESTINATION_TYPE parameter and must be one of
 * CMS_TEMPORARY_TOPIC or CMS_TEMPORARY_QUEUE otherwise CMS_ERROR is returned.
 *
 * This is a convenience method that is equivalent to calling createDestination
 * and specifying a temporary destination type and leaving the name value as NULL.
 *
 * @param session
 *      The Session to use to create the new Destination.
 * @param type
 *      The Type of Destination that is to be created.
 * @param destination
 *      The address of the location to store the new Destination instance.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_createTemporaryDestination(CMS_Session* session, CMS_DESTINATION_TYPE type, CMS_Destination** destination);

/**
 * Destroy the given Destination instance.
 *
 * @param destination
 *      The Destination to destroy.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_destroyDestination(CMS_Destination* destination);

/**
 * Compares to CMS Destination instances for equality.
 *
 * @param lhs
 *      The Destination on the left-hand side of the comparison.
 * @param rhs
 *      The Destination on the right-hand side of the comparison.
 * @param areEqual
 *      The address to write the boolean result of the comparison to.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_compareDestinations(CMS_Destination* lhs, CMS_Destination* rhs, int* areEqual);

/**
 * Checks if the supplied Destination is a Topic.
 *
 * @param destination
 *      The Destination to check for its type.
 * @param isTopic
 *      The address to write the boolean result of the operation.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_isDestinationTopic(CMS_Destination* destination, int* isTopic);

/**
 * Checks if the supplied Destination is a Queue.
 *
 * @param destination
 *      The Destination to check for its type.
 * @param isQueue
 *      The address to write the boolean result of the operation.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_isDestinationQueue(CMS_Destination* destination, int* isQueue);

/**
 * Checks if the supplied Destination is a Temporary type.
 *
 * @param destination
 *      The Destination to check for its type.
 * @param isTemporary
 *      The address to write the boolean result of the operation.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_isDestinationTemporary(CMS_Destination* destination, int* isTemporary);

#ifdef __cplusplus
}
#endif

#endif /* _CMS_DESTINATION_WRAPPER_H_ */
