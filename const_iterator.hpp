/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:23:56 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/04 02:43:30 by lgaudet-         ###   ########lyon.fr   */
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

			ConstVectorIter(): _data(NULL) {};
			ConstVectorIter(pointer data): _data(data) {}
			ConstVectorIter(const ConstVectorIter<T> & other): _data(other._data) {}
			ConstVectorIter<T> & operator=(ConstVectorIter<T> & other) {
				ConstVectorIter<T>::_data = other._data;
				return *this;
			}
			~ConstVectorIter<T>() {}

			friend bool operator==(const ConstVectorIter & lhs, const ConstVectorIter & rhs) {return lhs._data == rhs._data; }
			friend bool operator!=(const ConstVectorIter & lhs, const ConstVectorIter & rhs) { return !(lhs==rhs); }
			friend bool operator<(const ConstVectorIter & lhs, const ConstVectorIter & rhs) { return lhs._data < rhs._data; }
			friend bool operator>(const ConstVectorIter & lhs, const ConstVectorIter & rhs) { return lhs._data > rhs._data; }
			friend bool operator<=(const ConstVectorIter & lhs, const ConstVectorIter & rhs) { return lhs._data <= rhs._data; }
			friend bool operator>=(const ConstVectorIter & lhs, const ConstVectorIter & rhs) { return lhs._data >= rhs._data; }
			friend ConstVectorIter operator+(const ConstVectorIter & it, difference_type n) {
				ConstVectorIter<T> iter(*it);
				iter._data += n;
				return iter;
			}
			friend ConstVectorIter operator+(difference_type n, const ConstVectorIter & it) {
				ConstVectorIter<T> iter(*it);
				iter._data += n;
				return iter;
			}
			friend ConstVectorIter operator-(const ConstVectorIter & it, difference_type n) {
				ConstVectorIter<T> iter(*it);
				iter._data -= n;
				return iter;
			}
			friend difference_type operator-(const ConstVectorIter & lhs, const ConstVectorIter & rhs) { return lhs._data - rhs._data; }

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
}
#endif
