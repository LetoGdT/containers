/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_reverse_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:48:42 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/01 23:14:07 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_REVERSE_ITERATOR_HPP
# define CONST_REVERSE_ITERATOR_HPP
# include "vector.hpp"
# include "IteratorTraits.hpp"

/****************************************
 * Les itérateurs contiennent juste un pointeur sur la _data du vecteur, 
 * aucune vérification n’est faite sur la validité de la donnée pointée.
 * *************************************/

namespace ft {
	template<typename T>
		class ConstReverseVectorIter {
			public:
				typedef typename ft::vector<T>::difference_type difference_type;
				typedef typename ft::vector<T>::value_type value_type;
				typedef typename ft::vector<T>::pointer pointer;
				typedef typename ft::vector<T>::reference reference;
				typedef std::random_access_iterator_tag iterator_category;

				typedef iterator_traits<ConstReverseVectorIter<T>> iterator_traits;

				ConstReverseVectorIter(): _data(NULL) {};
				ConstReverseVectorIter(pointer data): _data(data) {}
				ConstReverseVectorIter(const ConstReverseVectorIter<T> & other): _data(other.data) {}
				ConstReverseVectorIter<T> & operator=(const ConstReverseVectorIter<T> & other) {
					_data = other._data;
					return *this;
				}
				~ConstReverseVectorIter<T>() {}

				friend bool operator==(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs);
				friend bool operator!=(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs);
				friend bool operator<(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs);
				friend bool operator>(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs);
				friend bool operator<=(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs);
				friend bool operator>=(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs);
				friend ConstReverseVectorIter<T> operator+(const ConstReverseVectorIter<T>& it, difference_type n);
				friend ConstReverseVectorIter<T> operator+(difference_type n, const ConstReverseVectorIter<T>& it);
				friend ConstReverseVectorIter<T> operator-(const ConstReverseVectorIter<T>& it, difference_type n);
				friend difference_type operator-(const ConstReverseVectorIter<T>& lhs, const ConstReverseVectorIter<T>& rhs);

				const reference operator*() const { return *_data; }
				const pointer operator->() const { return _data; }
				const reference operator[](difference_type n) const {
					return _data[n];
				}

				ConstReverseVectorIter<T> & operator++() {
					this->_data--;
					return *this;
				}
				ConstReverseVectorIter<T> operator++(int) { 
					VectorIter<T> iter(_data);
					this->_data--;
					return iter;
				}
				ConstReverseVectorIter<T> & operator--() {
					_data++;
					return *this;
				}
				ConstReverseVectorIter<T> operator--(int) { 
					VectorIter<T> iter(_data);
					this->_data++;
					return iter;
				}
				ConstReverseVectorIter<T>& operator+=(difference_type n) {
					_data -= n;
					return *this;
				}
				ConstReverseVectorIter<T>& operator-=(difference_type n) {
					_data += n;
					return *this;
				}
			private:
				pointer _data;
		};

	//opérateurs +
	template <typename T>
		ConstReverseVectorIter<T> operator+(const ConstReverseVectorIter<T>& it, typename ConstReverseVectorIter<T>::difference_type n) {
			ConstReverseVectorIter<T> iter(*it);
			iter._data -= n;
			return iter;
		}
	template <typename T>
		ConstReverseVectorIter<T> operator+(typename ConstReverseVectorIter<T>::difference_type n, const ConstReverseVectorIter<T>& it) {
			ConstReverseVectorIter<T> iter(*it);
			iter._data -= n;
			return iter;
		}
	//opérateurs -
	template <typename T>
		ConstReverseVectorIter<T> operator-(const ConstReverseVectorIter<T>& it, typename ConstReverseVectorIter<T>::difference_type n) {
			ConstReverseVectorIter<T> iter(*it);
			iter._data += n;
			return iter;
		}
	template <typename T>
		typename ConstReverseVectorIter<T>::difference_type operator-(const ConstReverseVectorIter<T>& lhs, const ConstReverseVectorIter<T>& rhs) {
			return lhs._data - rhs._data;
		}

	//opérateurs de comparaison
	template <typename T> bool operator==(const ConstReverseVectorIter<T> & lhs, const ConstReverseVectorIter<T> & rhs) {
		return lhs._data == rhs._data;
	}
	template <typename T> bool operator!=(const ConstReverseVectorIter<T> & lhs, const ConstReverseVectorIter<T> & rhs) {
		return !(lhs==rhs);
	}
	template <typename T> 
		bool operator<(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs) {
			return lhs._data > rhs._data;
		}
	template <typename T> 
		bool operator>(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs) {
			return lhs._data < rhs._data;
		}
	template <typename T> 
		bool operator<=(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs) {
			return lhs._data >= rhs._data;
		}
	template <typename T> 
		bool operator>=(const ConstReverseVectorIter<T> & lhs, ConstReverseVectorIter<T> & rhs) {
			return lhs._data <= rhs._data;
		}
};

#endif
