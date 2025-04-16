// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {

private:
    T data[N]; 
    int topIndex; 

public:
    TStack() : topIndex(-1) {}

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == N - 1;
    }

    bool push(const T& value) {
        if (isFull()) {
            return false; 
        }
        data[++topIndex] = value;
        return true;
    }

    T pop() {
        if (isEmpty()) {
            return T();
        }
        return data[topIndex--];
    }

    T top() const {
        if (isEmpty()) {
            return T(); 
        }
        return data[topIndex];
    }
};

#endif  
