// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

TStack<char, 100> stackf;
TStack<int, 100> stacks;

std::string infx2pstfx(std::string inf) {
    std::string out;
    for (char indicator : inf) {
        if (indicator == 40) {
            stackf.push(indicator);
        } else if (indicator >= 48 && indicator <= 57) {
            out += indicator;
            out += 32;
        } else if (indicator == 41) {
            while (stackf.get() != 40 && !stackf.isEmpty()) {
                out += stackf.pop();
                out += 32;
            }
            if (stackf.get() == 40)
                stackf.pop();
        } else if (indicator == 43 || indicator == 45) {
            if (!stackf.isEmpty()) {
                switch (stackf.get()) {
                case 43: {
                    out += 43;
                    out += 32;
                    stackf.pop();
                    break;
                }
                case 45: {
                    out += 45;
                    out += 32;
                    stackf.pop();
                    break;
                }
                case 42: {
                    out += 42;
                    out += 32;
                    stackf.pop();
                    break;
                }
                case 47: {
                    out += 47;
                    out += 32;
                    stackf.pop();
                    break;
                }
                }
                stackf.push(indicator);
            } else {
                stackf.push(indicator);
            }
        } else if (indicator == 42 || indicator == 47) {
            if (!stackf.isEmpty()) {
                switch (stackf.get()) {
                case 42: {
                    out += 42;
                    out += 32;
                    stackf.pop();
                    break;
                }
                case 47: {
                    out += 47;
                    out += 32;
                    stackf.pop();
                    break;
                }
                }
                stackf.push(indicator);
            } else {
                stackf.push(indicator);
            }
        }
    }
    if (!stackf.isEmpty()) {
        while (!stackf.isEmpty()) {
            out += stackf.pop();
            out += 32;
        }
        out.pop_back();
    }
    return out;
}

int eval(std::string pref) {
    std::string str;
    char S;
    for (char indicator : pref) {
        if ((indicator >= 48 && indicator <= 57)) {
            str += indicator;

        } else if (indicator == 32 && !str.empty()) {
            stacks.push(std::stoi(str));
            str.clear();
        } else if (indicator == 43 || indicator == 45 ||
            indicator == 42 || indicator == 47) {
            switch (indicator) {
            case 43: {
                S = stacks.pop();
                stacks.push(stacks.pop() + S);
                break;
            }
            case 45: {
                S = stacks.pop();
                stacks.push(stacks.pop() - S);
                break;
            }
            case 42: {
                S = stacks.pop();
                stacks.push(stacks.pop() * S);
                break;
            }
            case 47: {
                S = stacks.pop();
                stacks.push(stacks.pop() / S);
                break;
            }
            }
        }
    }
    return stacks.pop();
}
