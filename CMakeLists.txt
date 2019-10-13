cmake_minimum_required(VERSION 3.11)

project(indie_studio LANGUAGES CXX)

file(GLOB_RECURSE all LIST_DIRECTORIES true src/*)

file(GLOB_RECURSE source_files src/*.cpp)

file(GLOB_RECURSE header_files src/*.hpp)

foreach (file ${all})
  get_filename_component(dir ${file} DIRECTORY)
  list(APPEND include_dirs ${dir})
endforeach()

list(REMOVE_DUPLICATES include_dirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/irrlicht")

include(FindIrrlicht)

include_directories(${PROJECT_SOURCE_DIR}/irrlicht/include ${include_dirs})

link_directories(${Irrlicht_LIBRARIES})

add_executable(bomberman ${source_files} ${header_files})

find_package(SFML 2.5 COMPONENTS audio REQUIRED)

target_link_libraries(bomberman Irrlicht sfml-audio)

