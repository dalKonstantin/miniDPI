add_lib(logger_lib
  log/logger.cpp)

target_include_directories(logger_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
