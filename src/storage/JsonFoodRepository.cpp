#include "JsonFoodRepository.hpp"
#include "utils/Result.hpp"
#include <optional>
using json= nlohmann::json;

namespace cc::storage {
JsonFoodRepository::JsonFoodRepository(std::string filePath):filePath_{filePath}{}
// cc::utils::Result<void> JsonFoodRepository::save(const cc::models::Food& food);
   cc::utils::Result<std::optional<cc::models::Food>> getById(const std::string& id) {return  cc::utils::Result<std::optional<cc::models::Food>>::ok(std::nullopt);}
   cc::utils::Result<std::optional<cc::models::Food>> getByBarcode(const std::string& barcode) {return  cc::utils::Result<std::optional<cc::models::Food>>::ok(std::nullopt);}
   cc::utils::Result<std::vector<cc::models::Food>> list(int offset = 0, int limit = 50) {cc::utils::Result<std::optional<cc::models::Food>>::ok(std::nullopt); }
   cc::utils::Result<void> remove(const std::string& id){cc::utils::Result<std::optional<cc::models::Food>>::ok(std::nullopt);} 



/*
private:
    std::string id_;
    std::string name_;
    double totalKcal_{0.0};
    double caloriesPer100g_{0.0};
    std::vector<Nutrient> nutrients_;
    std::optional<double> servingSizeG_;
    std::optional<std::string> barcode_;
    std::optional<std::string> brand_;
    std::optional<std::string> imageUrl_;
    std::string source_{"manual"};
};// Food
  */
 
// class JsonFoodRepository : public FoodRepository {
// public:
  // explicit JsonFoodRepository(std::string filePath);

  // cc::utils::Result<void> save(const cc::models::Food& food) override;
  // cc::utils::Result<std::optional<cc::models::Food>> getById(const std::string& id) override;
  // cc::utils::Result<std::optional<cc::models::Food>> getByBarcode(const std::string& barcode) override;
  // cc::utils::Result<std::vector<cc::models::Food>> list(int offset = 0, int limit = 50) override;
  // cc::utils::Result<void> remove(const std::string& id) override;

  // void setFlushOnWrite(bool enable);

// private:
  // std::string filePath_;
  // bool flushOnWrite_ = true;
  // mutable std::mutex mtx_;
// };

} // namespace cc::storage
