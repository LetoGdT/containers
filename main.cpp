/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/04 17:37:00 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "is_integral.hpp"
#include <iostream>

int main() {
	if (ft::is_integral<long int>())
		std::cout <<  "pouet1" << std::endl;
	if (std::is_integral<long int>())
		std::cout << "allo" << std::endl;
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
