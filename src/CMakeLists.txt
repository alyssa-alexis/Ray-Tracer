# CMakeList.txt : CMake project for CMakeProject3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.30)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (SDL2-RT LANGUAGES CXX)

set(QB_PATH "${CMAKE_SOURCE_DIR}/qbLinAlg-main")

file(GLOB_RECURSE HPPS "${QB_PATH}/*.h")
file(GLOB_RECURSE HPPS "${QB_PATH}/*.hpp")
file(GLOB_RECURSE CPPS "${QB_PATH}/*.cpp")

find_package(SDL2 REQUIRED)


# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${CPPS} ${HPPS} "main.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${QB_PATH})
target_link_libraries(SDL2-RT ${SDL2_LIBRARIES})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDL2-RT PROPERTY CXX_STANDARD 17)
endif()