// Copyright 2021 NNTU-CS

#include <map>
#include "tstack.h"

TStack<char, 100> stackf;
TStack<int, 100> stacks;

std::string infx2pstfx(std::string inf) {
    std::string out;
    for (char ind : inf) {
        if (ind == 40) {
            stackf.push(ind);
        } else if (ind >= 48 && ind <= 57) {
            out += ind;
            out += 32;
        } else if (ind == 41) {
            while (stackf.get() != 40 && !stackf.isEmpty()) {
                out += stackf.pop();
                out += 32;
            }
            if (stackf.get() == 40)
                stackf.pop();
        } else if (ind == 43 || ind == 45) {
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
                stackf.push(ind);
            } else {
                stackf.push(ind);
            }
        } else if (ind == 42 || ind == 47) {
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
                stackf.push(ind);
            } else {
                stackf.push(ind);
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
    char St;
    for (char ind : pref) {
        if ((ind >= 48 && ind <= 57)) {
            str += ind;

        } else if (ind == 32 && !str.empty()) {
            stacks.push(std::stoi(str));
            str.clear();
        } else if (ind == 43 || ind == 45 ||
            ind == 42 || ind == 47) {
            switch (ind) {
            case 43: {
                St = stacks.pop();
                stacks.push(stacks.pop() + St);
                break;
            }
            case 45: {
                St = stacks.pop();
                stacks.push(stacks.pop() - St);
                break;
            }
            case 42: {
                St = stacks.pop();
                stacks.push(stacks.pop() * St);
                break;
            }
            case 47: {
                St = stacks.pop();
                stacks.push(stacks.pop() / St);
                break;
            }
            }
        }
    }
    return stacks.pop();
}
