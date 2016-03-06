#pragma once
#include <map>
#include <vector>

namespace WebForge {
namespace http {

using HeaderName = std::string;
using HeaderValue = std::string;
using CookieName = std::string;
using CookieValue = std::string;

class IncomingMessage {
public:
    IncomingMessage(std::vector<std::string>&& linesUploaded);
    IncomingMessage() = delete;

    std::map<HeaderName, HeaderValue> m_headers;
    std::map<CookieName, CookieValue> m_cookies;
private:
    std::vector<std::string> m_linesUploaded;
};

}
}