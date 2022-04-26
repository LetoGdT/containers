/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/26 20:33:02 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#ifndef STD
# include "vector.hpp"
# include "map.hpp"
# include "stack.hpp"
# define NAMESPACE ft
#else
# include <vector>
# include <map>
# include <stack>
# define NAMESPACE std
#endif

int main() {
	// Tests of vector
	{
		srand(424242);
		NAMESPACE::vector<int>::iterator i;

		NAMESPACE::vector<int> v(50, 42);
		std::cout << "Creating vector<int> v(50, 42)" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		NAMESPACE::vector<int> w(v);
		std::cout << "Creating vector<int> w(v)" << std::endl;
		for (i = w.begin() ; i != w.end() ; ++i)
			std::cout << *i << std::endl;
		NAMESPACE::vector<int> x;
		std::cout << "Creating vector<int> x" << std::endl;
		for (i = x.begin() ; i != x.end() ; ++i)
			std::cout << *i << std::endl;
		NAMESPACE::vector<int> y(v.begin(), v.end());
		std::cout << "Creating vector<int> z(v.begin(), v.end())" << std::endl;
		for (i = y.begin() ; i != y.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "v.assign(30, 52)" << std::endl;
		v.assign(30, 52);
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "verifying that the other vectors were not changed" << std::endl;
		for (i = w.begin() ; i != w.end() ; ++i)
			std::cout << *i << std::endl;
		for (i = x.begin() ; i != x.end() ; ++i)
			std::cout << *i << std::endl;
		for (i = y.begin() ; i != y.end() ; ++i)
			std::cout << *i << std::endl;

		std::cout << "Inserting 50 ’random’ numbers into v" << std::endl;
		v.clear();
		for (int j = 0 ; j < 50 ; ++j)
			v.insert(v.end(), rand()%100);
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;

		std::cout << "testing at function" << std::endl;
		try {
			std::cout << v.at(20) << std::endl;
			std::cout << "No exception was raised, as expected" << std::endl;
		} catch (std::exception & e) {
			std::cout << "Unexpected exception raised" << std::endl;
		}
		try {
			std::cout << v.at(40) << std::endl;
			std::cout << "No exception was raised, which is unexpected" << std::endl;
		} catch (std::exception & e) {
			std::cout << "exception caught, as expected" << std::endl;
		}
		std::cout << "Testing operator[]: " << std::endl;
		std::cout << v[4] << std::endl;
		//std::cout << v[40] << std::endl; // this line will segfault!
		std::cout << "Testing front: " << v.front() << std::endl;
		std::cout << "Testing back: " << v.back() << std::endl;

		std::cout << "testing insert operations" << std::endl;
		i = v.insert(v.end(), 42);
		std::cout << "value of returned iterator is correct: " << (*i == 42) << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		v.insert(v.begin(), 5, 42);
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		w.clear();
		for (int j = 0 ; j < 10 ; ++j)
			w.insert(w.end(), j);
		std::cout << "testing v.insert(v.begin(), w.begin(), w.end())" << std::endl;
		v.insert(v.begin(), w.begin(), w.end());
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing v.erase(v.end() - 1)" << std::endl;
		v.erase(v.end() - 1);
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing v.erase(v.begin())" << std::endl;
		v.erase(v.begin());
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing v.erase(v.begin() - 1)" << std::endl;
		v.erase(v.begin() - 1);
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		// segfault in std
		//std::cout << "testing v.erase(v.end())" << std::endl;
		//v.erase(v.end());
		//for (i = v.begin() ; i != v.end() ; ++i)
		//	std::cout << *i << std::endl;
		std::cout << "testing v.erase(v.begin() - 1, v.end())" << std::endl;
		i = v.erase(v.begin(), v.end() - 10);
		std::cout << *i << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		for (int j = 0 ; j < 15 ; ++j)
			v.insert(v.end(), rand()%100);
		std::cout << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing v.erase(v.begin() + 20, v.end())" << std::endl;
		i = v.erase(v.begin() + 20, v.end());
		std::cout << *i << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;


		std::cout << std::endl;
		NAMESPACE::vector<int>::const_iterator j;
		i = v.begin();
		j = v.begin();
		i++;
		std::cout << (i != j) << std::endl;
		std::cout << (i < j) << std::endl;
		std::cout << (i > j) << std::endl;
		std::cout << (i <= j) << std::endl;
		std::cout << (i >= j) << std::endl;
	}

	// Tests of map
	{
		NAMESPACE::map<int, int> m;
		m.insert(NAMESPACE::make_pair(2, 2));
		NAMESPACE::map<int, int>::iterator k;
		NAMESPACE::map<int, int>::const_iterator l;
	}

	//Tests of stack
	{
	}

	return 0;
}
