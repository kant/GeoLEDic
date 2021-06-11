add_executable(test_triangle triangle/test_orientation.cpp)
target_link_libraries(test_triangle geoledic-core
                                    GTest::gtest
                                    GTest::gtest_main)
gtest_discover_tests(test_triangle)
