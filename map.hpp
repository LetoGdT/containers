/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:04:09 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/13 23:10:30 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <limits>
# include <exception>
# include "AVL_tree.hpp"

namespace ft {
	template<typename Key,
			 typename T,
			 typename Compare,
			 typename Allocator>
	class MapIter;
	template<typename Key,
			 typename T,
			 typename Compare,
			 typename Allocator>
	class ConstMapIter;
	template<typename Key,
			 typename T,
			 typename Compare,
			 typename Allocator>
	class ReverseMapIter;
	template<typename Key,
			 typename T,
			 typename Compare,
			 typename Allocator>
	class ConstReverseMapIter;

	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T>>>
	class map {
		private:
			typedef AVL_tree<Key, T, Compare, Allocator> _tree_type;
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef MapIter<Key, T, Compare, Allocator> iterator;
			typedef ConstMapIter<Key, T, Compare, Allocator> const_iterator;
			typedef ReverseMapIter<Key, T, Compare, Allocator> reverse_iterator;
			typedef ConstReverseMapIter<Key, T, Compare, Allocator> const_reverse_iterator;

			map(): map(Compare(), Allocator()) {}
			explicit map(Compare const & comp, const Allocator& alloc = Allocator()) {
				_tree = _tree_type(comp, alloc);
			}
			template<class InputIt>
				map(InputIt first, InputIt last,
					const Compare& comp = Compare(),
					const Allocator& alloc = Allocator()): map(comp, alloc) {
				for (InputIt i = first ; i != last ; i++)
					_tree.insert(*i);
			}
			map(const map& other): _tree(other._tree) {}
			map& operator=(map const & other) {
				_tree = other.tree;
			}
			~map();

		//element access
			mapped_type & at(const key_type& key) {
				typename _tree_type::Node * tmp = _tree.find(key);
				if (tmp == NULL)
					throw std::out_of_range("ft::map: value not found");
				return tmp->_content->second;
			}
			const mapped_type & at(const key_type& key) const {
				typename _tree_type::Node * tmp = _tree.find(key);
				if (tmp == NULL)
					throw std::out_of_range("ft::map: value not found");
				return tmp->second;
			}
			mapped_type & operator[](const key_type& key) {
				typename _tree_type::Node * tmp = _tree.find(key);
				if (tmp == NULL)
					return _tree.insert(make_pair<key_type, mapped_type>(key, mapped_type()))->_content.second;
				return tmp->_content->second;
			}

		//iterators
			iterator begin() {
				typename _tree_type::Node * node = _tree.get_leftmost();
				iterator it(node, &_tree);
				return it;
			}
			iterator end() {
				typename _tree_type::Node * node = _tree.get_rightmost();
				iterator it(node, &_tree);
				++it;
				return it;
			}
			const_iterator begin() const {
				typename _tree_type::Node * node = _tree.get_leftmost();
				const_iterator it(node, &_tree);
				return it;
			}
			const_iterator end() const {
				typename _tree_type::Node * node = _tree.get_rightmost();
				const_iterator it(node, &_tree);
				++it;
				return it;
			}
			reverse_iterator rbegin() {
				typename _tree_type::Node * node = _tree.get_rightmost();
				reverse_iterator it(node, &_tree);
				return it;
			}
			reverse_iterator rend() {
				typename _tree_type::Node * node = _tree.get_leftmost();
				reverse_iterator it(node, &_tree);
				++it;
				return it;
			}
			const_reverse_iterator rbegin() const {
				typename _tree_type::Node * node = _tree.get_rightmost();
				const_reverse_iterator it(node, &_tree);
				return it;
			}
			const_reverse_iterator rend() const {
				typename _tree_type::Node * node = _tree.get_leftmost();
				const_reverse_iterator it(node, &_tree);
				++it;
				return it;
			}

		//capacity
			bool empty() const { return _tree.get_size() == 0; }
			size_type size() const { return _tree.get_size(); }
			size_type max_size() const { return std::numeric_limits<size_type>::max(); }

		//modifiers
			void clear() {
				_tree.clear();
			}

			std::pair<iterator, bool> insert(const value_type& value) {
				typename _tree_type::Node* node = insert(value);
				iterator iter(node, &_tree);
				return make_pair<iterator, bool>(iter, node != NULL);
			}
			iterator insert(iterator hint, const value_type& value) {
				return insert(value).first;
			}
			template< class InputIt >
			void insert(InputIt first, InputIt last) {
				for (InputIt it = first ; it != last ; ++it)
					insert(*it);
			}

			void erase(iterator pos) {
				_tree.erase((*pos).first);
			}
			void erase(iterator first, iterator last) {
				for (iterator it = first ; it != last ; ++it)
					_tree.erase((*it).first);
			}
			size_type erase(const Key& key) {
				size_type old_size = _tree.get_size();
				_tree.erase(key);
				return old_size != _tree.get_size();
			}
			void swap(map& other) {
				_tree.swap(other._tree);
			}

		//lookup
			size_type count(const Key& key) const {
				return (_tree.find(key) != NULL) ? 1 : 0;
			}
			iterator find(const Key& key) {
				iterator it(_tree.find(key), _tree);
				return it;
			}
			const_iterator find(const Key& key) const {
				const_iterator it(_tree.find(key), _tree);
				return it;
			}

			std::pair<iterator, iterator> equal_range(const Key& key) {
				std::pair<iterator, iterator> res;
			}
			std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
			iterator lower_bound( const Key& key );
			const_iterator lower_bound( const Key& key ) const;
			iterator upper_bound( const Key& key );
			const_iterator upper_bound( const Key& key ) const;

		//observers
			key_compare key_comp() const;
			std::map::value_compare value_comp() const;

		//friends
			friend bool operator==(map const & lhs, map const & rhs);
			friend bool operator!=(map const & lhs, map const & rhs);
			friend bool operator<(map const & lhs, map const & rhs);
			friend bool operator<=(map const & lhs, map const & rhs);
			friend bool operator>(map const & lhs, map const & rhs);
			friend bool operator>=(map const & lhs, map const & rhs);
			friend void swap(value_type& lhs, 
							 value_type& rhs );

		private:
			_tree_type _tree;
	};
}

#endif
