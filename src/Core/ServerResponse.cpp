#include "ServerResponse.hpp"

using namespace WebForge::http;
ServerResponse::ServerResponse(boost::asio::ip::tcp::socket& socket) : m_socket(socket)
{

}

std::string ServerResponse::getHeader(std::string field, std::string value)
{
    std::stringstream sstm;
    sstm << field << ":" << value << "\r\n";
    return sstm.str();
}

void ServerResponse::end(std::string body)
{
    auto contentLength = body.size();
    m_socket.send(boost::asio::buffer(std::string("HTTP/1.1 200 OK\r\n")) );
    m_socket.send(boost::asio::buffer(getHeader("Content-Length", std::to_string(contentLength))) );
    m_socket.send(boost::asio::buffer(std::string("\r\n")) );
    m_socket.send(boost::asio::buffer(body));
}

void ServerResponse::end()
{
    end("");
}