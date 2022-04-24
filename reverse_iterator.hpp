/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:13:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/24 16:24:49 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "iterator.hpp"

namespace ft{
	template<class Iter> class reverse_iterator {
		public:
			typedef Iter iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer pointer;
			typedef typename ft::iterator_traits<Iter>::reference reference;

			reverse_iterator() {}
			explicit reverse_iterator (iterator_type it): current(it) {}
			template <class U>
			reverse_iterator (reverse_iterator<U> const & rev_it):current(rev_it.base()) {}

			template<class U>
				reverse_iterator& operator=( const reverse_iterator<U>& other ) {
					current = other.current;
			}

			iterator_type base() const { return iterator_type(current); }

			reference operator*() const { return *current; }
			pointer operator->() const { return current.operator->(); }

			reverse_iterator& operator++() { return --current; }
			reverse_iterator operator++(int) { return current--; }

			reverse_iterator& operator--() { return ++current; }
			reverse_iterator operator--(int) { return current++; }

			reverse_iterator operator+(difference_type n) const {
				return reverse_iterator(current - n);
			}
			reverse_iterator operator-(difference_type n) const {
				return reverse_iterator(current + n);
			}

			reverse_iterator& operator+=(difference_type n) {
				current -= n;
				return *this;
			}
			reverse_iterator& operator-=(difference_type n) {
				current += n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return *(*this + n);
			}

			friend reverse_iterator operator+(typename reverse_iterator::difference_type n, const reverse_iterator& it) {
				return reverse_iterator(it.base() - n);
			}
			friend inline difference_type operator-(const reverse_iterator& lhs, const reverse_iterator& rhs ) {
				return rhs.base() - lhs.base();
			}

		protected:
			Iter current;
	};

	template<typename Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{ return lhs.base() == rhs.base(); }

	template<typename Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, reverse_iterator<Iterator>& rhs)
			{return rhs.base() < lhs.base();}

	template<typename Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return !(lhs == rhs);}

	template<typename Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs)
		{return rhs < lhs;}

	template<typename Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs)
		{return !(rhs < lhs);}

	template<typename Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs)
		{return !(lhs < rhs);}

	template<typename IteratorL, typename IteratorR>
	bool operator==(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
		{return lhs.base() == rhs.base();}

	template<typename IteratorL, typename IteratorR>
	bool operator<(const reverse_iterator<IteratorL>& lhs,const reverse_iterator<IteratorR>& rhs)
		{return rhs.base() < lhs.base();}

	template<typename IteratorL, typename IteratorR>
	bool operator!=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
		{return !(lhs == rhs);}

	template<typename IteratorL, typename IteratorR>
	bool operator>(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
		{return rhs < lhs;}

	template<typename IteratorL, typename IteratorR>
	bool operator<=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
		{return !(rhs < lhs);}

	template<typename IteratorL, typename IteratorR>
	bool operator>=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
		{return !(lhs < rhs);}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
		{return rhs.base() - lhs.base();}

	template<typename IteratorL, typename IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-(const reverse_iterator<IteratorR>& lhs, const reverse_iterator<IteratorR>& rhs)
		{return rhs.base() - lhs.base();}
}

#endif
