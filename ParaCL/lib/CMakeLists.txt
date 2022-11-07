
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

set(PROJECT_NAME ParaCL)
project(${PROJECT_NAME})

find_package(BISON)
find_package(FLEX)
BISON_TARGET(MyParser compiler.y ${CMAKE_CURRENT_SOURCE_DIR}/compiler.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/compiler.cpp.h  )
message(STATUS ${BISON_MyParser_OUTPUTS})

FLEX_TARGET(MyScanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)
message(STATUS ${FLEX_MyScanner_OUTPUTS})
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

 include_directories(${CMAKE_CURRENT_BINARY_DIR})
 add_executable(${PROJECT_NAME}
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
    error.cpp
    Node.cpp
 )
 target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
 target_link_libraries(${PROJECT_NAME} ${FLEX_LIBRARIES})

set(OUT_DIR ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})

