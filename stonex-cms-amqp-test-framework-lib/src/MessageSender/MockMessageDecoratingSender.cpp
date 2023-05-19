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

#include <fmt/format.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <MessageSender/MockMessageDecoratingSender.h>

stonex::messaging::test::MockMessageDecoratingSender::MockMessageDecoratingSender(const MessageDecoratingSenderConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageDecoratingSender(config, client_params, parent),
	mMessageDecorations(config.decorations())
{
}

std::string stonex::messaging::test::MockMessageDecoratingSender::createMessageBody()
{
	return fmt::format("{{\"source\":\"{}\",\"timestamp\":\"{}\",\"properties\":\"{{}}\"}}", mId, timestamp(), propertiesJson());
}

std::string stonex::messaging::test::MockMessageDecoratingSender::timestamp() const
{

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::stringstream timestamp;
	timestamp << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
	return timestamp.str();
}

std::string stonex::messaging::test::MockMessageDecoratingSender::propertiesJson() const
{
	std::stringstream property_json;
	std::for_each(std::cbegin(mMessageDecorations), std::cend(mMessageDecorations), [&property_json](const MessageTestField* item) {
		property_json << fmt::format("\"{}\":\"{}\",", item->name(), item->valueString());
	});

	auto property_json_string = property_json.str();
	if (!property_json_string.empty())
		property_json_string.pop_back();
	return property_json_string;
}
