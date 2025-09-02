#include "models/food.hpp"
#include "models/nutrient.hpp"
#include "utils/Result.hpp"
#include <array>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <clients/OpenFoodFactsClient.hpp>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <utility>
#include <utils/HttpClient.hpp>
#include <vector>
namespace cc::clients {
    OpenFoodFactsClient::OpenFoodFactsClient(const std::string baseUrl,const std::string userAgent):baseUrl_(baseUrl),userAgent_(userAgent){
  }

cc::utils::Result<cc::models::Food> OpenFoodFactsClient::parseFoodFromOffJson_barcode(cc::utils::Result<std::string> food_in_off_json_format){
    //  product 
    nlohmann::json j = nlohmann::json::parse(food_in_off_json_format.unwrap());
    auto product = j.at("product");
    cc::models::Food food_item;
    food_item.setName(product.at("brands").get<std::string>());
    //  nutriments
    auto nutriments = product.at("nutriments");
    std::vector<cc::models::Nutrient> ns;
    // protein
    models::Nutrient p;
    p.setName("protein");
    p.setUnit(nutriments.at("proteins_unit").get<std::string>());
    p.setValue(nutriments.at("proteins").get<double>());
    ns.push_back(p);
    // carbs
    models::Nutrient carbs;
    carbs.setName("carbohydrates");
    carbs.setUnit(nutriments.at("carbohydrates_unit"));
    carbs.setValue(nutriments.at("carbohydrates"));
    ns.push_back(carbs);
    //  fat 
    models::Nutrient fat;
    fat.setName("fat");
    fat.setUnit(nutriments.at("fat_unit"));
    fat.setValue(nutriments.at("fat"));
    ns.push_back(fat);
    food_item.setNutrients( ns);
    return cc::utils::Result<cc::models::Food>::ok(std::move(food_item));
}

cc::utils::Result<std::vector<cc::models::Food>> OpenFoodFactsClient::parseFoodFromOffJson(cc::utils::Result<std::string> food_in_off_json_format,std::string searched_item){ nlohmann::json j = nlohmann::json::parse(food_in_off_json_format.unwrap());
    auto products = j.value("products",nlohmann::json::array());
    const int max_number_of_products=4;
    std::vector<cc::models::Food> food_items;
    for(size_t i =0;i<products.size() && i<max_number_of_products;i++){
        auto nutriments = products[i].at("nutriments");
        // protein 
        cc::models::Food f;
        f.setName(searched_item+std::to_string(i));
        std::vector<cc::models::Nutrient> ns;
        // protein
        models::Nutrient p;
        p.setName("protein");
        p.setUnit(nutriments.at("proteins_unit").get<std::string>());
        p.setValue(nutriments.at("proteins").get<double>());
        ns.push_back(p);
        // carbs
        models::Nutrient carbs;
        carbs.setName("carbohydrates");
        carbs.setUnit(nutriments.at("carbohydrates_unit"));
        carbs.setValue(nutriments.at("carbohydrates"));
        ns.push_back(carbs);
        //  fat 
        models::Nutrient fat;
        fat.setName("fat");
        fat.setUnit(nutriments.at("fat_unit"));
        fat.setValue(nutriments.at("fat"));
        ns.push_back(fat);
        f.setNutrients( ns);
        food_items.push_back(f);
    }
    return cc::utils::Result<std::vector<cc::models::Food>>::ok(std::move(food_items));
}
  cc::utils::Result<std::vector<cc::models::Food>> OpenFoodFactsClient::searchByName(const std::string& query, int page /*= 1*/, int pageSize /*= 10*/, const std::string& locale /*= "en"*/){
      if(curl_global_init(CURL_GLOBAL_DEFAULT)!=0){
          std::cerr<<"curl_global_init failed\n";
          // chouf chno t returni hna 
      }
      cc::utils::HttpClient http;
      http.setTimeoutMs(5000);
      http.setUserAgents(this->userAgent_);


     this->updateLanguageCountry(locale); // from world to the choosen language or country
     auto r= http.getJson(this->baseUrl_+"/cgi/search.pl?search_terms="+query+"&search_simple=1&action=process&json=1");
      if(!r){
          std::cerr<<"GET failed: "<<r.unwrap_error().message<<"\n";
          return cc::utils::Result<std::vector<cc::models::Food>>::fail(cc::utils::ErrorCode::NetworkError, r.unwrap_error().message);
      }else{
        std::cout << "GET succeeded, body size = " << r.unwrap().size() << "\n";
        auto r_list_of_foods_parse= this->parseFoodFromOffJson(r,query);
        if(!r_list_of_foods_parse){
            std::cerr<<"parsing failed"<<std::endl; 
            return cc::utils::Result<std::vector<cc::models::Food>>::fail(cc::utils::ErrorCode::ParseError, r_list_of_foods_parse.unwrap_error().message);
        }else{
            std::cout<<"parsed succeeded"<<std::endl;
            return r_list_of_foods_parse;
        }
      }
  }

  cc::utils::Result<cc::models::Food> OpenFoodFactsClient::getByBarcode(const std::string& barcode, const std::string& locale ){
      if(curl_global_init(CURL_GLOBAL_DEFAULT)!=0){
          std::cerr<<"curl_global_init failed\n";
      }
      cc::utils::HttpClient http;
      http.setTimeoutMs(5000);
      http.setUserAgents(this->userAgent_);
      // GET https://world.openfoodfacts.org/api/v0/product/{barcode}.json
      this->updateLanguageCountry(locale);
      auto r= http.getJson(this->baseUrl_+"/api/v0/product/{"+barcode+"}.json");
      if(!r){
          std::cerr<<"GET failed: "<<r.unwrap_error().message<<"\n";
          return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::NetworkError, r.unwrap_error().message);
      }else{
        std::cout << "GET succeeded, body size = " << r.unwrap().size() << "\n";
        auto parsed_food= this->parseFoodFromOffJson_barcode(r);
        if(!parsed_food){ 
            std::cerr<<"parsing failed"<<std::endl; 
            return cc::utils::Result<cc::models::Food>::fail(cc::utils::ErrorCode::ParseError, parsed_food.unwrap_error().message);
        }else{
            std::cout<<"parsed succeeded"<<std::endl;
            return parsed_food;
        }
      }
      return cc::utils::Result<cc::models::Food>::ok(cc::models::Food());
  }

  void  OpenFoodFactsClient::setUserAgent(const std::string& ua){
      this->userAgent_=ua;
  }
  void  OpenFoodFactsClient::updateLanguageCountry(const std::string& locale){
      this->baseUrl_ = "https://"+locale+".openfoodfacts.org";
  }
} // namespace cc::clients
