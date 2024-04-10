// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int sraw(char u) 
{
    if (u == '+' || u == '-')
        return 1;
    if (u == '*' || u == '/')
        return 2;
    return 0;
}
std::string infx2post(std::string inf) 
{
    std::string pov;
    int zero = 0;
    TStack <char, 100> post;
    for (char i : inf)
      {
        if (i >= '0' && i <= '9') 
        {
            zero++;
            if (zero == 1) 
            {
                pov += i;
                continue;
            }
            pov = pov + ' ' + i;
        }
        else if (i == '+' || i == '-' || i == '*'\
            || i == '/' || i == '(' || i == ')')
        {
            if (i == '(')
            {
                post.push(i);
            }
            else if (post.isemp()) 
            {
                post.push(i);
            }
            else if (sraw(i) > sraw(post.get())) 
            {
                post.push(i);
            }
            else if (i == ')') 
            {
                while (post.get() != '(') 
                {
                    pov = pov + ' ' + post.get();
                    post.pop();
                }
                post.pop();
            }
            else 
            {
                int x = sraw(i);
                int y = sraw(post.get());
                while (!post.isemp() && x <= y)
                {
                    pov = pov + ' ' + post.get();
                    post.pop();
                }
                post.push(i);
            }
        }
    }
    while (!post.isemp())
    {
        pov = pov + ' ' + post.get();
        post.pop();
    }
    return pov;
}

int eval(std::string pref)
{
    // добавьте код
    TStack <int, 100> number;
    for (char i : pref)
    {
        if (i >= '0' && i <= '9')
        {
            number.push(i - '0');
        }
        else if (sraw(i)) {
            int x = number.get();
            number.pop();
            int y = number.get();
            number.pop();
            switch (i)
            {
            case '+':
                number.push(x + y);
                break;
            case '-':
                number.push(y - x);
                break;
            case '*':
                number.push(x * y);
                break;
            case '/':
                number.push(y / x);
                break;
            default:
                continue;
            }
        }
        else 
        {
            continue;
        }
    }
    return number.get();
}
