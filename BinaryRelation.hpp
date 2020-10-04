#pragma once
#include <fstream>
#include "Pair.hpp"
#include "List.hpp"


template<typename T, typename U>
class BinaryRelation {
protected:
	List< Pair<T, U>> relation;

public:
	BinaryRelation(List<Pair<T, U>> l = List<Pair<T, U>>());

	void add(const T& t, const U& u);
	void add(const Pair<T, U>& p);
	bool empty() const;
	bool operator==(const BinaryRelation<T, U>& rhs) const;
	bool function();
	bool injection();

	bool r(const T& t, const U& u); 
	BinaryRelation<T, U> operator+=(const BinaryRelation<T, U>& rhs);
	BinaryRelation<T, U> operator^=(const BinaryRelation<T, U>& rhs);
	BinaryRelation<T, U> operator*=(const BinaryRelation<T, U>& rhs);

	List<U> operator[](T const& e1);
	List<T> operator()(U const& e2);
	List<T> dom();
	List<U> ran();

	template<typename X, typename Y>
	friend BinaryRelation<X, Y> operator+(const BinaryRelation<X, Y>& lhs, const BinaryRelation<X, Y>& rhs);
	template<typename X, typename Y>
	friend BinaryRelation<X, Y> operator^(const BinaryRelation<X, Y>& lhs, const BinaryRelation<X, Y>& rhs);
	template<typename X, typename Y>
	friend BinaryRelation<X, Y> operator*(const BinaryRelation<X, Y>& lhs, const BinaryRelation<X, Y>& rhs);
	template<typename X, typename Y>
	friend std::ostream& operator<<(std::ostream& out, const BinaryRelation<X, Y>& br);
	template<typename X, typename Y>
	friend std::istream& operator>>(std::istream& in, BinaryRelation<X, Y>& br);
};

template<typename T, typename U>
inline BinaryRelation<T, U>::BinaryRelation(List<Pair<T, U>> l)
	:relation(l){}

template<typename T, typename U>
inline void BinaryRelation<T, U>::add(const T& t, const U& u)
{
	relation.add(Pair<T, U>(t, u));
}

template<typename T, typename U>
inline void BinaryRelation<T, U>::add(const Pair<T, U>& p)
{
	relation.add(p);
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::empty() const
{
	return (relation.size() == 0);
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::operator==(const BinaryRelation<T, U>& rhs) const
{
	if (relation.size() != rhs.relation.size()) return false;

	for (int i = 0; i < relation.size(); ++i) {
		bool found = false;
		for (int j = 0; j < rhs.relation.size(); ++j) {
			if (relation[i] == rhs.relation[j]) {
				found = true;
				break;
			}
		}
		if (!found) return false;
	}

	return true;
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::function()
{
	for (int i = 0; i < relation.size(); ++i) {
		T t = relation[i].first();
		U u = relation[i].second();
		for (int j = 0; j < relation.size(); ++j) 
			if (t == relation[j].first() && u != relation[j].second()) return false;
	}

	return true;
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::injection()
{
	for (int i = 0; i < relation.size(); ++i) {
		T t = relation[i].first();
		U u = relation[i].second();
		for (int j = 0; j < relation.size(); ++j)
			if (t == relation[j].first() && u != relation[j].second()) return false;
	}
	return true;
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::r(const T& t, const U& u)
{
	for (int i = 0; i < relation.size(); ++i)
		if (relation[i] == Pair<T, U>(t, u)) return true;

	return false;
}

template<typename T, typename U>
inline BinaryRelation<T, U> BinaryRelation<T, U>::operator+=(const BinaryRelation<T, U>& rhs)
{
	*this = *this + rhs;
	return *this;
}

template<typename T, typename U>
inline BinaryRelation<T, U> BinaryRelation<T, U>::operator^=(const BinaryRelation<T, U>& rhs)
{
	*this = *this ^ rhs;
	return *this;
}

template<typename T, typename U>
inline BinaryRelation<T, U> BinaryRelation<T, U>::operator*=(const BinaryRelation<T, U>& rhs)
{
	*this = *this * rhs;
	return *this;
}

template<typename T, typename U>
inline List<U> BinaryRelation<T, U>::operator[](T const& e1)
{
	List<U> rtrn;
	for (int i = 0; i < relation.size(); ++i)
		if (relation[i].first() == e1) rtrn.add(relation[i].second());


	return rtrn;
}

template<typename T, typename U>
inline List<T> BinaryRelation<T, U>::operator()(U const& e2)
{
	List<T> rtrn;
	for (int i = 0; i < relation.size(); ++i)
		if (relation[i].second() == e2) rtrn.add(relation[i].first());


	return rtrn;
}

template<typename T, typename U>
inline List<T> BinaryRelation<T, U>::dom()
{
	List<T> rtrn;
	for (int i = 0; i < relation.size(); ++i)
		rtrn.add(relation[i].first());

	return rtrn;
}

template<typename T, typename U>
inline List<U> BinaryRelation<T, U>::ran()
{
	List<U> rtrn;
	for (int i = 0; i < relation.size(); ++i)
		rtrn.add(relation[i].second());

	return rtrn;
}

template<typename X, typename Y>
inline BinaryRelation<X, Y> operator+(const BinaryRelation<X, Y>& lhs, const BinaryRelation<X, Y>& rhs)
{
	BinaryRelation<X, Y> rtrn = rhs;

	for (int i = 0; i < lhs.relation.size(); ++i)
		rtrn.add(lhs.relation[i]);

	return rtrn;
}

template<typename X, typename Y>
inline BinaryRelation<X, Y> operator^(const BinaryRelation<X, Y>& lhs, const BinaryRelation<X, Y>& rhs)
{
	BinaryRelation<X, Y> rtrn;
	for (int i = 0; i < rhs.relation.size(); ++i)
		for (int j = 0; j < lhs.relation.size(); ++j)
			if (rhs.relation[i] == lhs.relation[j]) rtrn.add(rhs.relation[i]);

	return rtrn;
}

template<typename X, typename Y>
inline BinaryRelation<X, Y> operator*(const BinaryRelation<X, Y>& lhs, const BinaryRelation<X, Y>& rhs)
{
	BinaryRelation<X, Y> rtrn;

	for (int i = 0; i < lhs.relation.size(); ++i)
		for (int j = 0; j < rhs.relation.size(); ++j)
			if (lhs.relation[i].second() == rhs.relation[j].first())
				rtrn.add(Pair<X, Y>(lhs.relation[i].first(), rhs.relation[j].second()));

	return rtrn;
}

template<typename X, typename Y>
inline std::ostream& operator<<(std::ostream& out, const BinaryRelation<X, Y>& br)
{
	if (br.relation.size() == 0) {
		out << "None!";
		return out;
	}

	for (int i = 0; i < br.relation.size() - 1; ++i)
		out << br.relation[i] << ", ";
	out << br.relation[br.relation.size() - 1];

	return out;
}

template<typename X, typename Y>
inline std::istream& operator>>(std::istream& in, BinaryRelation<X, Y>& br)
{
	X t;
	Y u;
	char c, trsh; // escape variable


	do {
		in >> trsh >> t >> trsh;
		in.get(c);
		in  >> u >> trsh; // the form is (t, u)
		br.add(t, u);
	}while (in.peek() != '\n');

	return in;
}
