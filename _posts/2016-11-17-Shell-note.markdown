---
layout:     post
title:      "shell编程笔记"
subtitle:   ""
data:       2016-11-16
authori:    "silence"
header-img: ""
tags:
        - 笔记



---
## Catalog

1、[shell变量](#section)

2、[shell流程控制](#section-1)

## shell变量

#### 变量

  shell变量是动态类型，使用前无需先声明定义；shell是弱类型语言，可以将任何类型的值赋给同一变量名。准确的说，shell变量统一的按照字符串存储，但是根据变量的上下文环境，允许程序执行一些不同的操作，例如字符串的比较和整数的加减等。

  例子：

```
#!/bin/bash
x=123
let "x += 1"
echo "x = $x"

#将x中的1换为abc
y=${x/1/abc}
echo "y = $y"
declare -i y
echo "y = $y"
z=abc22
echo "z = $z"

#将z中的abc换为11
m=${z/abc/11}
echo "m = $m"
n=""
echo "n = $n"
let "n += 1"
echo "n = $n"
echo "p = $p"
let "p += 1"
echo "p = $p"
```

  执行结果：

```
x = 124
y = abc24
y = abc24
z = abc22
m = 1122
n =
n = 1
p =
p = 1
```

  变量定义

  事实上，shell变量无须声明定义，每一个为使用的变量名都是一个空字符串，直接可以运算。

  `变量名=值`

>等号两边不能有空格

  变量清空

  `unset 变量名`

  引用变量名用${变量名}引用

  尽管无须声明定义，但为了更好的控制变量，shell提供declare命令来声明变量

  `declare attribute variable`

  其中，attribute表示变量的属性，常用属性如下：

  - -p：显示所有变量的值

  - -i：将变量定义为整数

  - -r：将变量声明为只读变量

  - -a：将变量声明为数组变量，不过没有必要。

  - -f：显示所有自定义函数，包括名称和函数体

  - -x：将变量设置为环境变量

>declare命令又写作typeset

#### 变量和引号

shell中有三种引号：分别为单引号，双引号，反引号

在反引号中的语句被shell当成命令在当前命令执行之前执行，并以它的标准输出取代整个反引号

双引号，除美元符号、单引号、反引号、反斜线之外，其他所有字符被当成普通字符

单引号，所有字符当成普通字符

反斜线，转义字符

>命令替换：**\`shell_command\`** 与 **$(shell_command)** 等价

#### 变量的作用域

1. 全局变量
    在函数外部定义的变量是全局变量，全局变量可以在函数内部使用。
2. 局部变量
    local关键字定义局部变量

#### 系统变量

- $HOME 家目录
- $PWD  当前路径
- $1、$2、... 运行脚本时的位置参数
- $0  当前脚本的名称
- $*  保存传递给脚本或进程的所有参数
- $$  当前进程或脚本的PID号
- $!  后台运行的最后一个进程的PID号
- $1  用于返回上一条命令是否成功执行。执行成功返回0，不成功返回1
- $#  用于保存脚本参数的个数
- $@

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

#### 变量运算

>**算数运算符：+、 -、 *、 /、 **(乘方)、 %(求余)**

在Linux Shell中，用户可以通过四种方式执行算数运算

- expr外部程序

expr是一个Shell命令，可以计算整个某个表达式的值，基本语法如下：

`expr expression`

例子：

```
#!/bin/bash
result=`expr 2 + 100`
echo "result = $result"
result=`expr 2 - 100`
echo "result = $result"
result=`expr 2 \* 5`
echo "result = $result"
result=`expr 24 / 8`
echo "result = $result"
result=`expr \( 2 - 6 \) \* 12`
echo "result = $result"
```

运算结果：

```
result = 102
result = -98
result = 10
result = 3
result = -48
```

>运算符两侧要添加空格，\*和（ ）要转义，`expr`不能计算乘方运算

- 使用`$((...))`

  使用这种形式来进行算术运算写法比较自由，无须对运算符和括号进行转义处理，可以采用松散或者紧凑的格式来书写表达式

```
#！/bin/bash

result=$((3+6))
echo "result = $result"
result=$(( 3 + 9 ))
echo "result = $result"
result=$(( 7/5 ))
echo "result = $result"
result=$((8%3))
echo "result = $result"
result=$(( (1-4)*5 ))
echo "result = $result"
```

- 使用`$[...]`

  与`$((...))`相同

- 使用`let`命令

  可以使用复合运算符

- 位运算

  `m>>n`数m右移n位

  `m<<n`数m左移n位

  `&` 按位与

  `|` 按位或

  `~ ` 按位非

  `^` 按位异或

## shell流程控制

#### 条件测试和捕获信号

>0表示true，1表示false

- 退出状态
  数字0表示命令或者程序成功执行
  数字1表示命令或者程序没有成功执行
  `exit 0`表示脚本成功执行
  `exit 1`表示脚本未成功执行

- 条件测试基本语法

  `test expression` 或 `[ expression ]`

> **[命令的作用与test相同，为了增加可读性，在后面添加一个]，条件表达式和[ ]之间必须要有空格**

- 文件测试

  格式：`[ -command parameter ]`

  常用命令及其含义

  - -d：测试目录是否存在

  - -f：测试文件是否存在

  - -L：测试链接文件是否存在

  - -b：测试块设备文件是否存在

  - -c：测试字符设备文件是否存在

  - -e：测试指定文件或目录是否存在

- 文件权限测试

  常用命令

  - -w：判断指定文件是否存在，并且有写权限

  - -r:判断指定文件是否存在，并且有读权限

  - -x:判断指定文件是否存在，并且有执行权限

  - -u:判断指定文件是否存在，并且有SUID权限

>针对脚本的执行用户

- 变量测试

  `[ -z $变量名 ]`测试字符串是否为空

- 字符串测试

  命令格式：`[ parameter1 operator parameter2 ]`

  parameter1和parameter2表示字符串，operator表示操作符

  操作符：

  - =：判断是否相等

  - ！=：判断是否不等

  - -n：判断是否为非空

- 数值测试：

  操作命令

  - -eq(=)：判断是否相等

  - -ne(!=)：判断是否不等

  - -lt：<

  - -le：<=

  - -gt：>

  - -ge：>=

- 逻辑操作符

  - -a：与

  - -o：或

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

## 循环

#### for循环

```
for 变量 in 列表
do
  语句块
done
```

输出1+2+...+100

```
sum=0
for i in {1..100}
do
  sum=$(($sum+i))
done
echo $sum
```

>{start..end..step}产生一个列表

打印当前目录下所有文件名

```
for i in `ls`
do
  echo $i
done
```

打印所有输入参数

```
for i
do
  echo $i
done
```

遍历数组

```
array=(Mon Tue Wed Thu Fri Sat Sun)
for day in ${array[*]}
do
  echo $day
done
```


类C风格的for循环语句

```
for ((expression1;expression2;expression3))
do
  statement1
  statement2
  ......
done
```

1加到100

```
sum=0
for ((i=1;i<=100;i++))
do
  sum=$[$sum+i]
done
echo $sum
```



#### while循环

```
while 条件表达式
do
  语句块
done
```

输出1～9的平方

```
i=1
while [ "$i" -lt 10 ]
do
  square=$[$i*$i]
  echo $square
  let "i++"
done
```


>continue和break控制循环

## 函数

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
