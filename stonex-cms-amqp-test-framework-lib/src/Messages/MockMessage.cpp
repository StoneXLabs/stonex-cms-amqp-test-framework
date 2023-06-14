
#include <chrono>

#include <Messages/MockMessage.h>
#include <fmt/format.h>
#include <fmt/chrono.h>

std::string MockMessage::timeStamp() const
{
	return fmt::format("\"timestamp\":\"{:%Y-%m-%dT%H:%M:%S}\"", std::chrono::system_clock::now());
}

std::string MockMessage::messageCount(long long count) const
{
	return fmt::format("\"message_count\":{}", count);
}

std::string MockMessage::messageProperties(const std::vector<MessageField*>& properties) const
{
	std::stringstream property_json;
	std::for_each(std::cbegin(properties), std::cend(properties), [&property_json](const MessageField* item) {
		switch (item->type())
		{
		case FIELD_TYPE::BOOLEANPROPERTY:
		case FIELD_TYPE::BYTEPROPERTY:
		case FIELD_TYPE::DOUBLEPROPERTY:
		case FIELD_TYPE::FLOATPROPERTY:
		case FIELD_TYPE::INTPROPERTY:
		case FIELD_TYPE::LONGPROPERTY:
		case FIELD_TYPE::SHORTPROPERTY:
			property_json << fmt::format("\"{}\":{},", item->name(), item->valueString());
			break;
		default:
			property_json << fmt::format("\"{}\":\"{}\",", item->name(), item->valueString());
			break;
		}
	});

	auto property_json_string = property_json.str();
	if (!property_json_string.empty()) {

		property_json_string.pop_back();
	}
	return "\"properties\":{" + property_json_string + '}';
}

