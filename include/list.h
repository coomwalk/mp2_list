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
// 

template <typename DataType>
class listIterator : public std::iterator<std::forward_iterator_tag, DataType>
{
public:
	using iterator_category = std::forward_iterator_tag;
	using difference_type   = std::ptrdiff_t;
	using value_type = DataType;
	using pointer = Node<DataType>*;
	using reference = DataType&;

	listIterator(pointer tmp) : p(tmp) {};
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
    if (this -> isEmpty()) last = p;
    head = p;
  }; // вставить элемент d 

  DataType ViewHead()
  {
    if (head != nullptr)
    return head -> data;
    else throw "isempty";
  }; // посмотреть первого
  ////////////////////////////////
  void InsertToTail(const DataType& d)
  {
    Node<DataType>* p = new Node<DataType>(d);

    if((this -> isEmpty()))
    {
      last = p;
      head = p;
    }
    else
    {
      last -> next = p;
      last = p;
    }
  }; // вставить элемент d последним

  DataType ViewTail()
  {
    if (last != nullptr)
      return last -> data;
    else throw "isempty";
  }; // посмотреть последнего
			///////////////////////////////////////////							
  void Delete(const DataType& d)
  {
    if(!(this->isEmpty()))
    {
      Node<DataType>* tmp;
      Node<DataType>* prev;
      if (this -> GetSize() == 1 && head -> data == d )
      {
        delete head;
        head = nullptr;
        last =nullptr;
        return;
      }
      if(head -> data == d)
      {
        tmp = head;
        head = head -> next;
        delete tmp;
        return;
      }
        prev = head;
        tmp = head -> next;
        while(tmp != nullptr)
        {
          if(tmp -> data == d)
          {
            prev -> next = tmp ->next;
            if(tmp -> next == nullptr) last = prev;
            delete tmp;
            break;
          }
          prev = tmp;
          tmp = tmp -> next;
        }
      
    }
  }; // удалить звено со значением data = d	
  
  listIterator<DataType> begin() const
  {
    listIterator<DataType> tmp (head);
    return tmp;
  }; // получить итератор на первое звено 

  listIterator<DataType> tail() const
  {
    listIterator<DataType> tmp(last);
    return tmp;
  }; // получить итератор на последнее звено

  listIterator<DataType> end() const
  {
    listIterator<DataType> tmp(nullptr);
    return tmp;
  }; // получить итератор на конец списка


  ~List()
  {
    this -> BreakCycle();
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
  List( const List& list2)
  {
    if(list2.head == nullptr)
    {
      head = last = nullptr;
      return;
    }

    head = new Node<DataType>(list2.head -> data);
    last = head;
    for(auto i = ++list2.begin(); i!= list2.end(); i++)
    {
      (*this).InsertToTail(i->data);
    }
  };
  
  List& operator=(const List& list2)
  {
    if(this == &list2) return *this; 
    if(list2.head == nullptr)
    {
     this -> Clean();
     return *this;
    } 
    int k = list2.GetSize() - this -> GetSize();///
    if(this -> GetSize() < list2.GetSize())
    {
      for (int i = 0; i < k; i++ )
      {
        this -> InsertToTail(DataType{});
      }
    }
    if(this -> GetSize() > list2.GetSize())
    {
      auto a = this -> begin();
      for (int i = 0; i < -k; i++ )
      {
        auto tmp = a;
        a++;
        this -> Delete(tmp -> data);
        
      }
    }

    auto a2 = list2.begin();
    for(auto i = this -> begin(); i!= this -> end(); i++)
    {
      i -> data = a2 -> data;
      a2++;
    }
    return *this;
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
  			
  void InsertAfter( const listIterator<DataType>& it, const DataType& d)
  {
    Node <DataType>* tmp = new Node <DataType>(d);
    auto itcopy = it;
    if(itcopy == this -> tail())
    {
      last -> next = tmp;
      last = tmp;
      return;
    }
    tmp -> next =  itcopy -> next;
    itcopy -> next = tmp;
  }; // вставить элемент d после звена node

  listIterator<DataType> Search(const DataType& d)
  {
    for(auto i = this->begin(); i!= this -> end(); i++)
    {
      if(i -> data == d)
      {
        return i;
      }
    }
    return this -> end();

  }; // найти указатель на звено со значением data = d
  
  void Delete(const listIterator<DataType>& it)  
  {
    if(!(this ->isEmpty()) && it != this -> end())
    {
      if(this -> begin() == it && this -> GetSize() == 1 )
      {
        delete head;
        head = nullptr;
        last = nullptr;
        return;
      }
      if(this -> begin() == it)
      {
        auto tmp =  head->next;
        delete head;
        head = tmp;
        return;
      }
    if(this -> tail() == it)
    {
      Node <DataType>* next_last = head;
      while(next_last -> next != last)
      {
        
        next_last = next_last -> next;
      }
      next_last -> next = nullptr;
      delete last;
      last = next_last;
      return;
    }
    //общий случчай
    Node <DataType>* pnt = head;
    auto tmp_it = ++(this -> begin());
    while(tmp_it != it)
    {
      tmp_it++;
      pnt = pnt -> next;
    }
    auto it_copy = it;
    Node <DataType>* l = it_copy -> next;
    delete (pnt -> next);
    pnt -> next = l;
    }
   else throw "error isempty or it = end()";

  }; // удалить звено со значением data = d	
										////////////////////////



  void Delete(const listIterator<DataType>& start, const listIterator<DataType>& finish)
  {
    auto copy_start = start;
    auto copy_finish = finish;
    bool st = false;
    bool fn = false;
    for(auto i = this -> begin(); i != this -> end(); i++)
    {
      if (i == copy_start) st = true;
      if (i == copy_finish) fn = true;
      if (st == false && fn == true) throw "error itterators";
    }
    if (copy_start == this -> begin() && copy_finish == this -> end())
    {
      this -> Clean();
      return;
    }
    for(auto it = copy_start; it != copy_finish; )
    {
        auto tmp = it;
        tmp++;
        this -> Delete(it);
        it = tmp;
    }
  };

  void DeleteAll(const DataType& d)///bred
  {
    if(!(this->isEmpty()))
    {
      for (auto it = this -> begin(); it != this -> end();)
      {
        auto tmp = it;
        tmp++;
        if(it -> data == d) this -> Delete(it);
        it = tmp;
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
      
      Node <DataType>* old_head = head;


      while(tmp != nullptr)
      {
        head -> next = tmp -> next;
        tmp -> next = newfirst;
        newfirst = tmp;
        tmp = head -> next;
      }
      head = newfirst;
      last = old_head;
    }

  }; // инвертировать список, т.е. звенья должны идти в обратном порядке

  List Merge(const listIterator<DataType>& start, const List& list2)
  {
    if(start != this -> end())
    {
    List <DataType> tmp;
    //insert to tail data
    auto copy_st = start;
    for(auto i = this -> begin(); i != copy_st; i++)
    {
      tmp.InsertToTail(i -> data);
    }
    tmp.InsertToTail(copy_st -> data);
    for(auto i = list2.begin(); i != list2.end(); i++)
    {
      tmp.InsertToTail(i -> data);
    }
    auto end = ++copy_st;
    for(auto i = end; i != this -> end(); i++)
    {
      tmp.InsertToTail(i -> data);
    }
    return tmp;
    }
    else throw "error it";

  }; // создать список3, добавив список2 в текущий список после итератора 

  void MergeWith(const listIterator<DataType>& start, const List& list2)// bred
  {
    if(start != this -> end())
    {
      auto copy_st = start;
      for(auto i = list2.begin(); i != list2.end(); i++)
      {
       this -> InsertAfter(copy_st, i -> data);
       copy_st++;
      }
    }
    else throw "error it";
  }; // в *this добавить список2 после итератора

  friend ostream& operator<<(ostream& os,  List<DataType>& l)
  {
    int k = 0;
    for(auto i = l.begin(); i != l.end(); i++)
    {
      os<<k<<" elem = "<<i -> data<<" next adress: "<< i -> next<<endl;
      k++;
    }
    
  };

  //friend istream& operator>>(istream& is,  List<DataType>& l)///////////////////////////////
 // {
   // DataType x;
//try {
  //  is >> x;
 //   l.InsertToTail(x);
//}
//catch (...) {}
    // как адекватно то написать    
//  };//////////////корректность ввода тип не Datatype
  
  void MadeUnique()
  {
    std::map<DataType, int> zxc;
    for (auto i = this -> begin(); i != this -> end(); i++)
    {
      if(zxc.find(i -> data) == zxc.end())
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
    while (fast != nullptr && fast->next != nullptr)
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
    if(this -> Cycle())
    {
    Node <DataType>* slow= head;
    Node <DataType>* fast = head;
    while (fast != nullptr && fast->next != nullptr)
    {
      slow = slow -> next;
      fast = (fast -> next) -> next;
      if(slow == fast) fast -> next = nullptr;
    } 
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

  int GetSize() const
  {
    int zxc = 0;
    for(auto i = this -> begin(); i != this -> end(); i++)
    {
      zxc++;
    }
    return zxc;

  }; // узнать число звеньев в списке
  
  List Merge(const List& list2)
  {
    List tmp(*this);
    for (auto i = list2.begin(); i != list2.end(); i++)
    {
      tmp.InsertToTail(i -> data);
    }
    return tmp;

  }; // создать список3, добавив в конец текущего списка список2

  bool operator==( const List& list2) const 
  {
    if(this -> GetSize() != list2.GetSize()) return false;
    int i = 0;
    auto zxc1 = this -> begin();
    auto zxc2 = list2.begin();
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