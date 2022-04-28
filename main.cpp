/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/28 18:27:04 by lgaudet-         ###   ########.fr       */
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
		std::cout << "testing v.erase(v.begin() + 2, v.begin() + 4)" << std::endl;
		i = v.erase(v.begin() + 2, v.begin() + 4);
		std::cout << *i << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing v.erase(v.begin(), v.begin() + 4)" << std::endl;
		i = v.erase(v.begin(), v.begin() + 4);
		std::cout << *i << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "current size of v: " << v.size() << std::endl;
		std::cout << "current v.back(): " << v.back() << std::endl;
		std::cout << "testing v.push_back(rand()%200)" << std::endl;
		v.push_back(rand()%200);
		std::cout << "current v.back(): " << v.back() << std::endl;
		std::cout << "current *(v.end() - 2) " << *(v.end() - 2) << std::endl;
		std::cout << "current size of v: " << v.size() << std::endl;
		std::cout << "testing v.pop_back()" << std::endl;
		v.pop_back();
		std::cout << "current v.back(): " << v.back() << std::endl;
		std::cout << "current size of v: " << v.size() << std::endl;
		std::cout << "testing v.resize with count equal to v.size()" << std::endl;
		std::cout << "before:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		v.resize(v.size());
		std::cout << "after:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing v.resize with count greater than v.size()" << std::endl;
		std::cout << "before:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		v.resize(v.size() + 10);
		std::cout << "after:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing v.resize with count smaller than v.size()" << std::endl;
		std::cout << "before:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		v.resize(v.size() - 10);
		std::cout << "after:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing v.swap(w)" << std::endl;
		std::cout << "before:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		v.swap(w);
		std::cout << "after:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		std::cout << "testing NAMESPACE::swap(v, w)" << std::endl;
		std::cout << "before:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;
		NAMESPACE::swap(v, w);
		std::cout << "after:" << std::endl;
		for (i = v.begin() ; i != v.end() ; ++i)
			std::cout << *i << std::endl;

		std::cout << std::endl;
		NAMESPACE::vector<int>::const_iterator j;
		i = v.begin();
		j = v.begin();
		i++;
		std::cout << "testing iterators" << std::endl;
		std::cout << "i: v.begin() + 1" << std::endl;
		std::cout << "j: v.begin()" << std::endl;
		std::cout << "*i: " << *i << std::endl;
		std::cout << "*j: " << *j << std::endl;
		std::cout << "(i != j): " << (i != j) << std::endl;
		std::cout << "(i < j): " << (i < j) << std::endl;
		std::cout << "(i > j): " << (i > j) << std::endl;
		std::cout << "(i <= j): " << (i <= j) << std::endl;
		std::cout << "(i >= j): " << (i >= j) << std::endl;
		std::cout << "*(i - 1): " << *(i - 1) << std::endl;
		std::cout << "*(i + 1): " << *(i + 1) << std::endl;
		std::cout << "*(1 + i): " << *(1 + i) << std::endl;
		std::cout << "i - j: " << i - j << std::endl;
		i--;
		std::cout << "i--" << std::endl;
		std::cout << "i: v.begin() + 1" << std::endl;
		std::cout << "j: v.begin()" << std::endl;
		std::cout << "*i: " << *i << std::endl;
		std::cout << "*j: " << *j << std::endl;
		std::cout << "(i != j): " << (i != j) << std::endl;
		std::cout << "(i < j): " << (i < j) << std::endl;
		std::cout << "(i > j): " << (i > j) << std::endl;
		std::cout << "(i <= j): " << (i <= j) << std::endl;
		std::cout << "(i >= j): " << (i >= j) << std::endl;
		std::cout << "*(i + 1): " << *(i + 1) << std::endl;
		std::cout << "*(1 + i): " << *(1 + i) << std::endl;
		std::cout << "i - j: " << i - j << std::endl;
		i++;
		NAMESPACE::vector<int>::const_iterator k = v.begin();
		std::cout << "testing iterators" << std::endl;
		std::cout << "k: v.begin() + 1" << std::endl;
		std::cout << "*k: " << *k << std::endl;
		std::cout << "(k != i): " << (k != i) << std::endl;
		std::cout << "(k < i): " << (k < i) << std::endl;
		std::cout << "(k > i): " << (k > i) << std::endl;
		std::cout << "(k <= i): " << (k <= i) << std::endl;
		std::cout << "(k >= i): " << (k >= i) << std::endl;
		std::cout << "k - i: " << k - i << std::endl;
		NAMESPACE::vector<int>::reverse_iterator l = v.rbegin();
		std::cout << "showing both normal and reverse iterators" << std::endl;
		for (i = v.begin() ; i != v.end() && l != v.rend() ; ++i, ++l)
			std::cout << *i << " " << *l << std::endl;
	}

	// Tests of map
	{
		NAMESPACE::map<int, int> m;
		for (int i = 0 ; i < 50 ; ++i) {
			int nb = rand()%100;
			m.insert(NAMESPACE::make_pair(nb, nb));
		}
		NAMESPACE::map<int, int>::iterator k;
		NAMESPACE::map<int, int> n = m;
		NAMESPACE::map<int, int> o(m);
		NAMESPACE::map<int, int> p(m.begin(), m.end());
		std::cout << "testing constructors" << std::endl;
		std::cout << "showing m" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "showing n" << std::endl;
		for (k = n.begin() ; k != n.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "showing o" << std::endl;
		for (k = o.begin() ; k != o.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "showing p" << std::endl;
		for (k = p.begin() ; k != p.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "testing ’at’ function" << std::endl;
		try {
			std::cout << "m.at(97): " << m.at(97) << std::endl;
		} catch (std::exception & e) {
			std::cout << "unexpected exception raised" << std::endl;
		}
		try {
			std::cout << "m.at(97): " << m.at(200) << std::endl;
			std::cout << "error: no exception was raised!" << std::endl;
		} catch (std::exception & e) {
			std::cout << "exception raised as expected" << std::endl;
		}
		std::cout << "testing operator[]" << std::endl;
		std::cout << "m[97]: " << m[97] << std::endl;
		std::cout << "m[97] = 200: " << (m[97] = 200) << std::endl;
		std::cout << "m[97]: " << m[97] << std::endl;
		std::cout << "m[97] = 97: " << (m[97] = 97) << std::endl;
		std::cout << "m[97]: " << m[97] << std::endl;
		std::cout << "m[200] = 200: " << (m[200] = 200) << std::endl;
		try {
			std::cout << "m.at(200): " << m.at(200) << std::endl;
		} catch (std::exception & e) {
			std::cout << "unexpected exception raised" << std::endl;
		}
		std::cout << "testing empty, size and clear functions" << std::endl;
		std::cout << "m.size(): " << m.size() << std::endl;
		std::cout << "m.empty(): " << m.empty() << std::endl;
		std::cout << "m.clear() " << std::endl; 
		m.clear();
		std::cout << "m.size(): " << m.size() << std::endl;
		std::cout << "m.empty(): " << m.empty() << std::endl;
		std::cout << "testing insert functions" << std::endl;
		NAMESPACE::pair<NAMESPACE::map<int, int>::iterator, bool> res = m.insert(NAMESPACE::make_pair(200, 200));
		std::cout << "iterator: " << (*res.first).first << std::endl;
		std::cout << "bool: " << res.second << std::endl;
		std::cout << "testing insert(iterator, iterator)" << std::endl;
		std::cout << "before" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).first << std::endl;
		m.insert(n.begin(), n.end());
		std::cout << "after" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).second << std::endl;
		std::cout << "testing erase(iterator pos)" << std::endl;
		m.erase(++m.begin());
		std::cout << "after" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).second << std::endl;
		m.erase(--m.end());
		std::cout << "testing erase(--m.end())" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).second << std::endl;
		std::cout << "m.size(): " << m.size()<< std::endl;
		k = m.begin();
		k++;
		k++;
		k++;
		std::cout << "k = m.begin()" << std::endl;
		std::cout << "k++" << std::endl;
		std::cout << "k++" << std::endl;
		std::cout << "k++" << std::endl;
		std::cout << "testing erase(++m.begin(), k)" << std::endl;
		m.erase(++m.begin(), k);
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).second << std::endl;
		m.clear();
		n.clear();
		for (int i = 0 ; i < 50 ; ++i) {
			int nb = rand() % 200;
			m.insert(NAMESPACE::make_pair(nb, nb));
		}
		for (int i = 0 ; i < 50 ; ++i) {
			int nb = rand() % 200;
			n.insert(NAMESPACE::make_pair(nb, nb));
		}
		std::cout << "testing m.swap(n)" << std::endl;
		std::cout << "before" << std::endl;
		std::cout << "m" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "n" << std::endl;
		for (k = n.begin() ; k != n.end() ; ++k)
			std::cout << (*k).first << std::endl;
		m.swap(n);
		std::cout << "after" << std::endl;
		std::cout << "m" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "n" << std::endl;
		for (k = n.begin() ; k != n.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "testing NAMESPACE::swap(m, n)" << std::endl;
		std::cout << "before" << std::endl;
		std::cout << "m" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "n" << std::endl;
		for (k = n.begin() ; k != n.end() ; ++k)
			std::cout << (*k).first << std::endl;
		NAMESPACE::swap(m, n);
		std::cout << "after" << std::endl;
		std::cout << "m" << std::endl;
		for (k = m.begin() ; k != m.end() ; ++k)
			std::cout << (*k).first << std::endl;
		std::cout << "n" << std::endl;
		for (k = n.begin() ; k != n.end() ; ++k)
			std::cout << (*k).first << std::endl;
	}

	//Tests of stack
	{
	}

	return 0;
}
