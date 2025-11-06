#pragma once
#include <string>
#include "utils/Result.hpp"
#include "models/food.hpp"
#include <crow.h>

namespace cc::utils
{

  
    // static Result<cc::models::Food> parseFoodFromOffJson(const std::string &jsonStr) const;
    // static std::string toJson(const cc::models::Food &food) const;
    // static Result<cc::models::Food> fromJson(const std::string &jsonStr) const;
    crow::json::wvalue to_crow_json(const nlohmann::json &j);
} // namespace cc::utils
