// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  std::string stack;
  std::string res;
public:
  TStack() : stack(""), res("") {}

  std::string infx2pstfx(const std::string& inf);

  int eval(const std::string& pref);
};

#endif  // INCLUDE_TSTACK_H_
