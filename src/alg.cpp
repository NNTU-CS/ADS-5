// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int p(char ch) {
    if (ch == '(') return 0;
    else if (ch == ')') return 1;
    else if (ch == '+' || ch == '-') return 2;
    else if (ch == '*' || ch == '/') return 3;
    else
        return -1;
}

bool isNum(char ch) {
    return (ch >= '0' && ch <= '9');
}

int len(std::string str) {
    char ch = str[0];
    int res = 0;
    while (ch != '\0') {
        ++res;
        ch = str[res];
    }
    return res;
}

int convertToInt(char ch) {
    char key[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int left = 0, right = sizeof(key) - 1;
    int mid = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (ch > key[mid]) {
            left = mid + 1;
        } else if (ch < key[mid]) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return mid;
}

std::string infx2pstfx(std::string inf) {
    Tstack<char> stch;
    std::string result;
    char tmp;
    int i = 0;
    char ch = inf[0];
    while (ch != '\0') {
        if (isNum(ch)) {
            result = result + ch + " ";
        } else {
            if (ch == ')')  {
                if (!stch.isEmpty()) {
                    tmp = stch.pop();
                    while (tmp != '(') {
                        result = result + tmp + " ";
                            if (!stch.isEmpty())
                                tmp = stch.pop();
                    }
                }
            } else if ((stch.isEmpty()) || ch == '(' || p(ch) > p(stch.get())) {
                stch.push(ch);
            } else if ((!stch.isEmpty())&&(p(ch) <= p(stch.get()))) {
                while ((!stch.isEmpty())&&(p(ch) <= p(stch.get()))) {
                    tmp = stch.pop();
                    result = result + tmp + " ";
                }
                stch.push(ch);
            }
        }
        ++i;
        ch = inf[i];
    }
    if (!stch.isEmpty()) {
        while (!stch.isEmpty()) {
            tmp = stch.pop();
            if (stch.isEmpty()) result = result + tmp;
            else
                result = result + tmp + " ";
        }
    }
    return result;
}

int eval(std::string pref) {
    Tstack<int> st_int;
    int l = len(pref);
    int tmp1 = 0, tmp2 = 0, res_tmp = 0, result = 0;
    int i = 0;
    char ch = pref[0];
    while (ch != '\0') {
        if (ch != ' ') {
            if (isNum(ch)) {
                st_int.push(convertToInt(ch));
            } else {
                if (!st_int.isEmpty()) tmp1 = st_int.pop();
                if (!st_int.isEmpty()) tmp2 = st_int.pop();
                if (ch == '+') res_tmp = tmp2 + tmp1;
                else if (ch == '-') res_tmp = tmp2 - tmp1;
                else if (ch == '*') res_tmp = tmp2 * tmp1;
                else if (ch == '/') res_tmp = tmp2 / tmp1;
                st_int.push(res_tmp);
            }
        }
        ++i;
        if (i <= l) {
            ch = pref[i];
        }
    }
    if (!st_int.isEmpty())
        result = st_int.pop();
    return result;
}
