#pragma once
#include <string>
#include "utils/Result.hpp"
#include "models/food.hpp"

namespace cc::utils {

class JsonParser {
public:
  Result<cc::models::Food> parseFoodFromOffJson(const std::string& jsonStr) const;
  std::string toJson(const cc::models::Food& food) const;
  Result<cc::models::Food> fromJson(const std::string& jsonStr) const;
};

} // namespace cc::utils

