#pragma once
typedef unsigned int uint;
#include<iostream>
namespace Mstd{
template<typename T>
struct Node_
{
private:
	T val;
public:
	Node_* next = nullptr;
	Node_() {}
	Node_(T val) { this->val=val; }
	T GetVal() { return val; }
	T& Val() { return val; }
	//For Array
	static Node_* Create(T* begin, T* end)
	{
		Node_* head, * p, * tail = nullptr;
		head = nullptr;
		for (T* q = begin; q < end; q++)
		{
			p = new Node_(*q);
			if (q == begin)head = tail = p;
			else
			{
				tail->next = p;
				tail = p;
			}
		}
		tail->next = nullptr;
		return head;
	}
	static Node_* Create(T* Array, uint Length)
	{
		Node_* head, * p, * end = nullptr;
		head = nullptr;
		for (uint i=0;i<Length;i++)
		{
			p = new Node_(Array[i]);
			if (i==0)head = end = p;
			else
			{
				end->next = p;
				end = p;
			}
		}
		end->next = nullptr;
		return head;
	}
	void insert(Node_*& list, T val)
	{
		Node_* p = list;
		while (p->next)
		{
			if (p->next->val > val)
			{
				Node_* q = new Node_(val);
				q->next = p->next;
				p->next = q;
				return ;
			}
			p = p->next;
		}
		Node_* q = new Node_(val);
		p->next = q;
		p = q;
		return;
	}
	static void Create(Node_*& list, T* arr, uint length)
	{
		static uint i = 0;
		if (i == length)return;
		list = new Node_(arr[i]);
		i++;
		Create(list->next, arr, length);
	}
	static void Create_h(Node_*& list, T* arr,uint length)
	{
		static uint i = 0;
		if (i == length) {
			 return;
		}
		if (i == 0) {
			list = new Node_(arr[i++]);
		}
		Node_* p;
		p =new Node_(arr[i++]);
		p->next = list;
		list = p;
		Create_h(list, arr,length);	
	}
	static Node_* Create(T array[], int Length)
	{
		Node_* head = new Node_(array[Length - 1]);
		Node_* p;
		int i = Length - 2;
		while (i >= 0)
		{
			p = new Node_(array[i--]);
			p = head->next;
			head->next = p->next;
		}
		head->next = nullptr;
		return head;
	}
	template<class Ty> friend ostream& operator<< (ostream & out, Node_<Ty>&n);
};
template<class Ty>
ostream& operator<< (ostream & out, Node_<Ty>n)
{
	out << n.val;
	return out;
}
template<typename T>
class List
{
	Node_<T>* linklist;
	uint Length;
	typedef Node_<T> LNode;
	typedef LNode* iterator;
	LNode* Begin;
	LNode* End=nullptr;
private:
	void Heap(T *arr,uint start,uint length)
	{
		int dad = start;
		int son = 2 * dad + 1;
		while (son < length)
		{
			if (son + 1 < length && arr[son] < arr[son + 1])
				son++;
			if (arr[dad]>arr[son])return;
			else {
				T t; t = arr[son]; arr[son] = arr[dad]; arr[dad] = t;
				dad = son;
				son = 2 * dad + 1;
			}
		}
	}
public:
	List() {
		this->linklist =nullptr; this->Length = 0; Begin = linklist;
	}
	List(T* begin , T* end) { 
		if (this->linklist)clear(); linklist =Node_<T>::Create(begin, end);
	int k = 0; for (T* q = begin; q < end; q++,k++);
	Length = k;
	Begin = linklist;
	}
	List(T* Array, uint Length) {
		if (this->linklist)clear();
		linklist = Node_<T>::Create(Array, Length); this->Length = Length; Begin = linklist;
	}
	uint length() { return Length; }
	iterator begin() { return linklist; }
	iterator end() { return this->End; }
	void assign(T* begin, T* end)
	{
		if (this->linklist)clear();
		linklist = Node_<T>::Create(begin, end);
		int k = 0; for (T* q = begin; q < end; q++, k++);
		Length = k;
		Begin = linklist;
	}
	void assign(T* Array, uint Length)
	{
		if (this->linklist)clear();
		linklist = Node_<T>::Create(Array, Length); 
		this->Length = Length;
		Begin = linklist;
	}
	void push_back(T val)
	{
		Node_<T>* p;
		p = new Node_<T>(val);
		if (linklist== nullptr) { End=linklist = p; Length++; return; }
			End->next = p;
			End = p;
		Length++;
	}
	T* ToArray()
	{
		LNode* p;
		p = linklist;
		if(p==nullptr)return nullptr;
		T* q = new T[Length];
		int i = 0;
		while (p)
		{
			q[i++] = p->GetVal();
			p = p->next;
		}
		return q;
	}
	void clear()
	{
		LNode* p;
		while (linklist)
		{
			p = linklist;
			linklist = p->next;
			delete p;
		}
	}
	bool isempty() { return linklist == nullptr; }
	template<class Ty> friend ostream& operator <<(ostream& out, List<Ty>& L);
	iterator find(const T val)
	{
		if (isempty())return End;
		iterator p = linklist;
		while (p)
		{
			if (p->GetVal() == val)
				break;
			p = p->next;
		}
		return p;
	}
	void Sort()
	{
		T* arr = ToArray();
		int i;
		for (i = Length / 2 - 1; i >= 0; i--)
			Heap(arr, i, Length);
		for (i = Length - 1; i > 0; i--)
		{
			T t;
			t = arr[0]; arr[0] = arr[i]; arr[i] = t;
			Heap(arr, 0, i);
		}
		clear();
		linklist = LNode::Create(arr, arr + Length);
		delete[]arr;
	}
	void reverse()
	{	
		if (isempty())return;
		T* a = ToArray();
		LNode* q,*head=new LNode(a[Length-1]);
		int i = 0;
		while (i < Length-1)
		{
			q = new LNode(a[i++]);
			q->next = head->next;
			head->next = q;
		}
		clear();
		linklist = head;
		delete[]a;
    }
	T& operator[](uint index)
	{
		int count = 0;
	if (index == 0 && linklist == nullptr) {
			T* t = new T;
			linklist = new LNode(*t);
			delete t;
			Length++;
			return linklist->Val();
		}
		LNode* p = linklist;
		if (index < Length)
		{
			while (p)
			{
				if (count == index)
					break;
				count++;
				p = p->next;
			}
			return p->Val();
		}
		else if (index == Length)
		{
			T* t = new T;
			LNode* q = new LNode(*t);
			delete t;
			while (p->next)p = p->next;
			p->next = q;
			p = q;
			Length++;
			return q->Val();
		}
		else return *new T;
	}
	int remove(iterator where)
	{
		iterator p =linklist;
		LNode* q;
		int count = 0;
		//if (p == where) { p = where->next; where->next = p->next; delete p; return where; }
		if (where == linklist) { q = p; linklist = q->next; delete q; Length--; return count; }
		else
		{
			while (p->next)
			{
				if (where->GetVal() == p->next->GetVal())
				{
					q = p->next; p->next = q->next; delete q; Length--; count++; break;
				}
				p = p->next;
				count++;
			}
			if (count <= Length)return count;
			else return -1;
		}
	}
	bool remove(T val)
	{
		iterator p = linklist;
		iterator q;
		if (linklist->GetVal() == val) { q = linklist; linklist = q->next; Length--; delete q; return true; }
		while (p->next)
		{
			if (p->next->GetVal() == val)
			{
				q = p->next; p->next = q->next; Length--; delete q; break;
			}
			p = p->next;
		}
		return p->next != nullptr;
	}
	iterator remove(uint position,iterator bedeleted)
	{
		LNode* q, * p = linklist;
		if (position == 0) { q = linklist; bedeleted->Val() = linklist->GetVal(); linklist = q->next;  delete q; Length--; return bedeleted; }
		else {
			int count = 0;
			while (p->next)
			{
				if (count == position-1)
				{
					q = p->next;bedeleted->Val() = p->next->GetVal(); p->next = q->next;  delete q; Length--; return bedeleted;
				}
				count++;
				p = p->next;
			}
		}
		return end();
	}
	void pop_back()
	{
		LNode l;
		remove(length() - 1, &l);
	}
	bool insert(T val,long position)
	{
		LNode* p = linklist;
		LNode* q;
		 if (position == Length) {
			push_back(val); return true;
		}
		else if (position == 0) {
			q = new LNode(val);  q->next = p;  linklist = q; Length++;
		return true; }
		else
		{
			long count = 1;
			while (p)
			{
				if (count==position)
				{
					q = new LNode(val);
					q->next = p->next;
					p->next = q;
					Length++;
				}
				count++;
				p = p->next;
			}
			if (count > Length)return false;
			else return true;
		}
	}
	~List(){}
	void unique()
	{
		Sort();
		T* arr = ToArray();
		int j = 0;
		this->Sort(arr, Length);
		for (int i = 0; i < Length; i++)
		{
			if (arr[i] != arr[i + 1])arr[j++] = arr[i];
		}
		clear();
		linklist = LNode::Create(arr, arr + j);
		Length = j;
		delete[]arr;
	}
	void swap(List& list)
	{
		List t(*this);
		linklist = list.linklist;
		Length = list.length();
		list = t;
	}
	void List_Adress()
	{
		LNode* p = linklist;
		while (p)
		{
			cout << p << endl;
			p = p->next;
		}
	}
	
};
template<class Ty>
ostream& operator <<(ostream& out, List<Ty>& L)
{
	Node_<Ty>* p=L.linklist;
	if (!L.isempty())
	{
		out << "[";
		while (p)
		{
			out << p->GetVal();
			if (p->next != nullptr)
				out << ",";
			p = p->next;
		}
		out << "]";
	}
	else out << "empty list";
	return out;
}
template<class Ty>
struct TNode
{
private:
	Ty val;
	typedef TNode* Lnode;
public:
	Lnode last = nullptr;
	Lnode next = nullptr;
	TNode() {}
	TNode(Ty val)
	{
		this->val = val;
	}
	Ty& value() { return val; }
	static Lnode Create(Ty arr[], uint length)
	{
		Lnode p, end, head;
		head = end = nullptr;
		for (uint i = 0; i < length; i++)
		{
			p = new TNode(arr[i]);
			if (i == 0)head = end = p;
			else {
				end->next = p;
				p->last = end;
				end = p;

			}
		}
		return head;
	}
	static TNode* Create(Ty* begin, Ty* end)
	{
		Lnode p, head;
		head= nullptr;
		for (Ty* q = end - 1; q >= begin; q--)
		{
			p = new TNode(*q);
			if (q==end-1)head= p;
			else {
				head->last = p;
				p->next = head;
				head = p;
			}
		}
		return head;
	}
};
template<class Ty>
class TList
{
	typedef TNode<Ty> Node;
	typedef Node* Lnode;
	typedef Lnode iterator;
	Lnode linklist;
	Lnode End;
	uint len;
	void exc(Ty& a, Ty& b)
	{
		Ty t;
		t = a; a = b; b = t;
	}
	void Heap(Ty* arr, uint s, uint length)
	{
		uint dad = s;
		uint son = dad * 2 + 1;
		while (son < length)
		{
			while (son + 1 < length && arr[son] < arr[son + 1])
				son++;
			if (arr[son] < arr[dad])return;
			else {
				exc(arr[son], arr[dad]);
				dad = son;
				son = 2 * dad + 1;
			}
		}
	}
	void Heapsort(Ty* arr, uint length)
	{
		int i;
		for (i = length / 2 - 1; i >= 0; i--)
			Heap(arr, i, length);
		for (i = length - 1; i > 0; i--)
		{
			exc(arr[0], arr[i]);
			Heap(arr, 0, i);
		}
	}
	typedef pair<iterator, bool> insdel;
public:
	TList() { End=linklist = nullptr; len = 0; }
	TList(Ty* arr, uint length)
	{
		End=linklist = Node::Create(arr, length);
		len = length;
	}
	bool operator ==(TList t)
	{
		return true;
	}
	TList(Ty* begin, Ty* end)
	{
		uint k = 0;
		for (Ty* p = begin; p < end; p++, k++);
		len = k;
		this->End=linklist = Node::Create(begin, end);
	}
	uint size() { return len; }
	iterator begin() { return linklist; }
	iterator end() {
		return nullptr;
	}
	iterator rbegin() {
		return End;
	}
	iterator rend() { return nullptr;}
	void push_back(const Ty& val)
	{
		Node* q = new Node(val);
		if (empty())
		{
			End=linklist = q; len++; return;
		}
		Lnode p = new Node(val);
		End->next = p;
		p->last = End;
		End = p;
		len++;
	}
	void push_back(Ty&& val)
	{
		Node* q = new Node(val);
		if (empty())
		{
			End=linklist = q; len++; return;
		}
		Lnode p = new Node(val);
		End->next = p;
		p->last = End;
		End = p;
		len++;
	}
	void push_front(const Ty& val)
	{
		Node* q = new Node(val);
		if (empty())
		{
			linklist = q; len++; return;
		}
		linklist->last = q;
		q->next = linklist;
		linklist = q;
		len++;
	}
	void push_front(Ty&& val)
	{
		Node* q = new Node(val);
		if (empty())
		{
			linklist = q; len++; return;
		}
		linklist->last = q;
		q->next = linklist;
		linklist = q;
		len++;
	}
	bool empty() {
		return linklist == nullptr;
	}
	Ty* toArray_z()
	{
		Lnode p = linklist;
		Ty* arr = new Ty[len];
		uint i = 0;
		while (p)
		{
			arr[i++] = p->value();
			p = p->next;
		}
		return arr;
	}
	Ty* toArray_n()
	{
		Lnode p = rbegin();
		Ty* arr = new Ty[len];
		int i = 0;
		while (p)
		{
			arr[i++] = p->value();
			p = p->last;
		}
		return arr;
	}
	void sort_z()
	{
		Ty* arr = toArray_z();
		Heapsort(arr, len);
		uint length = len;
		clear();
		linklist = Node::Create(arr, length);
		len = length;
		delete[]arr;
	}
	pair<iterator, bool> insert(uint position, Ty val)
	{
		pair<iterator, bool> p;
		Node* q = linklist;
		if (position < 0)return pair<iterator, bool>(nullptr, false);
		uint count = 0;
		iterator it = new Node(val);
		if(position==0){
			push_front(val);
			return pair<iterator, bool>(it, true);
		}
		if (position == len) {
			push_back(val);
			return pair<iterator, bool>(it, true);
		}
		while (q)
		{
			if (count == position-1)
			{
				
				it->next = q->next;
				it->last = q;
				q->next->last = it;
				q->next =it;	
				len++;
			}
			count++;
			q = q->next;
		}
		return pair<iterator, bool>(it, true);
	}
	void pop_back()
	{
		if (empty())return;
		if (len == 1) {
			delete linklist;
			linklist = nullptr;
			len--;
			return;
		}
		iterator p = rbegin();
		iterator q = p->last;
		q->next = nullptr;
		delete p;
		len--;
	}
	void pop_front()
	{
		Lnode p = linklist;
		if (p == nullptr)return;
		if (len == 1) {
			delete linklist;
			linklist = nullptr;
			--len;
			return;
		}
		Lnode q = p->next;
		delete p;
		linklist = q;
		linklist->last = nullptr;
		len--;
	}
	void sort_n()
	{
		Ty* arr = toArray_z();
		Heapsort(arr, len);
		uint length = len;
		int i;
		for (i = 0; i < len / 2; i++)
			exc(arr[i], arr[len - 1 - i]);
		clear();
		len = length;
		linklist = Node::Create(arr, arr+len);
		delete[]arr;
	}
	iterator find(Ty val)
	{
		iterator it=nullptr, p=linklist;
		while (p)
		{
			if (p->value() == val)
			{
				it = p;
				break;
			}
			p = p->next;
		}
		return it;
	}
	iterator find_p(uint position)
	{
		if (position >= len)return nullptr;
		uint count = 0;
		Lnode p = linklist;
		while (p)
		{
			if (count == position)
				break;
			p = p->next;
			count++;
		}
		return p;
	}
	insdel remove_v(Ty val)
	{
		iterator it=nullptr,q;
		q=it = find(val);
		insdel id;
		if (q == nullptr) return insdel(nullptr, false);
		id.second = it != nullptr;
			if (q->last == nullptr)
			{
				id.first = linklist; pop_front();
				return id;
			}
			else if (q->next == nullptr)
			{
				id.first = rbegin();
				pop_back();
				return id;
			}
			it->last->next = it->next;
			it->next->last = it->last;
			len--;
			delete it;
			return id;
		}
	insdel remove_p(uint position)
	{
		insdel id;
		if (position == 0)
		{
			id = insdel(linklist, true);
			pop_front();
			return id;
		}
		if (position == len - 1)
		{
			id = insdel(rbegin(), true);
			pop_back();
			return id;
		}
		uint count = 0;
		iterator it = linklist,q;
		while (it->next)
		{
			if (count == position - 1)
			{
				q = it->next;
				it->next = q->next;
				q->next->last = it;
				id = insdel(q, true);
				len--;
				delete q;
				return id;
			}
			count++;
			it = it->next;
		}
			return insdel(nullptr, false);
	}
	void clear() {
		Lnode p;
		while (linklist)
		{
			p = linklist;
			linklist = p->next;
			delete p;
		}
		len =0;
	}
	void unique()
	{
		Ty* arr = toArray_z();
		int i, j = 0;
		Heapsort(arr, len);
		for (i = 0; i < len; i++)
		{
			if (arr[i] != arr[i + 1])arr[j++]=arr[i];
		}
		clear();
		linklist = Node::Create(arr, j);
		len = j;
		delete[]arr;
	}
	~TList() {  }
	Ty front() { return linklist->value(); }
	Ty back() { return End->value(); }
	void swap(TList& tl)
	{
		TList t(*this);
		linklist = tl.linklist;
		len = tl.len;
		tl = t;
	}
	void reverse()
	{
		int* a = toArray_n();
		uint len = this->len;
		clear();
		this->len = len;
		linklist = Node::Create(a, this->len);
		delete[]a;
	}
	void merge(TList tl)
	{
		if (empty()) {
			End=linklist = tl.linklist; len = tl.len; return;
		}
		Lnode p = tl.linklist;
		while (p)
		{
			Lnode q = new Node(p->value());
			End->next = q;
			q->last = End;
			End = q;
			p = p->next;
		}
		len += tl.len;
	}
	void assign(Ty* arr,uint length)
	{
		if (!empty())clear();
		linklist = Node::Create(arr, length);
		len = length;
	}
	void assign(Ty* begin,Ty* end)
	{
		if (!empty())clear();
		uint k = 0;
		for (Ty* p = begin; p < end; p++, k++);
		len = k;
		linklist = Node::Create(begin, end);
	}
	void assign(const TList tl)
	{
		if (!empty())clear();
		linklist = tl.linklist;
		len = tl.len;
	}
	/*void Adressout_Z()
	{
		Lnode p = linklist;
		while (p)
		{
			cout << p << endl;
			p = p->next;
		}
	}*/
	template<class T> friend ostream& operator<<(ostream&, TList<T>);
};
template<class T>
ostream& operator<<(ostream& out, TList<T> tl)
{
	TNode<T>* p=tl.linklist;
	cout << "[";
	while (p)
	{
		out << p->value();
		if (p->next != nullptr)
			cout << ',';
		p = p->next;
	}
	out << "]";
	return out;
}
}