#pragma once
#include<string>
#include <optional>
#include <vector>
#include<chrono>
#include"models/nutrient.hpp"
#include <nlohmann/json.hpp>
namespace cc::models{

// Represents a single food item 
class Food{
public:
    Food()=default;
    Food(std::string id_ ,
            std::string name_,
            double caloriesPer100g_,
            std::vector<Nutrient> nutrient_,
            std::optional<double> servingSizeG_,
            std::optional<std::string> barcode_,
            std::optional<std::string> brand_,
            std::optional<std::string> imageUrl_);


  std::string to_string()const;
      // IDs & identity
  const std::string& id() const;
  void setId(std::string id);

  const std::string& name() const;
  void setName(std::string n);

  const std::optional<std::string>& brand() const;
  void setBrand(std::optional<std::string> b);

  const std::optional<std::string>& barcode() const;
  void setBarcode(std::optional<std::string> b);

  // nutrition
  double caloriesPer100g() const;
  void setCaloriesPer100g(double kcal);

  double totalKcal()const ; // it is a getter and not const while i need to calculate totalKcal before i give it back 
                       // no need to implement setter

  const std::optional<double>& servingSizeG() const;
  void setServingSizeG(std::optional<double> g);

  const std::vector<Nutrient>& nutrients() const;
  // std::vector<Nutrient>& nutrients();              // mutable access (for building)
  void setNutrients(std::vector<Nutrient> ns);

  // media/source
  const std::optional<std::string>& imageUrl() const;
  void setImageUrl(std::optional<std::string> url);

  const std::string& source() const;               // "off" | "manual" | ...
  void setSource(std::string s);

  // update totalKcal
  void update_totalKcal();

private:
    std::string id_;
    std::string name_;
    double totalKcal_{0.0};
    double caloriesPer100g_{0.0};
    std::vector<Nutrient> nutrients_;
    std::optional<double> servingSizeG_;
    std::optional<std::string> barcode_;
    std::optional<std::string> brand_;
    std::optional<std::string> imageUrl_;
    std::string source_{"manual"};
};// Food
inline void  to_json(nlohmann::json &j, const cc::models::Food &f){
    j={
        {"id",f.id()},
        {"name",f.name()},
        // {"totalKcal",f.totalKcal()},
        {"caloriesPer100g",f.caloriesPer100g()},
        {"nutrient",f.nutrients()},
        {"servingSizeG",f.servingSizeG()},
        {"barcode",f.barcode()},
        {"brand",f.barcode()},
        {"imageUrl",f.imageUrl()},
        {"source",f.source()}
       };
}

inline void from_json(const nlohmann::json &j,cc::models::Food &f){
    f.setId(j.at("id").get<std::string>());
    f.setName(j.at("name").get<std::string>());
    f.setCaloriesPer100g(j.at("caloriesPer100g").get<double>());
    f.setNutrients(j.at("nutrient").get<std::vector<cc::models::Nutrient>>());
    f.setServingSizeG(j.at("servingSizeG").get<std::optional<double>>().value());
    f.setBarcode(j.at("barcode").get<std::optional<std::string>>().value());
    f.setBrand(j.at("brand").get<std::optional<std::string>>().value());
    f.setImageUrl(j.at("imageUrl").get<std::string>());
    f.setSource(j.at("source").get<std::string>());
}
  
} // namespace cc::models
