cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

set(PROJECT_NAME Prim_MST)
project(${PROJECT_NAME})
set(SOURCES_CC
	src/MST.cc
)
set_source_files_properties(${SOURCES_CC} COMPILE_FLAGS "")
add_executable(${PROJECT_NAME} ${SOURCES_CC})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(	TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/test $<TARGET_FILE_DIR:${PROJECT_NAME}>/test
					)