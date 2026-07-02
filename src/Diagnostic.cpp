/**
 * @file Diagnostic.cpp
 * @author Kuriioo5 (github.com/Kuriioo5)
 */

module;

module lsp.Diagnostic;

namespace lsp 
{
    auto to_json(json& j, const Position& p) -> void
    {
        j = { 
            {"line", p.line}, 
            {"character", p.character} 
        };
    }

    auto to_json(json& j, const Diagnostic& d) -> void
    {
        j = {
            {"range", { 
                {"start", d.start}, 
                {"end", d.end} 
            }},
            {"severity", d.severity},
            {"message", d.message},
            {"source", "arklsp"}
        };
    }

}
