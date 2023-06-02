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

#include <MessageSender/MessageDecoratingFileSender.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/time_util.h>
#include <fmt/format.h>

namespace stonex {
	namespace messaging {
		namespace test {

			template <class T>
			class ProtobufMessageDecoratingFileSender : public MessageDecoratingFileSender
			{
			public:
				ProtobufMessageDecoratingFileSender(const MessageDecoratingSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent)
					:MessageDecoratingFileSender(config, client_params, parent)
				{
				};

			protected:
				virtual MESSAGE_SEND_STATUS send_bytes(int msg_delay_ms = 0) override
				{

					auto message_body = createMessageBody();

					if (message_body.empty())
						return MESSAGE_SEND_STATUS::FAILED;

					if (mSession && mProducer)
					{
						T protobuf_message;
						google::protobuf::util::JsonStringToMessage(message_body, &protobuf_message);

						auto size = protobuf_message.ByteSizeLong();
						unsigned char* message = (unsigned char*)malloc((size_t)size);
						protobuf_message.SerializeToArray(message, size);

						auto cms_message = mSession->createBytesMessage(message, protobuf_message.ByteSize());
						decorate(cms_message, mSession);
						mProducer->send(cms_message);
						delete cms_message;
						free(message);
						return MESSAGE_SEND_STATUS::ALL_SENT;
					}
					else
						return MESSAGE_SEND_STATUS::FAILED;
				};

				virtual MESSAGE_SEND_STATUS send_stream(int msg_delay_ms = 0) override { return MESSAGE_SEND_STATUS::SEND_ERROR; }
				virtual MESSAGE_SEND_STATUS send_map(int msg_delay_ms = 0) override { return MESSAGE_SEND_STATUS::SEND_ERROR; }
			};
		}
	}
}
