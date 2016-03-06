#include "IncomingMessage.hpp"
#include <regex>
#include <iostream>

using namespace WebForge::http;

std::regex headerKeyValueRegex{"^([a-zA-Z-]+):\\s+(\\S+)"};

IncomingMessage::IncomingMessage(std::vector<std::string> &&linesUploaded) : m_linesUploaded(linesUploaded)
{
    for(auto& line : m_linesUploaded) {
        std::smatch headerKeyValueMatch;
        std::regex_match (line, headerKeyValueMatch, headerKeyValueRegex);

        if(headerKeyValueMatch.size() == 3) {
            HeaderName headerName(headerKeyValueMatch.str(1));
            HeaderValue headerValue(headerKeyValueMatch.str(2));
            m_headers[headerName] = headerValue;
        }
    }
}