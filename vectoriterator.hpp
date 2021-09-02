//
// Created by Antioch Jeanett on 8/8/21.
//

#ifndef TEST_VECTORITERATOR_HPP
#define TEST_VECTORITERATOR_HPP

#include <iostream>
#include "tree.hpp"

namespace ft{

	template <class Iter>
			struct	iterator_traits {
				typedef typename Iter::difference_type	difference_type;
				typedef typename Iter::value_type	value_type;
				typedef typename Iter::pointer	pointer;
				typedef typename Iter::reference	reference;
				typedef typename Iter::iterator_category	iterator_category;
			};
	
	template <class Pair>
			struct	iterator_traits<ft::node<Pair> > {
				typedef typename std::ptrdiff_t 	difference_type;
				typedef typename ft::node<Pair>::node_pair	value_type;
				typedef typename ft::node<Pair>::node_pair*	pointer;
				typedef typename ft::node<Pair>::node_pair&	reference;
				typedef typename std::random_access_iterator_tag	iterator_category;
			};
	
	template <class Pair>
			struct	iterator_traits<const ft::node<Pair> > {
				typedef typename std::ptrdiff_t 	difference_type;
				typedef typename ft::node<Pair>::node_pair	value_type;
				typedef const typename ft::node<Pair>::node_pair*	pointer;
				typedef const typename ft::node<Pair>::node_pair&	reference;
				typedef typename std::random_access_iterator_tag	iterator_category;
			};

	template <class Iter>
			struct	iterator_traits<Iter *> {
				typedef typename std::ptrdiff_t 	difference_type;
				typedef Iter	value_type;
				typedef Iter*	pointer;
				typedef Iter&	reference;
				typedef std::random_access_iterator_tag	iterator_category;
			};

	template <class Iter>
			struct	iterator_traits<const Iter*> {
				typedef typename std::ptrdiff_t	difference_type;
				typedef Iter	value_type;
				typedef const Iter*	pointer;
				typedef const Iter&	reference;
				typedef std::random_access_iterator_tag	iterator_category;
			};

	template<class T>
		class checkConst{
		public:
			typedef T	_type;
		};

	template<class T>
			class checkConst<const T>{
			public:
				typedef T	_type;
			};

	template<class T>
			class checkConst<T*> {
			public:
				typedef T*	_type;
			};

	template<class T>
			class checkConst<const T*> {
			public:
				typedef T*	_type;
			};

	/*
	 * distance
	 * */

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last){
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return n;
	}

/**
 * VectorIterator
 * */
	template<typename T>
	class vectorIterator
	{
	private:
		typedef iterator_traits<T*>	_traits_type;
	public:
		typedef typename _traits_type::value_type			value_type;
		typedef typename _traits_type::difference_type		difference_type	;
		typedef typename _traits_type::pointer				pointer;
		typedef typename _traits_type::reference			reference;
		typedef typename _traits_type::iterator_category 	iterator_category;
//		typedef T									value_type;
//		typedef std::ptrdiff_t						difference_type;
//		typedef value_type*							pointer;
//		typedef value_type&							reference;
//		typedef std::random_access_iterator_tag 	iterator_category;

		vectorIterator(){
			_ptr = NULL;
		}
		vectorIterator(pointer src){
			_ptr = src;
		}
		vectorIterator(const vectorIterator &src){

				*this = src;
		}
		~vectorIterator(){}
		vectorIterator& operator= (const vectorIterator& x){
			if (this != &x)
			{
				this->_ptr = x._ptr;
			}
			return *this;
		}

		pointer base() const{
			return this->_ptr;
		}

		reference operator* ()
		{
			return *_ptr;
		}

		pointer operator-> ()
		{
			return &(*_ptr);
		}

		vectorIterator& operator++ ()
		{
			++this->_ptr;
			return *this;
		}

		vectorIterator operator++ (int)
		{
			vectorIterator tmp = *this;
			++this->_ptr;
			return tmp;
		}

		vectorIterator& operator-- ()
		{
			--this->_ptr;
			return *this;
		}

		vectorIterator operator-- (int)
		{
			vectorIterator tmp = *this;
			--this->_ptr;
			return tmp;
		}

		vectorIterator	operator+(difference_type n) {
			return vectorIterator(this->_ptr + n);
		}

		vectorIterator	operator-(difference_type n) {
			return vectorIterator(this->_ptr - n);
		}

		vectorIterator	&operator-=(difference_type n) {
			this->_ptr -= n;
			return *this;
		}

		vectorIterator	&operator+=(difference_type n) {
			this->_ptr += n;
			return *this;
		}

		reference 	operator[](difference_type n) {
			return (this->_ptr[n]);
		}

	private:
		pointer _ptr;

	};

	template <class T>
	typename vectorIterator<T>::difference_type operator-(const vectorIterator<T>& lhs, const vectorIterator<T>& rhs )
	{
		return lhs.base() - rhs.base();
	}

	template <class T> //перегрузка перегрузки it + n
	vectorIterator<T>	operator+(typename vectorIterator<T>::difference_type n, const vectorIterator<T>& it){
		return it + n;
	}


	template <class T>
	bool operator== (const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T>
	bool operator!= (const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T>
	bool operator<  (const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)
	{
		return (lhs.base()  < rhs.base());
	}

	template <class T>
	bool operator<= (const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)
	{
		return ((lhs < rhs) || (lhs == rhs));
	}

	template <class T>
	bool operator>  (const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T>
	bool operator>= (const vectorIterator<T>& lhs, const vectorIterator<T>& rhs)
	{
		return (!(lhs < rhs));
	}

	/**
 * ReverseIterator - общий
 * */

	template<class Iterator>
	class reverseIterator
	{
	private:
		//		pointer 	_ptr;
		typedef iterator_traits<Iterator>	_traits_type;
	public:
		typedef typename _traits_type::value_type			value_type;
		typedef typename _traits_type::difference_type		difference_type	;
		typedef typename _traits_type::pointer				pointer;
		typedef typename _traits_type::reference			reference;
		typedef typename _traits_type::iterator_category 	iterator_category;

		reverseIterator() : _base(Iterator()) {}


		explicit reverseIterator(const Iterator& src) : _base(src){
		}

		~reverseIterator(){}

		Iterator	base() const {
			return this->_base;
		}

		reverseIterator& operator= (const reverseIterator& x){
			if (this != &x)
			{
				this->_base = x._base;
			}
			return *this;
		}

		reference operator* ()
		{
			return *_base;
		}

		pointer operator-> ()
		{
			return &(*_base);
		}

		reverseIterator& operator++ ()
		{
			--this->_base;
			return *this;
		}

		reverseIterator operator++ (int)
		{
			reverseIterator tmp = *this;
			--this->_base;
			return tmp;
		}

		reverseIterator& operator-- ()
		{
			++this->_base;
			return *this;
		}

		reverseIterator operator-- (int)
		{
			reverseIterator tmp = *this;
			++this->_base;
			return tmp;
		}

		reverseIterator	operator+(difference_type n) {
			return reverseIterator(this->_base - n);
		}

		reverseIterator	operator-(difference_type n) {
			return reverseIterator(this->_base + n);
		}

		reverseIterator	&operator-=(difference_type n) {
			this->_base += n;
			return *this;
		}

		reverseIterator	&operator+=(difference_type n) {
			this->_base -= n;
			return *this;
		}

		reference 	operator[](difference_type n) {
			return *(*this + n);
		}

	protected:
		Iterator	_base;
	};

	template <class T>
	typename reverseIterator<T>::difference_type operator-(const reverseIterator<T>& lhs, const reverseIterator<T>& rhs )
	{
		return lhs.base() - rhs.base();
	}

	template <class T> //перегрузка перегрузки it + n
	reverseIterator<T>	operator+(typename reverseIterator<T>::difference_type n, const reverseIterator<T>& it){
		return it + n;
	}


	template <class T>
	bool operator== (const reverseIterator<T>& lhs, const reverseIterator<T>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T>
	bool operator!= (const reverseIterator<T>& lhs, const reverseIterator<T>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T>
	bool operator<  (const reverseIterator<T>& lhs, const reverseIterator<T>& rhs)
	{
		return (lhs.base()  > rhs.base());
	}

	template <class T>
	bool operator<= (const reverseIterator<T>& lhs, const reverseIterator<T>& rhs)
	{
		return ((lhs < rhs) || (lhs == rhs));
	}

	template <class T>
	bool operator>  (const reverseIterator<T>& lhs, const reverseIterator<T>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T>
	bool operator>= (const reverseIterator<T>& lhs, const reverseIterator<T>& rhs)
	{
		return (!(lhs < rhs));
	}

	/**
	* MapIterator
	* */
	template<typename T>
	class mapIterator
	{
	private:
		typedef iterator_traits<T>	_traits_type;
//		typedef tree
	public:
		typedef typename _traits_type::value_type			value_type;
		typedef typename _traits_type::difference_type		difference_type	;
		typedef typename _traits_type::pointer				pointer;
		typedef typename _traits_type::reference			reference;
		typedef typename std::bidirectional_iterator_tag  	iterator_category;
		//		typedef T									value_type;
		//		typedef std::ptrdiff_t						difference_type;
		//		typedef value_type*							pointer;
		//		typedef value_type&							reference;
		//		typedef std::random_access_iterator_tag 	iterator_category;

		mapIterator(){
			_ptr = NULL;
		}
		mapIterator(T *src){
			_ptr = src;
		}
		mapIterator(const mapIterator &src){

			*this = src;
		}
		~mapIterator(){}
		mapIterator& operator= (const mapIterator& x){
			if (this != &x)
			{
				this->_ptr = x._ptr;
			}
			return *this;
		}

		pointer base() const{
			return &this->_ptr->pair;
		}

		reference operator* () const
		{
			return _ptr->pair;
		}

		pointer operator-> () const
		{
			return this->base();
		}

		mapIterator& operator++ ()
		{
			_ptr = ft::tree<T>::min_to_max(_ptr);
			return *this;
		}

		mapIterator operator++ (int)
		{
			mapIterator tmp = *this;
			_ptr = ft::tree<T>::min_to_max(_ptr);
			return tmp;
		}

		mapIterator& operator-- ()
		{
			_ptr = ft::tree<T>::max_to_min(_ptr);
			return *this;
		}

		mapIterator operator-- (int)
		{
			mapIterator tmp = *this;
			_ptr = ft::tree<T>::max_to_min(_ptr);
			return tmp;
		}

	private:
		T *_ptr; // T - это нода

	};


	template <class T>
			bool operator== (const mapIterator<T>& lhs, const mapIterator<T>& rhs)
			{
				return (lhs.base() == rhs.base());
			}

	template <class T>
			bool operator!= (const mapIterator<T>& lhs, const mapIterator<T>& rhs)
			{
				return (!(lhs == rhs));
			}

};




#endif //TEST_VECTORITERATOR_HPP
