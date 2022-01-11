//
// Created by 胡柯青 on 2022-01-11.
//

#ifndef PORTABLE_TEST_LIB_H
#define PORTABLE_TEST_LIB_H

#include <cstdlib>
#include <climits>
#include <cstdarg>
#include <cstdio>
#include <cctype>
#include <cmath>

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <limits>

using namespace std;

/// region 可以供 check 使用的函数

class InStream {
private:

    int sid;

    char buffer[1024];

    char next();

    char peek();

public:

    /**
     * 构造函数
     * @param sid 读取的文件流地址
     */
    explicit InStream();

    /**
     * 设置 sid
     * @param sid sid 的值
     */
    void setSid(int sid);

    /**
     * 获取一个字节
     * @param desc 获取的字节的含义
     * @return 被获取的字节
     */
    char getByte(const string &desc);

    /**
     * 获取一个字符
     * @param desc 获取的字符的含义
     * @return 被获取的字符
     */
    char readChar(const string &desc);

    /**
     * 获取一个字符，并判断是否在范围内
     * @param lower 最小值（包含）
     * @param upper 最大值（不包含）
     * @param desc 获取的字符的含义
     * @return 被获取的字符
     */
    char readChar(char lower, char upper, const string &desc);

    /**
     * 获取一个空格，强调下一个必须是空格，若获取到的不是空格则会结束判题
     *
     * <p color="red">
     *   不推荐使用
     * </p>
     *
     * 推荐使用 StreamReader#readDelimiter 来实现跳过分隔符
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
     * 推荐使用 StreamReader#readDelimiter 来实现跳过分隔符
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
     * 推荐使用 StreamReader#readDelimiter 来实现跳过分隔符
     *
     * @param desc 制表符的含义
     */
    void getTab(const string &desc);

    /**
     * 读取分隔符，跳过接下来所有的分隔符号，若接下来第一个符号不是分隔符号，也不会抛出错误，而是什么也不做。通常不需要使用，除非
     *
     * @param desc 分割符号的含义
     */
    void readDelimiter(const string &desc);

    /**
     * 读取一个字符串，直到遇到一个分隔符，至少包含一个字符，和 StreamReader#readWord 完全等价，更推荐使用 readWork，在语意上更加合理
     * @param maxLen 最长长度
     * @param desc 字符串的含义
     * @return 字符串的含义
     */
    string readString(int maxLen, const string &desc);

    /**
     * 读取一个字符串，直到遇到一个分隔符，至少包含一个字符，和 StreamReader#readString 完全等价
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
     * @param desc 获取的浮点数的含义
     * @return 获取到的浮点数
     */
    double readReal(double L, double R, const string &desc);

    /**
     * 读取一个字符串，直到遇到一个换行符，至少包含一个字符
     * @param maxLen 最长长度
     * @param desc 字符串的含义
     * @return 字符串的含义
     */
    string readLine();

    /**
     * 检查当前是不是遇到 EOF 了，如果不是，则直接结束评测
     */
    void readEof();
};

class Result {
public:

    /**
     * 判定此结果有问题
     *
     * @param desc 描述有问题的地方
     */
    void wrongAnswer(const string &desc);

    /**
     * 判断是否正确，若满足则继续，若不正确则停止判题
     *
     * @param flag 需要判定的逻辑表达式
     * @param desc 描述内容
     */
    void ensure(bool flag, const string &desc);

    /**
     * 判断两个值是否相同，若满足则继续，若不正确则停止判题
     * @tparam T 值类型
     * @param lhs 需要判定的左值
     * @param rhs 需要判定的右值
     * @param lDesc 左值的含义
     * @param rDesc 右值的含义
     */
    template<typename T>
    void equal(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc);

    /**
     * 判断两个值是否不相同，若满足则继续，若不正确则停止判题
     * @tparam T 值类型
     * @param lhs 需要判定的左值
     * @param rhs 需要判定的右值
     * @param lDesc 左值的含义
     * @param rDesc 右值的含义
     */
    template<typename T>
    void notEqual(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc);

    /**
     * 判断左值是否严格大于右值，若满足则继续，若不正确则停止判题
     * @tparam T 值类型
     * @param lhs 需要判定的左值
     * @param rhs 需要判定的右值
     * @param lDesc 左值的含义
     * @param rDesc 右值的含义
     */
    template<typename T>
    void ge(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc);

    /**
     * 判断左值是否大于等于右值，若满足则继续，若不正确则停止判题
     * @tparam T 值类型
     * @param lhs 需要判定的左值
     * @param rhs 需要判定的右值
     * @param lDesc 左值的含义
     * @param rDesc 右值的含义
     */
    template<typename T>
    void geq(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc);

    /**
     * 判断左值是否小于右值，若满足则继续，若不正确则停止判题
     * @tparam T 值类型
     * @param lhs 需要判定的左值
     * @param rhs 需要判定的右值
     * @param lDesc 左值的含义
     * @param rDesc 右值的含义
     */
    template<typename T>
    void le(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc);

    /**
     * 判断左值是否小于等于右值，若满足则继续，若不正确则停止判题
     * @tparam T 值类型
     * @param lhs 需要判定的左值
     * @param rhs 需要判定的右值
     * @param lDesc 左值的含义
     * @param rDesc 右值的含义
     */
    template<typename T>
    void leq(const T &lhs, const T &rhs, const string &lDesc, const string &rDesc);
};

/**
 * 注册成为 check
 * @param argc main 函数的参数 0
 * @param argv main 函数的参数 1
 */
void registerTestlibCmd(int argc, char *argv[]);

/**
 * 判题结束，并输出 ac
 * @param desc 描述一些成功信息
 */
void accept(const string &desc);

/// endregion

#endif //PORTABLE_TEST_LIB_H
