#include <iostream>

using namespace std;

template <typename T>
class Node
{

    T data;
    Node<T> *next;

public:
    Node(T dat, Node<T> *nxt);
    T getVal();
    Node<T> *getNext();
    void setVal(T dat);
    void setNext(Node<T> *nxt);
};

template <typename T>
Node<T>::Node(T dat, Node<T> *nxt)
{
    data = dat;
    next = nxt;
}

template <typename T>
T Node<T>::getVal()
{
    return data;
}

template <typename T>
Node<T> *Node<T>::getNext()
{
    return next;
}

template <typename T>
void Node<T>::setVal(T dat)
{
    data = dat;
}

template <typename T>
void Node<T>::setNext(Node<T> *nxt)
{
    next = nxt;
}
