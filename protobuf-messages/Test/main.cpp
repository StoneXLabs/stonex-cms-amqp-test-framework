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

#include <messages/mock_message.pb.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/util/time_util.h>

int main()
{

	{
		auto message_json = "{\"source\":\"producer1\"}";

		framework::MockMessage protobuf_message;
		google::protobuf::util::JsonStringToMessage(message_json, &protobuf_message);

		auto size = protobuf_message.ByteSizeLong();
		unsigned char* message = (unsigned char*)malloc((size_t)size);
		protobuf_message.SerializeToArray(message, size);

		protobuf_message.PrintDebugString();
	}

	{
		auto message_json = "{\"source\":\"producer1\",\"timestamp\":\"21-05-2023 13-20-07\"}";

		framework::MockMessage protobuf_message;
		google::protobuf::util::JsonStringToMessage(message_json, &protobuf_message);

		auto size = protobuf_message.ByteSizeLong();
		unsigned char* message = (unsigned char*)malloc((size_t)size);
		protobuf_message.SerializeToArray(message, size);

		protobuf_message.PrintDebugString();
	}


//	protobuf_message2.timest("producer1");
}