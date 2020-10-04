#pragma once
#include <iomanip>
#include <fstream>

template<typename A, typename B>
struct Pair {
private:
	A elem1;
	B elem2;

	static const float EPS;
	static const int PRECISION = 2;

public:
	Pair(A e1 = A(), B e2 = B());
	Pair(const Pair<A, B>& other);

	const A& first() const;
	A& first();
	const B& second() const;
	B& second();
	bool operator==(const Pair<A, B>& pair) const;

	//specializations
	template<typename A>
	friend bool operator==(const Pair <A, float>& lhs, const Pair<A, float>& rhs);
	template<typename B>
	friend bool operator==(const Pair <float, B>& lhs, const Pair<float, B>& rhs);

	friend bool operator==(const Pair <float, float>& lhs, const Pair<float, float>& rhs);

	template<typename X, typename Y>
	friend std::ostream& operator<<(std::ostream& out, const Pair<X, Y>& pair);

	//specializations
	template<typename X>
	friend std::ostream& operator<<(std::ostream& out, const Pair<X, float>& pair);
	template<typename Y>
	friend std::ostream& operator<<(std::ostream& out, const Pair<float, Y>& pair);

	friend std::ostream& operator<<(std::ostream& out, const Pair<float, float>& pair);
};

//comparison precision
float EPS = 0.001f;

template<typename A, typename B>
inline Pair<A, B>::Pair(A e1, B e2)
	:elem1(e1), elem2(e2){}

template<typename A, typename B>
inline Pair<A, B>::Pair(const Pair<A, B>& other)
{
	if (this != &other) {
		elem1 = other.elem1;
		elem2 = other.elem2;
	}
}

template<typename A, typename B>
inline const A& Pair<A, B>::first() const
{
	return elem1;
}

template<typename A, typename B>
inline const B& Pair<A, B>::second() const
{
	return elem2;
}

template<typename A, typename B>
inline A& Pair<A, B>::first()
{
	return elem1;
}

template<typename A, typename B>
inline B& Pair<A, B>::second()
{
	return elem2;
}

template<typename A, typename B>
inline bool Pair<A, B>::operator==(const Pair<A, B>& pair) const
{
	return (elem1 == pair.elem1 && elem2 == pair.elem2);
}

//specializations for floating point numbers
template<typename A>
inline bool operator==(const Pair<A, float>& lhs, const Pair<A, float>& rhs)
{
	return (lhs.elem1 == rhs.elem1 && abs(lhs.elem2 - rhs.elem2) < EPS);
}

template<typename B>
inline bool operator==(const Pair<float, B>& lhs, const Pair<float, B>& rhs)
{
	return (abs(lhs.elem1 - rhs.elem1) < EPS && lhs.elem2 = rhs.elem2);
}

inline bool operator==(const Pair<float, float>& lhs, const Pair<float, float>& rhs)
{
	return (abs(lhs.elem1 - rhs.elem1) < EPS && abs(lhs.elem2 - rhs.elem2) < EPS);
}

template<typename X, typename Y>
inline std::ostream& operator<<(std::ostream& out, const Pair<X, Y>& pair)
{
	out << "(" << pair.elem1 << ", " << pair.elem2 << ")";
	return out;
}

//specializations for floating point numbers
template<typename X>
inline std::ostream& operator<<(std::ostream& out, const Pair<X, float>& pair)
{
	out << "(" << pair.elem1 << ", " << std::fixed << std::setprecision(Pair<X, float>::PRECISION) << pair.elem2 << ")";
	return out;
}

template<typename Y>
inline std::ostream& operator<<(std::ostream& out, const Pair<float, Y>& pair)
{
	out << "(" << std::fixed << std::setprecision(Pair<float, Y>::PRECISION) << pair.elem1 << ", " << pair.elem2 << ")";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const Pair<float, float>& pair)
{
	out << "(" << std::fixed <<std::setprecision(Pair<float, float>::PRECISION) << pair.elem1 << ", " << std::fixed << std::setprecision(Pair<float, float>::PRECISION) << pair.elem2 << ")";
	return out;
}


