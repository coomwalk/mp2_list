#ifndef __ASD_LIST__
#define __ASD_LIST__

#include <iostream>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t
using namespace std;

template <typename DataType>
struct Node
{
  DataType data;
  Node* next;
  
  Node(DataType d = DataType{}, Node* n = nullptr): data(d),next(n){};
  bool operator==(const Node& node2) const noexcept{return data == node2.data;};
  bool operator!=(const Node& node2) const noexcept {return data != node2.data;};
};

// example
// https://internalpointers.com/post/writing-custom-iterators-modern-cpp 

template <typename DataType>
class listIterator : public std::iterator<std::forward_iterator_tag, DataType>
{
public:
	using iterator_category = std::forward_iterator_tag;
	using difference_type   = std::ptrdiff_t;
	using value_type = DataType;
	using pointer = Node<DataType>*;
	using reference = DataType&;

	listIterator(pointer* tmp) : p(tmp) {};
	reference operator*() {return *p;};
	pointer  operator->() {return p;};
	listIterator& operator++() { p = p -> next; return *this;};
	listIterator operator++(int){listIterator tmp = *this; ++(*this); return tmp;};
	bool operator==(const listIterator& it2) const {return p == it2.p;};
	bool operator!=(const listIterator& it2) const {return p != it2.p;};

private:
	pointer p;
};

template <typename DataType>
class List
{
  Node<DataType>* head;
  Node<DataType>* last;
public:
  List() noexcept : head(nullptr), last(nullptr){}; // создать пустой список
  List(const DataType& d)
  {
    head = new Node<DataType>(d);
    last = head;
  }; // создать список из одного звена
  
  bool isEmpty()
  {
    return head == nullptr;
  }

  void InsertToHead(const DataType& d)
  {
    Node<DataType>* p = new Node<DataType>(d);
    p->next = head;
    head = p;
  }; // вставить элемент d первым

  DataType ViewHead()
  {
    return head -> data;
  }; // посмотреть первого
  ////////////////////////////////
  void InsertToTail(const DataType& d)
  {
    Node<DataType>* p = new Node<DataType>(d);
    last -> next = p;
    last = p;
  }; // вставить элемент d последним

  DataType ViewTail()
  {
    return last ->data;
  }; // посмотреть последнего
			///////////////////////////////////////////							
  void Delete(const DataType& d)
  {
    if(!(*this->isEmpty))
    {
      Node<DataType>* tmp;
      Node<DataType>* prev;
      if(head == d)
      {
        tmp = head;
        head = head -> next;
        delete tmp;
      }
      else
      {
        prev = head;
        tmp = head -> next;
        while(tmp != nullptr)
        {
          if(tmp -> data == d)
          {
            prev -> next = tmp ->next;
            if(tmp ->next == nullptr) last = prev;
            delete tmp;
            break;
          }
        }
      }
    }
    else
    {
      throw "list is empty";
    }
  }; // удалить звено со значением data = d	
  
  listIterator<DataType> begin()
  {
    return listIterator<DataType> tmp(head);
  }; // получить итератор на первое звено 

  listIterator<DataType> tail()
  {
    return listIterator<DataType> tmp(last);
  }; // получить итератор на последнее звено

  listIterator<DataType> end()
  {
    return istIterator<DataType> tmp(nullptr);
  }; // получить итератор на конец списка

  ~List()
  {
    if(head != nullptr)
    {
      Node<DataType>* tmp;
      tmp = head;
      while(head -> next != nullptr)
      {
        head = tmp -> next;
        delete tmp;
        tmp = head;
      }
      delete head;
    }
  };
//////////////////////
  List(const List& list2);
  
  List& operator=(const List& list2);
  
  void Clean(); // удалить все звенья  
  			
  void InsertAfter(const listIterator<DataType>& it, const DataType& d); // вставить элемент d после звена node

  listIterator<DataType> Search(const DataType& d); // найти указатель на звено со значением data = d
  
  void Delete(const listIterator<DataType>& it); // удалить звено со значением data = d	
										
  void Delete(const listIterator<DataType>& start, const listIterator<DataType>& finish);

  void DeleteAll(const DataType& d);

  void Inverse(); // инвертировать список, т.е. звенья должны идти в обратном порядке

  List Merge(const listIterator<DataType>& start, const List& list2); // создать список3, добавив список2 в текущий список после итератора 

  void MergeWith(const listIterator<DataType>& start, const List& list2); // в *this добавить список2 после итератора

  friend ostream& operator<<(ostream& os, const List<DataType>& l);

  friend istream& operator>>(istream& is, const List<DataType>& l);
  
  void MadeUnique(); // исключить повторяющиеся звенья

  bool Cycle();   // определить, есть ли цикл в списке

  void BreakCycle(); // "разомкнуть" цикл в списке

  std::string ToString(); // "зн 1; зн2; " 

  int GetSize(); // узнать число звеньев в списке
  
  List Merge(const List& list2); // создать список3, добавив в конец текущего списка список2

  bool operator==(const List& list2) const; // списки равны, если элементы в них идут в одинаковом порядке
};

#endif