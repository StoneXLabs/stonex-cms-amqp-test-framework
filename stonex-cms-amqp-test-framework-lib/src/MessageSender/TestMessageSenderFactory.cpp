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

#include <Configuration/FileMessageSenderConfiguration.h>
#include <Configuration/FileMessageCountingSenderConfiguration.h>
#include <Configuration/FileMessageDecoratingSenderConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingSenderConfiguration.h>

#include <MessageSender/MockProtobufMessageFileSender.h>
#include <MessageSender/MockProtobufMessageCountingFileSender.h>
#include <MessageSender/MockProtobufMessageDecoratingFileSender.h>
#include <MessageSender/MockProtobufMessageCountingDecoratingFileSender.h>


#include <MessageSender/TestMessageSenderFactory.h>
#include <MessageSender/MockMessageSender.h>
#include <MessageSender/MockProtobufMessageSender.h>
#include <MessageSender/MockMessageCountingSender.h>
#include <MessageSender/MockProtobufMessageCountingSender.h>
#include <MessageSender/MockMessageDecoratingSender.h>
#include <MessageSender/MockProtobufMessageDecoratingSender.h>
#include <MessageSender/MockMessageCountingDecoratingSender.h>
#include <MessageSender/MockProtobufMessageCountingDecoratingSender.h>
#include <messages/mock_message.pb.h>

MessageSender * stonex::messaging::test::TestSenderFactory::create_sender(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const
{
	if (std::cend(mProduceType) != std::find_if(std::cbegin(mProduceType), std::cend(mProduceType), [&sender_configuration](const std::string& item) {return sender_configuration.senderType() == item; }))
	{

		if (auto concrete_configuration = dynamic_cast<const MessageCountingSenderConfiguration*>(&sender_configuration)) {
			if (sender_configuration.senderType() == "framework")
				return new MockMessageCountingSender(*concrete_configuration, client_configuration, parent);
			else if (sender_configuration.senderType() == "framework-protobuf")
				return new MockProtobufMessageCountingSender<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageDecoratingSenderConfiguration*>(&sender_configuration)) {
			if (sender_configuration.senderType() == "framework")
				return new MockMessageDecoratingSender(*concrete_configuration, client_configuration, parent);
			else if (sender_configuration.senderType() == "framework-protobuf")
				return new MockProtobufMessageDecoratingSender<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageCountingDecoratingSenderConfiguration*>(&sender_configuration)) {
			if (sender_configuration.senderType() == "framework")
				return new MockMessageCountingDecoratingSender(*concrete_configuration, client_configuration, parent);
			else if (sender_configuration.senderType() == "framework-protobuf")
				return new MockProtobufMessageCountingDecoratingSender<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageSenderConfiguration*>(&sender_configuration)) {
			if (sender_configuration.senderType() == "framework-protobuf")
				return new ProtobufMessageFileSender<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingSenderConfiguration*>(&sender_configuration)) {
			if (sender_configuration.senderType() == "framework-protobuf")
				return new ProtobufMessageCountingFileSender<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageDecoratingSenderConfiguration*>(&sender_configuration)) {
			if (sender_configuration.senderType() == "framework-protobuf")
				return new ProtobufMessageDecoratingFileSender<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingDecoratingSenderConfiguration*>(&sender_configuration)) {
			if (sender_configuration.senderType() == "framework-protobuf")
				return new ProtobufMessageCountingDecoratingFileSender<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageSenderConfiguration*>(&sender_configuration)) {
			if (sender_configuration.senderType() == "framework")
				return new MockMessageSender(*concrete_configuration, client_configuration, parent);
			else if (sender_configuration.senderType() == "framework-protobuf")
				return new MockProtobufMessageSender<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
	}
	else
		return MessageSenderFactory::create_sender(sender_configuration, client_configuration, parent);
}

stonex::messaging::test::TestSenderFactory::TestSenderFactory()
	:mProduceType{ "framework","framework-protobuf" }
{
}