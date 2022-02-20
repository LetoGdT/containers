/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorTraits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:49:50 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/02/20 18:24:40 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORTRAITS_HPP
# define ITERATORTRAITS_HPP
# include <iterator>

namespace ft {
	template <class Iter>
		struct iterator_traits {
			typedef typename Iter::value_type value_type;
			typedef typename Iter::difference_type difference_type;
			typedef typename Iter::iterator_category iterator_category;
			typedef typename Iter::pointer pointer;
			typedef typename Iter::reference reference;
		};

	template <typename T>
		struct iterator_traits<T*> {
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef T* pointer;
			typedef T& reference;
		};

	template <typename T>
		struct iterator_traits<const T*> {
			typedef const T value_type;
			typedef ptrdiff_t difference_type;
			typedef std::random_access_iterator_tag iterator_category;
			typedef const T* pointer;
			typedef const T& reference;
		};
}

#endif
