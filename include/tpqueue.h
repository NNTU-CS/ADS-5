// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
    struct ITEM {
        T data;
        ITEM* next;
    };

 public:
    TPQueue() :head(nullptr), tail(nullptr) {}
    ~TPQueue() {
        while (head)
            pop();
    }
    void push(const T& data) {
        if (tail && head) {
            ITEM* current = head;

            if (current->data.prior >= data.prior) {
                while (current->next) {
                    if (current->next->data.prior < data.prior) {
                        ITEM* temp = create(data);
                        temp->next = current->next;
                        current->next = temp;
                        break;
                    } else {
                        current = current->next;
                    }
                }
            } else {
                current = create(data);
                current->next = head;
                head = current;
            }

            if (!current->next) {
                tail->next = create(data);
                tail = tail->next;
            }
        } else {
            head = create(data);
            tail = head;
        }
    }

    T pop() {
        assert(head);
        T data = head->data;
        ITEM* temp = head->next;
        delete head;
        head = temp;

        return data;
    }

 private:
    TPQueue::ITEM* create(const T& data) {
        ITEM* item = new ITEM;
        item->data = data;
        item->next = nullptr;
        return item;
    }
    ITEM* head;
    ITEM* tail;
};

struct SYM {
    char ch;
    int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
