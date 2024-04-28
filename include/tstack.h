// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
  T* stackArray;
  int size;
  int top;
public:
  TStack(int _size = 100); // Конструктор с параметром по умолчанию
  ~TStack(); // Деструктор
  void push(const T& value); // Добавление элемента в стек
  T pop(); // Удаление и возврат элемента из вершины стека
  T get(); // Получение элемента из вершины стека
  bool isEmpty(); // Проверка на пустоту стека
};

template <typename T>
TStack<T>::TStack(int _size) : size(_size), top(-1) {
    stackArray = new T[size];
}
template <typename T>
TStack<T>::~TStack() {
    delete[] stackArray;
}
template <typename T>
void TStack<T>::push(const T& value) {
    stackArray[++top] = value;
}
template <typename T>
T TStack<T>::pop() {
    return stackArray[top--];
}
template <typename T>
T TStack<T>::get() {
    return stackArray[top];
}
template <typename T>
bool TStack<T>::isEmpty() {
    return (top == -1);
}
};
#endif  // INCLUDE_TSTACK_H_
