cmake_minimum_required(VERSION 3.25)

project(tr-and-slate-or)

set(TARGET_NAME trandslateor)

add_library(
    ${TARGET_NAME}
    src/TranslationManager.cpp
    src/FileManager.cpp
    )

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)

target_include_directories(${TARGET_NAME} PUBLIC include)

add_subdirectory(extern)

target_link_libraries(${TARGET_NAME} PUBLIC nlohmann_json)
target_link_libraries(${TARGET_NAME} PUBLIC SimpleIni)

#file(COPY translations DESTINATION "${CMAKE_BINARY_DIR}")
