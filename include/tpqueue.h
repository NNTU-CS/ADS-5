// Copyright 2021 NNTU-CS
#include <iostream>
#include <cassert>
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

struct SYM {
    char ch;
    int prior;
};

template <typename T>
class TPQueue {
    struct ITEM {
        T data;
        ITEM* next;
    };
 public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue();
    void push(const T&);
    T pop();
    void print()const;

 private:
    TPQueue::ITEM* create(const T&);
    ITEM* head;
    ITEM* tail;
};

template<typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template<typename T>
TPQueue<T>::ITEM* TPQueue<T>::create(const T& Shinoa) {
    ITEM* Madoka = new ITEM;
    Madoka->data = Shinoa;
    Madoka->next = nullptr;
    return Madoka;
}

template <typename T>
void TPQueue<T>::push(const T& Asuna) {
    if (head) {
        if (head->data.prior < Asuna.prior) {
            auto* temp = head;
            head = create(Asuna);
            head->next = temp;
            return;
        }
        ITEM* Illya = this->head;
        while (Illya->next != nullptr) {
            if (Illya->next->data.prior < Asuna.prior) {
                auto *temp = Illya->next;
                Illya->next = create(Asuna);
                Illya->next->next = temp;
                return;
            }
            Illya = Illya->next;
        }
        Illya->next = create(Asuna);
        tail = Illya->next;
    } else {
        head = create(Asuna);
        tail = head;
    }
}

template<typename T>
T TPQueue<T>::pop() {
    if (head) {
        T Shirou = head->data;
        head = head->next;
        return Shirou;
    }
}

template <typename T>
void TPQueue<T>::print() const {
    ITEM* Acha = head;
    while (Acha) {
        std::cout << Acha->data.ch << std::endl;
        Acha = Acha->next;
    }
    std::cout << std::endl;
}

#endif // INCLUDE_TPQUEUE_H_
