#pragma once

#include <boost/asio.hpp>
#include <string>

namespace WebForge {
namespace http {

class ServerResponse
{
public:
    ServerResponse(boost::asio::ip::tcp::socket& socket);

    void end();
    void end(std::string body);
protected:
    std::string getHeader(std::string field, std::string value);
private:
    boost::asio::ip::tcp::socket& m_socket;
};

}
}
