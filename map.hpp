/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:04:09 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/05/02 14:42:10 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <limits>
# include <exception>
# include "pair.hpp"
# include "AVL_tree.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"
# include "lexicographical_compare.hpp"

namespace ft {
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		private:
			typedef AVL_tree<ft::pair<const Key, T>, Compare, Allocator> _tree_type;
			typedef typename _tree_type::Node _Node;
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
			typedef MapIter<value_type, Compare, Allocator, difference_type> iterator;
			typedef MapIter<value_type, Compare, Allocator, difference_type, const value_type*, const value_type&> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			map(){
				_tree = _tree_type(Compare(), Allocator());
			}
			explicit map(Compare const & comp, const Allocator& alloc = Allocator()) {
				_tree = _tree_type(comp, alloc);
			}
			template<class InputIt>
				map(InputIt first, InputIt last,
					const Compare& comp = Compare(),
					const Allocator& alloc = Allocator()) {
				_tree = _tree_type(comp, alloc);
				for (InputIt i = first ; i != last ; i++)
					_tree.insert(*i);
			}
			map(const map& other): _tree(other._tree) {}
			map& operator=(map const & other) {
				_tree = other.tree;
			}
			~map() {}

		//element access
			mapped_type & at(const key_type& key) {
				typename _tree_type::Node * tmp = _tree.find(key);
				if (tmp == NULL)
					throw std::out_of_range("map::at:  key not found");
				return tmp->_content.second;
			}
			const mapped_type & at(const key_type& key) const {
				typename _tree_type::Node * tmp = _tree.find(key);
				if (tmp == NULL)
					throw std::out_of_range("map::at:  key not found");
				return tmp->_content.second;
			}
			mapped_type & operator[](const key_type& key) {
				typename _tree_type::Node * tmp = _tree.find(key);
				if (tmp == NULL)
					return _tree.insert(make_pair(key, mapped_type()))->_content.second;
				return tmp->_content.second;
			}

		//iterators
			iterator begin() {
				_Node * node = _tree.get_leftmost();
				iterator it(node, &_tree);
				return it;
			}
			iterator end() {
				_Node * node = _tree.get_rightmost();
				iterator it(node, &_tree);
				++it;
				return it;
			}
			const_iterator begin() const {
				_Node * node = _tree.get_leftmost();
				const_iterator it(node, &_tree);
				return it;
			}
			const_iterator end() const {
				_Node * node = _tree.get_rightmost();
				const_iterator it(node, &_tree);
				++it;
				return it;
			}
			reverse_iterator rbegin() {
				_Node * node = _tree.get_rightmost();
				reverse_iterator it(iterator(node, &_tree));
				return it;
			}
			reverse_iterator rend() {
				_Node * node = _tree.get_leftmost();
				reverse_iterator it(iterator(node, &_tree));
				++it;
				return it;
			}
			const_reverse_iterator rbegin() const {
				_Node * node = _tree.get_rightmost();
				const_reverse_iterator it(iterator(node, &_tree));
				return it;
			}
			const_reverse_iterator rend() const {
				_Node * node = _tree.get_leftmost();
				const_reverse_iterator it(iterator(node, &_tree));
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

			ft::pair<iterator, bool> insert(const value_type& value) {
				_Node * node = _tree.insert(value);
				iterator iter(node, &_tree);
				return ft::make_pair(iter, node != NULL);
			}
			iterator insert(iterator hint, const value_type& value) {
				(void)hint;
				return insert(value).first;
			}
			template< class InputIt >
			void insert(InputIt first, InputIt last) {
				for (InputIt it = first ; it != last ; ++it)
					insert(*it);
			}

			void erase(iterator pos) {
				if (pos != end())
					_tree.erase((*pos).first);
			}
			void erase(iterator first, iterator last) {
				iterator it = first;
				while (it != last)
					_tree.erase((*it++).first);
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
				_Node * res = _tree.find(key);
				if (res == NULL)
					return end();
				iterator it(res, &_tree);
				return it;
			}
			const_iterator find(const Key& key) const {
				_Node * res = _tree.find(key);
				if (res == NULL)
					return end();
				const_iterator it(_tree.find(key), &_tree);
				return it;
			}

			ft::pair<iterator, iterator> equal_range(const Key& key) {
				ft::pair<iterator, iterator> res;
				res.first = lower_bound(key);
				res.second = upper_bound(key);
				return res;
			}
			ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
				ft::pair<const_iterator, const_iterator> res;
				res.first = lower_bound(key);
				res.second = upper_bound(key);
				return res;
			}
			iterator lower_bound(const Key& key) {
				typename _tree_type::Node * node = _tree.lower_bound(key);
				iterator it(node, &_tree);
				return it;
			}
			const_iterator lower_bound( const Key& key ) const {
				typename _tree_type::Node * node = _tree.lower_bound(key);
				const_iterator it(node, &_tree);
				return it;
			}
			iterator upper_bound( const Key& key ) {
				typename _tree_type::Node * node = _tree.upper_bound(key);
				iterator it(node, &_tree);
				return it;
			}
			const_iterator upper_bound( const Key& key ) const {
				typename _tree_type::Node * node = _tree.upper_bound(key);
				const_iterator it(node, &_tree);
				return it;
			}

		//observers
			key_compare key_comp() const { return _tree.get_comp(); }
			Compare value_comp() const { return _tree.get_value_comp; }

		//friends
			friend bool operator==(map const & lhs, map const & rhs) {
				if (lhs.size() != rhs.size())
					return false;
				for (map::const_iterator i = lhs.begin(), j = rhs.begin() ; i != lhs.end() ; ++i, ++j)
					if (*i != *j)
						return false;
				return true;
			}
			friend bool operator!=(map const & lhs, map const & rhs) {
				return !(lhs == rhs);
			}
			friend bool operator<(map const & lhs, map const & rhs) {
				return ft::lexicographical_compare(lhs.begin(), lhs.end(),
											   rhs.begin(), rhs.end());
			}
			friend bool operator<=(map const & lhs, map const & rhs) {
				return !(rhs < lhs);
			}
			friend bool operator>(map const & lhs, map const & rhs) {
				return rhs < lhs;
			}
			friend bool operator>=(map const & lhs, map const & rhs) {
				return !(lhs < rhs);
			}
		private:
			_tree_type _tree;
	};
	template <typename Key, typename T, typename Compare, typename Allocator>
	void swap(map<Key, T, Compare, Allocator> & lhs,
			  map<Key, T, Compare, Allocator> & rhs) {
		lhs.swap(rhs);
	}

}

# include "map_iterator.hpp"
#endif
