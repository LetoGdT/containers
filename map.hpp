/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:04:09 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/09 17:38:22 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <exception>
# include "AVL_tree.hpp"

namespace ft {
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T>>>
	class map {
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
			typedef MapIter<T> iterator;
			typedef ConstMapIter<T> const_iterator;
			typedef ReverseMapIter<T> reverse_iterator;
			typedef ConstReverseMapIter<T> const_reverse_iterator;

			map();
			explicit map(Compare const & comp, const Allocator& alloc = Allocator());
			template<class InputIt>
				map(InputIt first, InputIt last,
					const Compare& comp = Compare(),
					const Allocator& alloc = Allocator() );
			map(const map& other);
			map& operator=(map const & other);
			~map();

		//element access
			reference at(const key_type& key);
			const_reference at(const key_type& key) const;
			reference operator[](const key_type& key);
			const_reference operator[](const key_type& key) const;

		//iterators
			iterator begin() { return MapIter<T>(_data); }
			iterator end() { return MapIter<T>(&_data[_size]); }
			const_iterator begin() const { return ConstMapIter<T>(_data); }
			const_iterator end() const { return ConstMapIter<T>(&_data[_size]); }
			reverse_iterator rbegin() { return ReverseMapIter<T>(&_data[_size - 1]); }
			reverse_iterator rend() { return ConstReverseMapIter<T>(&_data[-1]); }
			const_reverse_iterator rbegin() const { return ConstReverseMapIter<T>(&_data[_size - 1]); }
			const_reverse_iterator rend() const { return ConstReverseMapIter<T>(&_data[-1]); }

		//capacity
			bool empty() const;
			size_type size() const;
			size_type max_size() const;

		//modifiers
			void clear();
			std::pair<iterator, bool> insert( const value_type& value );
			iterator insert( iterator hint, const value_type& value );
			template< class InputIt >
				void insert( InputIt first, InputIt last );
			void erase( iterator pos );
			void erase( iterator first, iterator last );
			size_type erase( const Key& key );
			void swap( map& other );

		//lookup
			size_type count( const Key& key ) const;
			iterator find( const Key& key );
			const_iterator find( const Key& key ) const;
			std::pair<iterator,iterator> equal_range( const Key& key );
			std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
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

	};
}

#endif
