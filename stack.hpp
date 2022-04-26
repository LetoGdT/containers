/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:58:54 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/26 14:21:25 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <deque>

namespace ft {
	template <class T, class Container = std::deque<T> >
	class stack {
		public:
			typedef Container container_type;
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef typename Container::reference reference;
			typedef typename Container::const_reference const_reference;

			stack(): c(Container()) {}
			explicit stack(Container const & cont = Container()): c(cont) {}
			stack(stack const & other) {
				c = other;
			}
			stack& operator=(stack const & other) {
				c = other;
			}
			~stack() {}

			reference top() { return c.back(); }
			const_reference top() const { return c.back(); }

			bool empty() const { return c.empty(); }
			size_type size() const { return c.size(); }

			void push(value_type const & value) {
				c.push_back(value);
			}
			void pop() { c.pop_back(); }


			friend bool operator==(stack const & lhs,
									stack const & rhs) {
				return lhs.c == rhs.c;
			}
			friend bool operator!=(stack const & lhs, stack const & rhs) {
				return lhs.c != rhs.c;
			}
			friend bool operator<(stack const & lhs, stack const & rhs) {
				return lhs.c < rhs.c;
			}
			friend bool operator<=(stack const & lhs, stack const & rhs) {
				return lhs.c <= rhs.c;;
			}
			friend bool operator>(stack const & lhs, stack const & rhs) {
				return lhs.c > rhs.c;
			}
			friend bool operator>=(stack const & lhs, stack const & rhs) {
				return lhs.c >= rhs.c;
			}

		private:
			Container c;
	};
}

#endif
