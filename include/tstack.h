// Modified stack implementation
#ifndef MODIFIED_STACK_H
#define MODIFIED_STACK_H

template<typename DataType, int MaxSize>
class TStack {
 private:
    DataType elements[MaxSize];
    int currentTop;

 public:
    TStack() : currentTop(-1) {}

    void push(const DataType& value) {
        if (isFull()) {
            throw std::string("Stack overflow");
        }
        elements[++currentTop] = value;
    }

    DataType pop() {
        if (isEmpty()) {
            throw std::string("Stack underflow");
        }
        return elements[currentTop--];
    }

    bool isEmpty() const {
        return currentTop == -1;
    }

    bool isFull() const {
        return currentTop == MaxSize - 1;
    }

    const DataType& get() const {
        return elements[currentTop];
    }
};

#endif
