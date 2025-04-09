// Copyright 2021 NNTU-CS
#include <stdexcept>
#include <string>
#include <array>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int max_size>
class CustomStack {
 private:
    std::array<T, MaxSize> items;
    int current_index;

 public:
    constexpr CustomStack() : current_index(-1) {}

    bool is_empty() const {
        return current_index < 0;
    }

    bool is_full() const {
        return current_index >= max_size - 1;
    }

    void add_item(const T& value) {
        if (is_full()) {
            throw std::string("stack is full");
        }
        items[++current_index] = value;
    }

    void remove_item() {
        if (is_empty()) {
            throw std::string("stack is empty");
        }
        --current_index;
    }

    const T& peek() const {
        if (is_empty()) {
            throw std::string("stack is empty");
        }
        return items[current_index];
    }

    T& peek() {
        if (is_empty()) {
            throw std::string("stack is empty");
        }
        return items[current_index];
    }
};

#endif  // INCLUDE_TSTACK_H_
