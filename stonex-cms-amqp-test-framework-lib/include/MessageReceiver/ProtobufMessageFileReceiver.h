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

#pragma once

#include <MessageReceiver/MessageFileReceiver.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/time_util.h>
#include <fmt/format.h>

namespace stonex {
	namespace messaging {
		namespace test {

			template <class T>
			class ProtobufMessageFileReceiver : public MessageFileReceiver
			{
			public:
				ProtobufMessageFileReceiver(const FileMessageReceiverConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent)
					:MessageFileReceiver(config, client_params, parent)
				{
				};

				std::string toString(const cms::Message* message) override {
					if (auto binary_message = dynamic_cast<const cms::BytesMessage*>(message))
					{
						auto length = binary_message->getBodyLength();

						if (length <= 0)
							return fmt::format("message length {}", length);

						unsigned char* data_ptr = binary_message->getBodyBytes();

						T protobuf_message;
						protobuf_message.ParseFromArray(data_ptr, length);

						return protobuf_message.DebugString();

					}
					else if (auto text_message = dynamic_cast<const cms::TextMessage*>(message))
					{
						return text_message->getText();
					}
					else {
						std::stringstream ss;
						ss << message;
						return ss.str();
					}
				}
			};
		}
	}
}
