cmake_minimum_required(VERSION 3.12)

project( fun VERSION 1.0.0 )

set_property(
    GLOBAL
    PROPERTY FOO
    1
    2
    3
)

get_cmake_property( foo_value FOO )
message( STATUS "value of FOO is: ${foo_value}" )

# set variable
set( my_list 1 2 3)
set( target DIRECTORY )
set_property(
    "${target}"
    PROPERTY FOO1
    ${my_list}
)

get_property( foo_value1 "${target}" PROPERTY FOO1 )
message( STATUS "value of FOO is: ${foo_value1}" )

# list expansion character
# if with quote, cmake try to join the list with ;
# so in order to keep the original shape, should do not ref variable with quote
set( target DIRECTORY "${PROJECT_SOURCE_DIR}")
set_property(
    ${target}   # here, should without quote, or will error
    PROPERTY FOO
    ${my_list}
)

get_property( foo_value ${target} PROPERTY FOO )    # here, ${target} without quote also
message( STATUS "value of FOO is: ${foo_value}")

# function
# ARGN is the remain params without name, the ARGV is the total params
function(fun first_arg second )
    foreach( arg IN LISTS ARGN )
        message( STATUS "arg: ${arg}")
    endforeach()
    
    foreach( arg IN LISTS ARGV )
        message( STATUS "arg: ${arg}" )
    endforeach()
endfunction(fun first_arg second )

fun( 1 2 3 4 5 )

# param in function will do a copy for the global variable
# so modify in function will not change the global variable default, if you specify the `PARENT_SCOPE`
set( global_var0 1)
set( global_var1 1)

function( change )
    message( STATUS "global_var0: ${global_var0}")
    message( STATUS "global_var1: ${global_var1}")
    set( global_var0 2)
    set( global_var1 2 PARENT_SCOPE)
    message( STATUS "global_var0, in change: ${global_var0}")
    message( STATUS "global_var1, in change: ${global_var1}")
endfunction()

change()
message( STATUS "global_var0, after change: ${global_var0}")
message( STATUS "global_var1, after change: ${global_var1}")

# modify
function(increment var)
   message( STATUS "var value: ${${var}}") 
   math( EXPR new_value "${${var}} + 1")
   set( ${var} ${new_value} PARENT_SCOPE)
endfunction()

set( value 14 )
increment(value)
message( STATUS "increment, value: ${value}")

