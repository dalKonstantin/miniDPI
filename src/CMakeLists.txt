# ============
# LOGGER LIB
# ============
add_library(logger_lib
  log/logger.cpp)

target_include_directories(logger_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_library(${PROJECT_NAME}::logger_lib ALIAS logger_lib)

# ============
# EXECUTABLE
# ============
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
  miniDPI::logger_lib
)
