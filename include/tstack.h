// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  private:
    static constexpr int kStackSize = size;
    T data[stackSize];
    int tIndex;
  
  public:
    TStack() : tIndex(-1) {}
  
    void push(const T& value) {
      if (tIndex < kStackSize - 1) {
        data[tIndex++] = value;
      }
    }
  
    T pop() {
      if (tIndex >= 0) {
        return data[tIndex--];
      }
      return T();
    }
  
    T top() const {
      if (tIndex >= 0) {
        return data[tIndex];
      }
      return T();
    }
  
    bool isEmpty() const {
      return tIndex == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
