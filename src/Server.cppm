/**
 * @file Server.cppm
 * @author Kuriioo5 (github.com/Kuriioo5)
 */

module;

#include <optional>
#include <string>
#include <iostream>

export module lsp.Server;

import lsp.json;
import lsp.Diagnostic;

export namespace lsp
{
    class Server
    {
    public:

        Server();

        ~Server();

        /**
         *
         */
        auto Start() -> void;

        /**
         *
         */
        [[nodiscard]] 
        auto IsRunning() -> const bool;

        /**
         *
         */
        auto ReadMessage() -> std::optional<json>;
                
        /**
         *
         */
        auto HandleMessage(const json& message) -> void; 

    private:
        
        /**
         *
         */
        bool m_running = false;

        /**
         *
         */
        auto Send(const json& response) -> void;

        /**
         *
         */
        auto PublishDiagnostics(
            const std::string& uri, 
            const std::vector<Diagnostic>& diagnostics
        ) -> void;

        /**
         *
         */
        auto AnalyzeDocument(
            const std::string& uri, 
            const std::string& text
        ) -> void;

    };

}

