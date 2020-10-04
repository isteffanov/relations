#pragma once
#include "String.hpp"
#include "BinaryRelation.hpp"

template<typename T, typename U>
class KnowledgeBase {
	List< Pair<String, BinaryRelation<T, U>>> knowledge;

public:
	KnowledgeBase(List< Pair<String, BinaryRelation<T, U>>> l = List< Pair<String, BinaryRelation<T, U>>>());

	void add(const String& s, const BinaryRelation<T, U>& br);
	void add(const Pair<String, BinaryRelation<T,U>>& p);
	bool function(); //if one of the relations isn't function, returns false 
	bool injection(); //if one of the relations isn't injection returns false

	bool r(const T&, const U& u); // returns true if the given pair is in one of the relations of the base
	KnowledgeBase<T, U>& operator+=(const KnowledgeBase<T, U>& rhs);
	KnowledgeBase<T, U>& operator^=(const BinaryRelation<T, U>& rhs);
	KnowledgeBase<T, U>& operator*=(const BinaryRelation<T, U>& rhs);
	List<U> operator[](T const& e1); //returns elements from all the relations combined
	List<T> operator()(U const& e2); //returns elements from all the relations combined
	List<T> dom();  //returns elements from all the relations combined
	List<U> ran();  //returns elements from all the relations combined

	template<typename X, typename Y>
	friend KnowledgeBase<X, Y> operator+(const KnowledgeBase<X, Y>& lhs, const KnowledgeBase<X, Y>& rhs);
	template<typename X, typename Y>
	friend KnowledgeBase<X, Y> operator^(const KnowledgeBase<X, Y>& lhs, const KnowledgeBase<X, Y>& rhs);
	template<typename X, typename Y>
	friend KnowledgeBase<X, Y> operator*(const KnowledgeBase<X, Y>& lhs, const KnowledgeBase<X, Y>& rhs);
	template<typename X, typename Y>
	friend std::ostream& operator<<(std::ostream& out, const KnowledgeBase<X, Y>& kb);
	template<typename X, typename Y>
	friend std::istream& operator>>(std::istream& in, KnowledgeBase<X, Y>& kb);
};

template<typename T, typename U>
inline KnowledgeBase<T, U>::KnowledgeBase(List<Pair<String, BinaryRelation<T, U>>> l)
	:knowledge(l){}

template<typename T, typename U>
inline void KnowledgeBase<T, U>::add(const String& s, const BinaryRelation<T, U>& br)
{
	for (int i = 0; i < knowledge.size(); ++i) {
		if (knowledge[i].first() == s) {
			knowledge[i].second() += br;
			return;
		}
	}
	knowledge.add(Pair<String, BinaryRelation<T, U>>(s, br));
}

template<typename T, typename U>
inline void KnowledgeBase<T, U>::add(const Pair<String, BinaryRelation<T, U>>& p)
{
	for (int i = 0; i < knowledge.size(); ++i) {
		if ( same_names(knowledge[i], p) ) {
			knowledge[i].second() += p.second();
			return;
		}
	}
	knowledge.add(p);
}

template<typename T, typename U>
inline bool KnowledgeBase<T, U>::function()
{
	int cnt = 0;
	for (int i = 0; i < knowledge.size(); ++i)
		if(knowledge[i].second().function()) cnt++;

	return (cnt == knowledge.size());
}

template<typename T, typename U>
inline bool KnowledgeBase<T, U>::injection()
{
	int cnt = 0;
	for (int i = 0; i < knowledge.size(); ++i)
		if (knowledge[i].second().injection()) cnt++;

	return (cnt == knowledge.size());
}

template<typename T, typename U>
inline bool KnowledgeBase<T, U>::r(const T& t, const U& u)
{
	for (int i = 0; i < knowledge.size(); ++i)
		if (knowledge[i].second().r(t, u)) return true;

	return false;
}

template<typename T, typename U>
inline KnowledgeBase<T, U>& KnowledgeBase<T, U>::operator+=(const KnowledgeBase<T, U>& rhs)
{
	for (int i = 0; i < knowledge.size(); ++i) 
		for (int j = 0; j < rhs.knowledge.size(); ++j) 
			if (same_names(knowledge[i], rhs.knowledge[j])) knowledge[i].second() += rhs.knowledge[j].second();
		
	return *this;
}

template<typename T, typename U>
inline KnowledgeBase<T, U>& KnowledgeBase<T, U>::operator^=(const BinaryRelation<T, U>& rhs)
{
	for (int i = 0; i < knowledge.size(); ++i)
		for (int j = 0; rhs.knowledge.size(); ++j)
			if (same_names(knowledge[i], rhs.knowledge[j])) knowledge[i].second() ^= rhs.knowledge[j].second();

	return *this;
}

template<typename T, typename U>
inline KnowledgeBase<T, U>& KnowledgeBase<T, U>::operator*=(const BinaryRelation<T, U>& rhs)
{
	for (int i = 0; i < knowledge.size(); ++i)
		for (int j = 0; rhs.knowledge.size(); ++j)
			if (same_names(knowledge[i], rhs.knowledge[j])) knowledge[i].second() *= rhs.knowledge[j].second();

	return *this;
}

template<typename T, typename U>
inline List<U> KnowledgeBase<T, U>::operator[](T const& e1)
{
	List<U> rtrn;

	for (int i = 0; i < knowledge.size(); ++i) 
		rtrn.addl(knowledge[i].second()[e1]);

	return rtrn;
}

template<typename T, typename U>
inline List<T> KnowledgeBase<T, U>::operator()(U const& e2)
{
	List<T> rtrn;

	for (int i = 0; i < knowledge.size(); ++i)
		rtrn.addl(knowledge[i].second()(e2));

	return rtrn;
}

template<typename T, typename U>
inline List<T> KnowledgeBase<T, U>::dom()
{
	List<T> rtrn;

	for (int i = 0; i < knowledge.size(); ++i)
		rtrn.addl(knowledge[i].second().dom());

	return rtrn;
}

template<typename T, typename U>
inline List<U> KnowledgeBase<T, U>::ran()
{
	List<U> rtrn;

	for (int i = 0; i < knowledge.size(); ++i)
		rtrn.addl(knowledge[i].second().ran());

	return rtrn;
}

template<typename X, typename Y>
inline KnowledgeBase<X, Y> operator+(const KnowledgeBase<X, Y>& lhs, const KnowledgeBase<X, Y>& rhs)
{
	KnowledgeBase<X, Y> rtrn = rhs;
	for (int i = 0; i < lhs.knowledge.size(); ++i) {
		bool found = false;
		for (int j = 0; j < rhs.knowledge.size(); ++j) {
			if (same_names(lhs.knowledge[i], rhs.knowledge[j])) {
				found = true;
				rtrn.add(lhs.knowledge[i].first(), lhs.knowledge[i].second() + rhs.knowledge[j].second());
				break;
			}
		}
		if(!found) rtrn.add(lhs.knowledge[i]);
	}

	return rtrn;
}

template<typename X, typename Y>
inline KnowledgeBase<X, Y> operator^(const KnowledgeBase<X, Y>& lhs, const KnowledgeBase<X, Y>& rhs)
{
	KnowledgeBase<X, Y> rtrn;

	for (int i = 0; i < lhs.knowledge.size(); ++i)
		for (int j = 0; j < rhs.knowledge.size(); ++j)
			if( same_names(lhs.knowledge[i], rhs.knowledge[j]) ) rtrn.add(lhs.knowledge[i].first(), lhs.knowledge[i].second() ^ rhs.knowledge[j].second());


	return rtrn;
}

template<typename X, typename Y>
inline KnowledgeBase<X, Y> operator*(const KnowledgeBase<X, Y>& lhs, const KnowledgeBase<X, Y>& rhs)
{
	KnowledgeBase<X, Y> rtrn;

	for (int i = 0; i < lhs.knowledge.size(); ++i) {
		for (int j = 0; j < rhs.knowledge.size(); ++j) {
			if (same_names(lhs.knowledge[i], rhs.knowledge[j])) {
				rtrn.add(lhs.knowledge[i].first(), lhs.knowledge[i].second() * rhs.knowledge[j].second());
			}
		}
	}
	return rtrn;
}

template<typename X, typename Y>
inline std::ostream& operator<<(std::ostream& out, const KnowledgeBase<X, Y>& kb)
{
	if (kb.knowledge.size() == 0) return out;

	int skip_cnt = 0;
	for (int i = 0; i < kb.knowledge.size(); ++i) {
		if (kb.knowledge[i].second().empty()) {
			skip_cnt++;
			continue;
		}
		out << kb.knowledge[i].first() << ": " << kb.knowledge[i].second() << '\n';
	}
	if (skip_cnt == kb.knowledge.size()) out << "None!";

	return out;
}

template<typename X, typename Y>
inline std::istream& operator>>(std::istream& in,  KnowledgeBase<X, Y>& kb)
{
	std::cout << "Please enter a Knowledge: <name> <(a, b )> <(c, d )> ... " << std::endl; //giving instructions

	String name;
	BinaryRelation<X, Y> br;
	in.get();
	in >> name;
	in >> br;
	kb.add(name, br);

	
	return in;
}

//helper methods:
template<typename T, typename U>
bool same_names(const Pair<String, BinaryRelation<T, U>>& k1, const Pair<String, BinaryRelation<T, U>>& k2)
{
	return (k1.first() == k2.first());
}
