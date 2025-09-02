#include "models/food.hpp"
#include "models/meal_log.hpp"
#include "models/nutrient.hpp"
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <bits/stdc++.h>
#include "nlohmann/json.hpp"
#include "storage/JsonFoodRepository.hpp"
#include "storage/FoodRepository.hpp"
#include "utils/Result.hpp"
#include "utils/HttpClient.hpp"
#include "clients/OpenFoodFactsClient.hpp"
int main()
{
    // TODO: load config, init services, run server
    // basmati rice
    // cc::models::Food f = cc::models::Food();
    // f.setName("basmati Rice");
    // f.setId("reference");
    // f.setBrand("lala fatima");
    // f.setBarcode("xxxxxxxx");
    // f.setCaloriesPer100g(200);
    // std::cout<<"food :"<<f.name()<<std::endl;
    // std::cout<<"food :"<<f.name()<<std::endl;
    // #################################################
    // 1) Build some nutrients
    cc::models::Nutrient protein{"protein", 10.2, "g"}; // per 100g
    cc::models::Nutrient fat{"fat", 5.8, "g"};
    cc::models::Nutrient carbs{"carbohydrates", 42.0, "g"};
    cc::models::Nutrient sugar{"sugars", 12.0, "g"};
    cc::models::Nutrient salt{"salt", 0.8, "g"};

    // 2) Build a Food
    cc::models::Food f;
    f.setId("test-uuid-1234");
    f.setName("Granola Bar");
    f.setBrand(std::string("FooBrand"));
    f.setBarcode(std::string("7622210449283"));
    f.setCaloriesPer100g(420.0);
    f.setServingSizeG(40.0); // default serving size 40g
    f.setSource("manual");
    f.setImageUrl(std::string("https://example.com/granola.jpg"));

    // add nutrients (mutable access)
    std::vector<cc::models::Nutrient> temp_nutrients{protein, fat, carbs, sugar, salt};
    f.setNutrients(temp_nutrients);
    std::vector<std::pair<std::string,double>>v;
    std::pair<std::string,double>pair_anas={f.id(),f.servingSizeG().value()};
    v.push_back(pair_anas);
    cc::models::MealLog lunch(cc::models::MEALNAME::Lunch,v);
    nlohmann::json j = protein; 
    nlohmann::json food_json = f;
    nlohmann::json lunch_json = lunch;
    // std::cout<<food_json.dump(4)<<std::endl;
    // std::cout<<food_json.dump(4)<<std::endl;
    std::cout<<lunch_json.dump(4)<<std::endl;
    //cc::storage::JsonFoodRepository json_repo("~/serialize_food");
    //json_repo.save(f);
    //######################
    // you need to initialise always before start the use of httpclient
    if (curl_global_init(CURL_GLOBAL_DEFAULT) != 0) {
        std::cerr << "curl_global_init failed\n";
        return 1;
    }

    cc::utils::HttpClient http;
    http.setTimeoutMs(5000);

    // 1) Basic GET
    auto r_temp = http.get("https://httpbin.org/get");
    if (!r_temp) {
        std::cerr << "GET failed: " << r_temp.unwrap_error().message << "\n";
    } else {
        std::cout << "GET succeeded, body size = " << r_temp.unwrap().size() << "\n";
        std::cout << "Body: " << r_temp.unwrap().substr(0, 200) << "...\n";
    }

    // 2) Redirect test
    auto r2_temp = http.get("http://httpbin.org/redirect/1");
    if (!r2_temp) {
        std::cerr << "Redirect failed: " << r2_temp.unwrap_error().message << "\n";
    } else {
        std::cout << "Redirect ok, body size = " << r2_temp.unwrap().size() << "\n";
    }

    // 3) Error test (404)
    auto r3_temp = http.get("https://httpbin.org/status/404");
    if (!r3_temp) {
        std::cout << "Correctly got error on 404: " << r3_temp.unwrap_error().message << "\n";
    } else {
        std::cerr << "Unexpected success for 404!\n";
    }
    // test json 
    auto temp = http.getJson("https://httpbin.org/json");
    if(!temp){
        std::cerr<<"getJson failed: "<<temp.unwrap_error().message<<"\n";
    }else{
        std::cout<<"JSON BODY"<<temp.unwrap().substr(0,200)<<"\n";
    }

    curl_global_cleanup();
    // at the end always cleanup with this function .
    // #######################################################
    std::string searched_item{"milk"};
    std::cout<<"search for "<<searched_item<<std::endl;
    cc::clients::OpenFoodFactsClient openfoodfactsclient{}; 
    auto result = openfoodfactsclient.searchByName(searched_item.c_str());
    if(result){
        auto items = result.unwrap();
        std::cout<<"numbers for 100g"<<std::endl;
        for(auto i : items){
            std::cout<<i.name()<<std::endl;
            if(i.nutrients().empty()){
                std::cout<<"nutrients is empty"<<std::endl;
            }
          
            for(auto n:i.nutrients()){
                std::cout<<n.name()<<" : "<<n.value()<<" "<<n.unit()<<std::endl;
            }
        }
    }

    /// ##############################
    /// 

    std::string barcode{"737628064502"};
    std::cout<<"#########################"<<std::endl;
    std::cout<<"TEST barcode"<<std::endl;
    std::cout<<"#########################"<<std::endl;
    auto result_barcode = openfoodfactsclient.getByBarcode(barcode);
    
    cc::models::Food food_barcode;
    if(result_barcode){
      food_barcode = result_barcode.unwrap(); 
            if(food_barcode.nutrients().empty()){
                std::cout<<"nutrients is empty"<<std::endl;
            }
            for(auto n:food_barcode.nutrients()){
                std::cout<<n.name()<<" : "<<n.value()<<" "<<n.unit()<<std::endl;
            }
    }

    // ############ json save ####################################
    
    cc::storage::JsonFoodRepository jsonFoodRepository("/home/anas/personal_projects/calorie-counter-backend/json_data_base.json");
    jsonFoodRepository.save(food_barcode);


    // ############ get by id from data base(json for now ) ##########
    std::cout<<"testing get by id from data base (json for now )"<<std::endl;
    jsonFoodRepository.getById("0737628064502");
    // ################################# test result #############
    auto r1 = cc::utils::Result<int>::ok(123);
    if (r1)
    {
        int x = r1.unwrap();
        std::cout<<"x : "<<x<<std::endl;
    }

    auto r2 = cc::utils::Result<int>::fail(cc::utils::ErrorCode::ParseError, "bad json");
    if (!r2)
    {
        auto &e = r2.unwrap_error();
    }

    auto r3 = cc::utils::Result<void>::ok();
    auto r4 = cc::utils::Result<void>::fail(cc::utils::ErrorCode::StorageError, "disk full");
    //////////////////////////////////////////////////////////////////
    return 0;
}
