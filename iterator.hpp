/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:05:23 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/01 23:18:59 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include "vector.hpp"
# include "IteratorTraits.hpp"

/****************************************
 * Les itérateurs contiennent juste un pointeur sur la _data du vecteur, 
 * aucune vérification n’est faite sur la validité de la donnée pointée.
 * *************************************/

namespace ft{
	template<typename T>
		class VectorIter {
			public:
				typedef typename ft::vector<T>::difference_type difference_type;
				typedef typename ft::vector<T>::value_type value_type;
				typedef typename ft::vector<T>::pointer pointer;
				typedef typename ft::vector<T>::reference reference;
				typedef std::random_access_iterator_tag iterator_category;

				typedef iterator_traits<VectorIter<T>> iterator_traits;

				VectorIter(): _data(NULL) {};
				VectorIter(pointer data): _data(data) {}
				VectorIter(const VectorIter<T> & other): _data(other._data) {}
				VectorIter<T> & operator=(VectorIter<T> & other) {
					VectorIter<T>::_data = other._data;
					return *this;
				}
				~VectorIter<T>() {}

				friend bool operator==(const VectorIter<T> & lhs, const VectorIter<T> & rhs);
				friend bool operator!=(const VectorIter<T> & lhs, const VectorIter<T> & rhs);
				friend bool operator<(const VectorIter<T> & lhs, const VectorIter<T> & rhs);
				friend bool operator>(const VectorIter<T> & lhs, const VectorIter<T> & rhs);
				friend bool operator<=(const VectorIter<T> & lhs, const VectorIter<T> & rhs);
				friend bool operator>=(const VectorIter<T> & lhs, const VectorIter<T> & rhs);
				friend VectorIter<T> operator+(const VectorIter<T>& it, difference_type n);
				friend VectorIter<T> operator+(difference_type n, const VectorIter<T>& it);
				friend VectorIter<T> operator-(const VectorIter<T>& it, difference_type n);
				friend difference_type operator-(const VectorIter<T>& lhs, const VectorIter<T>& rhs);

				reference operator*() { return *_data; }
				const reference operator*() const { return *_data; }
				pointer operator->() { return _data; }
				const pointer operator->() const { return _data; }
				reference operator[](difference_type n) {
					return _data[n];
				}
				const reference operator[](difference_type n) const {
					return _data[n];
				}

				VectorIter<T> & operator++() {
					this->_data++;
					return *this;
				}
				VectorIter<T> operator++(int) { 
					VectorIter<T> iter(_data);
					this->_data++;
					return iter;
				}
				VectorIter<T> & operator--() {
					_data--;
					return *this;
				}
				VectorIter<T> operator--(int) { 
					VectorIter<T> iter(_data);
					this->_data--;
					return iter;
				}
				VectorIter<T>& operator+=(difference_type n) {
					_data += n;
					return *this;
				}
				VectorIter<T>& operator-=(difference_type n) {
					_data -= n;
					return *this;
				}
			private:
				pointer _data;
		};

	//opérateurs +
	template <typename T>
		VectorIter<T> operator+(const VectorIter<T>& it, typename VectorIter<T>::difference_type n) {
			VectorIter<T> iter(*it);
			iter._data += n;
			return iter;
		}
	template <typename T>
		VectorIter<T> operator+(typename VectorIter<T>::difference_type n, const VectorIter<T>& it) {
			VectorIter<T> iter(*it);
			iter._data += n;
			return iter;
		}
	//opérateurs -
	template <typename T>
		VectorIter<T> operator-(const VectorIter<T>& it, typename VectorIter<T>::difference_type n) {
			VectorIter<T> iter(*it);
			iter._data -= n;
			return iter;
		}
	template <typename T>
		typename VectorIter<T>::difference_type operator-(const VectorIter<T>& lhs, const VectorIter<T>& rhs) {
			return rhs._data - lhs._data;
		}

	//opérateurs de comparaison
	template <typename T> bool operator==(const VectorIter<T> & lhs, const VectorIter<T> & rhs) {
		return lhs._data == rhs._data;
	}
	template <typename T> bool operator!=(const VectorIter<T> & lhs, const VectorIter<T> & rhs) {
		return !(lhs==rhs);
	}
	template <typename T> 
		bool operator<(const VectorIter<T> & lhs, const VectorIter<T> & rhs) {
			return lhs._data < rhs._data;
		}
	template <typename T> 
		bool operator>(const VectorIter<T> & lhs, const VectorIter<T> & rhs) {
			return lhs._data > rhs._data;
		}
	template <typename T> 
		bool operator<=(const VectorIter<T> & lhs, const VectorIter<T> & rhs) {
			return lhs._data <= rhs._data;
		}
	template <typename T> 
		bool operator>=(const VectorIter<T> & lhs, const VectorIter<T> & rhs) {
			return lhs._data >= rhs._data;
		}
};

#endif
