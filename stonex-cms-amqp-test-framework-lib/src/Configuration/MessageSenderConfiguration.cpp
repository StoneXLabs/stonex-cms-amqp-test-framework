/*
 * Copyright 2022 StoneX Financial Ltd.
 *
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


#include <Configuration/MessageSenderConfiguration.h>

interoperability_tests::config::producer::MessageSenderConfiguration::MessageSenderConfiguration(const std::string producerId, const std::string sessionId, int message_count, const std::string & message_file, const std::vector<MessageTestField*>& fields)
	:TestCaseProducerConfiguration(producerId, sessionId, message_file, message_count),
	mMessagesToSend{ message_count },
	mParameters{ fields }
{
}

const std::vector<MessageTestField*>& interoperability_tests::config::producer::MessageSenderConfiguration::properties() const
{
	return mParameters;
}

void interoperability_tests::config::producer::MessageSenderConfiguration::addProperty(MessageTestField* property)
{
	mParameters.emplace_back(property);
}

const int interoperability_tests::config::producer::MessageSenderConfiguration::messageToSend() const
{
	return mMessagesToSend;
}
