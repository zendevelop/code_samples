cmake_minimum_required(VERSION 3.12)

project(ControlFlow VERSION 1.0.0)

# bool condition
set(my_bool TRUE)

if(my_bool)
    message( STATUS "my condition met")
else()
    message( STATUS "my condition met fail")
endif()

# string compare condition
set(my_string "this is a string")
set(my_other_string "this is another string")

if( my_string STREQUAL my_other_string)
    message( STATUS "strings are the same")
else()
    message( STATUS "strings are different")
endif()
# if( NOT (my_string STREQUAL my_other_string))
# if( cond_a AND cond_b)

# while & math operation
set(my_value 4)

while(my_value LESS 10)
    message(STATUS "value is ${my_value}")
    math(EXPR my_value "${my_value} + 1")
endwhile()

# foreach
foreach( item IN ITEMS foo bar baz qux )
    message( STATUS "Item is ${item}")
endforeach()

foreach( idx RANGE 10 )
    message( STATUS "idx is ${idx}" )
endforeach()

foreach( idx RANGE 3 10 2 )     # RANGE start end step
    message( STATUS "idx is ${idx}")
endforeach()