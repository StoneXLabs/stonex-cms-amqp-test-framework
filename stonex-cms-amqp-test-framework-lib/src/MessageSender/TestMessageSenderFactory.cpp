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

#include <MessageSender/TestMessageSenderFactory.h>
#include <MessageSender/MockMessageSender.h>
#include <MessageSender/MockMessageCountingSender.h>
#include <MessageSender/MockMessageDecoratingSender.h>
#include <MessageSender/MockMessageCountingDecoratingSender.h>

MessageSender * stonex::messaging::test::TestSenderFactory::create_sender(const MessageSenderConfiguration & sender_configuration, CMSClientTestUnit & client_configuration, Notifier & parent) const
{

	if (auto concrete_configuration = dynamic_cast<const MessageCountingSenderConfiguration*>(&sender_configuration)) {
		return new MockMessageCountingSender(*concrete_configuration, client_configuration, parent);
	}
	else if (auto concrete_configuration = dynamic_cast<const MessageDecoratingSenderConfiguration*>(&sender_configuration)) {
		return new MockMessageDecoratingSender(*concrete_configuration, client_configuration, parent);
	}
	else if (auto concrete_configuration = dynamic_cast<const MessageCountingDecoratingSenderConfiguration*>(&sender_configuration)) {
		return new MockMessageCountingDecoratingSender(*concrete_configuration, client_configuration, parent);
	}
	else if (auto concrete_configuration = dynamic_cast<const MessageSenderConfiguration*>(&sender_configuration)) {
		return new MockMessageSender(*concrete_configuration, client_configuration, parent);
	}
	else
		return nullptr;
}
