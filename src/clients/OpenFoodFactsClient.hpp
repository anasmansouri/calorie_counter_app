#pragma once
#include <string>
#include <vector>
#include <memory>
#include "utils/Result.hpp"
#include "models/food.hpp"

namespace cc::clients {

class OpenFoodFactsClient {
public:
  explicit OpenFoodFactsClient(std::string baseUrl = "https://world.openfoodfacts.org",const std::string userAgent="CalorieCounter/1.0 (+https://example.com; anas@example.com)");

  cc::utils::Result<std::vector<cc::models::Food>> searchByName(const std::string& query, int page = 1, int pageSize = 10, const std::string& locale = "en");

  cc::utils::Result<cc::models::Food> getByBarcode(const std::string& barcode, const std::string& locale = "en");
  cc::utils::Result<std::vector<cc::models::Food>> parseFoodFromOffJson(cc::utils::Result<std::string> food_in_off_json_format,std::string searched_item);
  cc::utils::Result<cc::models::Food> parseFoodFromOffJson_barcode(cc::utils::Result<std::string> food_in_off_json_format);

  void  updateLanguageCountry(const std::string& locale);
  void setUserAgent(const std::string& ua);

private:
  std::string baseUrl_;
  std::string userAgent_ = "CalorieCounter/1.0 (+https://example.com; anas@example.com)"; // update it later
};

} // namespace cc::clients
