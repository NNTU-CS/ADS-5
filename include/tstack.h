// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  // добавьте код стека
  public:
    TStack() : top(-1) {
     dt = new T[size];
    }
    void push(const T& item) {
      if (tp <= size - 1)
        dt[++tp] = item;
      else
        throw std::string("stack is full");
    }
    T pop() {
      if (isEmpty())
        throw std::string("stack is empty");
      else
        return dt[tp--];
    }
    ~TStack() {
      delete[] dt;
    }
    bool isEmpty() const {
      return tp == -1;
    }
    T get() const {
      if (isEmpty())
        throw std::string("stack is empty");
      else
        return dt[tp];
    }
  private:
    T* dt;
    int tp;
};
#endif  // INCLUDE_TSTACK_H_
