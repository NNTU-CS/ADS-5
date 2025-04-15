// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(const char a) {
    switch (a) {
    case '(':
	return 0;
    case ')':
	return 1;
    case '+':
	return 2;
    case '-':
	return 2;
    case '*':
	return 3;
    case '/':
	return 3;
    default:
	return -1;
    }
}


std::string infx2pstfx(const std::string& inf) {
    std::string post;
    TStack<char, 100> stack;
    bool needSpace = false;
    for (int i = 0; i < inf.size(); i++) {
 	char current = inf[i];
	int currentPrior = prior(current);
	if (currentPrior == -1) {
	    if (needSpace) {
		post += ' ';
	    }
		post += current;
		needSpace = false;
	}
        else if (current == '(') {
		stack.push(current);
		needSpace = false;
	}
	else if (current == ')') {
		while (!stack.isEmpty() && stack.get() != '(') {
			post += ' ';
			post += stack.get();
			stack.pop();
		}
		stack.pop();
		needSpace = true;
	} else {
		while (!stack.isEmpty() &&
			prior(stack.get()) >= currentPrior &&
			stack.get() != '(') {
			post += ' ';
			post += stack.get();
			stack.pop();
		}
		post += ' ';
		stack.push(current);
		needSpace = false;
	}
    }
    while (!stack.isEmpty()) {
	post += ' ';
	post += stack.get();
	stack.pop();
    }
    return post;
}

int eval(const std::string& pref) {
      TStack<int, 100> stack;
      std::string number = "";
      for (size_t i = 0; i < pref.length(); i++) {
	      char c = pref[i];
              if (isdigit(c)) {
		number += c;
	      }
	      else if (c == ' ') {
		      if (!number.empty()) {
			      stack.push(std::stoi(number));
			      number = "";
		      }
	      }
	      else if (prior(c) >= 2) {
		      if (!stack.isEmpty()) {
			      int b = stack.get();
			      stack.pop();
			      if (!stack.isEmpty()) {
				      int a = stack.get();
				      stack.pop();
				      switch (c) {
					      case '+': stack.push(a + b); break;
					      case '-': stack.push(a - b); break;
					      case '*': stack.push(a * b); break;
					      case '/': stack.push(a / b); break;
				      }
			      }
		      }
	      }
      }
	if (!number.empty()) {
		stack.push(std::stoi(number));
	}
	return stack.get();
}
