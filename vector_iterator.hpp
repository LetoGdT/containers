/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:05:23 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/24 23:05:10 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
# include <memory>
# include "iterator.hpp"

/****************************************
 * Les itérateurs contiennent juste un pointeur sur la _data du vecteur, 
 * aucune vérification n’est faite sur la validité de la donnée pointée.
 * *************************************/

namespace ft{
	template<typename T,
			 typename Distance = std::ptrdiff_t,
			 typename Pointer = T*,
			 typename Reference = T&,
			 typename Category = std::random_access_iterator_tag>
	class VectorIter: public ft::iterator<Category, T, Distance, Pointer, Reference> {
		public:
			typedef Distance difference_type;
			typedef T value_type;
			typedef Pointer pointer;
			typedef Reference reference;
			typedef Category iterator_category;

			VectorIter(): _data(NULL) {};
			VectorIter(pointer data): _data(data) {}
			VectorIter(const VectorIter & other): _data(other._data) {}
			template<class U>
			VectorIter(const VectorIter<U> & other) { _data = other.get_data(); }
			VectorIter & operator=(VectorIter const & other) {
				_data = other._data;
				return *this;
			}
			~VectorIter() {}

			friend VectorIter operator+(difference_type n, const VectorIter & it) {
				VectorIter iter(*it);
				iter._data += n;
				return iter;
			}
			friend VectorIter operator-(const VectorIter & it, difference_type n) {
				VectorIter iter(*it);
				iter._data -= n;
				return iter;
			}

			friend VectorIter operator+(const VectorIter & it, difference_type n) {
				VectorIter iter(*it);
				iter._data += n;
				return iter;
			}

			reference operator*() const { return *_data; }
			pointer operator->() const { return _data; }
			reference operator[](difference_type n) {
				return _data[n];
			}
			const reference operator[](difference_type n) const {
				return _data[n];
			}

			VectorIter & operator++() {
				this->_data++;
				return *this;
			}
			VectorIter operator++(int) { 
				VectorIter iter(_data);
				this->_data++;
				return iter;
			}
			VectorIter & operator--() {
				_data--;
				return *this;
			}
			VectorIter operator--(int) { 
				VectorIter iter(_data);
				this->_data--;
				return iter;
			}
			VectorIter& operator+=(difference_type n) {
				_data += n;
				return *this;
			}
			VectorIter& operator-=(difference_type n) {
				_data -= n;
				return *this;
			}

			pointer get_data() const { return _data; }

		private:
			pointer _data;
	};
	template<typename IteratorL, typename IteratorR>
	bool operator==(const IteratorL & lhs, const IteratorR & rhs) {
		return lhs._data == rhs._data;
	}
	template<typename IteratorL, typename IteratorR>
	bool operator!=(const IteratorL & lhs, const IteratorR & rhs) {
		return !(lhs==rhs);
	}
	template<typename IteratorL, typename IteratorR>
	bool operator<(const IteratorL & lhs, const IteratorR & rhs) {
		return lhs.get_data() < rhs.get_data();
	}
	template<typename IteratorL, typename IteratorR>
	bool operator>(const IteratorL & lhs, const IteratorR & rhs) {
		return rhs._data < lhs._data;
	}
	template<typename IteratorL, typename IteratorR>
	bool operator<=(const IteratorL & lhs, const IteratorR & rhs) {
		return !(rhs._data < lhs._data);
	}
	template<typename IteratorL, typename IteratorR>
	bool operator>=(const IteratorL & lhs, const IteratorR & rhs) {
		return !(lhs._data < rhs._data);
	}

	template<typename IteratorL, typename IteratorR>
	typename IteratorL::difference_type operator-(const IteratorL & lhs, const IteratorR & rhs) {
		return lhs.get_data() - rhs.get_data();
	}
}
#endif
