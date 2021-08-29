//
// Created by Antioch Jeanett on 8/29/21.
//

#ifndef VECTOR_TREE_HPP
#define VECTOR_TREE_HPP

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
				typedef Pair node_pair;
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

				static node	*find(node **root, first_type &key, bool is_create = false){
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

				static node *	insert(node **root, node *new_node, allocator_type &_alloc){
					node	*tmp = find(root, new_node->pair.first, true);
					if (tmp == NULL)
					{
						*root = new_node;
						new_node->end->parent = new_node; // root
						new_node->end->left = new_node; // min node
						new_node->end->right = new_node; // max node
						return new_node;
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
						return new_node;
					}
					else if (*new_node < *tmp)
					{
						tmp->left = new_node;
						if (tmp == min_node(tmp, true))
						{
							tmp->end->left = new_node; // новая нода становится минимальной
						}
						return new_node;
					}
					return NULL;//tmp;
				}

				static bool 	erase(node **root, first_type &key, allocator_type &_alloc){
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
				}

				static node	*min_node(node *now_node, bool is_root = false){
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

				static node	*max_node(node *now_node, bool is_root = false){
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
				static node	*max_to_min(node *now_node){
					if (now_node != NULL)
					{
						if (now_node->end == NULL) // если это end нода, то меняем на максимальную ноду
							{
							if (now_node->parent != NULL) // если end нода не является рутом (т.е. в мапе есть хоть одна обычная нода)
								{
								now_node = now_node->right;
								}
							}
						else if (now_node == min_node(now_node, true)) // если это минимальная нода, то меняем на end ноду
							{
							now_node = now_node->end;
							}
						else if (now_node->left != NULL)
						{
							now_node = max_node(now_node->left); // если левая ветка существует, то мы ищем максимальную ноду слева
						}
						else if (now_node->parent != NULL)
						{
							while (now_node->parent->left == now_node) // пока леавя ветка парент равна текущей ноде, мы меняем текущую ноду на парент. Как только текущая нода будет справа у парент, то мы последний раз меняем тек ноду на парент
								{
								now_node = now_node->parent;
								}
							now_node = now_node->parent;
						}
					}
					return now_node;
				}

				/*increment*/
				static node	*min_to_max(node *now_node){
					if (now_node != NULL)
					{
						if (now_node->end == NULL) // если это end нода, то меняем на минимальную ноду
							{
							if (now_node->parent != NULL) // если end нода не является рутом (т.е. в мапе есть хоть одна обычная нода)
								{
								now_node = now_node->left;
								}
							}
						else if (now_node == max_node(now_node, true)) // если это максимальная нода, то меняем на end ноду
							{
							now_node = now_node->end;
							}
						else if (now_node->right != NULL)
						{
							now_node = min_node(now_node->right); // если правая ветка существует, то мы ищем минимальную ноду справа
						}
						else if (now_node->parent != NULL)
						{
							while (now_node->parent->right == now_node) // пока правая ветка парент равна текущей ноде, мы меняем текущую ноду на парент. Как только текущая нода будет слева у парент, то мы последний раз меняем тек ноду на парент
								{
								now_node = now_node->parent;
								}
							now_node = now_node->parent;
						}
					}
					return now_node;
				}

				static void	clear(node **root, allocator_type &_alloc){
					while ((*root)->end != NULL)
					{
						erase(root, (*root)->pair.first, _alloc);
					}
				}

				static size_t max_size(allocator_type &_alloc){
					return _alloc.max_size();
				}

				static node	*get_root(node *now_node){
					return  now_node->end->parent;
				}

				static void 	delete_node(node *n, allocator_type &_alloc){
					if (n != NULL)
					{
						_alloc.destroy(n); // вызывает деструктор объекта(ноды)
						_alloc.deallocate(n, 1); // освобождаем выделенную память
					}
				}

				static node *	get_end(node *n)
				{
					if (n->end == NULL) // значит это энд нода
						return n;
					return n->end;
				}
			};

}

namespace tree {
	void f() {};
}

#endif //VECTOR_TREE_HPP
