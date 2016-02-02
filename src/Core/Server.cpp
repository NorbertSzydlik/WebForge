#include <iostream>
#include <boost/bind.hpp>
#include "Server.hpp"

using namespace WebForge::http;
using boost::asio::ip::tcp;

Server::Server(Server::RequestListener requestListener) : m_requestListener(requestListener)
{
}

void Server::startAccept()
{
    ConnectionPtr newConnection = Connection::create(m_ioService, m_requestListener);
    m_acceptor->async_accept(newConnection->getSocket(),
                           boost::bind(&Server::handleAccept, this, newConnection,
                                       boost::asio::placeholders::error));
}

void Server::handleAccept(ConnectionPtr newConnection, const boost::system::error_code& errorCode)
{
    if(!errorCode) {
        std::cout << "newConnection start" << std::endl;
        newConnection->start();
    }
    startAccept();
}

void Server::listen(unsigned short port)
{
    m_acceptor = std::make_unique<tcp::acceptor>(m_ioService, tcp::endpoint(tcp::v4(), port));

    startAccept();

    m_ioService.run();
}
