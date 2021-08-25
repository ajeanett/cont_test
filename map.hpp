//
// Created by Antioch Jeanett on 8/25/21.
//

#ifndef VECTOR_MAP_HPP
#define VECTOR_MAP_HPP

#include <iostream>
#include "vectoriterator.hpp"

namespace ft{
	/**********PAIR************/
	template <class T1, class T2>
	class	pair{
	public:
		typedef T1 first_type;
		typedef T2 second_type;
		first_type first;
		second_type second;

	public:
//		default (1)
		pair() : first(first_type()), second(second_type ()){}
//		copy (2)
		template<class U, class V> pair (const pair<U,V>& pr) :  first(pr.first), second(pr.second){} ;
//		initialization (3)
		pair (const first_type& a, const second_type& b) :  first(a), second(b){} ;

		pair& operator= (const pair& pr){
			if (this != &pr)
			{
				this->first = pr.first;
				this->second = pr.second;
			}
			return *this;
		}
	};

	template <class T1, class T2>
			bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
			bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(lhs==rhs); }

	template <class T1, class T2>
			bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
			bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(rhs<lhs); }

	template <class T1, class T2>
			bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return rhs<lhs; }

	template <class T1, class T2>
			bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
			{ return !(lhs<rhs); }

	template <class T1,class T2>
			pair<T1,T2> make_pair (T1 x, T2 y)
			{
				return ( pair<T1,T2>(x,y) );
			}
	/**********LESS************/
	template <class T>
			class	less : std::binary_function <T,T,bool>{
				bool operator() (const T& x, const T& y) const {return x<y;}
			};
	/**********NODE************/
	template <class T1, class T2>
			class 	node{
			public:
				pair<T1, T2> pair;
				node *right;
				node *left;
				node *parent;
//				node *end;
				node() : pair(ft::pair<T1, T2>()), right(NULL), left(NULL), parent(NULL){}
				node(const ft::pair<T1, T2> &pr) : pair(pr), right(NULL), left(NULL), parent(NULL){}
				node(const node &copy) : pair(copy.pair), right(copy.right), left(copy.left), parent(copy.parent){}
				~node(){}
				bool operator>(const T1 &val)
				{ return this->pair.first > val; }
				bool operator<(const T1 &val)
				{ return this->pair.first < val; }
				bool operator==(const T1 &val)
				{ return this->pair.first == val; }
				bool operator!=(const T1 &val)
				{ return this->pair.first != val; }
				bool operator<=(const T1 &val)
				{ return this->pair.first <= val; }
				bool operator>=(const T1 &val)
				{ return this->pair.first >= val; }
			};

	template <class T1, class T2>
	bool operator==(const node<T1,T2>& lhs, const node<T1,T2>& rhs)
	{ return rhs.pair.first == lhs.pair.first; }

	template <class T1, class T2>
	bool operator!=(const node<T1,T2>& lhs, const node<T1,T2>& rhs)
	{ return rhs.pair.first != lhs.pair.first; }

	template <class T1, class T2>
	bool operator>(const node<T1,T2>& lhs, const node<T1,T2>& rhs)
	{ return rhs.pair.first < lhs.pair.first; }

	template <class T1, class T2>
	bool operator<(const node<T1,T2>& lhs, const node<T1,T2>& rhs)
	{ return rhs.pair.first > lhs.pair.first; }

	template <class T1, class T2>
	bool operator<=(const node<T1,T2>& lhs, const node<T1,T2>& rhs)
	{ return rhs.pair.first >= lhs.pair.first; }

	template <class T1, class T2>
	bool operator>=(const node<T1,T2>& lhs, const node<T1,T2>& rhs)
	{ return rhs.pair.first <= lhs.pair.first; }

	/**********TREE************/
	template < class Key, class T, class Alloc = std::allocator<node<Key,T> > >
	class tree{
	public:
		typedef Key first_type;
		typedef T second_type;
		typedef node<first_type, second_type> node;
		typedef ft::pair<first_type, second_type> pair;
		typedef Alloc allocator_type;
	private:
		allocator_type _alloc;
	public:
		tree(const allocator_type& alloc = allocator_type()) : _alloc(alloc){}
		~tree(){}
		node *create_node(pair &src){
			node *_new = _alloc.allocate(1);
			node	tmp(src);
			_alloc.construct(_new, tmp);
			return _new;
		}

		bool	insert(node **root, node *new_node, node *end){
			if (*root == end)
			{
				*root = new_node;
				end->parent = *root;
			}
			else
			{
				node * tmp = *root;
				while (*tmp != *new_node)
				{
					if (*new_node < *tmp)
					{
						//go to left
						if (tmp->left != NULL)
							tmp = tmp->left;
						else
						{
							tmp->left = new_node;
							new_node->parent = tmp;
							return true;
						}
					}
					else if (*new_node > *tmp)
					{
						//go to right
						if (tmp->right != NULL)
							tmp = tmp->right;
						else
						{
							tmp->right = new_node;
							new_node->parent = tmp;
							return true;
						}
					}
				}
				delete_node(new_node);
				return false;
			}
			return true;
		}

		bool 	erase(node **root, first_type &key, node *end){
			node *remove = find(root, key, end);
			if (remove)
			{


				node*	replace = NULL;
				if (remove->left)
					replace = erase_left(remove, root);
				else if (remove->right)
					replace = erase_right(remove, root);
				else
					replace = erase_not_child(remove, root);
				if (replace) {
					remove->pair.first = replace->pair.first;
					remove->pair.second = replace->pair.second;
				}
				else
					replace = remove;
				if (replace == remove && remove == *root) {
					*root = NULL;
					if (replace->end)
						replace->end->parent = NULL;
				}


				delete_node(remove);
				return true;
			}
			return false;
		}

		node	*find(node **root, first_type &key, node *end, bool is_create = false, pair *src = NULL){
			if (*root != end)
			{
				node *tmp = *root;
				while (tmp)
				{
					if (key < *tmp)
					{
						//go to left
						tmp = tmp->left;
					}
					else if (key > *tmp)
					{
						//go to right
						tmp = tmp->right;
					}
					else if (key == *tmp)
					{
						return tmp;
					}
				}
				if (is_create)
				{
					node *new_node = create_node(*src);
					insert(root, new_node, end);
					return new_node;
				}
			}
			return NULL;
		}

		node	*min_node(node *now_node, bool is_root = false){
			if (is_root == true)
			{
				now_node = get_root(now_node);
			}
			while (now_node->left != NULL)
			{
				now_node = now_node->left;
			}
			return now_node;
		}

		node	*max_node(node *now_node, bool is_root = false){
			if (is_root == true)
			{
				now_node = get_root(now_node);
			}
			while (now_node->right != NULL)
			{
				now_node = now_node->right;
			}
			return now_node;
		}

		/*decrement*/
		node	*max_to_min(node *now_node){
			if (get_root(now_node) != end)
			{
				if (now_node == end)
				{
					now_node = max_node(now_node, true);
				}
			}
			return now_node;
		}

		/*increment*/
		node	*min_to_max(node *now_node){
		}

		void	clear(node *now_node){
		}

		size_t max_size(){
		}

		node	*get_root(node *now_node){

			while (now_node->parent != NULL)
			{
				now_node = now_node->parent;
			}
			return  now_node;
		}

		void 	delete_node(node *n){
		}
	};

	/**********MAP************/
	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map{

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const typename checkConst<key_type>::_type ,mapped_type> value_type;
		typedef Compare key_compare;
		typedef less<value_type>	value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;


	private:

	public:

	};
}

#endif //VECTOR_MAP_HPP
