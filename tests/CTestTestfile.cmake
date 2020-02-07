# CMake generated Testfile for 
# Source directory: /net/cremi/vho/PL3-IUG-Grp8/tests
# Build directory: /net/cremi/vho/PL3-IUG-Grp8/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("create_window" "/net/cremi/vho/PL3-IUG-Grp8/tests/unit_tests" "create_window" "--durations" "yes" "--warn" "NoAssertions" "--name" "unit_tests ( build)")
set_tests_properties("create_window" PROPERTIES  FAIL_REGULAR_EXPRESSION "No tests ran" LABELS ";unit;" TIMEOUT "10")
add_test("fill_window" "/net/cremi/vho/PL3-IUG-Grp8/tests/unit_tests" "fill_window" "--durations" "yes" "--warn" "NoAssertions" "--name" "unit_tests ( build)")
set_tests_properties("fill_window" PROPERTIES  FAIL_REGULAR_EXPRESSION "No tests ran" LABELS ";unit;" TIMEOUT "10")
