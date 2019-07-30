# SubDirectory & Definition in CMake

## SubDirecotry

注意事项

- build library时`add_library`中的source file要写相对路径

```shell
add_library{
	say-hello
	src/say-hello/hello.cpp
}

target_link_libraries( cmake-good PRIVATE say-hello)
```

- 外部要使用的头文件要在library中进行声明

```
target_include_directories(say-hello PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
```

> `${CMAKE_CURRENT_SOURCE_DIR}`为CMakeLists.txt所在的library的主目录。

- 在最外层的CMakeLists.txt中，library的包含路径要写在前面

```
add_subdirectory(say-hello)    # library include 在前
add_subdirectory(main)
```



## Definition

在library中定义宏

```
target_compile_definitions(say-hello PUBLIC SAY_HELLO_VERSION=4
```

在library和外面的main中，都可以使用此定义：

```
void hello::say_hello() {
    cout << "hello, world, in library! version: " << SAY_HELLO_VERSION << endl;
}
```

注意，definition有三种访问限制符：

- PUBLIC: library中和外面都可以使用；
- PRIVATE: 只能在library中使用，外部无法使用；
- INTERFACE: 只能在外部使用，library中无法使用；