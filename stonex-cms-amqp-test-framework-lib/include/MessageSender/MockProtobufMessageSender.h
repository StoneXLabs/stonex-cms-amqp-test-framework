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

#include <MessageSender/MockMessageSender.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/time_util.h>
#include <fmt/format.h>

namespace stonex {
	namespace messaging {
		namespace test {

			template <class T>
			class MockProtobufMessageSender : public MockMessageSender
			{
			public:
				MockProtobufMessageSender(const MessageSenderConfiguration& config, CMSClientTestUnit & client_params, Notifier& parent)
					:MockMessageSender(config, client_params, parent)
				{
				};

				virtual std::string timeStamp() const override
				{
					auto timestamp = google::protobuf::util::TimeUtil::GetCurrentTime();
					auto test = google::protobuf::util::TimeUtil::ToString(timestamp);
					return  fmt::format("\"timestamp\":\"{}\"", test);
				};
			protected:
				virtual bool send_bytes(int msg_delay_ms = 0) override
				{
					auto message_body = createMessageBody();

					if (message_body.empty())
						return false;

					if (mSession && mProducer)
					{
						T protobuf_message;
						google::protobuf::util::JsonStringToMessage(message_body, &protobuf_message);

						auto size = protobuf_message.ByteSizeLong();
						unsigned char* message = (unsigned char*)malloc((size_t)size);
						protobuf_message.SerializeToArray(message, size);

						auto cms_message = mSession->createBytesMessage(message, protobuf_message.ByteSize());
						mProducer->send(cms_message);
						free(message);
						return true;
					}
					else
						return false;
				};

				virtual bool send_stream(int msg_delay_ms = 0) override
				{
					return false;
				};

				virtual bool send_map(int msg_delay_ms = 0) override
				{
					return false;
				};
			};
		}
	}
}