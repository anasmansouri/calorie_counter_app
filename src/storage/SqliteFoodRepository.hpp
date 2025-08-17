#pragma once
#include <string>
#include <mutex>
#include "storage/FoodRepository.hpp"

namespace cc::storage {

class SqliteFoodRepository : public FoodRepository {
public:
  explicit SqliteFoodRepository(std::string dbPath);

  cc::utils::Result<void> save(const cc::models::Food& food) override;
  cc::utils::Result<std::optional<cc::models::Food>> getById(const std::string& id) override;
  cc::utils::Result<std::optional<cc::models::Food>> getByBarcode(const std::string& barcode) override;
  cc::utils::Result<std::vector<cc::models::Food>> list(int offset = 0, int limit = 50) override;
  cc::utils::Result<void> remove(const std::string& id) override;

  // migrations (optional)
  cc::utils::Result<void> migrate();
  int schemaVersion() const;

private:
  std::string dbPath_;
  mutable std::mutex mtx_;
};

} // namespace cc::storage
