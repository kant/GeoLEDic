add_executable(test_geometry geometry/test_Edge.cpp)
target_link_libraries(test_geometry geoledic-core
                                    GTest::gtest
                                    GTest::gtest_main)
gtest_discover_tests(test_geometry)
