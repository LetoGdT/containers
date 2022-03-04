/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:56:45 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/04 17:32:02 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP
# include <limits>

namespace ft{
	template <typename T>
	struct is_integral {
		public:
			static const bool value = std::numeric_limits<T>::is_integer;
			operator bool() const { return value; }
			typedef bool value_type;
			typedef std::integral_constant<bool, value> type;
	};
}

#endif
