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
  // up to now i don't find any ids in json file , so no need for this for now
  cc::utils::Result<cc::models::Food> JsonFoodRepository::getById(const std::string &id)
  {
    // std::ifstream infile(this->filePath_);
    // nlohmann::json file_content;
    // if (infile.is_open() && infile.peek() != std::ifstream::traits_type::eof())
    // {
    // infile >> file_content;
    // infile.close();
    // for(auto i : file_content){
    // if(i["id"].get<std::string>()==id){
    // return cc::utils::Result<cc::models::Food>::ok(cc::models::Food());
    // }
    // }
    // }
    // else
    // {
    // return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::NotFound,"item not found");
    // }
    return cc::utils::Result<cc::models::Food>::ok(cc::models::Food());
  }
  cc::utils::Result<cc::models::Food> JsonFoodRepository::getByBarcode(const std::string &barcode)
  {
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