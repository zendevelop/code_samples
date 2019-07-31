# This a comment
cmake_minimum_required(VERSION 3.12)

project(script_basic VERSION 1.0.0)
# all vaiable is string, so below line is same as above
#project("script_basic" "VERSION" "1.0.0")

set( MY_VARIABLE "I am a variable!" )
message( STATUS "show message in ${PROJECT_NAME}, version: ${PROJECT_VERSION} ")
message( STATUS "MY_VARIABLE value is : ${MY_VARIABLE}")