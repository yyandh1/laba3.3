cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта
project(Test)

# Включаем поддержку C++14
set(CMAKE_CXX_STANDARD 14)

# Найдем GoogleTest (предполагаем, что его уже установили на вашей системе)
find_package(GTest REQUIRED)

# Включаем директорию для исходников
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

# Создаем исполнимый файл для тестов
add_executable(stack_test stack_test.cpp)
add_executable(hashtable_test hashtable_test.cpp)
add_executable(List1_test List1_test.cpp)
add_executable(List2_test List2_test.cpp)
add_executable(array_test massive_test.cpp)
add_executable(queue_test queue_test.cpp)
add_executable(tree_test tree_test.cpp)

# Подключаем библиотеку GoogleTest
target_link_libraries(stack_test ${GTEST_LIBRARIES} pthread)
target_link_libraries(hashtable_test ${GTEST_LIBRARIES} pthread)
target_link_libraries(List1_test ${GTEST_LIBRARIES} pthread)
target_link_libraries(List2_test ${GTEST_LIBRARIES} pthread)
target_link_libraries(array_test ${GTEST_LIBRARIES} pthread)
target_link_libraries(queue_test ${GTEST_LIBRARIES} pthread)
target_link_libraries(tree_test ${GTEST_LIBRARIES} pthread)

# Включаем поддержку покрытия (использование gcov)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} --coverage")

# Настройка для использования CTest
enable_testing()

# Добавляем тесты
add_test(NAME StackTest COMMAND stack_test)
add_test(NAME HashtableTest COMMAND hashtable_test)
add_test(NAME List1Test COMMAND List1_test)
add_test(NAME List2Test COMMAND List2_test)
add_test(NAME ArrayTest COMMAND array_test)
add_test(NAME QueueTest COMMAND queue_test)
add_test(NAME TreeTest COMMAND tree_test)

# Настроим отчет покрытия в формате HTML
# Для этого добавляем шаг для генерации отчетов с использованием gcovr
find_program(GCOVR_EXECUTABLE gcovr)

if(GCOVR_EXECUTABLE)
    add_custom_target(
        coverage
        COMMAND ${GCOVR_EXECUTABLE} -r ${CMAKE_SOURCE_DIR} --html --html-details -o coverage_report.html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating HTML coverage report"
    )
endif()

# Если вы хотите создать отчет в формате lcov:
find_program(LCOV_EXECUTABLE lcov)

if(LCOV_EXECUTABLE)
    add_custom_target(
        lcov_report
        COMMAND ${LCOV_EXECUTABLE} --capture --directory . --output-file coverage.info
        COMMAND ${LCOV_EXECUTABLE} --remove coverage.info '/usr/*' '*/test/*' --output-file coverage_filtered.info
        COMMAND ${LCOV_EXECUTABLE} --list coverage_filtered.info
        COMMAND genhtml coverage_filtered.info --output-directory out
        COMMENT "Generating lcov coverage report"
    )
endif()
