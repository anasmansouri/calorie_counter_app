#pragma once
#include "models/meal_log.hpp"
#include "models/food.hpp"
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

namespace cc::models
{

    MealLog::MealLog(MEALNAME name) : name_{name}
    {
        this->id_tsUtc_ = std::chrono::system_clock::now();
    }
    MEALNAME MealLog::getName() const
    {
        return this->name_;
    }
    void MealLog::setName(MEALNAME name)
    {
        this->name_ = name;
    }

    double MealLog::totalKcal() const
    {
        double sum{0};
        for (auto it = this->food_items_.begin(); it != this->food_items_.end(); ++it)
        {
            // sum+=it->second.totalKcal;
        }
        return sum;
    }
    std::chrono::system_clock::time_point MealLog::id() const
    {
        return this->id_tsUtc_;
    }

    void MealLog::setId(std::chrono::system_clock::time_point id_tsUtc_){
        this->id_tsUtc_ = id_tsUtc_;
    }
    void MealLog::setFoodItems(std::vector<std::pair<std::string, double>> food_items)
    {
        this->food_items_ = food_items;
        for (auto food_item : this->food_items_)
        {
            //
        }
    }

    std::vector<std::pair<std::string, double>> MealLog::food_items() const
    {
        return this->food_items_;
    }
    // operations
    void MealLog::addFoodItem(const std::string &foodId, double grams)
    {
        this->food_items_.push_back({foodId, grams});
    }
    bool MealLog::removeFoodItem(const std::string &foodId)
    {
        for (auto it = this->food_items_.begin(); it != this->food_items_.end(); it++)
        {
            if (it->first == foodId)
            {
                this->food_items_.erase(it);
                // maybe you need to remove it from the data base
                return true;
            }
        }
        return false;
    }
} // namespace cc::models
