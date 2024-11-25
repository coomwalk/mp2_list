#include "list.h"

Node::Node(DataType d, Node* n) : data(d), next(n)
{
}

Node::Node(const Node& node2)
{
	data = node2.data;
}

bool Node::operator==(const Node& node2) const
{
	return (data == node2.data);
}

List::List() : head(nullptr) {}

void List::InsertToHead(const DataType& d)
{
	Node* p = new Node(d, head);
	// Node* p = new Node;
	//p->data = d;
	//p->next = head;
	head = p;
}

void List::InsertToTail(const DataType& d)
{
	Node* tmp; // ходилка
	tmp = head;

	if (isEmpty())
	{
		InsertToHead(d);
	}
	else
	{
		while (tmp->next != nullptr) // это признак хвоста
		{
			tmp = tmp->next;
		}
		tmp->next = new Node(d, nullptr);
	}
}

DataType List::ViewTail()
{
	if (isEmpty())
		throw std::logic_error("list is empty");
	else
	{
		Node* tmp = head; // ходилка
		while (tmp->next != nullptr) // это признак хвоста
		{
			tmp = tmp->next;
		}
		return tmp->data;
	}
}

void List::Delete(const DataType& d)
{
	Node* tmp = head; // ходилка
	Node* prev = nullptr;

	while ((tmp!= nullptr) && (tmp->data != d))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp != nullptr) 
	{
		if (prev != nullptr)
		{
			prev->next = tmp->next;
		}
		else
		{
			// это голова
			head = head->next;
		}
		delete tmp;
	}
}

listIterator List::tail()
{
	Node* tmp = head; // ходилка
	while (tmp->next != nullptr) // это признак хвоста
	{
		tmp = tmp->next;
	}
	return listIterator(tmp);
}

listIterator List::end()
{
	return listIterator();
}

List::~List()
{
}


