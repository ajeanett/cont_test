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
	template <class Pair>
			class 	node{
			public:
				typedef typename Pair::first_type key_type;
				Pair pair;
				node *right;
				node *left;
				node *parent;
				node *end;
				node(node *end = NULL) : pair(Pair()), right(NULL), left(NULL), parent(NULL), end(end) {}
				node(const Pair &pr, node *end = NULL) : pair(pr), right(NULL), left(NULL), parent(NULL), end(end){}
				node(const node &copy) : pair(copy.pair), right(copy.right), left(copy.left), parent(copy.parent), end(copy.end){}
				~node(){}
				bool operator>(const key_type &val)
				{ return this->pair.first > val; }
				bool operator<(const key_type &val)
				{ return this->pair.first < val; }
				bool operator==(const key_type &val)
				{ return this->pair.first == val; }
				bool operator!=(const key_type &val)
				{ return this->pair.first != val; }
				bool operator<=(const key_type &val)
				{ return this->pair.first <= val; }
				bool operator>=(const key_type &val)
				{ return this->pair.first >= val; }
			};

	template <class Pair>
	bool operator==(const node<Pair>& lhs, const node<Pair>& rhs)
	{ return rhs.pair.first == lhs.pair.first; }

	template <class Pair>
	bool operator!=(const node<Pair>& lhs, const node<Pair>& rhs)
	{ return rhs.pair.first != lhs.pair.first; }

	template <class Pair>
	bool operator>(const node<Pair>& lhs, const node<Pair>& rhs)
	{ return rhs.pair.first < lhs.pair.first; }

	template <class Pair>
	bool operator<(const node<Pair>& lhs, const node<Pair>& rhs)
	{ return rhs.pair.first > lhs.pair.first; }

	template <class Pair>
	bool operator<=(const node<Pair>& lhs, const node<Pair>& rhs)
	{ return rhs.pair.first >= lhs.pair.first; }

	template <class Pair>
	bool operator>=(const node<Pair>& lhs, const node<Pair>& rhs)
	{ return rhs.pair.first <= lhs.pair.first; }

	/**********TREE************/
	template < class Node = ft::node<ft::pair<int, int> >, class Alloc = std::allocator<Node> >
	class tree{
	public:
		typedef typename Node::key_type first_type;
		typedef Node node;
		typedef Alloc allocator_type;
//	private:
//		allocator_type _alloc;
	public:
		tree(const allocator_type& alloc = allocator_type()){}
		~tree(){}

		static node *create_node(node &src, allocator_type _alloc){
			node *_new = _alloc.allocate(1);
			_alloc.construct(_new, src); // конструктор ноды вызвать в map
			return _new;
		}

		node	*find(node **root, first_type &key, bool is_create = false){
			if ((*root)->end != NULL)
			{
				node *tmp = *root;
				while (tmp)
				{
					if (key < *tmp)
					{
						//go to left
						if (is_create == true && tmp->left == NULL)
							return tmp;
						tmp = tmp->left;
					}
					else if (key > *tmp)
					{
						//go to right
						if (is_create == true && tmp->right == NULL)
							return tmp;
						tmp = tmp->right;
					}
					else if (key == *tmp)
					{
						return tmp;
					}
				}
			}
			return NULL;
		}

		bool	insert(node **root, node *new_node, allocator_type &_alloc){
			node	*tmp = find(root, new_node->pair.first, true);
			if (tmp == NULL)
			{
				*root = new_node;
				new_node->end->parent = new_node; // root
				new_node->end->left = new_node; // min node
				new_node->end->right = new_node; // max node
				return true;
			}
			else if (*tmp == *new_node)
			{
				delete_node(new_node, _alloc);
			}
			else if (*new_node > *tmp)
			{
				tmp->right = new_node;
				if (tmp == max_node(tmp, true))
				{
					tmp->end->right = new_node; // новая нода становится максимальной
				}
				return true;
			}
			else if (*new_node < *tmp)
			{
				tmp->left = new_node;
				if (tmp == min_node(tmp, true))
				{
					tmp->end->left = new_node; // новая нода становится минимальной
				}
				return true;
			}
			return false;
		}

		bool 	erase(node **root, first_type &key, allocator_type &_alloc){
			node	*remove = find(root, key);
			if (remove != NULL)
			{
				node	*replace = NULL;
				if (remove->left != NULL)
				{
					replace = max_node(remove->left);
					if (replace == remove->left)
					{
						replace->parent = remove->parent;
						if (replace->parent != NULL)
						{
							if (replace->parent->right == remove)
							{
								/*Если удаляемый элемент был у парента справа*/
								replace->parent->right = replace;
							}
							else
							{
								/*Если удаляемый элемент был у парента слева*/
								replace->parent->left = replace;
							}
						}
						replace->right = remove->right;
						if (replace->right != NULL)
						{
							replace->right->parent = replace; // меняем парент у правой ветки с удаленной ноды на новую
						}
					}
					else
					{
						/**/
						replace->parent->right = replace->left; // соединяем левую ветку у реплейс с парентом реплейс, если она есть (у  replace правая ветка точно NULL, а левая может быть не NULL)
						if (replace->left != NULL)
						{
							replace->left->parent = replace->parent; //на место replace ставим его левую ноду, чтобы они были двусвязны
						}
						replace->parent = remove->parent;
						if (replace->parent != NULL) // поменяли не корень
						{

							if (replace->parent->right == remove)
							{
								/*Если удаляемый элемент был у парента справа*/
								replace->parent->right = replace;
							}
							else
							{
								/*Если удаляемый элемент был у парента слева*/
								replace->parent->left = replace;
							}
						}
						replace->right = remove->right;
						if (replace->right != NULL)
						{
							replace->right->parent = replace; // связали правую ветку с новой нодой replace
						}
						replace->left = remove->left;
						if (replace->left != NULL)
						{
							replace->left->parent = replace; // связали левая ветку с новой нодой replace
						}
					}
					/*Если remove максимальная нода, то максимальной становится replace*/
					if (remove == max_node(remove, true))
					{
						remove->end->right = replace;
					}
				}
				else if (remove->right != NULL)
				{
					replace = min_node(remove->right);
					if (replace == remove->right)
					{
						replace->parent = remove->parent;
						if (replace->parent != NULL) // не рут
						{
							if (replace->parent->right == remove)
							{
								/*Если удаляемый элемент был у парента справа*/
								replace->parent->right = replace;
							}
							else
							{
								/*Если удаляемый элемент был у парента слева*/
								replace->parent->left = replace;
							}
						}
					}
					else
					{
						/**/
						replace->parent->left = replace->right; // соединяем правую ветку у реплейс с парентом реплейс, если она есть (у  replace левая ветка точно NULL, а правая может быть не NULL)
						if (replace->right != NULL)
						{
							replace->right->parent = replace->parent; //на место replace ставим его левую ноду, чтобы они были двусвязны
						}
						replace->parent = remove->parent;
						if (replace->parent != NULL) // поменяли не корень
						{
							if (replace->parent->right == remove)
							{
								/*Если удаляемый элемент был у парента справа*/
								replace->parent->right = replace;
							}
							else
							{
								/*Если удаляемый элемент был у парента слева*/
								replace->parent->left = replace;
							}
						}
						replace->right = remove->right;
						if (replace->right != NULL)
						{
							replace->right->parent = replace; // связали правую ветку с новой нодой replace
						}
					}
					/*Если remove минимальная нода, то минимальной становится replace*/
					if (remove == min_node(remove, true))
					{
						remove->end->left = replace;
					}
				}
				else // если у remove нет детей
				{
					replace = remove->parent;
					if (replace != NULL) // не рут
					{
						if (replace->right == remove)
						{
							/*Если удаляемый элемент был у парента справа*/
							replace->right = NULL;
						}
						else
						{
							/*Если удаляемый элемент был у парента слева*/
							replace->left = NULL;
						}
					}
					if (remove == max_node(remove, true))
					{
						remove->end->right = remove->parent;
					}
					else if (remove == min_node(remove, true))
					{
						remove->end->left = remove->parent;
					}
				}
				if (remove == *root)
				{
					if (replace != NULL)
					{
						*root = replace;
						replace->end->parent = replace;
					}
					else
					{
						*root = remove->end; // мы удалили единственную ноду
						(*root)->parent = NULL;
						(*root)->left = NULL;
						(*root)->right = NULL;
					}
				}
				delete_node(remove, _alloc);
				return true;
			}
			return false;




//			node *remove = find(root, key, end);
//
//			if (remove == NULL)
//			{
//				//что делать?
//				return false;
//			}
//			if (remove)
//			{
//				if ((remove->left == NULL || remove->left == end) && (remove->right == NULL || remove->right == end )) // нет child
//				{
//
//				}
//				node*	replace = NULL;
//				if (remove->left)
//					replace = erase_left(remove, root);
//				else if (remove->right)
//					replace = erase_right(remove, root);
//				else
//					replace = erase_not_child(remove, root);
//				if (replace) {
//					remove->pair.first = replace->pair.first;
//					remove->pair.second = replace->pair.second;
//				}
//				else
//					replace = remove;
//				if (replace == remove && remove == *root) {
//					*root = NULL;
//					if (replace->end)
//						replace->end->parent = NULL;
//				}
//				delete_node(remove);
//				return true;
//			}
//			return false;
		}

		node	*min_node(node *now_node, bool is_root = false){
			if (is_root == true)
			{
				return now_node->end->left;
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
				return now_node->end->right;
			}
			while (now_node->right != NULL)
			{
				now_node = now_node->right;
			}
			return now_node;
		}

		/*decrement*/
		node	*max_to_min(node *now_node){
			return now_node;
		}

		/*increment*/
		node	*min_to_max(node *now_node){
			return now_node;
		}

		void	clear(node *now_node){
		}

		size_t max_size(allocator_type &_alloc){
			return _alloc.max_size();
		}

		node	*get_root(node *now_node){
			return  now_node->end->parent;
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
