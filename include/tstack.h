// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#pragma once

#include <stdexcept>
#include <cstddef>

template<typename T, std::size_t N>
class TStack {
 public:
    constexpr TStack() noexcept : _top(0) {}
    constexpr std::size_t size()  const noexcept { return _top; }
    constexpr bool        empty() const noexcept { return _top == 0; }
    constexpr bool        full()  const noexcept { return _top == N; }
    T&       top()       { check_empty(); return _data[_top - 1]; }
    const T& top() const { check_empty(); return _data[_top - 1]; }
    void push(const T& value) {
        if (full()) throw std::runtime_error("stack overflow");
        _data[_top++] = value;
    }
    void pop() {
        check_empty();
        --_top;
    }
    void clear() noexcept { _top = 0; }
 private:
    T _data[N];
    std::size_t _top;
    void check_empty() const {
        if (empty()) throw std::runtime_error("stack underflow");
    }
};

#endif  // INCLUDE_TSTACK_H_
