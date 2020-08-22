
项目介绍
=======
这是一个 `Linux` 下的守护进程框架</br>

出于对项目优化的目的以及学习掌握并使用 `X Macro` 技巧，本项目巧</br>
妙的使用 `X Macro` 编写了一份可任意扩展进程数量，并且带参数传递</br>
的守护进程管理框架。</br>

此份代码极其精简，使用起来也非常方便，如果你正好需要一个守护进</br>
程又不希望对现有项目进项太大调整，不妨可以尝试一下。

当然，如果你能完全保证项目稳定工作，确实不需要使用守护进程，但</br>
是有一个突发状况的预案，说不定会在关键时刻给你带来惊喜。
</br></br>

目录结构
=======

```tree
.
├── build.sh                    # 编译执行脚本
├── CMakeLists.txt              # CMake 根工程文件
├── build/                      # 编译生成目录以及可执行文件包含在该目录下
└── source/                         # 源码目录
    |
    ├── CMakeLists.txt                  # CMake 子工程文件
    ├── controller/                     # 控制器目录，守护进程的与子进程控制器目录
    │   ├── w21Deamons.c                # 本项目守护进程的实现源码
    │   └── w21Deamons.h                # 本项目守护进程的头文件
    |
    └── main.cpp                        # 项目入口文件
```


使用说明
=======

1、编译
-------

```bash
w0x0021@ubuntu:~/w21Deamons$ ./build.sh
```

2、代码修改
----------

本项目使用需要修改的地方总共有3处关键位置，和1处入口调用，针对 `w21Deamons.h` 文件的修改位置，已经在头文件中使用注释标注了需要修改的区域，注释标记如下：

```C
/*******************************************************************
 *       Please change the code for this area - Start              *
 *******************************************************************/
/*
    ...
    需要修改的代码区域
    ...
*/
W21DMS_XMACROS(TASK_MAX , w21Dms_gTask, w21Dms_taskMaxFunc)         /*** 此行不能修改 ***/
/*******************************************************************
 *       Please change the code for this area - End                *
 *******************************************************************/
```

需要修改的 `3处关键` 和 `1处入口` 分别为：

- `修改1：` 子进程入口函数格式规范
- `修改2：` 在头文件 `w21Deamons.h` 添加对子进程入口函数的声明
- `修改3：` 在头文件 `w21Deamons.h` 添加子进程任务
- `入口：` 项目入口 `main()` 函数中调用守护进程

具体修改方法如下：
    
#### 修改1：子进程入口函数格式规范

- 1、入口函数名任意
- 2、返回值为 `void`
- 3、参数包含两个: ```(int, char **)``` ，所接受的参数为项目的 `main()` 函数传递的两个参数，未做修改

    **例：**

    ```C
    void task_name(int argc, char **argv);
    ```

#### 修改2： 在头文件 `w21Deamons.h` 添加对子进程入口函数的声明

在本项目中，添加子进程的入口函数声明方式有两种
- `方法1: ` 直接将子进程入口函数声明写到 `w21Deamons.h` 头文件中
- `方法2：` 将带有子进程入口函数声明的头文件 `include` 到 `w21Deamons.h` 头文件中

    **例：**

    假设：需要添加子任务数量为3个，函数名分别为 `task1_main`、`task3_main`、`task3_main`
    
    > 方法1：

    ```C
    /*******************************************************************
     *       Please change the code for this area - Start              *
     *******************************************************************/
    void task1_main(int argc, char **argv);
    void task2_main(int argc, char **argv);
    void task3_main(int argc, char **argv);
    #define W21DMS_MACROS                                               \
                                                                        \
        W21DMS_XMACROS(TASK_MAX , w21Dms_gTask, w21Dms_taskMaxFunc)     /*** The line dose not be changed ***/
    /*******************************************************************
     *       Please change the code for this area - End                *
     *******************************************************************/
    ```

    > 方法2：

    `task1.h`
    ```C
    void task1_main(int argc, char **argv);
    ```
    </br>
    
    `task2.h`
    ```C
    void task1_main(int argc, char **argv);
    ```
    </br>
    
    `task3.h`
    ```C
    void task1_main(int argc, char **argv);
    ```

    </br>

    `w21Demons.h`
    ```C
    /*******************************************************************
     *       Please change the code for this area - Start              *
     *******************************************************************/
    #include "task1.h"
    #include "task2.h"
    #include "task3.h"
    #define W21DMS_MACROS                                               \
                                                                        \
        W21DMS_XMACROS(TASK_MAX , w21Dms_gTask, w21Dms_taskMaxFunc)     /*** The line dose not be changed ***/
    /*******************************************************************
     *       Please change the code for this area - End                *
     *******************************************************************/
    ```

    **注意：** 为了避免发生不必要的编译异常，建议使用 `方法1`

</br>

#### 修改3： 在头文件 `w21Deamons.h` 添加子进程任务

添加子进程任务主要由宏 `W21DMS_MACROS` 控制，每新增一条任务的程序代码规范如下：

```C
W21DMS_XMACROS(TASK_INDEX_x, w21Dms_gTask, task_mainName)   \
```

其中：
- `W21DMS_XMACROS` : 该宏即 `X MACROS` 技巧的实现, 实现过程在 `w21Demons.c` 文件中，此处只做使用说明，该技巧说明暂略。

- `TASK_INDEX_x` : 任务的索引，此参数格式无要求，只需要保持书写规范，使用大写即可，但是不能与其它任务的索引名称相同，且不能使用 `TASK_MAX`

- `w21Dms_gTask` : 此参数为固定全局变量名，该变量为 `w21Dms_TaskStatus_t` 类型的数组，数组个数为 `TASK_MAX` ，而 `TASK_MAX` 的值等于该头文件下所有子进程成的数量 `+1` 个。该值根据新增任务数量改变而改变，无需单独修改

- `task_mainName` : 子进程的入口函数名

- `\` : 每新增一条任务，结尾不能缺少换行转义，表示 `W21DMS_MACROS` 未结束，改宏结束的真正位置在索引为 `TASK_MAX` 这条任务，这条进程只是一条空进程，执行一次过后即结束，目的只是为了创建名为 `TASK_MAX` 的枚举索引。

**例：**

还是假设：需要添加子任务数量为3个，函数名分别为 `task1_main`、`task3_main`、`task3_main`，修改后的程序代码片段如下：

```C
/*******************************************************************
 *       Please change the code for this area - Start              *
 *******************************************************************/
void task1_main(int argc, char **argv);
void task2_main(int argc, char **argv);
void task3_main(int argc, char **argv);
#define W21DMS_MACROS                                               \
    W21DMS_XMACROS(TASK_FUN1, w21Dms_gTask, task1_main)             \
    W21DMS_XMACROS(TASK_FUN2, w21Dms_gTask, task2_main)             \
    W21DMS_XMACROS(TASK_FUN3, w21Dms_gTask, task3_main)             \
                                                                    \
    W21DMS_XMACROS(TASK_MAX , w21Dms_gTask, w21Dms_taskMaxFunc)     /*** The line dose not be changed ***/
/*******************************************************************
 *       Please change the code for this area - End                *
 *******************************************************************/
```

#### 入口： 项目入口 `main()` 函数中调用守护进程

本项目只需要在程序入口调用守护进程的入口函数 `w21Dms_Main()` 即可。

入口调用如下：

```C
int main(int argc, char **argv)
{
	w21Dms_Main(argc, argv);
	return 0;
}
```

---

该项目暂未对子进程的返回值、以及按条件新增进程等处理，后续有机会再进行完善。

个人博客: [山中书](https://www.wangsansan.com)

CSDN博客: [CSDN博客 - 山中书](https://blog.csdn.net/byb123)

