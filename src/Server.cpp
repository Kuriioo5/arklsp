/**
 * @file Server.cpp
 * @author Kuriioo5 (github.com/Kuriioo5)
 */

module;

#include <iostream>

module lsp.Server;

import lsp.Diagnostic;

namespace lsp
{
    Server::Server() {}

    Server::~Server() = default;

    auto Server::Start() -> void
    {
        m_running = true;
    }

    auto Server::IsRunning() -> const bool
    {
        return m_running;
    }

    auto Server::ReadMessage() -> std::optional<json>
    {
        std::string line;
        int contentLength = 0;

        while (std::getline(std::cin, line)) 
        {
            if (line.empty() || line == "\r")
            {
                break;
            }

            const std::string prefix = "Content-Length: ";
            if (line.compare(0, prefix.size(), prefix) == 0)
            {
                contentLength = std::stoi(line.substr(prefix.size()));
            }
        }

        if (contentLength <= 0)
        {
            return std::nullopt;
        }

        std::string body(contentLength, '\0');
        std::cin.read(body.data(), contentLength);

        if (!std::cin)
        {
            return std::nullopt;
        }

        return json::parse(body);
    }

    auto Server::HandleMessage(const json& message) -> void
    {
        if (!message.contains("method"))
        {
            return;
        }

        const std::string method = message["method"];

        if (method == "initialize")
        {
            json result = {
                {"capabilities", {
                    {"textDocumentSync", 1}
                }},
                {"serverInfo", {
                    {"name", "arklsp"},
                    {"version", "0.0.1"}
                }}
            };

            Send({
                {"jsonrpc", "2.0"},
                {"id", message.at("id")},
                {"result", result}
            });
        }
        else if (method == "textDocument/didOpen")
        {
            const auto& doc = message["params"]["textDocument"];
            std::string uri  = doc["uri"];
            std::string text = doc["text"]; 

            AnalyzeDocument(uri, text);
        }
        else if (method == "shutdown")
        {
            Send({
                {"jsonrpc", "2.0"},
                {"id", message.at("id")},
                {"result", nullptr}
            });
        }
        else if (method == "exit")
        {
            m_running = false;
        }
    }

    auto Server::Send(const json& response) -> void
    {
        std::string body = response.dump();

        std::cout
            << "Content-Length: "
            << body.size()
            << "\r\n\r\n"
            << body;

        std::cout.flush();
    }

    auto Server::PublishDiagnostics(
        const std::string& uri, 
        const std::vector<Diagnostic>& diagnostics
    ) -> void
    {
        Send({
            {"jsonrpc", "2.0"},
            {"method", "textDocument/publishDiagnostics"},
            {"params", {
                {"uri", uri},
                {"diagnostics", diagnostics}
            }}
        });
    }

    auto Server::AnalyzeDocument(
        const std::string& uri, 
        const std::string& text
    ) -> void
    {
        std::vector<Diagnostic> diagnostics;

        Diagnostic d;
        d.severity = 1;
        d.start = {
            .line = 1,
            .character = 1
        };
        d.end = {
            .line = 1,
            .character = 15
        };
        d.message = "Expected (";
        diagnostics.push_back(d);

        PublishDiagnostics(uri, diagnostics);
    }

}
