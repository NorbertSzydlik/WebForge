#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <vector>
#include <string>

#include "IncomingMessage.hpp"
#include "ServerResponse.hpp"


namespace WebForge {
namespace http {

class Connection;
using ConnectionPtr = std::shared_ptr<Connection>;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    using RequestListener = std::function<void(WebForge::http::IncomingMessage&, WebForge::http::ServerResponse&)>;

    static ConnectionPtr create(boost::asio::io_service& ioService, RequestListener requestListener) {
        return ConnectionPtr(new Connection(ioService, requestListener));
    }

    void start();
    boost::asio::ip::tcp::socket& getSocket();
protected:
    Connection(boost::asio::io_service& ioService, RequestListener requestListener);

    void getData();
    void handleReadLine(const boost::system::error_code& ec,
                        std::size_t bytes_transferred);
    void handleRequest();
private:
    boost::asio::ip::tcp::socket m_socket;
    RequestListener m_requestListener;

    boost::asio::streambuf m_data;

    std::vector<std::string> m_linesUploaded;
};

}
}

