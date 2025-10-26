#pragma once
#include "models/food.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdint>
#include <nlohmann/json.hpp>

namespace cc::models {

enum class MEALNAME:uint8_t{
  Breakfast,
  Lunch,
  Dinner,
  Snack
}; // enum::MEALNAME
class MealLog {
private:
  MEALNAME name_{MEALNAME::Lunch};
  std::vector<std::pair<std::string,double>> food_items_; // foodId, grams
  double totalKcal_{0};
public:
  // constructors 
  MealLog()=default;
  MealLog(MEALNAME mealName,std::vector<std::pair<std::string,double>> food_items);
  // getters 
  MEALNAME getName() const;
  double totalKcal() const;
  std::vector<std::pair<std::string,double>> food_items() const;
  // setters 
  void setName(MEALNAME name){
      this->name_=name;
  }
  void setTotalKcal(double kcal){
      this->totalKcal_=kcal;
  }
  void setFoodItems(std::vector<std::pair<std::string,double>> food_items){
      this->food_items_=food_items;
  }
  // operations 
  void addFoodItem(const std::string& foodId, double grams);
  bool removeFoodItem(const std::string& foodId);
}; // MealLog
   inline void to_json(nlohmann::json &j,const cc::models::MealLog &m){
       j={
           {"name",m.getName()},
           {"totalKcal",m.totalKcal()},
           {"foodItems",m.food_items()}
       };
   }
   inline  void from_json(const nlohmann::json &j, cc::models::MealLog &m){
       m.setName(j.at("name").get<MEALNAME>());
       m.setTotalKcal(j.at("totalKcal").get<double>());
       m.setFoodItems(j.at("foodItems").get<std::vector<std::pair<std::string,double>>>());
   }
} // namespace cc::models
