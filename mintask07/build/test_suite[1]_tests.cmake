add_test( Test0.Test0 /home/natalia/programmingCplusplus/mintask07/build/test_suite [==[--gtest_filter=Test0.Test0]==] --gtest_also_run_disabled_tests)
set_tests_properties( Test0.Test0 PROPERTIES WORKING_DIRECTORY /home/natalia/programmingCplusplus/mintask07/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( test_suite_TESTS Test0.Test0)
