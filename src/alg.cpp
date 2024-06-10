// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <stack>
#include <queue>

int getPr(char inf) {
    switch (inf) {
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
        return 2;
        break;
    default:
        return 0;
        break;
    }
}
std::string infx2pstfx(std::string inf) {
    std::string str = "";
    std::stack<char> stack1;
    std::queue<char> queue;
    for (int i = 0; i < inf.length(); ++i) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            queue.push(inf[i]);
            continue;
        } else {
            if (inf[i] != '(' && inf[i] != ')') {
                queue.push(' ');
            }
            if (inf[i] == '(') {
                stack1.push(inf[i]);
                continue;
            }
            if (inf[i] == ')') {
                while ((!(stack1.empty()))) {
                    if (stack1.top() == '(') {
                        stack1.pop();
                        continue;
                    }
                    queue.push(stack1.top());
                    stack1.pop();
                }
                continue;
            }
            if (stack1.empty() || ((stack1.top()) == '(')) {
                stack1.push(inf[i]);
                continue;
            }
            if (getPr(inf[i]) > getPr(stack1.top())) {
                stack1.push(inf[i]);
                continue;
            }
            if (getPr(inf[i]) <= getPr(stack1.top())) {
                while (!(stack1.empty())) {
                    if ((getPr(inf[i]) <= getPr(stack1.top()))
                        || ((stack1.top()) == '(')) {
                        queue.push
                        (stack1.top());
                        queue.push(' ');
                        stack1.pop();
                    }
                }
                stack1.push(inf[i]);
                continue;
            }
        }
    }
    while (!(stack1.empty())) {
        if ((stack1.top() == '(') || (stack1.top() == ')')) {
            stack1.pop();
        }
        queue.push(' ');
        queue.push(stack1.top());
        stack1.pop();
    }
    while ((!(queue.empty()))) {
        str += queue.front();
        queue.pop();
    }
    return str;
}
// вычисление выражения, записанного в постфиксной форме
int eval(std::string post) {
    int res = 0, a = 0, b = 0, sum = 0;
    int num = 0;
    bool por = false;
    std::stack<int> stack1;
    for (int i = 0; i < post.length(); ++i) {
        if (post[i] == ' ' && por) {
            stack1.push(sum);
            num = 0;
            sum = 0;
        }
        if (post[i] >= '0' && post[i] <= '9') {
            //stack1.push(post[i] - 48);
            num++;
            por = true;
            if (num > 1) {
                sum *= 10;
                sum+= post[i] - 48;
            } else {
                sum += post[i] - 48;
            }
        } else if (post[i] != ' ') {
            por = false;
            b = stack1.top();
            stack1.pop();
            a = stack1.top();
            stack1.pop();
            switch (post[i]) {
            case '+':
                stack1.push(a + b);
                break;
            case '-':
                stack1.push(a - b);
                break;
            case '*':
                stack1.push(a * b);
                break;
            case '/':
                stack1.push(a / b);
                break;
            default:
                break;
            }
        }
    }
    res = stack1.top();
    return res;
}
