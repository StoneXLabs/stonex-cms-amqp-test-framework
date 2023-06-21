/*
 * Copyright 2023 StoneX Financial Ltd.
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

#include <MessageReceiver/TestMessageReceiverFactory.h>

#include <Configuration/MessageCountingReceiverConfiguration.h>
#include <Configuration/MessageDecoratingReceiverConfiguration.h>
#include <Configuration/MessageCountingDecoratingReceiverConfiguration.h>
#include <Configuration/FileMessageReceiverConfiguration.h>
#include <Configuration/FileMessageCountingReceiverConfiguration.h>
#include <Configuration/FileMessageDecoratingReceiverConfiguration.h>
#include <Configuration/FileMessageCountingDecoratingReceiverConfiguration.h>

#include <MessageReceiver/ProtobufMessageCountingReceiver.h>
#include <MessageReceiver/ProtobufMessageDecoratingReceiver.h>
#include <MessageReceiver/ProtobufMessageCountingDecoratingReceiver.h>
#include <MessageReceiver/ProtobufMessageFileReceiver.h>
#include <MessageReceiver/ProtobufMessageCountingFileReceiver.h>
#include <MessageReceiver/ProtobufMessageDecoratingFileReceiver.h>
#include <MessageReceiver/ProtobufMessageCountingDecoratingFileReceiver.h>
#include <MessageReceiver/ProtobufMessageReceiver.h>

#include <messages/mock_message.pb.h>

stonex::messaging::test::TestMessageReceiverFactory::TestMessageReceiverFactory()
	:mConsumerType{ "framework-protobuf" }
{
}

MessageReceiver* stonex::messaging::test::TestMessageReceiverFactory::create_receiver(const MessageReceiverConfiguration& receiver_configuration, CMSClientTestUnit& client_configuration, Notifier& parent) const
{
	if (std::cend(mConsumerType) != std::find_if(std::cbegin(mConsumerType), std::cend(mConsumerType), [&receiver_configuration](const std::string& item) {return receiver_configuration.receiverType() == item; }))
	{
		if (auto concrete_configuration = dynamic_cast<const MessageCountingReceiverConfiguration*>(&receiver_configuration)) {
			if (receiver_configuration.receiverType() == "framework-protobuf")
				return new ProtobufMessageCountingReceiver<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageDecoratingReceiverConfiguration*>(&receiver_configuration)) {
			if (receiver_configuration.receiverType() == "framework-protobuf")
				return new ProtobufMessageDecoratingReceiver<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageCountingDecoratingReceiverConfiguration*>(&receiver_configuration)) {
			if (receiver_configuration.receiverType() == "framework-protobuf")
				return new ProtobufMessageCountingDecoratingReceiver<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageReceiverConfiguration*>(&receiver_configuration)) {
			if (receiver_configuration.receiverType() == "framework-protobuf")
				return new ProtobufMessageFileReceiver<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingReceiverConfiguration*>(&receiver_configuration)) {
			if (receiver_configuration.receiverType() == "framework-protobuf")
				return new ProtobufMessageCountingFileReceiver<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageDecoratingReceiverConfiguration*>(&receiver_configuration)) {
			if (receiver_configuration.receiverType() == "framework-protobuf")
				return new ProtobufMessageDecoratingFileReceiver<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const FileMessageCountingDecoratingReceiverConfiguration*>(&receiver_configuration)) {
			if (receiver_configuration.receiverType() == "framework-protobuf")
				return new ProtobufMessageCountingDecoratingFileReceiver<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
		else if (auto concrete_configuration = dynamic_cast<const MessageReceiverConfiguration*>(&receiver_configuration)) {
			 if (receiver_configuration.receiverType() == "framework-protobuf")
				return new ProtobufMessageReceiver<framework::MockMessage>(*concrete_configuration, client_configuration, parent);
			else
				return nullptr;
		}
	}
	else
		return MessageReceiverFactory::create_receiver(receiver_configuration, client_configuration, parent);
}