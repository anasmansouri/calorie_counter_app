#include "FoodService.hpp"
#include "models/food.hpp"

namespace cc
{
    namespace services
    {

        // TODO: implement your classes/functions here
        FoodService::FoodService(std::shared_ptr<cc::storage::FoodRepository> repo,
                                 std::shared_ptr<cc::clients::OpenFoodFactsClient> off) : repo_{repo}, off_{off}

        {
        }

        cc::utils::Result<cc::models::Food> FoodService::getOrFetchByBarcode(const std::string &bardcode)
        {
            cc::utils::Result<cc::models::Food> f;
            f = this->repo_->getById_or_Barcode(bardcode);
            if (f)
            {
                return f;
            }
            else
            {
                f = this->off_->getByBarcode(bardcode);
                if (f)
                {
                    return f;
                }
            }
            return cc::utils::Result<cc::models::Food>::ok(cc::models::Food{});
        }

        // zed der les cas , bach thkam l program 
        cc::utils::Result<void> FoodService::addManualFood(const cc::models::Food &food){
            this->repo_->save(food);
            return cc::utils::Result<void>::ok();
        }
    } // namespace services
} // namespace cc
