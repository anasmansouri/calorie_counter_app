# Add a static library target 
add_library(${PROJECT_NAME_VAR} STATIC server.cpp)

#set the public include directory for this target 
target_include_directories(${PROJECT_NAME_VAR} PUBLIC 
        ${CMAKE_SOURCE_DIR}/include)
