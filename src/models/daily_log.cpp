#pragma once
#include "models/daily_log.hpp"
#include "meal_log.hpp"
#include <algorithm>
#include <vector>

namespace cc::models
{

  DailyLog::DailyLog(std::chrono::system_clock::time_point tsUtc) : tsUtc_{tsUtc} {}
  void DailyLog::addMeal(const MealLog &meal) { this->meals_.push_back(meal); }
  double DailyLog::totalKcal() const
  {
    double sum_of_calories{0};
    // std::ranges::for_each(this->meals_, [&sum_of_calories](auto &meal)
                          // { sum_of_calories += meal.totalKcal(); });
    return sum_of_calories;
  }

  void DailyLog::addMeals(const std::vector<MealLog> meals)
  {
    this->meals_ = meals;
  }

  std::vector<MealLog> DailyLog::meals() const { return this->meals_; }
} // namespace cc::models
