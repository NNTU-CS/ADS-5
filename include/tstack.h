#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, constexpr int kStackSize>
class TStack {
    T data[kStackSize];
    int top;

public:
    TStack() : top(-1) {}

    void Push(T value) {
        if (top < kStackSize - 1) {
            data[++top] = value;
        }
    }

    T Pop() {
        if (!IsEmpty()) {
            return data[top--];
        }
        return T();
    }

    T Top() {
        if (!IsEmpty()) {
            return data[top];
        }
        return T();
    }

    bool IsEmpty() {
        return top == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
