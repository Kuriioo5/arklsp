/**
 * @file Diagnostic.cppm
 * @author Kuriioo5 (github.com/Kuriioo5)
 */

module;

#include <string>

export module lsp.Diagnostic;

import lsp.json;

export namespace lsp
{
    struct Position
    {
        int line;
        int character;
    };

    struct Diagnostic
    {
        Position start; 
        Position end;

        int severity;

        std::string message;
    };


    auto to_json(json& j, const Position& p) -> void;

    auto to_json(json& j, const Diagnostic& d) -> void;
}
