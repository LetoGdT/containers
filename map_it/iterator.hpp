/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:29:36 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/11 17:57:47 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
# include "../IteratorTraits.hpp"
# include "../map.hpp"

namespace ft{
	template<typename T, 
			 typename Key,
			 typename tree_type>
	class MapIter {
		private:
			typedef typename AVL_tree<Key,
					 		  T,
							  typename ft::map<Key, T>::Compare,
							  typename ft::map<Key, T>::Allocator>::Node _Node;

		public:
			typedef typename ft::map<T, Key>::difference_type difference_type;
			typedef typename ft::map<T, Key>::value_type value_type;
			typedef typename ft::map<T, Key>::pointer pointer;
			typedef typename ft::map<T, Key>::reference reference;
			typedef std::random_access_iterator_tag iterator_category;

			MapIter(): _data(NULL), _is_end(false) {}
			MapIter(pointer data): _data(data), _is_end(false) {}
			MapIter(const MapIter & other): _data(other._data), _is_end(other._is_end) {}
			MapIter & operator=(MapIter const & other) {
				_data = other._data;
				_is_end = other._is_end;
				return *this;
			}
			~MapIter() {}

			friend bool operator==(const MapIter & lhs, const MapIter & rhs) {return !(lhs < rhs || lhs > rhs); }
			friend bool operator!=(const MapIter & lhs, const MapIter & rhs) { return !(lhs==rhs); }
			friend bool operator<(const MapIter & lhs, const MapIter & rhs) { return lhs._data < rhs._data; }
			friend bool operator>(const MapIter & lhs, const MapIter & rhs) { return lhs._data > rhs._data; }
			friend bool operator<=(const MapIter & lhs, const MapIter & rhs) { return lhs._data <= rhs._data; }
			friend bool operator>=(const MapIter & lhs, const MapIter & rhs) { return lhs._data >= rhs._data; }
			friend MapIter operator+(const MapIter & it, difference_type n) {
				MapIter iter(it);
				for (int i = 0 ; i < n ; i++)
					iter++;
				return iter;
			}
			friend MapIter operator+(difference_type n, const MapIter & it) {
				MapIter iter(it);
				for (int i = 0 ; i < n ; i++)
					iter++;
				return iter;
			}
			friend MapIter operator-(const MapIter & it, difference_type n) {
				MapIter iter(it);
				for (int i = 0 ; i < n ; i++)
					iter--;
				return iter;
			}
			friend difference_type operator-(const MapIter & lhs, const MapIter & rhs) {
				difference_type res;
				MapIter it(rhs);
				for (res = 0 ; it != lhs && it._is_end == false ; it++)
					res++;
				return res;
			}

			reference operator*() { return _data->content; }
			const reference operator*() const { return _data->content; }
			pointer operator->() { return &(_data->content); }
			const pointer operator->() const { return &(_data->content); }
			reference operator[](difference_type n) {
				MapIter iter(*this);
				return *(iter + n);
			}
			const reference operator[](difference_type n) const {
				return _data[n];
			}

			MapIter & operator++() {
				_Node* tmp = get_successor_iterator(_data);
				if (tmp == NULL)
					_is_end = true;
				else
					_data = get_successor_iterator(_data);
				return *this;
			}
			MapIter operator++(int) { 
				MapIter iter(_data);
				_Node* tmp = get_successor_iterator(_data);
				if (tmp == NULL)
					_is_end = true;
				else
					_data = get_successor_iterator(_data);
				return iter;
			}
			MapIter & operator--() {
				_Node* tmp = get_predecessor_iterator(_data);
				if (tmp != NULL) {
					_is_end = false;
					_data = get_predecessor_iterator(_data);
				}
				return *this;
			}
			MapIter operator--(int) { 
				MapIter iter(_data);
				_Node* tmp = get_predecessor_iterator(_data);
				if (tmp != NULL) {
					_is_end = false;
					_data = get_predecessor_iterator(_data);
				}
				return iter;
			}
			MapIter& operator+=(difference_type n) {
				_data += n;
				return *this;
			}
			MapIter& operator-=(difference_type n) {
				_data -= n;
				return *this;
			}

		private:
			_Node*	_data;
			tree_type _tree;
			bool	_is_end;
	};
}

#endif
