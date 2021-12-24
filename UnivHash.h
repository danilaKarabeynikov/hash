#pragma once
#include <vector>
#include <list>
#include <random>
#include <time.h>
#include "Hash.h"

void generateNum(size_t& a, size_t &b)
{
	a = rand();
	a = a == 0 ? 13 : a;
	b = rand();
}
template<typename T, typename HashFun>
class UnivHashNode
{
public:
	UnivHashNode(size_t a, size_t b, size_t m, Hash<T, HashFun> hashTable)
		: _a(a), _b(b), _m(m), _hashTable(hashTable)
	{
	}
	UnivHashNode()
		: _a(0), _b(0), _m(0)
	{
	}

public:
	size_t _a;
	size_t _b;
	size_t _m;
	Hash<T, HashFun> _hashTable;
};


template<typename T, typename HashFun>
class UnivHash
{
public:
	UnivHash(size_t m, HashFun f, std::vector<T> arrT);
	HashNode<T>* search(const T& value);
	void add(const T& value);
	void remove(const T& value);
private:
	std::vector<UnivHashNode<T, HashFun>> _univHashTable;
	HashFun* _f;
	size_t _a;
	size_t _b;
	size_t _p;
};

template<typename T, typename HashFun>
UnivHash<T, HashFun>::UnivHash(size_t m, HashFun f, std::vector<T> arrT)
{
	for (int i = 0; i < m; ++i)
	{
		Hash<T, HashFun> hashClass(m, f);
		UnivHashNode<T, HashFun> hashNode(0, 0, 0, hashClass);
		_univHashTable.push_back(hashNode);
	}
		
	_a = 13; _b = 7; _p = 31; _f = f;

	for (size_t i = 0; i < arrT.size(); ++i)
		_univHashTable[_f(arrT[i], m, _a, _b, _p)]._m++;

	for (size_t i = 0; i < m; ++i)
	{
		size_t a, b;
		generateNum(a, b);
		size_t curM = (_univHashTable[i]._m)*(_univHashTable[i]._m);
		curM = curM > m ? curM * curM : (m + curM) * (m + curM);
		_univHashTable[i]._m = curM;
		_univHashTable[i]._a = a;
		_univHashTable[i]._b = b;
		Hash<T, HashFun> hashTable(curM, f, a, b, _p);
		_univHashTable[i]._hashTable = hashTable;
	}

	for (size_t i = 0; i < arrT.size(); ++i)
		add(arrT[i]);
}

template<typename T, typename HashFun>
void UnivHash<T, HashFun>::add(const T& value)
{
	size_t curInd = _f(value, _univHashTable.size(), _a, _b, _p);
	_univHashTable[curInd]._hashTable.add(value);
}

template<typename T, typename HashFun>
HashNode<T>* UnivHash<T, HashFun>::search(const T& value)
{
	size_t curInd = _f(value, _univHashTable.size(), _a, _b, _p);
	return _univHashTable[curInd]._hashTable.search(value);
}

template<typename T, typename HashFun>
void UnivHash<T, HashFun>::remove(const T& value)
{
	size_t curInd = _f(value, _univHashTable.size(), _a, _b, _p);
	_univHashTable[curInd]._hashTable.remove(value);
}