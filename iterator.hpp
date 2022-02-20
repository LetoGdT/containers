/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:05:23 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/02/20 20:13:19 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include "vector.hpp"

namespace ft{
	template<typename T> class VectorIter {
		public:
			typedef typename ft::vector<T>::difference_type difference_type;
			typedef typename ft::vector<T>::value_type value_type;
			typedef typename ft::vector<T>::pointer pointer;
			typedef typename ft::vector<T>::reference reference;
			typedef std::random_access_iterator_tag iterator_category;

			typedef iterator_traits<VectorIter<T>> iterator_traits;

			VectorIter():
				_data(NULL) {};
			VectorIter(typename ft::vector<T>::pointer data):
				_data(data) {}
			VectorIter<T> & operator=(VectorIter<T> & other) {
				VectorIter<T>::_data = other._data;
				return *this;
			}

			bool operator==(VectorIter<T> & other) {
				return this->_data == other._data;
			}
			bool operator!=(VectorIter<T> & other) {
				return !operator==(other);
			}
			reference operator*() {
				return *_data;
			}
			pointer operator->() {
				return _data;
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
			bool operator<(VectorIter<T>& other) {
				return this->_data < other._data;
			}
			bool operator>(VectorIter<T>& other) {
				return this->_data > other._data;
			}
			bool operator<=(VectorIter<T>& other) {
				return this->_data <= other._data;
			}
			bool operator>=(VectorIter<T>& other) {
				return this->_data >= other._data;
			}
			VectorIter<T>& operator+=(difference_type n) {
				_data += n;
				return *this;
			}
			VectorIter<T>& operator-=(difference_type n) {
				_data -= n;
				return *this;
			}
			reference operator[](difference_type n) {
				return _data[n];
			}
		protected:
			typename vector<T>::pointer _data;
	};
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

	template<typename T>
	class ReverseVectorIter: public virtual VectorIter<T> {
		public:
			ReverseVectorIter():
				VectorIter<T>::_data(NULL) {};
			ReverseVectorIter(typename ft::vector<T>::pointer data):
				VectorIter<T>::_data(data) {}
			ReverseVectorIter<T> & operator++() {
				this->_data--;
				return *this;
			}
			ReverseVectorIter<T> operator++(int) { 
				ReverseVectorIter<T> iter(this->_data);
				this->_data--;
				return iter;
			}
	};

	template<typename T>
	class ConstVectorIter: public virtual VectorIter<T> {
		public:
			ConstVectorIter():
				VectorIter<T>::_data(NULL) {};
			ConstVectorIter(typename ft::vector<T>::pointer data):
				VectorIter<T>(data) {}
			typename ft::vector<T>::reference operator*() {
				return const_cast<T>(VectorIter<T>::operator*());
			}
	};

	template<typename T>
	class ConstReverseVectorIter: public ConstVectorIter<T>, public ReverseVectorIter<T> {
		public:
			ConstReverseVectorIter():
				VectorIter<T>::_data(NULL) {};
			ConstReverseVectorIter(typename ft::vector<T>::pointer data):
				ReverseVectorIter<T>(data) {}
			typename ft::vector<T>::reference operator*() {
				return ConstVectorIter<T>::operator*();
			}
			VectorIter<T> & operator++() {
				return ReverseVectorIter<T>::operator++();
			}
			VectorIter<T> operator++(int n) {
				return ReverseVectorIter<T>::operator++(n);
			}
	};
};

#endif
