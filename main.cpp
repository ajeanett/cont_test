//#include "headers.hpp"
//#include <functional>
//#include <ios>
//#include <iostream>
//#include <iterator>
//#include <list>
//#include <map>
//#include <ostream>
//#include <string>
//#include <type_traits>
//#include <utility>
//#include <vector>
//#include "map.hpp"
//#include "vector.hpp"
//#include "stack.hpp"
////#include "red_black_tree.hpp"
////#include "new_iterator.hpp"
//#include <stack>
//
////#include "stack.hpp"
//
//
//
//int		main(int narg, char **args) {
////	double c[3] = {17.9,2.3,3.4};
////	std::bidirectional_iterator_tag;
//
////	std::vector<double> kekstd(2.0, 5.0);
////	ft::vector<double> kek(2.0, 5.0);
////	kek.assign(c, c + 1);
////	std::cout << *kek.begin() << std::endl;
//	mkdir("./test", 0777);
//	if (narg < 2) {
//		test_vector();
//		test_map();
//		test_stack();
//	}
//	else {
//		for (size_t i = 1; i < narg; ++i){
//			if (std::string(args[i]) == "map")
//				test_map();
//			if (std::string(args[i]) == "vector")
//				test_vector();
//			if (std::string(args[i]) == "stack")
//				test_stack();
//		}
//	}
//	return 0;
//}



#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
		{
		public:
			MutantStack() {}
			MutantStack(const MutantStack<T>& src) { *this = src; }
			MutantStack<T>& operator=(const MutantStack<T>& rhs)
					{
				this->c = rhs.c;
				return *this;
					}
					~MutantStack() {}

					typedef typename ft::stack<T>::container_type::iterator iterator;

			iterator begin() { return this->c.begin(); }
			iterator end() { return this->c.end(); }
		};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
//		std::cout << i << ":" << COUNT << std::endl;
	}
	std::cout << "should be constant with the same test: " << 1 << std::endl;

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	std::cout << "should be constant with the same test: " << 2 << std::endl;
	ft::vector<Buffer>().swap(vector_buffer);
	std::cout << "should be constant with the same test: " << 3 << std::endl;

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	std::cout << "should be constant with the same test: " << 4 << std::endl;
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	std::cout << "should be constant with the same test: " << 5 << std::endl;

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
	{
		iterable_stack.push(letter);
		std::cout << letter << std::endl;
	}
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}