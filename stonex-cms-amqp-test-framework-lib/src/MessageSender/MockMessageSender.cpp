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
#include <MessageSender/MockMessageSender.h>

stonex::messaging::test::MockMessageSender::MockMessageSender(const MessageSenderConfiguration & config, CMSClientTestUnit & client_params, Notifier & parent)
	:MessageSender(config, client_params, parent)
{
}

std::string stonex::messaging::test::MockMessageSender::createMessageBody()
{
	return fmt::format("{{\"source\":\"{}\",\"timestamp\":\"{}\"}}", mId, timestamp());

}

std::string stonex::messaging::test::MockMessageSender::timestamp() const
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::stringstream timestamp;
	timestamp << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
	return timestamp.str();
}
