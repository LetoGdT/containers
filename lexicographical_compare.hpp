/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:46:48 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/08 19:07:16 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft {
	template<
		class InputIt1,
		class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 != *first2)
				return *first1 < *first2;
			first1++;
			first2++;
		}
		return first2 != last2;
	}

	template<
		class InputIt1,
		class InputIt2,
		class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2,
								 Compare comp) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 != *first2)
				return comp(*first1, *first2);
			first1++;
			first2++;
		}
		return first2 != last2;
	}
}

#endif
