#include "../Node.hpp"

template <typename T>
class List
{

  Node<T> *head;

public:
  List();
  ~List();
  void insertBeforeFirst(T dat);
  void insertAfterLast(T dat);
  T readFirst();
  T removeFirst();
  T removeNode(T dat);
  void listAll();
};

template <typename T>
List<T>::List()
{
  head = 0;
}

template <typename T>
List<T>::~List()
{
  Node<T> *cursor = head;
  while (head)
  {
    cursor = cursor->getNext();
    delete head;
    head = cursor;
  }
  head = 0; // Officially empty
}

template <typename T>
void List<T>::insertBeforeFirst(T dat)
{
  head = new Node<T>(dat, head);
}

template <typename T>
void List<T>::insertAfterLast(T dat)
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
T List<T>::readFirst()
{
  return head->getVal();
}

template <typename T>
T List<T>::removeFirst()
{
  T retval;
  if (head != 0)
  {
    cout << "Removendo: " << head << endl;
    cout << "e fica:" << head->getVal() << endl;
    retval = head->getVal();
    Node<T> *oldHead = head;
    head = head->getNext();
    delete oldHead;
  }
  return retval;
}

template <typename T>
T List<T>::removeNode(T dat)
{
  Node<T> *p = head;
  Node<T> *q = head;
  int result;

  if (head == 0)
    result = 0;
  else
  {
    while ((q != 0) && (q->getVal() != dat))
    { // Error!! the addresses will always be different!
      p = q;
      q = p->getNext();
    }
    if (q != 0)
    {
      if (q == head)
      { // it is the first node
        result = q->getVal();
        head = q->getNext();
        delete q;
      }
      else
      { // the node is in the middle
        result = q->getVal();
        p->setNext(q->getNext());
        delete q;
      }
    }
    else
      result = 0; // node not found!
  }

  return result;
}

template <typename T>
void List<T>::listAll()
{
  Node<T> *aux = head;
  while (aux != 0)
  {
    cout << aux->getVal() << endl;
    aux = aux->getNext();
  }
}
