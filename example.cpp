#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    setTestId(1);

    int cnt = inf.readInt("Number of integer");
    for (int i = 0; i < cnt; ++i) {
        int tmp = inf.readInt(0, 11, "Number");
        cout << tmp << " \n"[i == cnt - 1];
    }

    cnt = inf.readInt("Number of float");
    for (int i = 0; i < cnt; ++i) {
        double tmp = inf.readReal(0, 10, "Number");
        cout << tmp << " \n"[i == cnt - 1];
    }

    cnt = inf.readInt("Number of big integer");
    for (int i = 0; i < cnt; ++i) {
        long long tmp = inf.readLong(0, 10000000000L, "Number");
        cout << tmp << " \n"[i == cnt - 1];
    }

    cnt = inf.readInt("Number of word");
    for (int i = 0; i < cnt; ++i) {
        int len = ouf.readInt("Len of word");
        string tmp = ouf.readWord(len, "Word");
        cout << tmp << " \n"[i == cnt - 1];
    }

    cnt = inf.readInt("Number of line");
    for (int i = 0; i < cnt; ++i) {
        string tmp = ouf.readLine(100, "Word");
        cout << tmp << " \n"[i == cnt - 1];
    }

    accept("AC");
}
