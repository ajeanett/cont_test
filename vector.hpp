//
// Created by Antioch Jeanett on 8/7/21.
//

#ifndef TEST_VECTOR_HPP
#define TEST_VECTOR_HPP

#include <iostream>
#include "vectoriterator.hpp"

namespace ft{

	/*****************IS_INTEGRAL********************/
	template <class T>
			struct	is_integral : std::false_type {};
	template <> struct	is_integral<bool> : std::true_type {};
	template <> struct	is_integral<char> : std::true_type {};
	template <> struct	is_integral<char16_t> : std::true_type {};
	template <> struct	is_integral<char32_t> : std::true_type {};
	template <> struct	is_integral<wchar_t> : std::true_type {};
	template <> struct	is_integral<signed char> : std::true_type {};
	template <> struct	is_integral<int> : std::true_type {};
	template <> struct	is_integral<short int> : std::true_type {};
	template <> struct	is_integral<long int> : std::true_type {};
	template <> struct	is_integral<long long int> : std::true_type {};
	template <> struct	is_integral<unsigned char> : std::true_type {};
	template <> struct	is_integral<unsigned short int> : std::true_type {};
	template <> struct	is_integral<unsigned int> : std::true_type {};
	template <> struct	is_integral<unsigned long int> : std::true_type {};
	template <> struct	is_integral<unsigned long long int> : std::true_type {};

	/*****************ENABLE_IF********************/
	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	/*****************VECTOR***********************/

	template < class T, class Alloc = std::allocator<T> > class vector{
	public:
		typedef  T										value_type;
		typedef typename std::allocator<value_type >	allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef vectorIterator<value_type >				iterator;
		typedef vectorIterator<const typename checkConst<value_type>::_type>	const_iterator;
		typedef reverseIterator<iterator>				reverse_iterator;
		typedef reverseIterator<const_iterator>			const_reverse_iterator;

		typedef ptrdiff_t								difference_type;
		typedef size_t									size_type;

		/*push_back, insert -основной, вызывает push_back*/

		/*default*/
		explicit vector (const allocator_type& alloc = allocator_type()) :
		_val(NULL), _capacity(0), _size(0), _allocator(alloc){
//			_val = new value_type;
			_val = _allocator.allocate(0);
		}

		/*fill (2)*/
		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) :
						 _val(NULL) , _size(0), _capacity(n) , _allocator(alloc){
			//insert n элементов со значением val
			_val = _allocator.allocate(n); //в insert будет allocate
			insert(begin(), n, val);

		}
		/*range (3)*/
		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
				: _val(NULL) , _size(0), _capacity(0), _allocator(alloc){
					_val = _allocator.allocate(0); //в insert будет allocate
					insert(begin(), first, last);
		}
		/*copy (4)*/
		vector (const vector& x) :_val(NULL) ,  _capacity(0), _size(0){
			if (this != &x)
			{
				*this = x;
			}// написать перегрузку оператора присваивания
		}

		~vector(){
			// удалить массив
			for (int i = 0; i < _size; ++i){
				_allocator.destroy(&_val[i]);
//				_allocator.destroy(_val+i); // альтернативный вариант
			}
			_allocator.deallocate(_val, _capacity);
		}

		vector& operator= (const vector& x)
		{
//			this->clear();
			if (this != &x){
				if (_val) {
					for (int i = 0; i < _size; ++i){
						_allocator.destroy(&_val[i]);
					}
					_allocator.deallocate(_val, _capacity);
				}
				_allocator = x._allocator;
				_capacity = x.capacity();
				_size = x.size();
				_val = _allocator.allocate(_capacity);
				for (size_t i = 0; i < _size; ++i) {
					_allocator.construct(&_val[i], x._val[i]); // создает объект  x._val[i] по адресу &_val[i]
				}
			}
			return *this;
		}

		iterator begin(){
//			return vectorIterator<T>(_val); //альтернативный вариант
			return iterator(_val);
		}
		const_iterator begin() const{
			return const_iterator(_val);
		}

		iterator end(){
			return iterator(_val + _size);
		}
		const_iterator end() const{
			return const_iterator(_val + _size);
		}

		reverse_iterator rbegin(){
			return reverse_iterator(this->end() - 1);
		}
		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(this->end() - 1);
		}

		reverse_iterator rend(){
			return reverse_iterator(this->begin() - 1);
		}

		const_reverse_iterator rend() const{
			return const_reverse_iterator(this->begin() - 1);
		}

		size_type size() const{
			return _size;
		}

		size_type max_size() const{
			return _allocator.max_size();
		}

		void resize (size_type n, value_type val = value_type()){
			if ( n <= _size)
			{
				for (size_type i = _size; i > n; --i)
				{
					_allocator.destroy(&_val[i-1]);
				}
			}
			else
			{
				insert(end(), n - size(), val);
				// если есть val - использовать insert;
			}
		}

		void reserve (size_type n){
			if (n > max_size())
				throw std::length_error("ERROR: attempt to resize above max_size");
			if (n > _capacity){
				if (n < _capacity * 2)
					n = _capacity * 2;
				pointer _new = _allocator.allocate(n);
				for (size_type i = 0; i < _size; i++) {
					_allocator.construct(_new + i, _val[i]);
					_new[i] = _val[i];
					_allocator.destroy(&_val[i]);
				}
				_allocator.deallocate(_val, _capacity);
				_capacity = n;
				_val = _new;
			}
		}

		size_type capacity() const{
			return _capacity;
		}

		bool empty() const{
			return _size == 0;
		}

		reference operator[] (size_type n){
			return _val[n];
		}
		const_reference operator[] (size_type n) const{
			return _val[n];
		}

		reference at (size_type n){
			if (n >= _size)
				throw std::out_of_range("ERROR: element is out of range");
			return _val[n];
		}
		const_reference at (size_type n) const{
			if (n >= _size)
				throw std::out_of_range("ERROR: element is out of range");
			return _val[n];
		}

		reference front(){
			return *(begin());
		}
		const_reference front() const{
			return *(begin());
		}

		reference back(){
			return *(rbegin());
		}
		const_reference back() const{
			return *(rbegin());
		}

//		range (1)
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true){
			clear();
			insert(begin(), first, last);

		}
//		fill (2)
		void assign (size_type n, const value_type& val){
			clear();
			insert(begin(), n, val);
		}

//		single element (1)
		iterator insert (iterator position, const value_type& val){
			size_type	pos = position - begin();
			insert(position, 1, val);
			return iterator(&_val[pos]);
		}
//		fill (2)
		void insert (iterator position, size_type n, const value_type& val){
			reserve(_size + n);
			size_type start_point = position - begin();
			for (size_type i = _size - 1; i >= start_point; --i)
			{
//				value_type tmp = _val[i];
//				_allocator.destroy(&_val[i]);
//				_allocator.construct(&_val[i + n], tmp);
				_allocator.construct(&_val[i + n], _val[i]);
				if (i < (start_point + n))
				{
//					_allocator.construct(&_val[i], val);
					_val[i] = val;
				}
			}
			_size += n;
		}
//		range (3)
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true){
			size_type n = ft::distance(first, last);
			reserve(_size + n);
			size_type start_point = position - begin();
			for (size_type i = _size - 1; i >= start_point; --i)
			{
//				value_type tmp = _val[i];
//				_allocator.destroy(&_val[i]);
//				_allocator.construct(&_val[i + n], tmp);
				_allocator.construct(&_val[i + n], _val[i]);
				if (i < (start_point + n))
				{
//					_allocator.construct(&_val[i], *first);
					--last;
					_val[i] = *last;
				}
			}
			_size += n;
		}

		void clear(){
			for (int i = 0; i < _size; ++i){
				_allocator.destroy(&_val[i]);
			}
			_size = 0;
		}

		void push_back (const value_type& val){
			std::cout << "push1:" << std::endl;
			insert(end(), 1, val);
			std::cout << "push2:" << std::endl;
		}

		void pop_back(){
			erase(end() -  1);
		}

		iterator erase (iterator position){
			erase(position, position + 1);
			return position;
		}
		iterator erase (iterator first, iterator last){
			size_type dist = last - first;

			size_type start_point = first - begin();
			for (size_type i = start_point; i < _size; ++i)
			{
				if (i < _size - dist)
				{
					_val[i] = _val[i + dist];
				}
				else
				{
					_allocator.destroy(&_val[i]);
				}
			}
			_size -= dist;
			return first;
		}

		void swap (vector& x){
			vector	tmp(*this);
			*this = x;
			x = tmp;
		}

		allocator_type get_allocator() const{
			return _allocator;
		}

	private:
		value_type * _val;
		size_type	_capacity;
		size_type	_size;
		allocator_type _allocator;
//		friend bool operator== (const stack<TStack,ContainerStack>& lhs, const stack<TStack,ContainerStack>& rhs);
//		template <class TStack, class ContainerStack>
//		friend bool operator<  (const stack<TStack,ContainerStack>& lhs, const stack<TStack,ContainerStack>& rhs);


	};

//	(1)
	template <class T, class Alloc>
			bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
				typename vector<T,Alloc>::const_iterator	first1 = lhs.begin();
				typename vector<T,Alloc>::const_iterator	first2 = rhs.begin();
				typename vector<T,Alloc>::const_iterator	last1 = lhs.end();
				typename vector<T,Alloc>::const_iterator	last2 = rhs.end();
				while (first1!=last1)
				{
					if (first2==last2 || *first2<*first1)
						return false;
					else if (*first1<*first2)
						return true;
					++first1;
					++first2;
				}
				return (first2!=last2);
			}
//	(2)
template <class T, class Alloc>
			bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
				return !(lhs==rhs);
			}
//	(3)
	template <class T, class Alloc>
			bool operator==  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
				typename vector<T,Alloc>::const_iterator	first1 = lhs.begin();
				typename vector<T,Alloc>::const_iterator	first2 = rhs.begin();
				typename vector<T,Alloc>::const_iterator	last1 = lhs.end();
				typename vector<T,Alloc>::const_iterator	last2 = rhs.end();
				while (first1!=last1)
				{
					if (first2==last2 || *first2!=*first1)
						return false;
					++first1;
					++first2;
				}
				if (first2!=last2)
					return false;
				return true;
			}
//	(4)
	template <class T, class Alloc>
			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
				return lhs < rhs || lhs == rhs;
			}
//	(5)
	template <class T, class Alloc>
			bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
				return !(lhs<=rhs);
			}
//	(6)
	template <class T, class Alloc>
			bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
				return !(lhs < rhs);
			}

			template <class T, class Alloc>
					void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
						x.swap(y);
					}

//	template <class InputIterator>
//	void test () {
////		typename ft::enable_if<, bool>::type
//		std::cout << std::boolalpha << is_integral<InputIterator>::value << std::endl;
//	}








//template < class Alloc > class vector<bool, Alloc>{
//						public:
//							typedef  bool									value_type;
//							typedef typename std::allocator<value_type >	allocator_type;
//
//							class reference{
//								friend class vector;
//								reference(){}                                          // no public constructor
//							public:
//								~reference(){}
//								operator bool () const{
//
//								}                               // convert to bool
//								reference& operator= (const bool x){
//									return *this;
//								}                  // assign from bool
//								reference& operator= (const reference& x){
//									return *this;
//								}            // assign from bit
//								void flip(){}                                          // flip bit value.
//							};
//
//							typedef value_type 								const_reference;
//							typedef value_type*								pointer;
//							typedef const value_type*						const_pointer;
//							typedef vectorIterator<value_type>				iterator;
//							typedef vectorIterator<const typename checkConst<value_type>::_type>	const_iterator;
//							typedef reverseIterator<iterator>				reverse_iterator;
//							typedef reverseIterator<const_iterator>			const_reverse_iterator;
//
//							typedef ptrdiff_t								difference_type;
//							typedef size_t									size_type;
//
//							/*push_back, insert -основной, вызывает push_back*/
//
//							/*default*/
//							explicit vector (const allocator_type& alloc = allocator_type()) :
//							_val(NULL), _capacity(0), _size(0), _allocator(alloc){
//								//			_val = new value_type;
//								_val = _allocator.allocate(0);
//							}
//
//							/*fill (2)*/
//							explicit vector (size_type n, const value_type& val = value_type(),
//											 const allocator_type& alloc = allocator_type()) :
//											 _val(NULL) , _size(0), _capacity(n) , _allocator(alloc){
//								//insert n элементов со значением val
//								//			_val = _allocator.allocate(n); //в insert будет allocate
//
//							}
//							/*range (3)*/
//							template <class InputIterator>
//									vector (InputIterator first, InputIterator last,
//											const allocator_type& alloc = allocator_type(), typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true)
//											: _val(NULL) , _size(0), _capacity(0), _allocator(alloc){
//												//
//											}
//											/*copy (4)*/
//											vector (const vector& x) :_val(NULL) ,  _capacity(0), _size(0){
//												if (this != &x)
//												{
//													*this = x;
//												}// написать перегрузку оператора присваивания
//											}
//
//											~vector(){
//												// удалить массив
//												for (int i = 0; i < _size; ++i){
//													_allocator.destroy(&_val[i]);
//													//				_allocator.destroy(_val+i); // альтернативный вариант
//												}
//												_allocator.deallocate(_val, _capacity);
//											}
//
//											vector& operator= (const vector& x)
//													{
//												//			this->clear();
//												if (this != &x){
//													if (_val) {
//														for (int i = 0; i < _size; ++i){
//															_allocator.destroy(&_val[i]);
//														}
//														_allocator.deallocate(_val, _capacity);
//													}
//													_allocator = x._allocator;
//													_capacity = x.capacity();
//													_size = x.size();
//													_val = _allocator.allocate(_capacity);
//													for (size_t i = 0; i < _size; ++i) {
//														_allocator.construct(&_val[i], x._val[i]); // создает объект  x._val[i] по адресу &_val[i]
//													}
//												}
//												return *this;
//													}
//
//													iterator begin(){
//												//			return vectorIterator<T>(_val); //альтернативный вариант
//												return iterator(_val);
//											}
//											const_iterator begin() const{
//												return const_iterator(_val);
//											}
//
//											iterator end(){
//												return iterator(_val) + _size;
//											}
//											const_iterator end() const{
//												return const_iterator(_val) + _size;
//											}
//
//											reverse_iterator rbegin(){
//												return reverse_iterator(this->end() - 1);
//											}
//											const_reverse_iterator rbegin() const{
//												return const_reverse_iterator(this->end() - 1);
//											}
//
//											reverse_iterator rend(){
//												return reverse_iterator(this->begin() - 1);
//											}
//
//											const_reverse_iterator rend() const{
//												return const_reverse_iterator(this->begin() - 1);
//											}
//
//											size_type size() const{
//												return _size;
//											}
//
//											size_type max_size() const{
//												return _allocator.max_size();
//											}
//
//											void resize (size_type n, value_type val = value_type()){
//												if ( n <= _size)
//												{
//													for (size_type i = _size; i > n; --i)
//													{
//														_allocator.destroy(&_val[i-1]);
//													}
//												}
//												else
//												{
//													insert(end(), n - size(), val);
//													// если есть val - использовать insert;
//												}
//											}
//
//											void reserve (size_type n){
//												if (n > max_size())
//													throw std::length_error("ERROR: attempt to resize above max_size");
//												if (n > _capacity){
//													if (n < _capacity * 2)
//														n = _capacity * 2;
//													pointer _new = _allocator.allocate(n);
//													for (size_type i = 0; i < _size; i++) {
//														_allocator.construct(_new + i, _val[i]);
//														_new[i] = _val[i];
//														_allocator.destroy(&_val[i]);
//													}
//													_allocator.deallocate(_val, _capacity);
//													_capacity = n;
//													_val = _new;
//												}
//											}
//
//											size_type capacity() const{
//												return _capacity;
//											}
//
//											bool empty() const{
//												return _size == 0;
//											}
//
//											reference operator[] (size_type n){
//												return _val[n];
//											}
//											const_reference operator[] (size_type n) const{
//												return _val[n];
//											}
//
//											reference at (size_type n){
//												if (n >= _size)
//													throw std::out_of_range("ERROR: element is out of range");
//												return _val[n];
//											}
//											const_reference at (size_type n) const{
//												if (n >= _size)
//													throw std::out_of_range("ERROR: element is out of range");
//												return _val[n];
//											}
//
//											reference front(){
//												return *(begin());
//											}
//											const_reference front() const{
//												return *(begin());
//											}
//
//											reference back(){
//												return *(rbegin());
//											}
//											const_reference back() const{
//												return *(rbegin());
//											}
//
//											//		range (1)
//											template <class InputIterator>
//													void assign (InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true){
//												clear();
//												insert(begin(), first, last);
//
//											}
//											//		fill (2)
//											void assign (size_type n, const value_type& val){
//												clear();
//												insert(begin(), n, val);
//											}
//
//											//		single element (1)
//											iterator insert (iterator position, const value_type& val){
//												size_type	pos = position - begin();
//												insert(position, 1, val);
//												return iterator(&_val[pos]);
//											}
//											//		fill (2)
//											void insert (iterator position, size_type n, const value_type& val){
//												reserve(_size + n);
//												size_type start_point = position - begin();
//												for (size_type i = _size - 1; i >= start_point; --i)
//												{
//													//				value_type tmp = _val[i];
//													//				_allocator.destroy(&_val[i]);
//													//				_allocator.construct(&_val[i + n], tmp);
//													_allocator.construct(&_val[i + n], _val[i]);
//													if (i < (start_point + n))
//													{
//														//					_allocator.construct(&_val[i], val);
//														_val[i] = val;
//													}
//												}
//												_size += n;
//											}
//											//		range (3)
//											template <class InputIterator>
//													void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!is_integral<InputIterator>::value, bool>::type = true){
//												size_type n = distance(first, last);
//												reserve(_size + n);
//												size_type start_point = position - begin();
//												for (size_type i = _size - 1; i >= start_point; --i)
//												{
//													//				value_type tmp = _val[i];
//													//				_allocator.destroy(&_val[i]);
//													//				_allocator.construct(&_val[i + n], tmp);
//													_allocator.construct(&_val[i + n], _val[i]);
//													if (i < (start_point + n))
//													{
//														//					_allocator.construct(&_val[i], *first);
//														--last;
//														_val[i] = *last;
//													}
//												}
//												_size += n;
//											}
//
//											void clear(){
//												for (int i = 0; i < _size; ++i){
//													_allocator.destroy(&_val[i]);
//												}
//												_size = 0;
//											}
//
//											void push_back (const value_type& val){
//												insert(end(), 1, val);
//											}
//
//											void pop_back(){
//												erase(end() -  1);
//											}
//
//											iterator erase (iterator position){
//												erase(position, position + 1);
//												return position;
//											}
//											iterator erase (iterator first, iterator last){
//												size_type dist = last - first;
//
//												size_type start_point = first - begin();
//												for (size_type i = start_point; i < _size; ++i)
//												{
//													if (i < _size - dist)
//													{
//														_val[i] = _val[i + dist];
//													}
//													else
//													{
//														_allocator.destroy(&_val[i]);
//													}
//												}
//												_size -= dist;
//												return first;
//											}
//
//											void swap (vector& x){
//												vector	tmp(*this);
//												*this = x;
//												x = tmp;
//											}
//
//											allocator_type get_allocator() const{
//												return _allocator;
//											}
//
//
//
//						private:
//							value_type * _val;
//											size_type	_capacity;
//											size_type	_size;
//											allocator_type _allocator;
//											//		friend bool operator== (const stack<TStack,ContainerStack>& lhs, const stack<TStack,ContainerStack>& rhs);
//											//		template <class TStack, class ContainerStack>
//											//		friend bool operator<  (const stack<TStack,ContainerStack>& lhs, const stack<TStack,ContainerStack>& rhs);
//
//
//						};
}

#endif //TEST_VECTOR_HPP
