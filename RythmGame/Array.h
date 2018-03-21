//#pragma once
//template<class T>
//class Array
//{
//private:
//	T* _array;
//	int _size;
//public:
//	Array(int size)
//	{
//		_array = new T[size];
//		_size = size;
//	};
//	~Array()
//	{
//		if (NULL != _array) {
//			delete[] _array;
//		}
//		_array = NULL;
//		_size = 0;
//	};
//	T& operator[](int index);
//	operator T*();
//	void Resize(int newSize);
//	void Insert(T num, int index);
//	void Remove(int index);
//	bool SaveData(const char* fn);
//	bool LoadData(const char* fn);
//	int Size();
//	void Set(int index, T newItem)
//	{
//		_array[index] = newItem;
//	}
//	T Get(int index)
//	{
//		return _array[index];
//	}
//};
//template<class T>
//T& Array<T>::operator[](int index)
//{
//	return _array[index];
//}
//template<class T>
//Array<T>::operator T*()
//{
//	return _array;
//}
//template<class T>
//void Array<T>::Resize(int newSize)
//{
//	T* newArray = new T[newSize];
//	if (NULL == newArray)
//		return;
//
//	int minSize = 0;
//
//	if (newSize < _size)
//		minSize = newSize;
//	else
//		minSize = _size;
//
//	for (int i = 0; i < minSize; i++)
//	{
//		newArray[i] = _array[i];
//	}
//	if (NULL != _array) {
//		delete[] _array;
//	}
//	_array = newArray;
//	_size = newSize;
//}
//template<class T>
//void Array<T>::Insert(T num, int index)
//{
//	for (int i = _size - 1; i > index; i--)
//	{
//		_array[i] = _array[i - 1];
//	}
//	_array[index] = num;
//}
//template<class T>
//void Array<T>::Remove(int index)
//{
//	for (int i = index; i < _size - 1; i++)
//	{
//		_array[i] = _array[i + 1];
//	}
//}
//template<class T>
//bool Array<T>::SaveData(const char* fn)
//{
//	FILE *fp = fopen(fn, "wb");
//	if (NULL == fp)
//	{
//		return false;
//	}
//	int ws = fwrite(_array, sizeof(T), _size, fp);
//
//	fclose(fp);
//	if (ws != _size)
//	{
//		return false;
//	}
//	return true;
//}
//template<class T>
//bool Array<T>::LoadData(const char* fn)
//{
//	FILE *fp = fopen(fn, "rb");
//	if (NULL == fp)
//	{
//		return false;
//	}
//	int rs = fread(_array, sizeof(T), _size, fp);
//	fclose(fp);
//	if (rs != _size)
//	{
//		return false;
//	}
//	return true;
//}
//template<class T>
//int Array<T>::Size()
//{
//	return _size;
//}