/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/26 15:03:21 by lgaudet-         ###   ########.fr       */
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
	NAMESPACE::vector<int> v(50, 42);

	NAMESPACE::vector<int>::iterator i;
	NAMESPACE::vector<int>::const_iterator j;
	i = v.begin();
	j = v.begin();
	i++;
	std::cout << (i < j) << std::endl;
	std::cout << (i > j) << std::endl;
	std::cout << (i == j) << std::endl;

	NAMESPACE::map<int, int> m;
	m.insert(NAMESPACE::make_pair(2, 2));
	NAMESPACE::map<int, int>::iterator k;
	NAMESPACE::map<int, int>::const_iterator l;

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
