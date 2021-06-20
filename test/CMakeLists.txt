add_executable(test_edge Edge/test_orientation.cpp)
target_link_libraries(test_edge geoledic-core
                                GTest::gtest
                                GTest::gtest_main)
gtest_discover_tests(test_edge)

add_executable(test_triangle triangle/common-test-helpers.cpp
                             triangle/test_edges.cpp
                             triangle/test_orientation.cpp)
target_link_libraries(test_triangle geoledic-core
                                    GTest::gtest
                                    GTest::gtest_main)
gtest_discover_tests(test_triangle)
