# Utils module
add_library(cc_utils
    utils/Result.hpp utils/Result.cpp
    utils/HttpClient.hpp utils/HttpClient.cpp
    utils/Json.hpp
)
target_include_directories(cc_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Models module
add_library(cc_models
    models/food.hpp models/food.cpp
    models/nutrient.hpp models/nutrient.cpp
    models/meal_log.hpp models/meal_log.cpp
    models/daily_log.hpp models/daily_log.cpp
    models/DTOs.hpp
)
target_include_directories(cc_models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Clients module
add_library(cc_clients
    clients/OpenFoodFactsClient.cpp clients/OpenFoodFactsClient.hpp
)

# libcurl library 
find_package(CURL REQUIRED)
#target_include_directories(cc_clients PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(cc_clients PRIVATE ${CURL_LIBRARIES})

target_include_directories(cc_clients PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cc_clients PRIVATE cc_utils)

# Storage module
add_library(cc_storage
    storage/FoodRepository.hpp
    storage/JsonFoodRepository.cpp storage/JsonFoodRepository.hpp
    storage/SqliteFoodRepository.cpp storage/SqliteFoodRepository.hpp
)
target_include_directories(cc_storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cc_storage PUBLIC cc_models cc_utils)

# Services module
add_library(cc_services
    services/FoodService.cpp services/FoodService.hpp
    services/AuthService.cpp services/AuthService.hpp
    services/UserService.cpp services/UserService.hpp
)
target_include_directories(cc_services PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cc_services PUBLIC cc_storage cc_clients cc_models cc_utils)

# API module
add_library(cc_api
    api/Server.cpp api/Server.hpp
)
target_include_directories(cc_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cc_api PUBLIC cc_services cc_utils)

# Main executable
add_executable(cc_app main.cpp)
#target_link_libraries(cc_app PRIVATE cc_api ${CURL_LIBRARIES})
target_link_libraries(cc_app PRIVATE cc_api)
#target_link_libraries(cc_app PRIVATE cc_models)
