cmake_minimum_required(VERSION 3.20.0)
project(Server VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(CTest)
enable_testing()

add_executable(Server main.cpp User.cpp UserDB.cpp)
target_link_libraries(Server PRIVATE pqxx pq)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
