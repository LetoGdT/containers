/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:40:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/02/20 19:56:58 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

int main() {
	std::allocator<std::string> alloc;
	std::string *data = alloc.allocate(10);
	for (int i = 0 ; i < 10 ; i++)
		alloc.construct(data + i, "allo" + std::to_string(i));

	std::string *tmp = alloc.allocate(20);

	memmove(tmp, data, 10 * sizeof(std::string));
	alloc.deallocate(data, 10);
	for (int i = 0 ; i < 10 ; i++) {
		std::cout << tmp[i] << std::endl;
		alloc.destroy(tmp + i);
	}
	alloc.deallocate(tmp, 20);
}
