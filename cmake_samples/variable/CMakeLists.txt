cmake_minimum_required(VERSION 3.12)

project(var_test VERSION 1.0.0)

set( myVar1 a b c)
message( STATUS ${myVar1} ", quoted: ${myVar1}")

# multi-line 
set( myVar "goes here")
set( multiLine "First line ${myVar}
    Second line with a \"quoted\" word")
message( STATUS ${multiLine})

# use lua way string
set( multiLine [[
    First line
    Second line
]])
message( STATUS ${multiLine})

set( trafficLight Green CACHE STRING "Status of something")
set_property( CACHE trafficLight PROPERTY STRINGS Red Orange Green)