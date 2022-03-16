# List the name of the source file you need to test
# For ex: src/bi_array.cpp, should have an equivalent
# this is for bi_array_test.cpp file 
set(UNIT_TEST_LIST 
  key_value) # this is for    src/key_value.cpp[.h] files 

#
######## No need to modify anything below this point
#

# Create a list (UNIT_TEST_SOURCE_LIST) of all the test files. This list 
# is based on the list of source files (UNIT_TEST_LIST) from above
foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST ${NAME}_test.cpp)
endforeach()

set(TARGET_NAME main_test)
set(LIB_NAME mylib)      # lib name, this should match the $LIB_NAME from src/CMakeList.txt file
# This will create your testing file. In this case I used the
# ca1_test as the name for the unit test executable file.
add_executable(${TARGET_NAME} ${UNIT_TEST_SOURCE_LIST})
# The name of the lib, must match given to it in the  src/ folder 
target_link_libraries(${TARGET_NAME}
  PUBLIC ${LIB_NAME})

# Include 3rd party libraries
target_include_directories(${TARGET_NAME}
  PUBLIC ../externals/catch2/)

# define test
add_test(
  NAME catch_test
  COMMAND $<TARGET_FILE:${TARGET_NAME}> --success
  )