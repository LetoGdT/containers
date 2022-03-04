/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/04 03:17:01 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"
#include "reverse_iterator.hpp"
#include "const_reverse_iterator.hpp"
#include <iostream>

int main() {
	ft::vector<int> v;

	v.insert(v.begin(), 10);
	v.insert(v.begin(), 9);
	v.insert(v.begin(), 8);
	v.insert(v.begin(), 7);
	v.insert(v.begin(), 6);
	v.insert(v.begin(), 5);
	v.insert(v.begin(), 4);
	v.insert(v.begin(), 3);
	v.insert(v.begin(), 2);
	v.insert(v.begin(), 1);
	v.insert(v.begin(), 0);
	v.insert(v.begin(), 0);
	v.insert(v.begin(), 0);
	v.insert(v.begin(), 0);
	v.insert(v.begin(), 0);
	v.insert(v.begin(), 0);
	v.insert(v.begin(), 0);
	v.insert(v.begin(), 2);
	std::cout << "List:" << std::endl;
	for (ft::vector<int>::iterator i = v.begin() ; i !=v.end() ; i++)
		std::cout << *i << std::endl;
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
