// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

struct SYM {
    char ch;
    int prior;
};

template <typename T>
class LListQueue {
    struct ITEM {
        T data;
        ITEM* next;
    };
 public:
    LListQueue() : head(nullptr), tail(nullptr) {}
    ~LListQueue();
    void push(const T&);
    T pop();
    void print()const;

 private:
    LListQueue::ITEM* create(const T&);
    ITEM* head;
    ITEM* tail;
};

template<typename T>
LListQueue<T>::~LListQueue() {
    while (head) {
        pop();
    }
}

template<typename T>
LListQueue<T>::ITEM* LListQueue<T>::create(const T& Shinoa) {
    ITEM* Madoka = new ITEM;
    Madoka->data = Shinoa;
    Madoka->next = nullptr;
    return Madoka;
}

template <typename T>
void LListQueue<T>::push(const T& Asuna) {
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
    }
    else {
        head = create(Asuna);
        tail = head;
    }
}

template<typename T>
T LListQueue<T>::pop() {
    if (head) {
        ITEM* Konata = head->next;
        T Shirou = head->data;
        delete head;
        head = Konata;
        return Shirou;
    }
    else {
        return (T)0;
    }
}

template <typename T >
void LListQueue<T>::print() const
{
    ITEM* Acha = head;
    while (Acha) {
        std::cout << Acha->data.ch << " " << Acha->data.prior << std::endl;
        Acha = Acha->next;
    }
    std::cout << std::endl;
}

#endif // INCLUDE_TPQUEUE_H_
