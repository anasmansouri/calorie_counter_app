#pragma once
#include "models/food.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstdint>
#include <nlohmann/json.hpp>
#include "utils/date_time_utils.hpp"

namespace cc::models
{

  enum class MEALNAME : uint8_t
  {
    Breakfast,
    Lunch,
    Dinner,
    Snack
  }; // enum::MEALNAME
  class MealLog
  {
  private:
    std::chrono::system_clock::time_point id_tsUtc_;
    MEALNAME name_{MEALNAME::Lunch};
    std::vector<std::pair<std::string, double>> food_items_; // foodId, grams
    double totalKcal_{0};

  public:

    // constructors
    MealLog() = default;
    // MealLog(MEALNAME mealName,std::vector<std::pair<std::string,double>> food_items);
    MealLog(MEALNAME mealName);

    // setters
    void setName(MEALNAME name);
    void setId(std::chrono::system_clock::time_point id_tsUtc_);
    // void setTotalKcal(double kcal){
    // this->totalKcal_=kcal;
    // }
    
    // getters
    MEALNAME getName() const;
    void setFoodItems(std::vector<std::pair<std::string, double>> food_items);
    std::chrono::system_clock::time_point id() const;
    double totalKcal() const;
    std::vector<std::pair<std::string, double>> food_items() const;
    // operations
    void addFoodItem(const std::string &foodId, double grams);
    bool removeFoodItem(const std::string &foodId);
  }; // MealLog
  inline void to_json(nlohmann::json &j, const cc::models::MealLog &m)
  {
    j = {
        {"name", m.getName()},
        {
            "foodItems",
            m.food_items(),
        },
        {"id", cc::utils::toIso8601(m.id())}};
  }
  inline void from_json(const nlohmann::json &j, cc::models::MealLog &m)
  {
    m.setId(m.id());
    m.setName(j.at("name").get<MEALNAME>());
    // m.setTotalKcal(j.at("totalKcal").get<double>());
    m.setFoodItems(j.at("foodItems").get<std::vector<std::pair<std::string, double>>>());
  }
} // namespace cc::models
