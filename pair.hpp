/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:02:20 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/04 16:25:48 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft{
	template <
		class T1,
		class T2>
	class pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() {
			first = T1();
			second = T2();
		}
		pair( const T1& x, const T2& y ) {
			first = x;
			second = y;
		}
		template<
			class U1, 
			class U2>
		pair( const pair<U1, U2>& p ) {
			first = p.first;
			second = p.second;
		}
		pair& operator=(pair const & other) {
			first = other.first;
			second = other.second;
		}
		~pair();

		friend pair make_pair(T1 t, T2 u);
		friend bool operator==(pair const & lhs, pair const & rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }
		friend bool operator!=(pair const & lhs, pair const & rhs) { return !(lhs == rhs); }
		friend bool operator<(pair const & lhs, pair const & rhs) { return lhs.first < rhs.first && lhs.second < rhs.second; }
		friend bool operator>(pair const & lhs, pair const & rhs) { return lhs.first > rhs.first && lhs.second > rhs.second; }
		friend bool operator<=(pair const & lhs, pair const & rhs) { return lhs.first <= rhs.first && lhs.second <= rhs.second; }
		friend bool operator>=(pair const & lhs, pair const & rhs) { return lhs.first >= rhs.first && lhs.second >= rhs.second; }
	};
}

#endif
