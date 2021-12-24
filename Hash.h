#pragma once
#include <vector>
#include <list>
template<typename T>
class HashNode
{
public:
	HashNode(T& value)
	{
		_value = value;
		_status = 1;
	}
	HashNode()
	{
		_status = 0;
	}
	T _value;
	int _status;
};

template<typename T, typename HashFun>
class Hash
{
public:
	Hash(size_t m, HashFun f);
	Hash(size_t m, HashFun f, size_t a, size_t b, size_t p);
	HashNode<T>* search(const T& value);
	void add(const T& value);
	void remove(const T& value);

private:
	std::vector<HashNode<T>> _hashTable;
	HashFun* _f;
	size_t _a;
	size_t _b;
	size_t _p;
	size_t _m;
	double _tableInd;
	double _maxTableInd;
	size_t _curCount;
	void insert(size_t ind, const T& value);
	void resize();
};

template<typename T, typename HashFun>
Hash<T, HashFun>::Hash(size_t m, HashFun f)
{
	_hashTable.resize(m);
	for (size_t i = 0; i < m; ++i)
	{
		HashNode<T> node;
		_hashTable[i] = node;
	}

	_f = f;
	_a = 0;
	_b = 0;
	_p = 0;
	_tableInd = 0;
	_curCount = 0;
	_maxTableInd = 0.5;
}

template<typename T, typename HashFun>
Hash<T, HashFun>::Hash(size_t m, HashFun f, size_t a, size_t b, size_t p)
{
	_hashTable.resize(m);
	for (size_t i = 0; i < m; ++i)
	{
		HashNode<T> node;
		_hashTable[i] = node;
	}

	_f = f;
	_a = a;
	_b = b;
	_p = p;
	_tableInd = 0;
	_curCount = 0;
	_maxTableInd = 0.5;
}

template<typename T, typename HashFun>
void Hash<T, HashFun>::insert(size_t ind, const T& value)
{
	_hashTable[ind]._value = value;
	_hashTable[ind]._status = 1;
	++_curCount;
	_tableInd = _curCount / (double)(_hashTable.size());
	if (_tableInd > _maxTableInd)
		resize();
}

template<typename T, typename HashFun>
void Hash<T, HashFun>::add(const T& value)
{
	size_t curInd = (*_f)(value, _hashTable.size(), _a, _b, _p);
	if (_hashTable[curInd]._status == 1 && _hashTable[curInd]._value == value)
		return;

	if (_hashTable[curInd]._status == 0 || _hashTable[curInd]._status == -1)
		return insert(curInd, value);

	for (size_t i = 1; i <= _hashTable.size(); ++i)
	{
		size_t indToIns = (curInd + i) % _hashTable.size();
			if (_hashTable[indToIns]._status == 0
				|| _hashTable[indToIns]._status == -1)
				return insert(indToIns, value);
	}

	resize();
	add(value);
}

template<typename T, typename HashFun>
void Hash<T, HashFun>::resize()
{
	std::vector<HashNode<T>> hashTable(_hashTable.begin(), _hashTable.end());
	_hashTable.clear();
	_hashTable.resize(hashTable.size() * 2);
	_curCount = 0;
	_tableInd = 0;
	size_t prevCount = hashTable.size();
	for (size_t i = 0; i < prevCount; ++i)
	{
		if (hashTable[i]._status == 1)
			add(hashTable[i]._value);
	}
}

template<typename T, typename HashFun>
HashNode<T>* Hash<T, HashFun>::search(const T& value)
{
	size_t curInd = _f(value, _hashTable.size(), _a, _b, _p);
	if (_hashTable[curInd]._status == 1 && _hashTable[curInd]._value == value)
		return &_hashTable[curInd];

	for (size_t i = 1; i <= _hashTable.size(); ++i)
	{
		size_t indToIns = (curInd + i) % _hashTable.size();
		if (_hashTable[indToIns]._status == -1)
			return nullptr;

		if (_hashTable[indToIns]._status == 1 && _hashTable[indToIns]._value == value)
			return &_hashTable[indToIns];
	}

	return nullptr;
}

template<typename T, typename HashFun>
void Hash<T, HashFun>::remove(const T& value)
{
	HashNode<T>* findNode = search(value);
	if (findNode)
		findNode->_status = -1;
}
