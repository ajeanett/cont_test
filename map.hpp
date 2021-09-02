//
// Created by Antioch Jeanett on 8/25/21.
//

#ifndef VECTOR_MAP_HPP
#define VECTOR_MAP_HPP

#include <iostream>
#include "vectoriterator.hpp"
#include "tree.hpp"

namespace ft{
//	/**********VALUE_COMPARE**********/
//	template <class Key, class T, class Compare, class Alloc>
//			class map<Key,T,Compare,Alloc>::value_compare
//			{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
//				friend class map;
//
//			protected:
//				Compare comp;
//
//				value_compare(Compare c) : comp(c)
//				{}  // constructed with map's comparison object
//			public:
//				typedef bool result_type;
//				typedef value_type first_argument_type;
//				typedef value_type second_argument_type;
//
//				bool operator()(const value_type &x, const value_type &y) const
//				{
//					return comp(x.first, y.first);
//				}
//			}

//template <class Key, class T, class Compare, class Alloc>
//		class map<Key,T,Compare,Alloc>::value_compare
//				: public std::binary_function<value_type,value_type,bool>{
//		protected:
//			Compare comp;
//		public:
//			typedef bool result_type;
//			typedef value_type first_argument_type;
//			typedef value_type second_argument_type;
//			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
//			bool operator() (const value_type& x, const value_type& y) const
//			{
//				return comp(x.first, y.first);
//			}
//		};

	/**********MAP************/
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::node<pair<const Key,T> > > >
	class map{

	public:
		typedef	Key																	key_type;
		typedef T																	mapped_type;
		typedef pair<const typename checkConst<key_type>::_type ,mapped_type>		value_type;
		typedef Compare																key_compare;
		typedef less<value_type>													value_compare;
//		typedef class value_compare													value_compare;
//		class 																		value_compare;
		typedef Alloc																allocator_type;
		typedef typename allocator_type::reference									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer									pointer;
		typedef typename allocator_type::const_pointer								const_pointer;
		typedef ptrdiff_t															difference_type;
		typedef size_t 																size_type;
		typedef mapIterator<node<value_type> >										iterator;
		typedef mapIterator<const typename checkConst<node<value_type> >::_type> 	const_iterator;
		typedef reverseIterator<iterator>											reverse_iterator;
		typedef reverseIterator<const_iterator>										const_reverse_iterator;
		
//		class value_compare {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
////			friend class map;
//
//				protected:
//					key_compare comp;
//
//					value_compare(Compare c) : comp(c)
//					{}  // constructed with map's comparison object
//				public:
//					typedef bool result_type;
//					typedef value_type first_argument_type;
//					typedef value_type second_argument_type;
//
//					bool operator()(const value_type &x, const value_type &y) const
//					{
//						return comp(x.first, y.first);
//					}
//				}


	private:
		typedef tree<node<value_type> > map_tree;
		allocator_type				_allocator;
		key_compare					_keyCompare;
		value_compare				_valueCompare;
		node<value_type>			*_root;
		node<value_type>			*_end;
		size_type					_size;

	public:

//		empty (1)
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _allocator(alloc), _keyCompare(comp), _root(NULL), _end(NULL), _size(0) /*_valueCompare*/ {
		_root = map_tree::create_node( ft::node<value_type>() , _allocator);
		_end = _root;
	}
//	range (2)
		template <class InputIterator>
			map (InputIterator first, InputIterator last,
				 const key_compare& comp = key_compare(),
				 const allocator_type& alloc = allocator_type(), char (*)[sizeof(*first)] = NULL) :_allocator(alloc), _keyCompare(comp), _root(NULL), _end(NULL), _size(0){
				_root = map_tree::create_node( ft::node<value_type>() , _allocator);
				_end = _root;
				insert(first, last);
			}
//	copy (3)
		map (const map& x){
			_allocator = allocator_type();
			_root = map_tree::create_node( ft::node<value_type>() , _allocator);
			_end = _root;
			if (this != &x)
			{
				*this = x;
			}
		}

		~map(){
		map_tree::clear(&_root, _allocator);
		map_tree ::delete_node(_root, _allocator);
		}

		map& operator= (const map& x){
			if (this != &x)
			{
				std::cout << "start" << std::endl;
				map_tree::clear(&_root, _allocator);
				std::cout << "clear" << std::endl;
				_allocator = x._allocator;
				insert(x.begin(), x.end());
				std::cout << "insert" << std::endl;
				_keyCompare = x._keyCompare;
				_valueCompare = x._valueCompare;
				_size = x._size;
			}
			return (*this);
		}

		iterator begin(){
			return iterator(map_tree::min_node(_root));
		}
		const_iterator begin() const{
			return const_iterator(map_tree::min_node(_root));
		}

		iterator end(){
			return iterator(map_tree::get_end(_root));
		}
		const_iterator end() const{
			return const_iterator(map_tree::get_end(_root));
		}

		reverse_iterator rbegin(){
			return reverse_iterator(--end());
		}

		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(--end());
		}

		reverse_iterator rend(){
			return reverse_iterator(end());
		}
		const_reverse_iterator rend() const{
			return const_reverse_iterator(end());
		}

		bool empty() const{
			return _size == 0;
		}

		size_type size() const{
			return _size;
		}

		size_type max_size() const{
			return _allocator.max_size();
		}

		mapped_type& operator[] (const key_type& k){
			node<value_type> *src = map_tree::create_node(node<value_type>(pair<key_type, mapped_type>(k, mapped_type()), _end), _allocator);
			node<value_type> *tmp = map_tree::insert(&_root, src, _allocator);
			return tmp->pair.second;
		}

//		single element (1)
		pair<iterator,bool> insert (const value_type& val){
			bool _ret = false;
			node<value_type> *src = map_tree::create_node(node<value_type>(val, _end), _allocator);
			node<value_type> *tmp = map_tree::insert(&_root, src, _allocator);
			if (tmp == src)
			{
				++_size;
				_ret = true;
			}
			return ft::pair<iterator, bool>(iterator(tmp), _ret);
		}
//		with hint (2)
		iterator insert (iterator position, const value_type& val) {
			node<value_type> *src = map_tree::create_node(node<value_type>(val, _end), _allocator);
			node<value_type> *tmp = map_tree::insert(&_root, src, _allocator);
			if (tmp == src)
			{
				++_size;
			}
			return iterator(tmp);
		}
//		range (3)
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL){
				size_t i = 0;
				for (; first != last; ++first)
//				while (first != last)
				{
					std::cout << ++i << std::endl;
					this->insert(*first);
//					++first;
				}
		}

//		(1)
		void erase (iterator position){
			bool _del = map_tree::erase(&_root, position.base()->first, _allocator);
			if (_del)
			{
				--_size;
			}
		}
//		(2)
		size_type erase (const key_type& k){
			bool _del = map_tree::erase(&_root, k, _allocator);
			if (_del)
			{
				--_size;
			}
			return static_cast<size_type>(_del);
		}
//		(3)
		void erase (iterator first, iterator last){
			while (first != last)
			{
				this->erase((*first++).first);
			}
		}

		void swap (map& x){
			map	_tmp = *this;
			*this = x;
			x = _tmp;
		}

		void clear(){
			map_tree::clear(&_root, _allocator);
			_size = 0;
		}

		key_compare key_comp() const{
			return _keyCompare;
		}

		value_compare value_comp() const{
			return _valueCompare;
		}

		iterator find (const key_type& k){
//
			node<value_type> *tmp = map_tree::find(_root, k);
			if (tmp)
			{
				return iterator(tmp);
			}
			return end();

		}
		const_iterator find (const key_type& k) const{
			node<value_type> *tmp = map_tree::find(_root, k);
//			node<pair<key_type, mapped_type> > *tmp = map_tree::find(&_root, k);
			if (tmp)
			{
				return iterator(tmp);
			}
			return end();
		}
		size_type count (const key_type& k) const{
//			node<value_type> *tmp = map_tree::find(&_root, k);
			if ((map_tree::find(_root, k)) != NULL)
				return 1;
			return 0;
//			node<pair<Key, mapped_type> > *tmp = map_tree::find(&_root, k);
//			const_iterator tmp = find(k);
//			if (tmp != end())
//			{
//				return 1;
//			}
//			return 0;
		}

		iterator lower_bound (const key_type& k){
//			node<value_type> *tmp = map_tree::min_node(_root);
//			while (tmp && k > tmp->pair.first)
//				tmp = map_tree::min_to_max(tmp);
//			if (tmp)
//				return iterator(tmp);
//			return end();
			
			iterator it = begin();
			iterator ite = end();
			while (it != ite && _keyCompare(it->first, k))
			{
				++it;
			}
			return it;
		}
		const_iterator lower_bound (const key_type& k) const{
//			node<value_type> *tmp = map_tree::min_node(_root);
//			while (tmp && k > tmp->pair.first)
//				tmp = map_tree::min_to_max(tmp);
//			if (tmp)
//				return const_iterator(tmp);
//			return end();
			const_iterator it = begin();
			const_iterator ite = end();
			while (it != ite && _keyCompare(it->first, k))
			{
				++it;
			}
			return it;
		}
		
		iterator upper_bound (const key_type& k){
			iterator it = lower_bound(k);
			iterator ite = end();
			while (it != ite && !_keyCompare(k, it->first))
			{
				++it;
			}
			return it;
		}
		const_iterator upper_bound (const key_type& k) const{
			const_iterator it = lower_bound(k);
			const_iterator ite = end();
			while (it != ite && !_keyCompare(k, it->first))
			{
				++it;
			}
			return it;
		}
		
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		
		pair<iterator,iterator>             equal_range (const key_type& k){
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		};
}

#endif //VECTOR_MAP_HPP
