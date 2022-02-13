<div align="center">
    <h1>PortableOJ TestLib</h1>
</div>

# Intro
这是 [Portable OJ](https://github.com/PortableOJ/portable-oj) 系统的 testlib 实现代码，这个项目其参考了 [testlib](https://github.com/MikeMirzayanov/testlib) 的实现。
并对其实现的内容在 Portable OJ 的系统上进行部分的改进和优化，使得其更加容易进行编写

由于 Portable OJ 仅需要编写 Checker，本系统目前只适用于编写 Checker

# Samples
你可以在 [standard](https://github.com/PortableOJ/portable-testlib/tree/master/standard) 目录下找到所有 Portable OJ 提供的
所有默认的 Checker 的源代码。你可以参考其中的代码来编写自己的需要的 Checker，或者根据 Checker 的内容来了解 Portable OJ 的判题标准。

同时，你也可以在 [oi-wiki](https://oi-wiki.org/tools/testlib/checker/) 找到有关 Checker 编写的一些理论参考说明
（注意，此处网站的 API 为标准 testlib 的 API，与本文提供的有所出入，但编写思想仍然相同）

# 使用说明

## 编写 Checker 方法

所有的 Checker 默认使用 GNU G++ C++17作为编译器，请依照 C++17 的规范进行编写

### 引用 testlib
首先你需要在 Checker 开头引用必要的头文件

```c++
#include "testlib.h"
```

这是必须要做的，此后你可以使用来自 testlib 提供的 API 进行判题

### 注册 Checker
在 main 函数的第一行，注册 Checker

```c++
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
}
```

### 设置当前的测试编号
由于有相当一部分题目在一个文件内有多组输入数据，所以 testlib 提供了 API 用于设置当前的测试序号，便于检查校验

使用 API

```c++
setTestId(1);
```

可以将当前的测试序号定为 1，当然你也可以改为其他数字。但是请注意，若你不希望输出测试序号，则可以不调用此函数或者提供一个小于等于 0 的整数即可

### 读取输入输出和答案
testlib 提供了三个输入流用于获取必要的数据
```c++
InStream inf // 当前测试的输入数据
InStream ouf // 当前测试下，用户代码的输出数据
InStream anf // 当前测试下，标准代码的输出数据
```
你可以在下面的 API 说明中找到所有的读入数据方式

### 回答判断结果
`ouf` 和 `anf` 还实现了 `Result` 的接口，当你调用其中的接口时，则表明此输入流的数据是错误的，或者不够优秀的。

当然，标准代码的输出数据也可以是不正确的，因为可能存在出题人疏忽的情况，这会导致本应该是正确的题目却得到了错误的回复。

当你调用 `ouf` 的 `Result` 下的接口时，系统则会认定用户的代码有误，并返回 `Wrong Answer`。

而当你调用 `anf` 的 `Result` 下的接口时，系统则会认为用户的代码更优，并返回 `Judge Fail`。这会让出题人能够发现是否是其标准答案有误

你可以在下面的 API 说明中找到所有的输出结果方式

最后，若你发现两者都是正确的，此时，你需要调用 `accept(msg...)` 来告诉 testlib，你认为两者均正确，你可以在最下方找到此 API

# API

## InStream 篇
主要分为两类，`get` 系列和 `read` 系列。其中 `get` 系列能够更加精确的操作每一个字节，而 `read` 系列更多是从可见字符角度进行处理

需要注意的是 `read` 系列会默认跳过接下来的分隔符，然后再读取有效部分，并可能读取有效数据后紧接着的一个分隔符。所以请不要混用这两个系列的 API

所有的 `get` 系列均为不推荐使用

> **因为作为一个 OnlineJudge 出题人，我们需要考虑的，应该是做题人的思想和逻辑，而不是刻意去扣那么一个空格回车这种无伤大雅的问题**

### Get 系列
```c++
/**
 * 获取一个字节
 * @param desc 获取的字节的含义
 * @return 被获取的字节
 */
char getByte(const string &desc);

/**
 * 获取一个空格，强调下一个必须是空格，若获取到的不是空格则会结束判题
 *
 * <p color="red">
 *   不推荐使用
 * </p>
 *
 * 推荐使用 InStream#readDelimiter 来实现跳过分隔符
 *
 * @param desc 空格的含义
 */
void getSpace(const string &desc);

/**
 * 获取一个回车，强调下一个必须是回车，若获取到的不是回车则会结束判题
 *
 * <p color="red">
 *   不推荐使用
 * </p>
 *
 * 推荐使用 InStream#readDelimiter 来实现跳过分隔符
 *
 * @param desc 回车的含义
 */
void getReturn(const string &desc);

/**
 * 获取一个制表符，强调下一个必须是一个制表符，若获取到的不是制表符则会结束判题
 *
 * <p color="red">
 *   不推荐使用
 * </p>
 *
 * 推荐使用 InStream#readDelimiter 来实现跳过分隔符
 *
 * @param desc 制表符的含义
 */
void getTab(const string &desc);

/**
 * 检查当前是不是遇到 EOF 了，强调必须是当前是否是 eof，如果不是，则直接结束评测
 * <p color="red">
 * 不推荐使用
 * </p>
 * 判题系统通常应该无视程序额外输出的换行符等结束符号，这些符号通常是被习惯性添加的或者作为一种默认规范存在的
 */
void getEof();

/**
 * 检查是否已经到达文件结束了，若为 true 则文件未结束
 * <p color="red">
 * 不推荐使用
 * </p>
 * 这是一种强制判断是否存在 EOF 的结果，若存在任何的换行符等，此函数均不返回 true
 *
 * @return 文件是否还有字节
 */
bool notGetEof();
```

### Read 系列
```c++
/**
 * 读取分隔符，跳过接下来所有的分隔符号，若接下来第一个符号不是分隔符号或者遇到文件结束，也不会抛出错误，而是什么也不做。通常不需要使用，除非需要高度的自定义
 *
 * @return 是否读取到了文件结束
 */
bool readDelimiter();

/**
 * 获取下面第一个非分隔符字符
 * @param desc 获取的字符的含义
 * @return 被获取的字符
 */
char readChar(const string &desc);

/**
 * 获取下面第一个非分隔符字符，并判断是否在范围内
 * @param lower 最小值（包含）
 * @param upper 最大值（不包含）
 * @param desc 获取的字符的含义
 * @return 被获取的字符
 */
char readChar(char lower, char upper, const string &desc);

/**
 * 读取一个字符串，直到遇到一个分隔符，至少包含一个字符，和 InStream#readWord 完全等价，更推荐使用 readWord，在语意上更加合理
 * @param maxLen 最长长度
 * @param desc 字符串的含义
 * @return 字符串的含义
 */
string readString(int maxLen, const string &desc);

/**
 * 读取一个字符串，直到遇到一个分隔符，至少包含一个字符，和 InStream#readString 完全等价
 * @param maxLen 最长长度
 * @param desc 字符串的含义
 * @return 字符串的含义
 */
string readWord(int maxLen, const string &desc);

/**
 * 获取一个 32 位的整数，若值超出了 32 位整数范围，则按照自动溢出计算
 *
 * @param desc 获取的整数的含义
 * @return 获取到的整数
 */
int readInt(const string &desc);

/**
 * 获取一个 32 位的整数，若值超出了 32 位整数范围，则按照自动溢出计算，并判断是否在一定范围（溢出后判断）
 *
 * @param lower 最小值（包含）
 * @param upper 最大值（不包含）
 * @param desc 获取的整数的含义
 * @return 获取到的整数
 */
int readInt(int lower, int upper, const string &desc);

/**
 * 获取一个 64 位的整数，若值超出了 64 位整数范围，则按照自动溢出计算
 *
 * @param desc 获取的整数的含义
 * @return 获取到的整数
 */
long long readLong(const string &desc);

/**
 * 获取一个 64 位的整数，若值超出了 64 位整数范围，则按照自动溢出计算，并判断是否在一定范围（溢出后判断）
 *
 * @param lower 最小值（包含）
 * @param upper 最大值（不包含）
 * @param desc 获取的整数的含义
 * @return 获取到的整数
 */
long long readLong(long long lower, long long upper, const string &desc);

/**
 * 获取一个浮点数
 *
 * @param desc 获取的浮点数的含义
 * @return 获取到的浮点数
 */
double readReal(const string &desc);

/**
 * 获取一个浮点数，并判断是否在一定范围（溢出后判断）
 *
 * @param lower 最小值
 * @param upper 最大值
 * @param desc 获取的浮点数的含义
 * @return 获取到的浮点数
 */
double readReal(double lower, double upper, const string &desc);

/**
 * 读取一个字符串，直到遇到一个换行符，并读走此换行符，可能是空行
 * <p color="red">
 *   不推荐使用
 * </p>
 *
 * 题目要求的输出格式应当尽可能通过分隔符进行分割，而不是强制要求相同格式，这不符合出题价值观
 *
 * @param maxLen 最长长度
 * @param desc 字符串的含义
 * @return 字符串的含义
 */
string readLine(int maxLen, const string &desc);

/**
 * 检查是否已经没有可读内容了，若剩余的字节都是分隔符，则 OK，否则，则直接结束评测
 */
void readEof();
```

## Result 篇
当需要出现 `Wrong Answer` 或者 `Judge Fail` 的时候，才需要调用此函数。此接口下提供了一些简单的判断方法

```c++
/**
 * 判定此结果有问题
 *
 * @param desc 描述有问题的地方
 */
void wrongAnswer(const string &desc) const;

/**
 * 判定此结果有问题
 *
 * @tparam Args 格式化参数内容
 * @param format 格式化模版
 * @param args 格式化内容
 */
template<class ...Args>
#ifdef __linux__
__attribute__((__format__ (__printf__, 2, 0)))
#endif
__attribute__((format (__printf__, 2, 0)))
void wrongAnswer(const char *format, const Args &...args) const;

/**
 * 判断是否正确，若满足则继续，若不正确则停止判题
 *
 * @param flag 需要判定的逻辑表达式
 * @param desc 描述内容
 */
void ensure(bool flag, const string &desc) const;

/**
 * 判断两个值是否相同，若满足则继续，若不正确则停止判题
 * @tparam T 值类型
 * @param lhs 需要判定的左值
 * @param rhs 需要判定的右值
 * @param lDesc 左值的含义
 * @param rDesc 右值的含义
 */
template<typename T>
void equal(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc) const;

/**
 * 判断两个值是否不相同，若满足则继续，若不正确则停止判题
 * @tparam T 值类型
 * @param lhs 需要判定的左值
 * @param rhs 需要判定的右值
 * @param lDesc 左值的含义
 * @param rDesc 右值的含义
 */
template<typename T>
void notEqual(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc) const;

/**
 * 判断左值是否严格大于右值，若满足则继续，若不正确则停止判题
 * @tparam T 值类型
 * @param lhs 需要判定的左值
 * @param rhs 需要判定的右值
 * @param lDesc 左值的含义
 * @param rDesc 右值的含义
 */
template<typename T>
void ge(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc) const;

/**
 * 判断左值是否大于等于右值，若满足则继续，若不正确则停止判题
 * @tparam T 值类型
 * @param lhs 需要判定的左值
 * @param rhs 需要判定的右值
 * @param lDesc 左值的含义
 * @param rDesc 右值的含义
 */
template<typename T>
void geq(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc) const;

/**
 * 判断左值是否小于右值，若满足则继续，若不正确则停止判题
 * @tparam T 值类型
 * @param lhs 需要判定的左值
 * @param rhs 需要判定的右值
 * @param lDesc 左值的含义
 * @param rDesc 右值的含义
 */
template<typename T>
void le(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc) const;

/**
 * 判断左值是否小于等于右值，若满足则继续，若不正确则停止判题
 * @tparam T 值类型
 * @param lhs 需要判定的左值
 * @param rhs 需要判定的右值
 * @param lDesc 左值的含义
 * @param rDesc 右值的含义
 */
template<typename T>
void leq(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc) const;
```

## 通用函数篇
这些函数可以直接调用，通常是一些全局设置等
```c++
/**
 * 注册成为 check
 * @param argc main 函数的参数 0
 * @param argv main 函数的参数 1
 */
void registerTestlibCmd(int argc, char *argv[]);

/**
 * 设置当前的判题 ID
 * @param id 新的判题 ID
 */
void setTestId(int id);

/**
 * 判题结束，并输出 ac
 * @param desc 描述一些成功信息
 */
void accept(const string &desc);

/**
 * 判题结束，并输出 ac
 * @tparam Args 格式化参数类型
 * @param desc 格式化模版
 * @param args 格式化参数
 */
template<class ...Args>
#ifdef __linux__
__attribute__((__format__ (__printf__, 1, 0)))
#endif
__attribute__((format (__printf__, 1, 0)))
void accept(const char *desc, const Args &...args);
```