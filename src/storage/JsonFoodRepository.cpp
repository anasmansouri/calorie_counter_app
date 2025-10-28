#include "JsonFoodRepository.hpp"

namespace cc::storage
{
  JsonFoodRepository::JsonFoodRepository(std::string filePath) : filePath_{filePath} {}
  cc::utils::Result<void> JsonFoodRepository::save(const cc::models::Food &food)
  {

    std::ifstream infile(filePath_);
    nlohmann::json file_content;
    if (infile.is_open() && infile.peek() != std::ifstream::traits_type::eof())
    {
      infile >> file_content;
      infile.close();
    }
    else
    {
      file_content = nlohmann::json::array();
    }
    file_content.push_back(food);
    std::cout << file_content.dump(4) << std::endl;
    std::ofstream o(filePath_);
    if (o.is_open())
    {
      o << file_content.dump(4) << std::endl;
      o.close();
      return cc::utils::Result<void>::ok();
    }
    else
    {
      std::cout << "can't open file" + filePath_ << std::endl;
      return cc::utils::Result<void>::fail(cc::utils::ErrorCode::StorageError, "can't open file");
    }
  }

  cc::utils::Result<cc::models::Food> JsonFoodRepository::getById(const std::string &id)
  {
    std::ifstream infile(this->filePath_);
    nlohmann::json file_content;
    if (infile.is_open() && infile.peek() != std::ifstream::traits_type::eof())
    {
      infile >> file_content;
      infile.close();
      for (auto i : file_content)
      {
        std::cout << "founded id " << i["id"].get<std::string>() << " expected id : " << id << std::endl;
        if (i["id"].get<std::string>() == id)
        {
          std::vector<cc::models::Nutrient> nutrients;
          for (nlohmann::json n : nutrients)
          {
            nutrients.push_back(cc::models::Nutrient(n["name"].get<std::string>(), n["value"].get<double>(), n["unit"].get<std::string>()));
          }
          return cc::utils::Result<cc::models::Food>::ok(cc::models::Food(i["id"].get<std::string>(),
                                                                          i["name"].get<std::string>(),
                                                                          i["caloriesPer100g"].get<double>(),
                                                                          nutrients,
                                                                          0,
                                                                          i["barcode"].get<std::string>(),
                                                                          i["brand"].get<std::string>(),
                                                                          i["imageUrl"].get<std::string>()));
        }
      }
      return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::NotFound, "item not found");
    }
    else
    {
      return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::NotFound, "file is empty , or can't open that file");
    }
    return cc::utils::Result<cc::models::Food>::ok(cc::models::Food());
  }
  cc::utils::Result<cc::models::Food> JsonFoodRepository::getByBarcode(const std::string &barcode)
  {
    std::ifstream infile(this->filePath_);
    nlohmann::json file_content;
    if (infile.is_open() && infile.peek() != std::ifstream::traits_type::eof())
    {
      infile >> file_content;
      infile.close();
      for (auto i : file_content)
      {
        if (i["barcode"].get<std::string>() == barcode)
        {
          std::vector<cc::models::Nutrient> nutrients;
          for (nlohmann::json n : nutrients)
          {
            nutrients.push_back(cc::models::Nutrient(n["name"].get<std::string>(), n["value"].get<double>(), n["unit"].get<std::string>()));
          }
          return cc::utils::Result<cc::models::Food>::ok(cc::models::Food(i["id"].get<std::string>(),
                                                                          i["name"].get<std::string>(),
                                                                          i["caloriesPer100g"].get<double>(),
                                                                          nutrients,
                                                                          0,
                                                                          i["barcode"].get<std::string>(),
                                                                          i["brand"].get<std::string>(),
                                                                          i["imageUrl"].get<std::string>()));
        }
      }
      return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::NotFound, "item not found");
    }
    else
    {
      return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::NotFound, "file is empty , or can't open that file");
    }
    return cc::utils::Result<cc::models::Food>::ok(cc::models::Food());
  }
  cc::utils::Result<std::vector<cc::models::Food>> JsonFoodRepository::list(int offset, int limit)
  {
    return cc::utils::Result<std::vector<cc::models::Food>>::ok({});
  }
  cc::utils::Result<void> JsonFoodRepository::remove(const std::string &id)
  {
    return cc::utils::Result<void>::ok();
  }

  // update or insert if doesn't exist
  cc::utils::Result<void> JsonFoodRepository::upsert(const cc::models::Food &food)
  {
    return cc::utils::Result<void>::ok();
  }

  // clear all records
  cc::utils::Result<void> JsonFoodRepository::clear()
  {
    return cc::utils::Result<void>::ok();
  }

  void JsonFoodRepository::setFlushOnWrite(bool enable) {}
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