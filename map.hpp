//
// Created by Antioch Jeanett on 8/25/21.
//

#ifndef VECTOR_MAP_HPP
#define VECTOR_MAP_HPP

#include <iostream>
#include "vectoriterator.hpp"
#include "tree.hpp"

namespace ft{
	/**********MAP************/
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map{

	public:
		typedef	Key																	key_type;
		typedef T																	mapped_type;
		typedef pair<const typename checkConst<key_type>::_type ,mapped_type>		value_type;
		typedef Compare																key_compare;
		typedef less<value_type>													value_compare;
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


	private:
		typedef tree<node<value_type> > map_tree;
		allocator_type				_allocator;
		key_compare					_keyCompare;
		value_compare				_valueCompare;
//		node<value_type>			*_current;
		node<value_type>			*_root;
//		node<value_type>			*_end;
		size_type					_size;

	public:

//		empty (1)
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _allocator(alloc), _root(NULL), _size(0) , _keyCompare(comp) /*_valueCompare*/ {
		_root = map_tree::create_node( ft::node<value_type>() , _allocator);
	}
//	range (2)
		template <class InputIterator>
			map (InputIterator first, InputIterator last,
				 const key_compare& comp = key_compare(),
				 const allocator_type& alloc = allocator_type()) :_allocator(alloc), _root(NULL), _size(0) , _keyCompare(comp){
		_root = map_tree::create_node( ft::node<value_type>() , _allocator);
		//insert(first, last);
	}
//	copy (3)
		map (const map& x){
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
				map_tree::clear(&_root, _allocator);
				_allocator = x._allocator;
//				_root = x._root;
//				insert(x.begin(), x.end());
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
			node<value_type> *tmp = map_tree::insert(&_root, map_tree::create_node(node<value_type>(pair<key_type, mapped_type>(k, mapped_type()))));
			return tmp->pair.second;
		}

//		single element (1)
		pair<iterator,bool> insert (const value_type& val){
			bool _ret = false;
			node<value_type> *tmp = map_tree::insert(&_root, map_tree::create_node(node<value_type>(val)));
			if (tmp)
			{
				++_size;
				_ret = true;

			}
			tmp = map_tree::find(&_root, val.first);
			if (tmp)
			{
				return ft::pair<iterator, bool>(iterator(tmp), _ret);
			}
			return ft::pair<iterator, bool>(iterator(this->end()), _ret);
		}
//		with hint (2)
		iterator insert (iterator position, const value_type& val) {
			node<value_type> *tmp = map_tree::insert(&_root, map_tree::create_node(node<value_type>(val)));
			if (tmp)
			{
				++_size;
			}
			tmp = map_tree::find(&_root, val.first);
			if (tmp)
			{
				return iterator(tmp);
			}
			return iterator(this->end());
		}
//		range (3)
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last){
				while (first != last)
				{
					this->insert(*first);
					++first;
				}
		}

//		(1)
		void erase (iterator position){
			bool _del = map_tree::erase(&_root, position.base()->first);
			if (_del)
			{
				--_size;
			}
		}
//		(2)
		size_type erase (const key_type& k){
			bool _del = map_tree::erase(&_root, k);
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
				this->erase(*first);
				++first;
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
			node<value_type> *tmp = map_tree::find(&_root, k);
			if (tmp)
			{
				return iterator(tmp);
			}
			return iterator(end());

		}
		const_iterator find (const key_type& k) const{


		}
		size_type count (const key_type& k) const{

		}

	};
}

#endif //VECTOR_MAP_HPP
