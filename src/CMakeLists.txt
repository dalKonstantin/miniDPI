# ============
# LOGGER LIB
# ============
add_library(logger_lib
  log/logger.cpp)

target_include_directories(logger_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_library(${PROJECT_NAME}::logger_lib ALIAS logger_lib)

# ============
# CLI11
# ============
add_library(CLI11 INTERFACE)
target_include_directories(CLI11 INTERFACE ${CMAKE_SOURCE_DIR}/third_party/CLI11/include)
add_library(${PROJECT_NAME}::CLI11 ALIAS CLI11)

# ============
# CORE LIB
# ============
add_library(core_lib
  core/ring_buffer.cpp
  core/sniffer.cpp
)
target_link_libraries(core_lib PRIVATE ${PROJECT_NAME}::CLI11 ${PCAP_LIBRARIES})

target_include_directories(core_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
add_library(${PROJECT_NAME}::core_lib ALIAS core_lib)

# ============
# EXECUTABLE
# ============
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${PROJECT_NAME}::logger_lib
  ${PROJECT_NAME}::core_lib
  ${PROJECT_NAME}::CLI11
  ${PCAP_LIBRARIES}
)
