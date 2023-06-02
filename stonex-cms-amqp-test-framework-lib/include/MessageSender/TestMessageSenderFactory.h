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

#include <MessageSender/MessageSenderFactory.h>

namespace stonex {
	namespace messaging {
		namespace test {

			class TestSenderFactory : public MessageSenderFactory
			{
			public:
				TestSenderFactory();
			protected:
				virtual MessageSender* create_sender(const MessageSenderConfiguration& sender_configuration, CMSClientTestUnit& client_configuration, Notifier& parent)  const;
			private:
				const std::vector<std::string> mProduceType;
			};
		}
	}
}