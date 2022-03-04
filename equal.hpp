/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:21:31 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/04 16:41:50 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
# define EQUAL_HPP
# include "IteratorTraits.hpp"
# include <iterator>

namespace ft{
	template<
		class InputIt1,
		class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		while (first1 != last1) {
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return true;
	}  
	template<
		class InputIt1, 
		class InputIt2, 
		class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
		while (first1 != last1) {
			if (!p(*first1, *first2))
				return false;
			first1++;
			first2++;
		}
		return true;
	}
};

#endif
