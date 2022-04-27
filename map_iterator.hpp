/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:29:36 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/27 21:51:04 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
# include "iterator.hpp"
# include "AVL_tree.hpp"

namespace ft{
	template<typename T,
			 typename Compare,
			 typename Allocator,
			 typename Distance = std::ptrdiff_t,
			 typename Pointer = T*,
			 typename Reference = T&,
			 typename Category = std::random_access_iterator_tag>
	class MapIter: public ft::iterator<Category, T, Distance, Pointer, Reference>{
		private:
			typedef AVL_tree<T, Compare, Allocator> _tree_type;
			typedef typename _tree_type::Node _Node;

		public:
			typedef Distance difference_type;
			typedef T value_type;
			typedef Pointer pointer;
			typedef Reference reference;
			typedef Category iterator_category;

			MapIter(): _data(NULL), _tree(NULL), _is_end(false) {}
			MapIter(_Node * data, _tree_type * const tree): _data(data),
														    _tree(tree),
														    _is_end(false) {
				if (!data || !tree)
					_is_end = true;
			}
			MapIter(const MapIter & other): _data(other._data),
											_tree(other._tree),
											_is_end(other._is_end) {}
			template<class U, class V, class X>
			MapIter(const MapIter<U, V, X> & other) {
				_data = other.get_data();
				_tree = other.get_tree();
				_is_end = other.get_is_end();
			}
			MapIter & operator=(MapIter const & other) {
				_data = other._data;
				_tree = other._tree;
				_is_end = other._is_end;
				return *this;
			}
			~MapIter() {}

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

			MapIter & operator++() {
				_Node* tmp = _tree->get_successor_iterator(_data);
				if (tmp == NULL)
					_is_end = true;
				else
					_data = tmp;
				return *this;
			}
			MapIter operator++(int) { 
				MapIter iter(_data, _tree);
				_Node* tmp = _tree->get_successor_iterator(_data);
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
				MapIter iter(_data, _tree);
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

			reference operator*() const { return _data->_content; }
			pointer operator->() const { return &(_data->_content); }
			reference operator[](difference_type n) {
				MapIter iter(*this);
				return *(iter + n);
			}
			const reference operator[](difference_type n) const {
				MapIter iter(*this);
				return *(iter + n);
			}

			_Node * get_data() const { return _data; }
			_tree_type * get_tree() const { return _tree; }
			bool get_is_end() const { return _is_end; }

		private:
			_Node*		_data;
			_tree_type*	_tree;
			bool		_is_end;
	};

	template<typename A,
			 typename B,
			 typename C,
			 typename D,
			 typename X1,
			 typename X2,
			 typename Y1,
			 typename Y2>
	bool operator==(const MapIter<A, B, C, D, X1, Y1> & lhs, const MapIter<A, B, C, D, X2, Y2> & rhs) {
		return lhs.get_data()->_content.first == rhs.get_data()->_content.first &&
				lhs.get_is_end() == rhs.get_is_end();
	}
	template<typename A,
			 typename B,
			 typename C,
			 typename D,
			 typename X1,
			 typename X2,
			 typename Y1,
			 typename Y2>
	bool operator!=(const MapIter<A, B, C, D, X1, Y1> & lhs, const MapIter<A, B, C, D, X2, Y2> & rhs) {
		return !(lhs==rhs);
	}
	template<typename A,
			 typename B,
			 typename C,
			 typename D,
			 typename X1,
			 typename X2,
			 typename Y1,
			 typename Y2>
	bool operator<(const MapIter<A, B, C, D, X1, Y1> & lhs, const MapIter<A, B, C, D, X2, Y2> & rhs) {
		return lhs.get_tree()->compare_nodes(lhs.get_data(), rhs.get_data()) ||
				(lhs.get_is_end() == false && rhs.get_is_end() == true);
	}
	template<typename A,
			 typename B,
			 typename C,
			 typename D,
			 typename X1,
			 typename X2,
			 typename Y1,
			 typename Y2>
	bool operator>(const MapIter<A, B, C, D, X1, Y1> & lhs, const MapIter<A, B, C, D, X2, Y2> & rhs) {
		return rhs < lhs;
	}
	template<typename A,
			 typename B,
			 typename C,
			 typename D,
			 typename X1,
			 typename X2,
			 typename Y1,
			 typename Y2>
	bool operator<=(const MapIter<A, B, C, D, X1, Y1> & lhs, const MapIter<A, B, C, D, X2, Y2> & rhs) {
		return !(rhs < lhs);
	}
	template<typename A,
			 typename B,
			 typename C,
			 typename D,
			 typename X1,
			 typename X2,
			 typename Y1,
			 typename Y2>
	bool operator>=(const MapIter<A, B, C, D, X1, Y1> & lhs, const MapIter<A, B, C, D, X2, Y2> & rhs) {
		return !(lhs < rhs);
	}
	
	template<typename A,
			 typename B,
			 typename C,
			 typename D,
			 typename X1,
			 typename X2,
			 typename Y1,
			 typename Y2>
	D operator-(const MapIter<A, B, C, D, X1, Y1> & lhs, const MapIter<A, B, C, D, X2, Y2> & rhs) {
		typename MapIter<A, B, C, D, X1, Y1>::difference_type res;
		MapIter<A, B, C, D, X2, Y2> it(rhs);
		for (res = 0 ; it != lhs && it._is_end == false ; it++)
			res++;
		return res;
	}
}

#endif
