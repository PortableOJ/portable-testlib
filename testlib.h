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

enum class TResult {
    _ok = 0,
    _wa = 1
};

class StreamReader {
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
    explicit StreamReader(int sid);

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

#endif //PORTABLE_TEST_LIB_H
