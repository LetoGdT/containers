/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/23 21:41:08 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
#include <vector>
#include <iostream>


int main() {
	std::vector<int> v;

	v.insert(v.begin(), 12);
	v.insert(v.begin(), 11);
	std::vector<int>::iterator it = v.begin();
	std::vector<int> w;
	it++;
	w.insert(w.begin(), v.begin(), it);
	for (std::vector<int>::iterator i = w.begin() ; i !=w.end() ; i++)
		std::cout << *i << std::endl;
	return 0;
}
*/
