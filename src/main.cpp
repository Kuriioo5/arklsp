/**
 * @file main.cpp
 * @author Kuriioo5 (github.com/Kuriioo5)
 */

import lsp.Server;

auto main() -> int
{
    lsp::Server server;
    server.Start();

    while (server.IsRunning())
    {
        auto message = server.ReadMessage();

        if (!message)
        {
            break;
        }

        server.HandleMessage(*message);
    }
}
