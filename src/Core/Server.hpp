#pragma once

#include <functional>
#include <memory>
#include <boost/asio.hpp>
#include "IncomingMessage.hpp"
#include "ServerResponse.hpp"
#include "Connection.hpp"

namespace WebForge {
namespace http {

class Server
{
public:
    using RequestListener = std::function<void(WebForge::http::IncomingMessage&, WebForge::http::ServerResponse&)>;

    Server() = delete;
    Server(RequestListener requestListener);
    void listen(unsigned short port);
protected:
    void startAccept();
    void handleAccept(ConnectionPtr newConnection, const boost::system::error_code& errorCode);
private:
    RequestListener m_requestListener;
    boost::asio::io_service m_ioService;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;
};

}
}