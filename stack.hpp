//
// Created by Antioch Jeanett on 8/7/21.
//

#ifndef TEST_STACK_HPP
#define TEST_STACK_HPP

#include <iostream>



namespace ft {

	template <class T, class Container = std::vector<T> >
	class	stack{
	public:
		typedef Container								container_type;
//		typedef T										value_type;
		typedef typename Container::value_type			value_type;
		typedef size_t									size_type;

		explicit stack (const container_type& cont = container_type()) :_cont(cont){}
		virtual ~stack() {};

		bool empty() const { return _cont.empty(); };
		size_type size() const { return _cont.size(); };
		value_type &top() { return _cont.back(); };
		const value_type &top() const { return _cont.back(); };
		void push(const value_type &val) { _cont.push_back(val); };
		void pop() { _cont.pop_back(); };

	protected:
		Container _cont;
		template <class TStack, class ContainerStack>
		friend bool operator== (const stack<TStack,ContainerStack>& lhs, const stack<TStack,ContainerStack>& rhs);
		template <class TStack, class ContainerStack>
		friend bool operator<  (const stack<TStack,ContainerStack>& lhs, const stack<TStack,ContainerStack>& rhs);

	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cont == rhs._cont);
	}

//	template <class T, class Container>
//	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
//	{
//		return (lhs._cont != rhs._cont);
//	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._cont < rhs._cont);
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
