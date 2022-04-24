/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:30:26 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/24 21:00:51 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <iterator>

namespace ft {
	template <class Category,
			  class T,
			  class Distance = std::ptrdiff_t,
			  class Pointer = T*,
			  class Reference = T&>
	class iterator {
		public:
			typedef T value_type;
			typedef Category iterator_category;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
	};

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
