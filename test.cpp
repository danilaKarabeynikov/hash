#include "pch.h"
#include "Hash.h"
#include "UnivHash.h"

#define M	11

size_t Fun(size_t k, size_t m, size_t a, size_t b, size_t p)
{
	return k % 11;
}

TEST(HashTest, HashSearchTest)
{
	size_t (*fcnPtr)(size_t, size_t, size_t, size_t, size_t) = Fun;
	size_t m = 11;
	Hash<size_t, size_t(size_t, size_t, size_t, size_t, size_t)> hash(m, Fun);

	hash.add(18);
	hash.add(14);
	hash.add(9);
	hash.add(20);
	hash.add(19);
	hash.add(12);
	hash.add(5);
	hash.add(27);
	hash.add(16);
	hash.add(34);
	hash.remove(9);

	HashNode<size_t>* findNode = hash.search(19);
	EXPECT_EQ(19, findNode->_value);
	EXPECT_EQ(1, findNode->_status);

	findNode = hash.search(9);
	EXPECT_FALSE(findNode);
}

TEST(UnivHashTests, UniverseSearchTest)
{
	size_t(*fcnPtr)(size_t, size_t, size_t, size_t, size_t) = Fun;
	size_t m = 11;
	std::vector<size_t> num{18, 14, 9, 20, 19, 12, 5, 27, 16, 34};
	UnivHash<size_t, size_t(size_t, size_t, size_t, size_t, size_t)> hash(m, Fun, num);
	hash.add(192);

	HashNode<size_t>* findNode = hash.search(27);
	EXPECT_EQ(27, findNode->_value);
	EXPECT_EQ(1, findNode->_status);

	findNode = hash.search(111);
	EXPECT_FALSE(findNode);

	hash.remove(27);
	findNode = hash.search(27);
	EXPECT_FALSE(findNode);
}

TEST(UnivHashTests, UniverseTotalSearchTest)
{
	size_t(*fcnPtr)(size_t, size_t, size_t, size_t, size_t) = Fun;
	size_t m = 11;
	std::vector<size_t> num{ 18, 14, 9, 20, 19, 12, 5, 27, 16, 34 };
	UnivHash<size_t, size_t(size_t, size_t, size_t, size_t, size_t)> hash(m, Fun, num);
	for (size_t i = 0; i < num.size(); ++i)
	{
		HashNode<size_t>* findNode = hash.search(num[i]);
		EXPECT_EQ(num[i], findNode->_value);
		EXPECT_EQ(1, findNode->_status);
	}
}

TEST(UnivHashTests, UniverseTotalRemoveTest)
{
	size_t(*fcnPtr)(size_t, size_t, size_t, size_t, size_t) = Fun;
	size_t m = 11;
	std::vector<size_t> num{ 18, 14, 9, 20, 19, 12, 5, 27, 16, 34 };
	UnivHash<size_t, size_t(size_t, size_t, size_t, size_t, size_t)> hash(m, Fun, num);
	for (size_t i = 0; i < num.size(); ++i)
	{
		hash.remove(num[i]);
		HashNode<size_t>* findNode = hash.search(num[i]);
		EXPECT_FALSE(findNode);
	}
}