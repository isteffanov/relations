#pragma once
#include <iostream>
#include <fstream>

template<class Type>
class List
{
private:
	Type* m_list;
	unsigned m_size;
	unsigned m_capacity;

	void init(unsigned capacity);
public:
	List(unsigned capacity = 2);
	List(List<Type> const& other);
	List<Type>& operator=(List<Type> const& other);
	~List();

	Type& operator[](int index);
	const Type& operator[](int index) const;
	inline unsigned size() const;

	bool add(const Type& thing); //returns false if the element was already in the list
	void addl(const List& list);
	void remove(Type const& thing);
	void shrink_to_fit(); //frees unused memory
};

template<typename type>
inline List<type>::List(unsigned capacity)
{
	m_size = 0;
	init(capacity);
}

template<typename Type>
inline List<Type>::List(List<Type> const& other)
{
	if (this != &other) {
		m_size = other.m_size;
		init(other.m_capacity);
		m_size = other.m_size;
		for (int i = 0; i < m_size; i++)
			m_list[i] = other.m_list[i];
	}
}

template<typename Type>
inline List<Type>& List<Type>::operator=(List<Type> const& other)
{
	if (this != &other) {
		delete[] m_list;
		init(other.m_capacity);
		m_size = other.m_size;
		for (int i = 0; i < m_size; i++)
			m_list[i] = other.m_list[i];
	}

	return *this;
}

template<typename Type>
inline List<Type>::~List()
{
	delete[] m_list;
	m_size = 0;
	m_capacity = 0;
}

template<class Type>
inline Type& List<Type>::operator[](int index)
{
	if (index < m_size)	return m_list[index];
	else
		throw std::out_of_range("Invalid index!");
}

template<class Type>
inline const Type& List<Type>::operator[](int index) const
{
	if (index < m_size)	return m_list[index];
	else
		throw std::out_of_range("Invalid index!");
}

template<typename Type>
inline void List<Type>::init(unsigned capacity)
{
	m_list = new Type[capacity];
	m_capacity = capacity;
}

template<typename Type>
inline unsigned List<Type>::size() const
{
	return m_size;
}

template<typename Type>
inline bool List<Type>::add(const Type& thing)
{
	for (int i = 0; i < m_size; ++i) //here we dont allow dublicates as we work with sets 
		if (m_list[i] == thing) return false;

	if (m_size >= m_capacity) {
		Type* temp = new Type[2 * m_capacity];
		for (int i = 0; i < m_size; ++i)
			temp[i] = m_list[i];

		delete[] m_list;
		m_list = temp;
		m_capacity *= 2;
	}
	m_list[m_size] = thing;
	m_size++;

	return true;
}

template<class Type>
inline void List<Type>::addl(const List& list)
{
	for (int i = 0; i < list.m_size; ++i)
		this->add(list[i]);
}


template<typename Type>
inline void List<Type>::remove(Type const& thing)
{
	int index = -1;
	for (int i = 0; i < m_size; ++i)
		if (m_list[i] == thing) index = i; //requires operator== overload

	if (index == -1) {
		std::cout << "Didnt find anything" << std::endl;
		return;
	}

	for (int i = index; i < m_size - 1; ++i)
		m_list[i] = m_list[i + 1]; //requires operator= overload

	m_size--;
}

template<typename Type>
inline void List<Type>::shrink_to_fit()
{
	Type* temp = new Type[m_size];
	for (int i = 0; i < m_size; ++i)
		temp[i] = m_list[i];

	delete[] m_list;
	m_list = temp;
	m_capacity = m_size;
}

template<typename Type>
std::ostream& operator<<(std::ostream& out, const List<Type>& thing)
{
	if (thing.size() == 0) return out;
	out << "{ ";
	for (int i = 0; i < thing.size() - 1; ++i)
		out << thing[i] << ", "; // requires operator<< overload
	out << thing[thing.size() - 1] << " }" << std::endl;

	return out;
}
