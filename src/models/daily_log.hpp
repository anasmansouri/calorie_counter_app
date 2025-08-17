#pragma once
#include <vector>
#include "meal_log.hpp"
#include <nlohmann/json.hpp>

namespace cc::models {

class DailyLog {
public:
  void addMeal(const MealLog& meal);
  void addMeals(const std::vector<MealLog> meals);
  void setTotalKcal(double kcal);
  //getters
  std::vector<MealLog> meals() const;
  double totalKcal() const;


private:
  std::vector<MealLog> meals_;
};

inline void to_json(nlohmann::json &j,const cc::models::DailyLog &d){
    j={
        {"meals",d.meals()},
    };
}

inline void from_json(const nlohmann::json &j,cc::models::DailyLog &d){
    d.addMeals(j.at("meals").get<std::vector<MealLog>>());
}

} // namespace cc::models
