#include "models/food.hpp"
#include "models/nutrient.hpp"
#include "utils/Result.hpp"
#include <nlohmann/json.hpp>
#include <algorithm>
#include <clients/OpenFoodFactsClient.hpp>
#include <curl/curl.h>
#include <iostream>
#include <utils/HttpClient.hpp>
#include <vector>
namespace cc::clients {
    OpenFoodFactsClient::OpenFoodFactsClient(const std::string baseUrl ):baseUrl_(baseUrl){

  }

  cc::utils::Result<std::vector<cc::models::Food>> OpenFoodFactsClient::searchByName(const std::string& query, int page /*= 1*/, int pageSize /*= 10*/, const std::string& locale /*= "en"*/){
      if(curl_global_init(CURL_GLOBAL_DEFAULT)!=0){
          std::cerr<<"curl_global_init failed\n";
          // chouf chno t returni hna 
      }
      cc::utils::HttpClient http;
      http.setTimeoutMs(5000);

      auto r= http.getJson(this->baseUrl_+"/cgi/search.pl?search_terms="+query+"&search_simple=1&action=process&json=1");
      if(!r){
          std::cerr<<"GET failed: "<<r.unwrap_error().message<<"\n";
      }else{
        std::cout << "GET succeeded, body size = " << r.unwrap().size() << "\n";
        // std::cout << "Body: " << .dump(4) << "...\n";
        nlohmann::json j= nlohmann::json::parse(r.unwrap());
        auto nutriments= j.value("products",nlohmann::json::array())[0].at("nutriments");

        models::Nutrient p;
        p.setName("protein");
        p.setUnit(nutriments.at("proteins_unit"));
        p.setValue(nutriments.at("proteins"));

        models::Nutrient fat;
        fat.setName("fat");
        fat.setUnit(nutriments.at("fat_unit"));
        fat.setValue( nutriments.at("fat"));
        

        models::Nutrient carbs;
        carbs.setName("carbs");
        carbs.setUnit(nutriments.at("carbohydrates_unit"));
        carbs.setValue(nutriments.at("carbohydrates"));

            
        models::Food f;
        f.setName(query);
        std::vector<models::Nutrient> ns;
        ns.push_back(p);
        ns.push_back(fat);
        ns.push_back(carbs);
        f.setNutrients(ns);
        std::vector<cc::models::Food> list_of_foods{f,}; 
        return cc::utils::Result<std::vector<cc::models::Food>>::ok(std::move(list_of_foods));
      }
      
  }

  cc::utils::Result<cc::models::Food> getByBarcode(const std::string& barcode, const std::string& locale = "en"){
      models::Food f;
      f.setName("omlita");
      models::Food f2;
      f2.setName("eggs");
      return cc::utils::Result<cc::models::Food>::ok(std::move(f));
  }

  void setUserAgent(const std::string& ua){
      //todo tat3mrha mn b3de
  }

} // namespace cc::clients
