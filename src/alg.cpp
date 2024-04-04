// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
    std::string s = "";
    TStack<char, 100> st;
    int len = inf.length();
    for (int i = 0; i < len; i++) {
        std::string var;
        int pr = 0;
        if (inf[i] >= '0' && inf[i] <= '9') {
            s += inf[i];
            s += ' ';
        } else {
            switch (inf[i]) {
            case '(': pr = 0; break;
            case ')': pr = 1; break;
            case '+': pr = 2; break;
            case '-': pr = 2; break;
            case '*': pr = 3; break;
            case '/': pr = 3; break;
            }

            if (pr == 0 || st.getTop() == 0) {
                st.push(inf[i]);
            } else if (pr == 1) {
                while ((var = st.pop()) != "(") {
                    s += var;
                    s += ' ';
                }
            } else if (pr > st.getPriority()) {
                st.push(inf[i]);
            } else {
                while (pr <= st.getPriority()) {
                    s += st.pop();
                    s += ' ';
                }
                st.push(inf[i]);
            }
        }
    }
    while (st.getTop() != 0) {
        s += st.pop();
        s += ' ';
    }
    s.erase(s.length() - 1, 1);
    return s;
}

int eval(std::string pref) {
    TStack<int, 100> st;
    int len = pref.length();
    int var1, var2, res;
    for (int i = 0; i < len; i += 2) {
        if (pref[i] >= '0' && pref[i] <= '9') {
            switch (pref[i]) {
            case '0': st.push(0); break;
            case '1': st.push(1); break;
            case '2': st.push(2); break;
            case '3': st.push(3); break;
            case '4': st.push(4); break;
            case '5': st.push(5); break;
            case '6': st.push(6); break;
            case '7': st.push(7); break;
            case '8': st.push(8); break;
            case '9': st.push(9); break;
            }
        } else {
            var1 = st.pop();
            var2 = st.pop();
            switch (pref[i]) {
                case '+': res = var2 + var1; break;
                case '-': res = var2 - var1; break;
                case '*': res = var2 * var1; break;
                case '/': res = var2 / var1; break;
            }
            st.push(res);
        }
    }
    return st.pop();
}
