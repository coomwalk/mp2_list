#ifndef __ASD_LIST__
#define __ASD_LIST__

#include <iostream>
#include <map>
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
    if((this -> isEmpty()))
    {
      head = p;
    }
    else
    {
      last -> next = p;
    }
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
  }; // удалить звено со значением data = d	
  
  listIterator<DataType> begin()
  {
    listIterator<DataType> tmp(head);
    return tmp;
  }; // получить итератор на первое звено 

  listIterator<DataType> tail()
  {
    listIterator<DataType> tmp(last);
    return tmp;
  }; // получить итератор на последнее звено

  listIterator<DataType> end()
  {
    listIterator<DataType> tmp(nullptr);
    return tmp;
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
  List(const List& list2)
  {
    if(list2.head == nullptr)
    {
      head = last = nullptr;
      return;
    }

    head = new Node<DataType>(*list2.head);
    last =head;
    for(const auto& i = list2.begin(); i!= list2.end(); i++)
    {
      (*this).InsertToTail(i->data);
    }
  };
  
  List& operator=(const List& list2)
  {
    return List(list2);
  };
  
  void Clean()
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
    head = nullptr;
    last = nullptr;
  }; // удалить все звенья  
  			
  void InsertAfter(const listIterator<DataType>& it, const DataType& d)
  {
    Node <DataType>* tmp = new Node <DataType>(d);
    tmp->next =  it->next;
    it->next = tmp;

  }; // вставить элемент d после звена node

  listIterator<DataType> Search(const DataType& d)
  {
    for(auto i = (*this).begin(); i!= (*this).end(); i++)
    {
      if(i->data == d)
      {
        return i;
      }
    }
    return (*this).end();

  }; // найти указатель на звено со значением data = d
  
  void Delete(const listIterator<DataType>& it)
  {
    if(!(this ->isEmpty))
    {
    if(head == *it)
    {
      head = head->next;
      delete *it;
      return;
    }
    if(last == *it)
    {
      auto tmp = this -> begin();
      while(tmp -> next != *it)
      {
        tmp++;
      }
      tmp ->next = nullptr;
      delete *it;
      return;
    }
    auto tmp = this -> begin();
    while(tmp -> next != *it)
    {
      tmp++;
    }
    tmp -> next = it -> next;
    delete *it;
    }

  }; // удалить звено со значением data = d	
										
  void Delete(const listIterator<DataType>& start, const listIterator<DataType>& finish)
  {
    if(*start == head)
    {
      head = finish->next;
      for(auto i = start; i !=finish; i++)
      {
        delete *i;
      }
      delete *finish;
      return;
    }
    auto tmp = this -> begin();
    while(tmp -> next != *start)
    {
      tmp++;
    }
    tmp -> next = finish -> next;;
    for(auto i = start; i !=finish; i++)
      {
        delete *i;
      }
    delete *finish;
  };

  void DeleteAll(const DataType& d)
  {
    if(!(*this->isEmpty))
    {
      
      for(auto i = this -> begin(); i != this -> end(); i++)
      {
        if(i -> data == d)
        {
          if(*i == head)
          {
            head = head -> next;
            delete *i;
            continue;
          }


          if (*i == last)
          {
            auto tmp = this -> begin();
            while(tmp -> next != *i)
              {
                tmp++;
              }
            tmp -> next = nullptr;
            last = *tmp;
            delete *i;
            continue;;
          }


          auto tmp = this -> begin();
            while(tmp -> next != *i)
              {
                tmp++;
              }
          tmp ->next = i -> next;
          delete *i;
        }
      }
    }
  };

  void Inverse()
  {
    if(this -> GetSize() == 0 || this -> GetSize() == 1) return;
    else
    {
      Node <DataType>* tmp = head -> next;
      Node <DataType>* newfirst = head;

      while(tmp != nullptr)
      {
        newfirst -> next = tmp -> next;
        tmp -> next = newfirst;
        newfirst = tmp;
        tmp = newfirst -> next;
      }
      head = newfirst;
    }

  }; // инвертировать список, т.е. звенья должны идти в обратном порядке

  List Merge(const listIterator<DataType>& start, const List& list2)
  {
    List <DataType> tmp;
    //insert to tail data
    for(auto i = this -> begin(); i != start; i++)
    {
      tmp.InsertToTail(i -> data);
    }
    tmp.InsertToTail(start -> data);
    for(auto i = list2.begin(); i != list2.end(); i++)
    {
      tmp.InsertToTail(i -> data);
    }
    auto end = ++start;
    for(auto i = end; i != this -> end(); i++)
    {
      tmp.InsertToTail(i -> data);
    }
    return tmp;
    

  }; // создать список3, добавив список2 в текущий список после итератора 

  void MergeWith(const listIterator<DataType>& start, const List& list2)
  {
    auto last_old = last;
    auto ref = *(++start);
    last = *(start);
    last -> next = nullptr;
    for(auto i = list2.begin(); i != list2.end(); i++)
    {
      this -> InsertToTail(i -> data);
    }
    last -> next = ref;
    last = last_old;

  }; // в *this добавить список2 после итератора

  friend ostream& operator<<(ostream& os, const List<DataType>& l)
  {
    int i = 0;
    for(auto i = l.begin(); i != l.end(); i++)
    {
      os<<i<<"elem = "<<i -> data<<" adress: "<< i -> next<<endl;
      i++;
    }
    
  };

  friend istream& operator>>(istream& is, const List<DataType>& l)///////////////////////////////
  {
    // как адекватно то написать    
  };//////////////корректность ввода тип не Datatype
  
  void MadeUnique()///////////////////////////////
  {
    std::map<DataType, int> zxc;
    for (auto i = this -> begin(); i != this -> end(); i++)
    {
      if(zxc.find[i -> data] != zxc.end())
      {
        zxc[i -> data] = 1;
      }
      else zxc[i -> data]++;
    }
    for(auto& [keys, count] : zxc)
    {
      for(int i = 0; i < count -1;i++)
      {
        this ->Delete(keys);
      }
    } 
    
  }; // исключить повторяющиеся звенья

  bool Cycle()
  {
    Node <DataType>* slow= head;
    Node <DataType>* fast = head;
    while (fast != nullptr)
    {
      slow = slow -> next;
      fast = (fast -> next) -> next;
      if(slow == fast) return true;
    } 
    return false;
    //два бегунка
  };   // определить, есть ли цикл в списке

  void BreakCycle()
  {
    Node <DataType>* slow= head;
    Node <DataType>* fast = head;
    while (fast != nullptr)
    {
      slow = slow -> next;
      fast = (fast -> next) -> next;
      if(slow == fast) slow -> next = nullptr;
    } 
    //два бегунка, где сойдутся next = nullptr
  }; // "разомкнуть" цикл в списке

  std::string ToString()
  {
    string tmp ="";
    for(auto i = this -> begin(); i != this -> end(); i++)
    {
      tmp += (std::to_string(i -> data) + "; ");
    }
    tmp.pop_back();
    tmp.pop_back();

    return tmp;  
  }; // "зн 1; зн2; " 

  int GetSize()
  {
    int zxc = 0;
    for(auto i = this -> begin(); i != this -> end(); i++)
    {
      zxc++;
    }
    return zxc;

  }; // узнать число звеньев в списке
  
  List Merge(const List& list2)//////////////////////////////////
  {
    List tmp(*this);
    for (auto i = list2.begin(); i != list2.end(); i++)
    {
      tmp.InsertToTail(i -> data);
    }

  }; // создать список3, добавив в конец текущего списка список2

  bool operator==(const List& list2) const
  {
    if(this -> GetSize != list2 -> GetSize) return false;
    int i = 0;
    auto zxc1 = this -> begin();
    auto zxc2 = list2 -> begin();
    while (zxc1 != this -> end())
    {
      if(zxc1 -> data != zxc2 -> data) return false;
      zxc1++;
      zxc2++;
    }
    
    return true;

  }; // списки равны, если элементы в них идут в одинаковом порядке
};

#endif