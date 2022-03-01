/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:23:56 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/01 23:11:52 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_ITERATOR_HPP
# define CONST_ITERATOR_HPP
# include "vector.hpp"
# include "IteratorTraits.hpp"

/****************************************
 * Les itérateurs contiennent juste un pointeur sur la _data du vecteur, 
 * aucune vérification n’est faite sur la validité de la donnée pointée.
 * *************************************/

namespace ft{
	template<typename T>
		class ConstVectorIter {
			public:
				typedef typename ft::vector<T>::difference_type difference_type;
				typedef typename ft::vector<T>::value_type value_type;
				typedef typename ft::vector<T>::pointer pointer;
				typedef typename ft::vector<T>::reference reference;
				typedef std::random_access_iterator_tag iterator_category;

				typedef iterator_traits<ConstVectorIter<T>> iterator_traits;

				ConstVectorIter(): _data(NULL) {};
				ConstVectorIter(pointer data): _data(data) {}
				ConstVectorIter(const ConstVectorIter<T> & other): _data(other._data) {}
				ConstVectorIter<T> & operator=(ConstVectorIter<T> & other) {
					ConstVectorIter<T>::_data = other._data;
					return *this;
				}
				~ConstVectorIter<T>() {}

				friend bool operator==(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs);
				friend bool operator!=(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs);
				friend bool operator<(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs);
				friend bool operator>(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs);
				friend bool operator<=(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs);
				friend bool operator>=(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs);
				friend ConstVectorIter<T> operator+(const ConstVectorIter<T>& it, difference_type n);
				friend ConstVectorIter<T> operator+(difference_type n, const ConstVectorIter<T>& it);
				friend ConstVectorIter<T> operator-(const ConstVectorIter<T>& it, difference_type n);
				friend difference_type operator-(const ConstVectorIter<T>& lhs, const ConstVectorIter<T>& rhs);

				const reference operator*() const { return const_cast<const value_type>(*_data); }
				const pointer operator->() const { return _data; }
				const reference operator[](difference_type n) const {
					return _data[n];
				}

				ConstVectorIter<T> & operator++() {
					this->_data++;
					return *this;
				}
				ConstVectorIter<T> operator++(int) { 
					ConstVectorIter<T> iter(_data);
					this->_data++;
					return iter;
				}
				ConstVectorIter<T> & operator--() {
					_data--;
					return *this;
				}
				ConstVectorIter<T> operator--(int) { 
					ConstVectorIter<T> iter(_data);
					this->_data--;
					return iter;
				}
				ConstVectorIter<T>& operator+=(difference_type n) {
					_data += n;
					return *this;
				}
				ConstVectorIter<T>& operator-=(difference_type n) {
					_data -= n;
					return *this;
				}
			private:
				pointer _data;
		};

	//opérateurs +
	template <typename T>
		ConstVectorIter<T> operator+(const ConstVectorIter<T>& it, typename ConstVectorIter<T>::difference_type n) {
			ConstVectorIter<T> iter(*it);
			iter._data += n;
			return iter;
		}
	template <typename T>
		ConstVectorIter<T> operator+(typename ConstVectorIter<T>::difference_type n, const ConstVectorIter<T>& it) {
			ConstVectorIter<T> iter(*it);
			iter._data += n;
			return iter;
		}
	//opérateurs -
	template <typename T>
		ConstVectorIter<T> operator-(const ConstVectorIter<T>& it, typename ConstVectorIter<T>::difference_type n) {
			ConstVectorIter<T> iter(*it);
			iter._data -= n;
			return iter;
		}
	template <typename T>
		typename ConstVectorIter<T>::difference_type operator-(const ConstVectorIter<T>& lhs, const ConstVectorIter<T>& rhs) {
			return rhs._data - lhs._data;
		}

	//opérateurs de comparaison
	template <typename T> bool operator==(const ConstVectorIter<T> & lhs, const ConstVectorIter<T> & rhs) {
		return lhs._data == rhs._data;
	}
	template <typename T> bool operator!=(const ConstVectorIter<T> & lhs, const ConstVectorIter<T> & rhs) {
		return !(lhs==rhs);
	}
	template <typename T> 
		bool operator<(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs) {
			return lhs._data < rhs._data;
		}
	template <typename T> 
		bool operator>(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs) {
			return lhs._data > rhs._data;
		}
	template <typename T> 
		bool operator<=(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs) {
			return lhs._data <= rhs._data;
		}
	template <typename T> 
		bool operator>=(const ConstVectorIter<T> & lhs, ConstVectorIter<T> & rhs) {
			return lhs._data >= rhs._data;
		}
};

#endif
