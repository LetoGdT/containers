/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/12 18:07:25 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "AVL_tree.hpp"
#include "pair.hpp"
#include <iostream>

int main() {
	ft::AVL_tree<int, int, std::less<int>, std::allocator<ft::pair<int, int>>> tree;
	for (int i = 0 ; i < 20 ; i++) {
		tree.insert(ft::pair<int, int>(i, i));
	}
	tree.print();
	tree.erase(9);
	tree.erase(11);
	tree.erase(5);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	tree.print();
	return 0;
}

*/
#include <map>
#include <iostream>
#include <string>
#include <string_view>

int main() {
	std::map<int, int> foo;

	foo.insert(std::pair<int, int>(1, 1));
	foo.insert(std::pair<int, int>(2, 2));
	foo.insert(std::pair<int, int>(3, 3));
	foo.insert(std::pair<int, int>(4, 4));
	foo.insert(std::pair<int, int>(5, 5));
	std::map<int, int>::iterator it;
	for (it = foo.begin() ; it != foo.end() ; ++it)
		std::cout << (*it).second << std::endl;
	std::cout << (it == foo.end()) << std::endl;
	it++;
	std::cout << (it == foo.end()) << std::endl;
	return 0;
}
