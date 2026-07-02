/**
 * @file json.cppm
 * @author Kuriioo5 (github.com/Kuriioo5)
 */

module;

#include <nlohmann/json.hpp>

export module lsp.json;

export namespace lsp
{
    using json = nlohmann::json;
}
