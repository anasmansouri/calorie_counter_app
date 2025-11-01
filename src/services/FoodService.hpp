#pragma once
#include <memory>
#include <vector>
#include <string>
#include "utils/Result.hpp"
#include "models/food.hpp"
#include "storage/FoodRepository.hpp"
#include "clients/OpenFoodFactsClient.hpp"

namespace cc::storage { class FoodRepository; }
namespace cc::clients { class OpenFoodFactsClient; }

namespace cc::services {

class FoodService {
public:
  FoodService(std::shared_ptr<cc::storage::FoodRepository> repo,
              std::shared_ptr<cc::clients::OpenFoodFactsClient> off);

  cc::utils::Result<cc::models::Food> getOrFetchByBarcode(const std::string& barcode);

  cc::utils::Result<void> addManualFood(const  cc::models::Food &food);
  cc::utils::Result<void> deleteFood(const std::string& id);
  cc::utils::Result<std::vector<cc::models::Food>> listFoods(int offset = 0, int limit = 50);

  void setCacheTtlSeconds(int seconds);

private:
  std::shared_ptr<cc::storage::FoodRepository> repo_;
  std::shared_ptr<cc::clients::OpenFoodFactsClient> off_;
  int cacheTtlSeconds_ = 0;
};

} // namespace cc::services
