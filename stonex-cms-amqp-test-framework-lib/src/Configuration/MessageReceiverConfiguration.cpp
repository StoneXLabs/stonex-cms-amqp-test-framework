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


#include <Configuration/MessageReceiverConfiguration.h>

interoperability_tests::config::consumer::MessageReceiverConfiguration::MessageReceiverConfiguration(const std::string consumerId, int message_count, const std::string & destination_type, const std::string & destination_address, const std::vector<MessageTestField*>& fields)
	:TestCaseMessageReceiverConfiguration(consumerId, destination_type, destination_address),
	mExpectedCount{message_count},
	mParameters{fields}
{
}

int interoperability_tests::config::consumer::MessageReceiverConfiguration::expectedMessagesCount() const
{
	return mExpectedCount;
}

const std::vector<MessageTestField*>& interoperability_tests::config::consumer::MessageReceiverConfiguration::properties() const
{
	return mParameters;
}

void interoperability_tests::config::consumer::MessageReceiverConfiguration::addProperty(MessageTestField *property)
{
	mParameters.push_back(property);
}
