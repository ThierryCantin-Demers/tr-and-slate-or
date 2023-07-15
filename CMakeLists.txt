cmake_minimum_required(VERSION 3.25)

project(tr-and-slate-or)

add_executable(
    ${PROJECT_NAME}
    src/TranslationManager.cpp
    src/FileManager.cpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(extern)

target_link_libraries(${PROJECT_NAME} PUBLIC json)
target_link_libraries(${PROJECT_NAME} PUBLIC simpleini)