// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T el[size];
    int indx;

 public:
    TStack() : indx(-1) {}

    bool push(const T& value) {
        if (indx >= size - 1) {
            return false;
        }
        el[++indx] = value;
        return true;
    }

    bool pop(T& value) {
        if (indx < 0) {
            return false;
        }
        value = el[indx--];
        return true;
    }

    bool top(T& value) const {
        if (indx < 0) {
            return false;
        }
        value = el[indx];
        return true;
    }

    bool isEmpty() const {
        return indx == -1;
    }

    int getSize() const {
        return indx + 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
