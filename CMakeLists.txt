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

#add_subdirectory(extern)

# nlohmann-json ======================================================================================
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)
# SimpleIni ======================================================================================
find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")
target_include_directories(${TARGET_NAME} PRIVATE ${SIMPLEINI_INCLUDE_DIRS})

# set(TRANSLATIONS_DIR_NAME translations)
# set(TRANSLATIONS_DIR_PATH ${CMAKE_BINARY_DIR}/${TRANSLATIONS_DIR_NAME})

# if(NOT (EXISTS "${TRANSLATIONS_DIR_PATH}" AND IS_DIRECTORY "${TRANSLATIONS_DIR_PATH}"))
#     file(COPY translations DESTINATION "${CMAKE_BINARY_DIR}")
# endif()
