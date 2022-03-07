/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:23:56 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/07 16:53:19 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "../vector.hpp"
# include "../IteratorTraits.hpp"

/****************************************
 * Les itérateurs contiennent juste un pointeur sur la _data du vecteur, 
 * aucune vérification n’est faite sur la validité de la donnée pointée.
 * *************************************/

namespace ft {
	template<typename T>
	class ReverseVectorIter {
		public:
			typedef typename ft::vector<T>::difference_type difference_type;
			typedef typename ft::vector<T>::value_type value_type;
			typedef typename ft::vector<T>::pointer pointer;
			typedef typename ft::vector<T>::reference reference;
			typedef std::random_access_iterator_tag iterator_category;

			ReverseVectorIter(): _data(NULL) {};
			ReverseVectorIter(pointer data): _data(data) {}
			ReverseVectorIter(const ReverseVectorIter<T> & other): _data(other.data) {}
			ReverseVectorIter<T> & operator=(const ReverseVectorIter<T> & other) {
				_data = other._data;
				return *this;
			}
			~ReverseVectorIter<T>() {}

			friend bool operator==(const ReverseVectorIter & lhs, const ReverseVectorIter & rhs) {return lhs._data == rhs._data; }
			friend bool operator!=(const ReverseVectorIter & lhs, const ReverseVectorIter & rhs) { return !(lhs==rhs); }
			friend bool operator<(const ReverseVectorIter & lhs, const ReverseVectorIter & rhs) { return lhs._data > rhs._data; }
			friend bool operator>(const ReverseVectorIter & lhs, const ReverseVectorIter & rhs) { return lhs._data < rhs._data; }
			friend bool operator<=(const ReverseVectorIter & lhs, const ReverseVectorIter & rhs) { return lhs._data >= rhs._data; }
			friend bool operator>=(const ReverseVectorIter & lhs, const ReverseVectorIter & rhs) { return lhs._data <= rhs._data; }
			friend ReverseVectorIter operator+(const ReverseVectorIter & it, difference_type n) {
				ReverseVectorIter<T> iter(*it);
				iter._data -= n;
				return iter;
			}
			friend ReverseVectorIter operator+(difference_type n, const ReverseVectorIter & it) {
				ReverseVectorIter<T> iter(*it);
				iter._data -= n;
				return iter;
			}
			friend ReverseVectorIter operator-(const ReverseVectorIter & it, difference_type n) {
				ReverseVectorIter<T> iter(*it);
				iter._data += n;
				return iter;
			}
			friend difference_type operator-(const ReverseVectorIter & lhs, const ReverseVectorIter & rhs) { return rhs._data - lhs._data; }

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

			ReverseVectorIter<T> & operator++() {
				this->_data--;
				return *this;
			}
			ReverseVectorIter<T> operator++(int) { 
				VectorIter<T> iter(_data);
				this->_data--;
				return iter;
			}
			ReverseVectorIter<T> & operator--() {
				_data++;
				return *this;
			}
			ReverseVectorIter<T> operator--(int) { 
				VectorIter<T> iter(_data);
				this->_data++;
				return iter;
			}
			ReverseVectorIter<T>& operator+=(difference_type n) {
				_data -= n;
				return *this;
			}
			ReverseVectorIter<T>& operator-=(difference_type n) {
				_data += n;
				return *this;
			}
		private:
			pointer _data;
	};

	//opérateurs +
	template <typename T>
		ReverseVectorIter<T> operator+(const ReverseVectorIter<T>& it, typename ReverseVectorIter<T>::difference_type n) {
			ReverseVectorIter<T> iter(*it);
			iter._data -= n;
			return iter;
		}
	template <typename T>
		ReverseVectorIter<T> operator+(typename ReverseVectorIter<T>::difference_type n, const ReverseVectorIter<T>& it) {
			ReverseVectorIter<T> iter(*it);
			iter._data -= n;
			return iter;
		}
	//opérateurs -
	template <typename T>
		ReverseVectorIter<T> operator-(const ReverseVectorIter<T>& it, typename ReverseVectorIter<T>::difference_type n) {
			ReverseVectorIter<T> iter(*it);
			iter._data += n;
			return iter;
		}
	template <typename T>
		typename ReverseVectorIter<T>::difference_type operator-(const ReverseVectorIter<T>& lhs, const ReverseVectorIter<T>& rhs) {
			return lhs._data - rhs._data;
		}

	//opérateurs de comparaison
	template <typename T> bool operator==(const ReverseVectorIter<T> & lhs, const ReverseVectorIter<T> & rhs) {
		return lhs._data == rhs._data;
	}
	template <typename T> bool operator!=(const ReverseVectorIter<T> & lhs, const ReverseVectorIter<T> & rhs) {
		return !(lhs==rhs);
	}
	template <typename T> 
		bool operator<(const ReverseVectorIter<T> & lhs, ReverseVectorIter<T> & rhs) {
			return lhs._data > rhs._data;
		}
	template <typename T> 
		bool operator>(const ReverseVectorIter<T> & lhs, ReverseVectorIter<T> & rhs) {
			return lhs._data < rhs._data;
		}
	template <typename T> 
		bool operator<=(const ReverseVectorIter<T> & lhs, ReverseVectorIter<T> & rhs) {
			return lhs._data >= rhs._data;
		}
	template <typename T> 
		bool operator>=(const ReverseVectorIter<T> & lhs, ReverseVectorIter<T> & rhs) {
			return lhs._data <= rhs._data;
		}
};

#endif
