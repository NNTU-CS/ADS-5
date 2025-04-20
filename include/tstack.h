#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
 private:
  static constexpr int kStackSize = size;
  T data[kStackSize];
  int top_index;

 public:
  TStack() : top_index(-1) {}

  void push(const T& value) {
    if (top_index < kStackSize - 1) {
      data[++top_index] = value;
    }
  }

  T pop() {
    if (!IsEmpty()) {
      return data[top_index--];
    }
    return T();
  }

  T peek() const {
    if (!IsEmpty()) {
        return data[top_index];
    }
    return T();
}

  T top() const {
    if (!IsEmpty()) {
      return data[top_index];
    }
    return T();
  }

  bool isEmpty() const {
    return top_index == -1;
  }
};


#endif  // INCLUDE_TSTACK_H_
