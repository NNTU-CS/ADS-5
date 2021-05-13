#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
    struct ITEM {
        T ch;
        ITEM *next;
    };
public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue();

    void push(const T &);
    T pop();
    void print() const;
  
private:
    TPQueue::ITEM *create(const T &);
    ITEM *head;
    ITEM *tail;
};

template<typename T>
typename TPQueue<T>::ITEM *TPQueue<T>::create(const T &ch) {
    ITEM *item = new ITEM;
    item->ch = ch;
    item->next = nullptr;
    return item;
}

template<typename T>
TPQueue<T>::~TPQueue() {
    while (head)
        pop();
}

template<typename T>
void TPQueue<T>::push(const T &ch) {
    if (tail && head) {
        ITEM *temp = head;
        if (ch.prior > temp->ch.prior) {
            temp = create(ch);
            temp->next = head;
            head = temp;
        } else {
            while (temp->next) {
                if (ch.prior > temp->next->ch.prior) {
                    ITEM *t = create(ch);
                    t->next = temp->next;
                    temp->next = t;
                    break;
                } else {
                    temp = temp->next;
                }
            }
        }
        if (!temp->next) {
            tail->next = create(ch);
            tail = tail->next;
        }
    } else {
        head = create(ch);
        tail = head;
    }
}

template<typename T>
T TPQueue<T>::pop() {
    if (head) {
        ITEM *temp = head->next;
        T ch = head->ch;
        delete head;
        head = temp;
        return ch;
    }
}

template<typename T>
void TPQueue<T>::print() const {
    ITEM *temp = head;
    while (temp) {
        std::cout << temp->ch << "␣";
        temp = temp->next;
    }
    std::cout << std::endl;
}

struct SYM {
  char data;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
