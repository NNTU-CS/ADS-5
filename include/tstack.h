// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  private:
    static constexpr int kStackSize = size;
    T m_data[kStackSize];
    int m_index;
  
  public:
    TStack() : m_index(-1) {}
  
    void push(const T& value) {
      if (m_index < kStackSize - 1) {
        m_data[++m_index] = value;
      }
    }
  
    T pop() {
      if (m_index >= 0) {
        return m_data[m_index--];
      }
      return T();
    }
  
    T top() const {
      if (m_index >= 0) {
        return m_data[m_index];
      }
      return T();
    }
  
    bool isEmpty() const {
      return m_index == -1;
    }
  
    bool isFull() const {
      return m_index == kStackSize - 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
