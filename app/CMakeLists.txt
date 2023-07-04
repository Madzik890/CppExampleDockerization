cmake_minimum_required(VERSION 3.8)

project(WebService)

set(CMAKE_CXX_STANDARD 20)

#find_package(OpenSSL REQUIRED)
#target_link_libraries(PriceSniffer OpenSSL::SSL)

file(GLOB WebService_src CONFIGURE_DEPENDS "src/*.hpp" "src/*.cpp" "src/*/*.hpp" "src/*/*.cpp" "src/*/*/*.hpp" "src/*/*/*.cpp" "src/*/*/*/*.hpp" "src/*/*/*/*.cpp" "src/*/*/*/*/*.hpp" "src/*/*/*/*/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/libs/cpp-httplib)


add_executable(WebService ${WebService_src})
target_link_libraries(WebService -lpthread)

