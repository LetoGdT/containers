/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/24 18:20:54 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "pair.hpp"
#include <iostream>

int main() {
	ft::vector<int> v(50, 42);

	for (ft::vector<int>::iterator it = v.begin() ; it != v.end() ; it++)
		std::cout << *it << std::endl;
	return 0;
}

/*
#include <map>
#include <iostream>
#include <string>
#include <string_view>

int main() {
	std::map<int, const char *> m;
	m.insert(std::make_pair(0, "zero"));
	m.insert(std::make_pair(1, "one"));
	m.insert(std::make_pair(3, "two"));

	std::cout << m.lower_bound(2)->second << std::endl;
	std::cout << m.upper_bound(2)->second << std::endl;
	return 0;
}
*/
