
#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H
#include<iostream>
#include "Exception.h"
#define nullptr NULL
template<typename Type>
class Double_sentinel_list
{
public:
	class Double_node
	{
	public:
		Double_node(Type const& = Type(), Double_node* = nullptr, Double_node* = nullptr);
		Type node_value;
		Double_node* previous_node;
		Double_node* next_node;
		Type value() const;
		Double_node* next() const;
		Double_node* previous() const;
	};
	Double_sentinel_list();
	~Double_sentinel_list();
	Double_sentinel_list(Double_sentinel_list const&);
	Double_sentinel_list(Double_sentinel_list&&);
	//Accessors
	int size() const; 
	void traversal(); 
	bool empty() const; 
	Type front() const; 
	Type back() const; 
	Double_node* begin() const; 
	Double_node* end() const; 
	Double_node* rbegin() const; 
	Double_node* rend() const;
	Double_node* find(Type const&) const;
	int count(Type const&) const; 
	//Mutators
	void swap(Double_sentinel_list& );
	Double_sentinel_list& operator=(Double_sentinel_list const);
  	Double_sentinel_list& operator=(Double_sentinel_list&&); 
	void push_front(Type const&); 
	void push_back(Type const&); 
	void pop_front(); 
	void pop_back(); 
	int erase(Type const& value);
private:
	int list_size;
	Double_node* head;
	Double_node* tail;
	
};
//declarations
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list()
{
	head = new typename Double_sentinel_list<Type>::Double_node(0, nullptr, nullptr);
	tail = new Double_sentinel_list<Type>::Double_node(0, nullptr, nullptr);
	//List head is now a double node (Acts like a head sentinel) which contains null with 2 nullptrs. 
	//List tail is now a double node (Acts like a tail sentinel) and will contain null and 2 pointers. Update its 'previous' pointer to point to the head sentinel.
	list_size = 0; //THe list size is 0 since list is empty.
	head->next_node = tail;
	tail->previous_node = head;

}
  template<typename Type>
 Double_sentinel_list<Type>::~Double_sentinel_list()
 {
 	list_size=0;
 	typename Double_sentinel_list<Type>::Double_node* ptr =head;
 	while (ptr != end())
 	{
		typename Double_sentinel_list<Type>::Double_node* tmp = ptr;
       ptr = ptr->next_node;
 		delete tmp;
		tmp = nullptr;
 	}
	delete ptr;
	ptr = nullptr;
 } 

 template<typename Type>
 Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type> const& list)
 {
 	list_size = list.list_size;
	typename Double_sentinel_list<Type>::Double_node* ptr = (list.head);
	ptr = ptr->next_node;
	head = new typename Double_sentinel_list<Type>::Double_node(0, nullptr, nullptr);
	tail = new typename Double_sentinel_list<Type>::Double_node(0, head, nullptr);
	head->next_node = tail;
	typename Double_sentinel_list<Type>::Double_node* cur = head;
 	while (ptr!=list.end())
 	{
 		typename Double_sentinel_list<Type>::Double_node* obj=new typename Double_sentinel_list<Type>::Double_node(ptr->node_value, cur, nullptr);
		cur->next_node = obj;
		cur = obj;
		ptr = ptr->next_node;
 	}
	tail->previous_node = cur;
	cur->next_node = tail;
}
 template<typename Type>
 Double_sentinel_list<Type>::Double_sentinel_list(Double_sentinel_list<Type>&& list)
{
	 head = new Double_node(0, nullptr, nullptr);
	 tail = new Double_node(0, head,  nullptr);
	 head->next_node = tail;
	 list_size = 0;
     swap(list);
 } 
// //Accessors Declaration
template<typename Type>
int Double_sentinel_list<Type>::size() const
{
	return list_size;
}
template<typename Type>
bool  Double_sentinel_list<Type>::empty() const
{
	if (list_size == 0)
		return true;
	else
		return false;
}
template<typename Type>
Type Double_sentinel_list<Type>::front() const
{
	if (empty())
	{
		throw underflow();
	}
	typename Double_sentinel_list<Type>::Double_node* obj = head->next_node;
	return obj->node_value;


}
template<typename Type>
Type Double_sentinel_list<Type>::back() const
{
	if (empty())
	{
		throw underflow();
	}
	typename Double_sentinel_list<Type>::Double_node* obj = tail->previous_node;
	return obj->node_value;
}
template<typename Type>
typename Double_sentinel_list<Type>::Double_node* Double_sentinel_list<Type>::begin() const
{
	return head->next();
}
template<typename Type>
typename Double_sentinel_list<Type>::Double_node* Double_sentinel_list<Type>::end() const
{
	return tail;
}
template<typename Type>
typename Double_sentinel_list<Type>::Double_node* Double_sentinel_list<Type>::rbegin() const
{

	return tail->previous_node;
}
template<typename Type>
typename Double_sentinel_list<Type>::Double_node* Double_sentinel_list<Type>::rend() const
{
	return head;
}
template<typename Type>
typename Double_sentinel_list<Type>::Double_node* Double_sentinel_list<Type>::find(Type const& obj) const
{
	typename Double_sentinel_list<Type>::Double_node* ptr = head->next_node;
	while (ptr != end())
	{
		if (ptr->node_value == obj)
			return ptr;
		ptr = ptr->next_node;
	}
	return end();
}
template<typename Type>
int Double_sentinel_list<Type>::count(Type const& obj) const
{
	int cnt = 0;
	typename Double_sentinel_list<Type>::Double_node* ptr = head;
	while (ptr != end())
	{
		if (ptr->node_value == obj)
			cnt++;
		ptr = ptr->next_node;
	}
	return cnt;
}

//Mutators Declaration
template <typename Type>
void Double_sentinel_list<Type>::swap(Double_sentinel_list<Type>& list)
{
	std::swap(head, list.head);
	std::swap(tail, list.tail);
	std::swap(list_size, list.list_size);
}
template <typename Type>
Double_sentinel_list<Type>& Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type>  rhs)
{
	swap(rhs);
	return *this;
}
template<typename Type>
Double_sentinel_list<Type>& Double_sentinel_list<Type>::operator=(Double_sentinel_list<Type>&& rhs)
{
	swap(rhs);
	return *this;
} 
template<typename Type>
void  Double_sentinel_list<Type>::push_front(Type const& new_value)
{
	typename Double_sentinel_list<Type>::Double_node* obj = new typename Double_sentinel_list<Type>::Double_node(new_value, head, head->next_node);
	head->next_node->previous_node = obj;
	head->next_node = obj;
	++list_size;
}
template<typename Type>
void  Double_sentinel_list<Type>::push_back(Type const& new_value)
{
	typename Double_sentinel_list<Type>::Double_node* ptr = new typename Double_sentinel_list<Type>::Double_node(new_value, tail->previous_node, tail);
	tail->previous_node->next_node = ptr;
	tail->previous_node = ptr;
	++list_size;
}
template<typename Type>
void  Double_sentinel_list<Type>::traversal()
{
	typename Double_sentinel_list<Type>::Double_node* ptr = head->next_node;
	while (ptr != end())
	{
		std::cout << ptr->node_value;
		std::cout << "\n";
		ptr = ptr->next_node;
	}
}

template<typename Type>
void  Double_sentinel_list<Type>::pop_front()
{
	if (empty())
	{
		throw underflow();
	}

	typename Double_sentinel_list<Type>::Double_node* obj = head->next_node;
	head->next_node = obj->next_node;
	obj->next_node->previous_node = head;
	delete obj;
	obj = nullptr;
	--list_size;


}
 template<typename Type>
 void Double_sentinel_list<Type>::pop_back()
 {
 	if (empty())
		throw underflow();
 	typename Double_sentinel_list<Type>::Double_node* obj = tail->previous_node;
	obj->previous_node->next_node = tail;
	 tail->previous_node = obj->previous_node;
 	delete obj;
	obj = nullptr;
	--list_size;
 }
template<typename Type>
int Double_sentinel_list<Type>::erase(Type const& value)
{
	int cnt = 0;
	typename Double_sentinel_list<Type>::Double_node* ptr = head->next_node;
	while (ptr != end())
	{

		typename Double_sentinel_list<Type>::Double_node* ptr2 = nullptr;
		if (ptr->node_value == value)
		{
			cnt++;
			ptr->previous_node->next_node = ptr->next_node;
			ptr->next_node->previous_node = ptr->previous_node;
			 ptr2 = ptr;
		}
		ptr = ptr->next_node;
		if (ptr2 != nullptr)
		{
			delete ptr2;
			ptr2 = nullptr;
		}

	}
	list_size-=cnt;
	return cnt;
}
template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const& nv,
	typename Double_sentinel_list<Type>::Double_node* pn,
	typename Double_sentinel_list<Type>::Double_node* nn) :
	// Updated the initialization list here
	node_value(nv), // This assigns 'node_value' the default value of Type
	previous_node(pn),
	next_node(nn)
{
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	// Enter your implementation here
	return node_value; // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node* Double_sentinel_list<Type>::Double_node::previous() const {
	// Enter your implementation here
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node* Double_sentinel_list<Type>::Double_node::next() const {
	// Enter your implementation here
	return next_node;
}
#endif
