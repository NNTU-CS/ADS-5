// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_


  template <typename T, std::size_t N>
class TStack {
private:
    T mas[N];
    std::size_t el;

public:
    TStack() : el(0) {}

    bool pol() const {
        return el >= N;
    }

    bool nepol() const {
        return el == 0;
    }

    void dob(const T& value) {
        if (pol()) {
            throw std::overflow_error("Error");
        }
        mas[el++] = value;
    }

    T dl() {
        if (nepol()) {
            throw std::underflow_error("Error");
        }
        return mas[--el];
    }

    T pe() const {
        if (nepol()) {
            throw std::underflow_error("Error");
        }
        return mas[el - 1];
    }
};

#endif  // INCLUDE_TSTACK_H_
