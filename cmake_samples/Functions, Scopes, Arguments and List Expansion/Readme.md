## 变量使用引号和不使用引号的区别
当我们引用一个变量的时候，`"${my_var}"`和`${my_var}`在变量为一个值的时候会得到一样的结果，但是如果变量是一个list，那么会有差别。

```
set( target DIRECTORY "${PROJECT_SOURCE_DIR}")

set_property(
	"${target}"
	PROPERTY FOO
	1
	2
	3
)

get_property( my_prop "${target}" PROPERTY FOO )
message( STATUS "value of my property: ${my_prop}")
```

上述script在执行时，会报错，出错原因是`set_property()`的参数期望的形式是`DIRECTORY "$PROJECT_SOURCE_DIR"` 这样的形式；而由引号引起来的变量，会尝试把有多个值的变量合成一个 ，形式如
`DIRECTORY;/home/peter/cmake_sample/list-expansion`，这会被认为是一个非法的参数。

而当我们把`"${target}"`在set_property()和get_property()的引号都去掉以后，就正常了。

## 函数中ARGN和ARGV的使用

- `ARGN`是除了有名字的参数后，剩下的所有参数的集合
- `ARGV`是所有的参数集合

## 函数中对全局变量的访问

- 函数中对全局变量的使用是对全局变量的一个拷贝，所以默认在函数中对全局变量的改变在函数结束后是不会生效的；
- 如果要对全局变量改变，要加上`PARENT_SCOPE`参数，注意当用这个对全局变量进行修改时，修改的是真正的全局变量，而在函数中对全局变量的拷贝则不受影响