add_executable(test_edge Edge/test_orientation.cpp)
target_link_libraries(test_edge geoledic-core
                                GTest::gtest
                                GTest::gtest_main)
gtest_discover_tests(test_edge)

add_executable(test_triangle Triangle/common-test-helpers.cpp
                             Triangle/test_edges.cpp
                             Triangle/test_orientation.cpp
                             Triangle/test_orientation_errors.cpp)
target_link_libraries(test_triangle geoledic-core
                                    GTest::gtest
                                    GTest::gtest_main)
gtest_discover_tests(test_triangle)
