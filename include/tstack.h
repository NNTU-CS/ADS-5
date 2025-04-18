// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int MSSize>
class TStack {
 private:
T data_[MSSize];
size_t size_ = 0;

 public:
T get(size_t index) const {
if (index < size_) {
return data_[index];
} else {
throw std::out_of_range("Index out of range");
}
}
};

bool empty() const { return size_ == 0; }
size_t size() const { return size_; }

void push(const T& value) {
if (size_ == MSSize) {
throw std::out_of_range("Stack overflow");
}
data_[size_++] = value;
}

T& top() {
if (empty()) {
throw std::out_of_range("Stack is empty");
}
return data_[size_ - 1];
}

const T& top() const {
if (empty()) {
throw std::out_of_range("Stack is empty");
}
return data_[size_ - 1];
}

void pop() {
if (empty()) {
throw std::out_of_range("Stack is empty");
}
--size_;
}
};

#endif  // INCLUDE_TSTACK_H_
