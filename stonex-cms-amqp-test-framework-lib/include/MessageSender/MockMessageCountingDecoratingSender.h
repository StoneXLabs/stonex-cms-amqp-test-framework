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

#pragma once

#include <chrono>
#include <MessageSender/MessageSender.h>
#include <Configuration/MessageCountingDecoratingSenderConfiguration.h>
#include <utils/SentMessageCounter.h>
#include <utils/MessageDecorator.h>
#include <Messages/MockMessage.h>

namespace stonex {
	namespace messaging {
		namespace test {

			class MockMessageCountingDecoratingSender : public MessageSender, public SentMessageCounter, public MessageDecorator, public MockMessage
			{
			public:
				MockMessageCountingDecoratingSender(const MessageCountingDecoratingSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent);
				virtual std::string createMessageBody();
				virtual MESSAGE_SEND_STATUS send_text(int msg_delay_ms = 0) override;
				virtual MESSAGE_SEND_STATUS send_bytes(int msg_delay_ms = 0) override;
				virtual MESSAGE_SEND_STATUS send_stream(int msg_delay_ms = 0) override;
				virtual MESSAGE_SEND_STATUS send_map(int msg_delay_ms = 0) override;
			private:
				std::vector <MessageField*> mMessageDecorations;
			};

		}
	}
}