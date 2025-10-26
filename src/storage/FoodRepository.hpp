#pragma once
#include <memory>
#include <vector>
#include <optional>
#include <string>
#include <iostream>
#include <fstream>
#include "utils/Result.hpp"
#include "models/food.hpp"


namespace cc::storage {

class FoodRepository {
public:
  virtual ~FoodRepository() = default;

  virtual cc::utils::Result<void> save(const cc::models::Food& food) = 0;
  virtual cc::utils::Result<cc::models::Food> getById(const std::string& id) = 0;
  virtual cc::utils::Result<cc::models::Food> getByBarcode(const std::string& barcode) = 0;
  virtual cc::utils::Result<std::vector<cc::models::Food>> list(int offset = 0, int limit = 50) = 0;
  virtual cc::utils::Result<void> remove(const std::string& id) = 0;

  // optional:
  // update or insert if doesn't exist 
  virtual cc::utils::Result<void> upsert(const cc::models::Food& food) = 0;
  // clear all records 
  virtual cc::utils::Result<void> clear() = 0;
};

} // namespace cc::storage
