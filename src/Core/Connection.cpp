#include "Connection.hpp"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>

using namespace WebForge::http;
using namespace boost::asio::ip;

Connection::Connection(boost::asio::io_service& ioService, Connection::RequestListener requestListener) :
        m_socket(ioService),
        m_requestListener(requestListener)
{
}
boost::asio::ip::tcp::socket& Connection::getSocket()
{
    return m_socket;
}

void Connection::start()
{
    getData();
}

void Connection::getData()
{
    auto self = shared_from_this();
    boost::asio::async_read_until(m_socket, m_data, "\r\n",
                                  boost::bind(&Connection::handleReadLine, self,
                                              boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
void Connection::handleReadLine(const boost::system::error_code& error, std::size_t)
{
    if(error) {
        m_socket.close();
        std::cout << "Socket for connection closed" << std::endl;
        return;
    }
    std::istream lineStream(&m_data);
    std::string line;
    std::getline(lineStream, line);
    boost::algorithm::trim(line);

    std::cout << "Received line with length=" << line.size() << ": " << line << std::endl;

    m_linesUploaded.push_back(line);

    if(line.size() == 0) {
        std::cout << "End of http header" << std::endl;
        handleRequest();
        m_linesUploaded.clear();
    }

    getData();
}

void Connection::handleRequest()
{
    IncomingMessage request(std::move(m_linesUploaded));
    ServerResponse response(m_socket);

    m_requestListener(request, response);
}