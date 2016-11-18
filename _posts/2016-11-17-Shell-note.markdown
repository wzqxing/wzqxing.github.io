---
layout:     post
title:      "shell编程笔记"
subtitle:   ""
data:       2016-11-16
authori:    "silence"
header-img: ""
tags:
        - 笔记
        - 编程
        - Linux



---
## Catalog

1、[常用shell变量]((#section))

2、[shell流程控制]((#section-1))

## 常用shell变量


- $HOME 家目录
- $PWD  当前路径
- $1、$2、... 运行脚本时的位置参数
- $0  当前脚本的名称
- $*  保存传递给脚本或进程的所有参数
- $$  当前进程或脚本的PID号
- $!  后台运行的最后一个进程的PID号
- $1  用于返回上一条命令是否成功执行。执行成功返回0，不成功返回1
- $#  用于保存脚本参数的个数

例子

```
#!/bin/bash
#This is a test script

#利用$0输出当前脚本的名称
echo "script name:"$0
echo "all parameters:"$*
echo "PID is the :"$$
echo "success of previous command:"$?
```

## shell流程控制

#### 条件测试和捕获信号

>0表示true，1表示false

- 退出状态
  数字0表示命令或者程序成功执行
  数字1表示命令或者程序没有成功执行
  `exit 0`表示脚本成功执行
  `exit 1`表示脚本未成功执行

- 文件测试

  格式：`[-command parameter]`

  常用命令及其含义

  - d：测试目录是否存在

  - f：测试文件是否存在

  - L：测试链接文件是否存在

  - b：测试块设备文件是否存在

  - c：测试字符设备文件是否存在

  - e：测试指定文件或目录是否存在

- 文件权限测试

  常用命令

  - w：判断指定文件是否存在，并且有写权限

  - r:判断指定文件是否存在，并且有读权限

  - x:判断指定文件是否存在，并且有执行权限

  - u:判断指定文件是否存在，并且有SUID权限

>针对脚本的执行用户

- 变量测试

  [ -z $变量名]测试变量是否定义

- 字符串测试

  命令格式：`[parameter1 operator parameter2]`

  parameter1和parameter2表示字符串，operator表示操作符

  操作符：

  - =：判断是否相等

  - ！=：判断是否不等

  - n：判断是否为空

- 数值测试：

  操作命令

  - eq(=)：判断是否相等

  - ne(!=)：判断是否不等

  - lt：<

  - le：<=

  - gt：>

  - ge：>=

- 逻辑操作符

  - a：与

  - o：或

  - !：非


#### 条件判断语句

- if语句

```
  if 条件表达式
    then
      语句 1
      语句 2
      ......
  fi
```

- if else语句

```
  if 条件表达式
    then
      语句块 1
  else
      语句块 2
  fi
```

- if elif语句

```
  if 条件表达式 1
    then
      语句块 1
  elif 条件表达式 2
    then
      语句快 2
  ......
  else
      语句块
  fi
```

#### 循环语句

- for循环

```
  for 变量 in 列表
  do
    语句块
  done
```

- while循环

```
  while 条件表达式
  do
    语句块
  done
```

>continue和break控制循环

#### 函数定义

```
  function 函数名()
  {
    语句块
  }
```

或者

```
  函数名()
  {
    语句块
  }
```

- 函数调用

  函数名 [参数]

- 函数形参

  $1、$2、$3......

- 返回执行状态

  return：最后一条语句的执行状态返回

  return 0：返回成功执行

  return 1：返回错误执行信息

- 函数文件的调用

  `路径名 ./函数文件名`  
