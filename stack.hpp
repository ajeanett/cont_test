//
// Created by Antioch Jeanett on 8/7/21.
//

#ifndef TEST_STACK_HPP
#define TEST_STACK_HPP

#include <iostream>
#include "vector.hpp"



namespace ft {

	template <class T, class Container = ft::vector<T> >
	class	stack{
	public:
		typedef Container								container_type;
//		typedef T										value_type;
		typedef typename Container::value_type			value_type;
		typedef size_t									size_type;

		explicit stack (const container_type& cont = container_type()) :c(cont){}
		virtual ~stack() {};

		bool empty() const { return c.empty(); };
		size_type size() const { return c.size(); };
		value_type &top() { return c.back(); };
		const value_type &top() const { return c.back(); };
		void push(const value_type &val) { c.push_back(val); };
		void pop() { c.pop_back(); };

	protected:
		Container c;
		template <class TStack, class ContainerStack>
		friend bool operator== (const stack<TStack,ContainerStack>& lhs, const stack<TStack,ContainerStack>& rhs);
		template <class TStack, class ContainerStack>
		friend bool operator<  (const stack<TStack,ContainerStack>& lhs, const stack<TStack,ContainerStack>& rhs);

	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

//	template <class T, class Container>
//	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
//	{
//		return (lhs.c != rhs.c);
//	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return ((lhs < rhs) || (lhs == rhs));
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif //TEST_STACK_HPP
