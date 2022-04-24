/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:05:23 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/24 17:49:53 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include "vector.hpp"

/****************************************
 * Les itérateurs contiennent juste un pointeur sur la _data du vecteur, 
 * aucune vérification n’est faite sur la validité de la donnée pointée.
 * *************************************/

namespace ft{
	template<typename T,
			 typename Pointer,
			 typename Reference,
			 typename Category>
	class VectorIter: iterator<Category, T> {
		public:
			typedef typename ft::vector<T>::difference_type difference_type;
			typedef typename ft::vector<T>::value_type value_type;
			typedef typename ft::vector<T>::pointer pointer;
			typedef typename ft::vector<T>::reference reference;
			typedef std::random_access_iterator_tag iterator_category;

			VectorIter(): _data(NULL) {};
			VectorIter(pointer data): _data(data) {}
			VectorIter(const VectorIter & other): _data(other._data) {}
			template<class U>
			VectorIter(const VectorIter<U> & other): _data(other._data) {}
			VectorIter & operator=(VectorIter const & other) {
				VectorIter::_data = other._data;
				return *this;
			}
			~VectorIter() {}

			friend bool operator==(const VectorIter & lhs, const VectorIter & rhs) {return lhs._data == rhs._data; }
			friend bool operator!=(const VectorIter & lhs, const VectorIter & rhs) { return !(lhs==rhs); }
			friend bool operator<(const VectorIter & lhs, const VectorIter & rhs) { return lhs._data < rhs._data; }
			friend bool operator>(const VectorIter & lhs, const VectorIter & rhs) { return lhs._data > rhs._data; }
			friend bool operator<=(const VectorIter & lhs, const VectorIter & rhs) { return lhs._data <= rhs._data; }
			friend bool operator>=(const VectorIter & lhs, const VectorIter & rhs) { return lhs._data >= rhs._data; }
			friend VectorIter operator+(const VectorIter & it, difference_type n) {
				VectorIter iter(*it);
				iter._data += n;
				return iter;
			}
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
			friend difference_type operator-(const VectorIter & lhs, const VectorIter & rhs) { return lhs._data - rhs._data; }

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
		private:
			pointer _data;
	};
}
#endif
