#include "JsonFoodRepository.hpp"
#include "models/food.hpp"
#include "nlohmann/json.hpp"
#include "utils/Result.hpp"
#include <fstream>
#include <iostream>

#include <iterator>
#include <optional>
#include <ostream>
#include <vector>
using json = nlohmann::json;

namespace cc::storage
{
  JsonFoodRepository::JsonFoodRepository(std::string filePath) : filePath_{filePath} {}
  cc::utils::Result<void> JsonFoodRepository::save(const cc::models::Food& food){
      std::ofstream file(this->filePath_);
      if(!file.is_open()){
          std::cerr<<"can't open file"<<std::endl;
          return cc::utils::Result<void>::fail(cc::utils::ErrorCode::NotFound, "can't open file");
      }
      nlohmann::json j = food;
      file <<j.dump(4);
      file.close();
      return cc::utils::Result<void>::ok();
  }

  cc::utils::Result<cc::models::Food> JsonFoodRepository::getById(const std::string &id) { 
      nlohmann::json j;
      std::ifstream file(this->filePath_);
      if(!file.is_open()){
          std::cerr<<"can't open file"<<std::endl;
          return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::NotFound, "can't open file");
      }
      try {
         file>>j;   
      } catch (const nlohmann::json::parse_error &e) {
          std::cerr<<"parse error"<<e.what()<<std::endl;
          return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::ParseError, e.what());
      }
      std::cout<<j.dump(4)<<std::endl;
      std::cout<<"founded id :"<<j["id"]<<"  ||| searched id "<<id<<std::endl;
      if(j["id"]==id){
          std::cout<<"item founded"<<std::endl;
      }
      return cc::utils::Result<cc::models::Food>::ok(cc::models::Food());
  }

  cc::utils::Result<cc::models::Food> JsonFoodRepository::getByBarcode(const std::string &barcode) { 
      return cc::utils::Result<cc::models::Food>::ok(cc::models::Food()); 
  }

  cc::utils::Result<std::vector<cc::models::Food>> JsonFoodRepository::list(int offset, int limit ) {
      return cc::utils::Result<std::vector<cc::models::Food>>::ok(std::vector<cc::models::Food>{}); 
  }

  cc::utils::Result<void> JsonFoodRepository::remove(const std::string &id) { 
      return cc::utils::Result<void>::ok();
  }

   // update or insert if doesn't exist 
  cc::utils::Result<void> JsonFoodRepository::upsert(const cc::models::Food& food){
      return cc::utils::Result<void>::ok();
  }
  // clear all records 
  cc::utils::Result<void> JsonFoodRepository::clear(){
      return cc::utils::Result<void>::ok();
  }
} // namespace cc::storage
