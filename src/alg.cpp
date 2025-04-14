// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  std::string postfixNotation;
  TStack<char, 100> operatorStorage;
  std::map<char, int> operationPriority = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
  };

  for (size_t pos = 0; pos < inf.size(); ++pos) {
    char currSym = inf[pos];
    
    if (isdigit(currSym)) {
      while (pos < inf.size() && isdigit(inf[pos])) {
        postfixNotation += inf[pos++];
      }
      postfixNotation += ' ';
      pos--;
    } 
    else if (currSym == '(') {
      operatorStorage.push(currSym);
    } 
    else if (currSym == ')') {
      while (!operatorStorage.empty() && 
             operatorStorage.get() != '(') {
        postfixNotation += operatorStorage.get();
        postfixNotation += ' ';
        operatorStorage.pop();
      }
      operatorStorage.pop();
    } 
    else {
      while (!operatorStorage.empty() && 
             operatorStorage.get() != '(' && 
             operationPriority[currSym] <= 
             operationPriority[operatorStorage.get()]) {
        postfixNotation += operatorStorage.get();
        postfixNotation += ' ';
        operatorStorage.pop();
      }
      operatorStorage.push(currSym);
    }
  }

  while (!operatorStorage.empty()) {
    postfixNotation += operatorStorage.get();
    postfixNotation += ' ';
    operatorStorage.pop();
  }

  if (!postfixNotation.empty() && 
      postfixNotation.back() == ' ') {
    postfixNotation.pop_back();
  }

  return postfixNotation;
}

int eval(const std::string& pref) {
  TStack<int, 100> calcStack;

  for (size_t idx = 0; idx < pref.size(); ++idx) {
    char currChar = pref[idx];
    
    if (isdigit(currChar)) {
      int numVal = 0;
      while (idx < pref.size() && isdigit(pref[idx])) {
        numVal = numVal * 10 + (pref[idx++] - '0');
      }
      calcStack.push(numVal);
      idx--;
    } 
    else if (currChar == ' ') {
      continue;
    } 
    else {
      int rightOp = calcStack.get();
      calcStack.pop();
      int leftOp = calcStack.get();
      calcStack.pop();
      
      switch (currChar) {
        case '+': 
          calcStack.push(leftOp + rightOp); 
          break;
        case '-': 
          calcStack.push(leftOp - rightOp); 
          break;
        case '*': 
          calcStack.push(leftOp * rightOp); 
          break;
        case '/': 
          calcStack.push(leftOp / rightOp); 
          break;
      }
    }
  }

  return calcStack.get();
}
