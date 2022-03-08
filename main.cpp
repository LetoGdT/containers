/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/08 19:09:17 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "is_integral.hpp"
#include "pair.hpp"
#include <iostream>

int main() {
	ft::vector<int> v;
	ft::vector<int> w;

	for (int i = 0 ; i < 5 ; i++)
		v.push_back(i);
	for (int i = 0 ; i < 10 ; i++)
		w.push_back(i);

	for (auto it = v.begin() ; it != v.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	for (auto it = w.begin() ; it != w.end() ; it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	std::cout << ((v == w)?"true":"false") << std::endl;
	v.push_back(12);
	std::cout << ((v > w)?"true":"false") << std::endl;
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
