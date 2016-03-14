#include "IncomingMessage.hpp"
#include <regex>
#include <iostream>
#include <boost/tokenizer.hpp>

using namespace WebForge::http;

std::regex headerKeyValueRegex{"^([a-zA-Z-]+):\\s+(\\S+)"};
using CharTokenizer = boost::tokenizer<boost::char_separator<char> >;
boost::char_separator<char> cookieSeparator(";");

IncomingMessage::IncomingMessage(std::vector<std::string> &&linesUploaded) : m_linesUploaded(linesUploaded)
{
    for(auto& line : m_linesUploaded)
    {
        std::smatch headerKeyValueMatch;
        std::regex_match(line, headerKeyValueMatch, headerKeyValueRegex);

        if (headerKeyValueMatch.size() != 3)
        {
            continue;
        }
        HeaderName headerName(headerKeyValueMatch.str(1));
        HeaderValue headerValue(headerKeyValueMatch.str(2));
        if(headerName == "Cookie")
        {
            CharTokenizer cookiePairs(headerValue, cookieSeparator);
            for(std::string const& cookiePair : cookiePairs)
            {
                auto assignmentPosition = cookiePair.find("=");
                if (assignmentPosition == std::string::npos)
                {
                    continue;
                }
                auto cookieName = cookiePair.substr(0, assignmentPosition);
                auto cookieValue = cookiePair.substr(assignmentPosition + 1);
                std::cout << "COOKIE: " << cookieName << "=" << cookieValue << std::endl;
                m_cookies[cookieName] = cookieValue;
            }
        }
        else
        {
            m_headers[headerName] = headerValue;
        }
    }
}
