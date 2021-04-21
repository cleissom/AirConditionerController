#include "Node.hpp"

template <typename T>
class Queue
{

    Node<T> *head;

public:
    Queue();
    ~Queue();
    void push(T dat);
    T pop();
    bool empty();
};

template <typename T>
Queue<T>::Queue()
{
    head = 0;
}

template <typename T>
Queue<T>::~Queue()
{
    Node<T> *cursor = head;
    while (head)
    {
        cursor = cursor->getNext();
        delete head;
        head = cursor;
    }
    head = 0;
}

template <typename T>
void Queue<T>::push(T dat)
{
    Node<T> *p = head;
    Node<T> *q = head;

    if (head == 0)
        head = new Node<T>(dat, head);
    else
    {
        while (q != 0)
        {
            p = q;
            q = p->getNext();
        }
        p->setNext(new Node<T>(dat, 0));
    }
}

template <typename T>
T Queue<T>::pop()
{
    T retval;
    if (head != 0)
    {
        retval = head->getVal();
        Node<T> *oldHead = head;
        head = head->getNext();
        delete oldHead;
    }
    return retval;
}

template <typename T>
bool Queue<T>::empty()
{
    return head == 0;
}
