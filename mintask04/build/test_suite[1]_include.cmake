if(EXISTS "/home/natalia/programmingCplusplus/mintask04/build/test_suite[1]_tests.cmake")
  include("/home/natalia/programmingCplusplus/mintask04/build/test_suite[1]_tests.cmake")
else()
  add_test(test_suite_NOT_BUILT test_suite_NOT_BUILT)
endif()
