//#pragma once
//#include<stdio.h>
//template<class T> class Node;
//template<class T> class DLinkedList;
//template<class T> class DLinkedListIterator;
//
//template<class T>
//class Node
//{
//private:
//public:
//	Node<T>()
//	{
//	}
//	~Node<T>()
//	{
//	}
//
//	Node<T>* _next;
//	Node<T>* _prev;
//	T _data;
//
//	void InsertAfter(T data) {
//		Node<T>* newNode = new Node<T>();
//		newNode->_prev = this;
//		newNode->_next = _next;
//		newNode->_data = data;
//		if (0 != _next) {
//			_next->_prev = newNode;
//		}
//		_next = newNode;
//	}
//	void InsertBefore(T data) {
//		Node<T>* newNode = new Node<T>();
//		newNode->_prev = _prev;
//		newNode->_next = this;
//		newNode->_data = data;
//		if (0 != _prev) {
//			_prev->_next = newNode;
//		}
//		_prev = newNode;
//	}
//	void Dlink()
//	{
//		if (0 != _prev)
//			_prev->_next = _next;
//		if (0 != _next)
//			_next->_prev = _prev;
//	}
//};
//template<class T>
//class DLinkedList
//{
//private:
//public:
//	DLinkedList<T>()
//	{
//		_head = 0;
//		_tail = 0;
//		_count = 0;
//	}
//
//	~DLinkedList<T>()
//	{
//		Node<T>* _node = _head;
//		Node<T>* _next;
//		while (0 != _node)
//		{
//			_next = _node->_next;
//			delete _node;
//			_node = _next;
//		}
//	}
//	Node<T>* _head;
//	Node<T>* _tail;
//	int _count;
//
//	int Count()
//	{
//		return _count;
//	}
//	void Append(T data)
//	{
//		if (0 == _head)
//		{
//			Node<T>* node = new Node<T>();
//			node->_data = data;
//			node->_next = 0;
//			node->_prev = 0;
//			_head = node;
//			_tail = node;
//			_count++;
//		}
//		else
//		{
//			_tail->InsertAfter(data);
//			_tail = _tail->_next;
//			_count++;
//		}
//	}
//	void Preppend(T data)
//	{
//		if (0 == _head)
//		{
//			Node<T>* node = new Node<T>();
//			node->_data = data;
//			node->_next = 0;
//			node->_prev = 0;
//			_head = node;
//			_tail = node;
//			_count++;
//		}
//		else
//		{
//			_head->InsertBefore(data);
//			_head = _head->_prev;
//			_count++;
//		}
//	}
//	void RemoveHead()
//	{
//		if (0 == _head)
//		{
//			_tail = 0;
//		}
//		else
//		{
//			Node<T>* newNode = _head->_next;
//			delete _head;
//			_head = newNode;
//
//			_head->_prev = 0;
//		}
//		_count--;
//	}
//	void RemoveTail()
//	{
//		if (0 == _tail)
//		{
//			_head = 0;
//		}
//		else
//		{
//			Node<T>* newNode = _tail->_prev;
//			delete _tail;
//			_tail = newNode;
//			_tail->_next = 0;
//		}
//		_count--;
//	}
//	DLinkedListIterator<T> GetIterator()
//	{
//		return DLinkedListIterator<T>(this, _head);
//	}
//	void Remove(DLinkedListIterator<T>& itr)
//	{
//		if (0 == itr._node)
//		{
//			return;
//		}
//		else
//		{
//			Node<T>* newNode = itr._node;
//			if (newNode == _head)
//			{
//				_head = _head->_next;
//			}
//			if (newNode == _tail)
//			{
//				_tail = _tail->_prev;
//			}
//
//			itr.Force();
//			newNode->Dlink();
//			delete newNode;
//
//			if (0 == _head)
//			{
//				_tail = 0;
//			}
//			_count--;
//		}
//	}
//	void InsertAfter(DLinkedListIterator<T>& itr, T data)
//	{
//		if (0 != itr._node)
//		{
//			itr._node->InsertAfter(data);
//			if (itr._node == _tail)
//			{
//				_tail = itr._node->_next;
//			}
//			_count++;
//		}
//		else
//		{
//			Append(data);
//		}
//	}
//	void InsertBefore(DLinkedListIterator<T>& itr, T data)
//	{
//		if (0 != itr._node)
//		{
//			itr._node->InsertBefore(data);
//			if (itr._node == _head)
//			{
//				_head = itr._node->_prev;
//			}
//			_count++;
//		}
//		else
//		{
//			Preppend(data);
//		}
//	}
//
//	bool SaveData(const char* fn)
//	{
//		FILE *fp = fopen(fn, "wb");
//		if (NULL == fp)
//		{
//			return false;
//		}
//		Node<T>* node = _head;
//		int ws = fwrite(&_count, sizeof(int), 1, fp);
//		while (0 != node)
//		{
//			fwrite(&node->_data, sizeof(T), 1, fp);
//			node = node->_next;
//		}
//
//		fclose(fp);
//		if (ws != _count)
//		{
//			return false;
//		}
//		return true;
//	}
//	bool LoadData(const char* fn)
//	{
//		FILE *fp = fopen(fn, "rb");
//		if (NULL == fp)
//		{
//			return false;
//		}
//		fread(&_count, sizeof(int), 1, fp);
//		int count = _count;
//
//		for (int i = 0; i < count; i++)
//		{
//			T data;
//			fread(&data, sizeof(T), 1, fp);
//			Append(data);
//			_count--;
//		}
//		fclose(fp);
//		return true;
//	}
//};
//template<class T>
//class DLinkedListIterator
//{
//private:
//public:
//	DLinkedList<T>* _dList;
//	Node<T>* _node;
//	DLinkedListIterator<T>(DLinkedList<T>* dll, Node<T>* node)
//	{
//		_dList = dll;
//		_node = node;
//	}
//	void Start()
//	{
//		if (0 != _dList)
//			_node = _dList->_head;
//	}
//	void End()
//	{
//		if (0 != _dList)
//			_node = _dList->_tail;
//	}
//	void Force()
//	{
//		if (0 != _node)
//			_node = _node->_next;
//	}
//	void Back()
//	{
//		if (0 != _node)
//			_node = _node->_prev;
//	}
//	bool Valid()
//	{
//		if (0 == _node)
//			return false;
//		return true;
//	}
//	T Item()
//	{
//		return _node->_data;
//	}
//};