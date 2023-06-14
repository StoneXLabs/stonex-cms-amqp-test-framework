
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