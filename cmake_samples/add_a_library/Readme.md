# Add a library

## 基本用法

- 首先准备好要编译成library的source file；
- 在`CMakeLists.txt`中新增

```shell
add_library{
	say-hello
	hello.cpp
}

target_link_libraries( cmake-good PRIVATE say-hello)
```

1-4行新增了一个library，第6行是指定在生成可执行文件时，需要link新生成的这个library

生成library时，默认是STATIC；

如果要生成动态库

```
add_library {
	say-hello SHARED
	hello.cpp
}
```

