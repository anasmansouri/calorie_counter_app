#pragma once
#include <string>
#include <mutex>
#include "storage/FoodRepository.hpp"
#include "nlohmann/json.hpp"

namespace cc::storage {

class JsonFoodRepository : public FoodRepository {
public:
  explicit JsonFoodRepository(std::string filePath);

  cc::utils::Result<void> save(const cc::models::Food& food) override;
  cc::utils::Result<std::optional<cc::models::Food>> getById(const std::string& id) override;
  cc::utils::Result<std::optional<cc::models::Food>> getByBarcode(const std::string& barcode) override;
  cc::utils::Result<std::vector<cc::models::Food>> list(int offset = 0, int limit = 50) override;
  cc::utils::Result<void> remove(const std::string& id) override;

  void setFlushOnWrite(bool enable);

private:
  std::string filePath_;
  bool flushOnWrite_ = true;
  mutable std::mutex mtx_;
};

} // namespace cc::storage
