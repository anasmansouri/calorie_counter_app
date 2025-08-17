- Barcode lookup
#######################################################################
HTTP GET /foods/barcode/:code
  ↓
Server → FoodService::getOrFetchByBarcode(barcode)
  ↓
FoodRepository::getByBarcode(barcode)
  ├─ found → return Result<Food>::ok
  └─ not found →
         OpenFoodFactsClient::getByBarcode(barcode)
           ├─ network/parse error → Result::fail(NetworkError/ParseError)
           └─ success (Food)
                ↓
                FoodRepository::save(Food)
                ↓
                return Food
  ↓
Server maps Result to HTTP:
  ok → 200 + Food JSON
  fail(NotFound) → 404
  fail(NetworkError/ParseError/StorageError) → 502/500

- Search by name
#####################################################################
HTTP GET /foods/search?q=...&limit=10
  ↓
Server → FoodService::searchPreferLocalThenOff(name, limit)
  ↓
FoodRepository::list/filter (or dedicated search)
  ├─ enough results → return
  └─ else →
        OpenFoodFactsClient::searchByName(...)
        parse → vector<Food>
        (optional) upsert into repository
        return merged results
  ↓
Server → 200 + JSON array

- Add a manual food
###################################################################
HTTP POST /foods (JSON)
  ↓
Server validates → to Food (JsonParser::fromJson)
  ↓
FoodService::addManualFood(food)
  ↓
- validate required fields (name, kcal/100g)
- check conflicts (same barcode already exists?)
- repository.save(food)
  ↓
Server → 201 Created or 409 Conflict / 400 InvalidInput

- List foods
##################################################################
HTTP GET /foods?offset=&limit=
  ↓
FoodService::listFoods(offset, limit)
  ↓
FoodRepository::list(offset, limit)
  ↓
Server → 200 + JSON
