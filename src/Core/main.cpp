#include "Server.hpp"
#include "IncomingMessage.hpp"
#include "ServerResponse.hpp"

void requestListener(WebForge::http::IncomingMessage request, WebForge::http::ServerResponse response)
{
    response.end("<h1>Hello, World!</h1>\n");
}

int main()
{
    WebForge::http::Server server(requestListener);
    server.listen(8080);
    return 0;
}