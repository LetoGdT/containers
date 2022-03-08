/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/08 20:40:28 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "is_integral.hpp"
#include "pair.hpp"
#include <iostream>

int main() {
	ft::vector<int> v;

	for (int i = 0 ; i < 20 ; i++)
		v.push_back(i);

	ft::vector<int> w;
	for (auto i = 0 ; i < 5 ; i++)
		w.push_back(i + 40);

	for (auto it = v.begin() ; it != v.end() ; it++)
		std::cout << *it << std::endl;

	v.assign(w.begin(), w.end());

	std::cout << std::endl;
	for (auto it = v.begin() ; it != v.end() ; it++)
		std::cout << *it << std::endl;

	std::cout << std::endl;
	std::cout << v.capacity() << std::endl;
	std::cout << v.size() << std::endl;

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
