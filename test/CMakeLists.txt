add_executable(test_edge Edge/test_orientation.cpp)
target_link_libraries(test_edge geoledic-core
                                GTest::gtest
                                GTest::gtest_main)
gtest_discover_tests(test_edge)

add_executable(test_notes Notes/test_notes.cpp
                          Notes/test_decaying_notes.cpp)
target_link_libraries(test_notes geoledic-core
                                GTest::gtest
                                GTest::gtest_main)
gtest_discover_tests(test_notes)

add_executable(test_triangle Triangle/common-test-helpers.cpp
                             Triangle/test_edges.cpp
                             Triangle/test_geometry.cpp
                             Triangle/test_orientation.cpp
                             Triangle/test_orientation_errors.cpp)
target_link_libraries(test_triangle geoledic-core
                                    GTest::gtest
                                    GTest::gtest_main)
gtest_discover_tests(test_triangle)

add_executable(test_vertex Vertex/test_angles.cpp)
target_link_libraries(test_vertex geoledic-core
                                GTest::gtest
                                GTest::gtest_main)
gtest_discover_tests(test_vertex)

add_executable(test_vector Vector/test_vector.cpp)
target_link_libraries(test_vector geoledic-core
                                GTest::gtest
                                GTest::gtest_main)
gtest_discover_tests(test_vector)
