#include "Channel.h"

#include <array>
#include <algorithm>
#include <regex>

namespace RunFragment {

std::unique_ptr<Channel> Channel::fromString(std::string str) {
	return std::unique_ptr<Channel> {Channel::fromStringRaw(std::move(str))};
}

Channel* Channel::fromStringRaw(std::string str) {
	std::array<std::string, 4> bufs {{ "BufA", "BufB", "BufC", "BufD" }};
	const auto it = std::find(bufs.begin(), bufs.end(), std::move(str));

	if(it != bufs.end()) {
		auto kind = static_cast<ChannelBuf::Kind>(std::distance(bufs.begin(), it));
		
		return new ChannelBuf {kind};
	}
	
	std::regex re {"^.*\\.(png|jpg|jpeg|tiff|gif|tga)$"};
	
	if(std::regex_match(str, re)) {
		return new ChannelImage {str};
	}

	return nullptr;
}

void validate(boost::any& value, const std::vector<std::string>& args, Channel**, int) {
	namespace po = boost::program_options;
	
	const std::string& arg = po::validators::get_single_string(args);
	
	if(arg == "none") {
		value = boost::any {static_cast<Channel*>(nullptr)};
		return;
	}
	
	auto channel = Channel::fromStringRaw(arg);
	
	if(channel) {
		value = boost::any {std::move(channel)};
	}
	else {
		throw po::validation_error {po::validation_error::invalid_option_value};
	}
}

}
