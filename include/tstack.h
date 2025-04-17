// Copyright 2021 NNTU-CS
template<typename T, int size>
class TStack {
 public:
  TStack() : top(-1) {}

  void push(const T& val) {
    if (top < size - 1)
      data[++top] = val;
  }

  T pop() {
    if (!isEmpty())
      return data[top--];
    return T();
  }

  T peek() const {
    if (!isEmpty())
      return data[top];
    return T();
  }

  bool isEmpty() const {
    return top == -1;
  }

 private:
  T data[size];  // NOLINT(runtime/arrays)
  int top;
};
