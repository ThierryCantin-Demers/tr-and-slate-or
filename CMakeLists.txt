cmake_minimum_required(VERSION 3.25)

project(tr-and-slate-or)

set(TARGET_NAME trandslateor)

add_library(
    ${TARGET_NAME}
    src/TranslationManager.cpp
    src/FileManager.cpp
    )

if(MSVC)
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(${TARGET_NAME} PUBLIC include)

include(cmake/CPM.cmake)

# nlohmann-json ======================================================================================
if(NOT TARGET nlohmann_json::nlohmann_json)
    CPMFindPackage(
    NAME          "nlohmann_json"
    VERSION       "3.11.2"
    GITHUB_REPOSITORY "nlohmann/json"
    )
endif()

target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)
# ====================================================================================================

# SimpleIni ==========================================================================================
if(NOT TARGET SimpleIni)
    CPMFindPackage(
    NAME          "SimpleIni"
    VERSION       "4.20"
    GITHUB_REPOSITORY "brofield/simpleini"
    )
endif()

target_link_libraries(${TARGET_NAME} PRIVATE SimpleIni)
# ====================================================================================================
