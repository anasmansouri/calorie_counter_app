#pragma once
#include <string>
#include <vector>
#include <memory>
#include "utils/Result.hpp"
#include "models/food.hpp"

namespace cc::clients {

class OpenFoodFactsClient {
public:
  explicit OpenFoodFactsClient(std::string baseUrl = "https://world.openfoodfacts.org");

  cc::utils::Result<std::vector<cc::models::Food>> searchByName(const std::string& query, int page = 1, int pageSize = 10, const std::string& locale = "en");

  cc::utils::Result<cc::models::Food> getByBarcode(const std::string& barcode, const std::string& locale = "en");

  void setUserAgent(const std::string& ua);

private:
  std::string baseUrl_;
  std::string userAgent_;
};

} // namespace cc::clients
