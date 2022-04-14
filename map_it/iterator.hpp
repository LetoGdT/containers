/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:29:36 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/13 15:03:49 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
# include "../IteratorTraits.hpp"
# include "../map.hpp"

namespace ft{
	template<typename T, 
			 typename Key,
			 typename Compare,
			 typename Allocator>
	class MapIter {
		private:
			typedef AVL_tree<Key, T, Compare, Allocator> _tree_type;
			typedef typename ft::map<Key, T, Compare, Allocator> _map_type;
			typedef typename _tree_type::Node _Node;

		public:
			typedef typename _map_type::difference_type difference_type;
			typedef typename _map_type::value_type value_type;
			typedef typename _map_type::pointer pointer;
			typedef typename _map_type::reference reference;
			typedef std::random_access_iterator_tag iterator_category;

			MapIter(): MapIter(NULL, NULL) {}
			MapIter(pointer const data, _tree_type * const tree): _data(data),
																  _is_end(false),
																  _tree(tree) {}
			MapIter(const MapIter & other): _data(other._data),
											_is_end(other._is_end),
											_tree(other._tree) {}
			MapIter & operator=(MapIter const & other) {
				_data = other._data;
				_is_end = other._is_end;
				return *this;
			}
			~MapIter() {}

			friend bool operator==(const MapIter & lhs, const MapIter & rhs) {return lhs._data.first == rhs._data.first; }
			friend bool operator!=(const MapIter & lhs, const MapIter & rhs) { return !(lhs==rhs); }
			friend bool operator<(const MapIter & lhs, const MapIter & rhs) { return lhs._tree->compare_nodes(lhs._data, rhs._data); }
			friend bool operator>(const MapIter & lhs, const MapIter & rhs) { return (lhs >= rhs) && (lhs != rhs); }
			friend bool operator<=(const MapIter & lhs, const MapIter & rhs) { return lhs < rhs || lhs == rhs; }
			friend bool operator>=(const MapIter & lhs, const MapIter & rhs) { return !(lhs < rhs); }

			friend MapIter operator+(const MapIter & it, difference_type n) {
				MapIter iter(it);
				return iter += n;
			}
			friend MapIter operator+(difference_type n, const MapIter & it) {
				MapIter iter(it);
				return iter += n;
			}
			friend MapIter operator-(const MapIter & it, difference_type n) {
				MapIter iter(it);
				return iter -= n;
			}
			friend difference_type operator-(const MapIter & lhs, const MapIter & rhs) {
				difference_type res;
				MapIter it(rhs);
				for (res = 0 ; it != lhs && it._is_end == false ; it++)
					res++;
				return res;
			}

			MapIter & operator++() {
				_Node* tmp = _tree->get_successor_iterator(_data);
				if (tmp == NULL)
					_is_end = true;
				else
					_data = tmp;
				return *this;
			}
			MapIter operator++(int) { 
				MapIter iter(_data);
				_Node* tmp = get_successor_iterator(_data);
				if (tmp == NULL)
					_is_end = true;
				else
					_data = tmp;
				return iter;
			}
			MapIter & operator--() {
				_Node* tmp = _tree->get_predecessor_iterator(_data);
				if (tmp != NULL) {
					_is_end = false;
					_data = tmp;
				}
				return *this;
			}
			MapIter operator--(int) { 
				MapIter iter(_data);
				_Node* tmp = _tree->get_predecessor_iterator(_data);
				if (tmp != NULL) {
					_is_end = false;
					_data = tmp;
				}
				return iter;
			}
			MapIter& operator+=(difference_type n) {
				if (n < 0)
					for (difference_type i = 0 ; i > n ; i--)
						(*this)--;
				else
					for (difference_type i = 0; i < n ; i++)
						(*this)++;
				return *this;
			}
			MapIter& operator-=(difference_type n) {
				return (*this) += -n;
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
				MapIter iter(*this);
				return *(iter + n);
			}

		private:
			_Node*		_data;
			_tree_type*	_tree;
			bool		_is_end;
	};
}

#endif
