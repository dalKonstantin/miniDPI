# ============
# LOGGER LIB
# ============
add_library(logger_lib
  log/logger.cpp)

target_include_directories(logger_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_library(${PROJECT_NAME}::logger_lib ALIAS logger_lib)

# ============
# CORE LIB
# ============
add_library(core_lib
  core/ring_buffer.cpp
)

target_include_directories(core_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_library(${PROJECT_NAME}::core_lib ALIAS core_lib)

# ============
# EXECUTABLE
# ============
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
  miniDPI::logger_lib
  miniDPI::core_lib
)
