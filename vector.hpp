/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:25:09 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/26 20:48:54 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <exception>
# include <limits>
# include <cstring>
# include "is_integral.hpp"
# include "lexicographical_compare.hpp"
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"
# define _MEMORY_ALLOWANCE 2
# define _INITIAL_CAPACITY 10

namespace ft {
	template<typename T,
			 class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef T& reference;
			typedef const T& const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef VectorIter<T, difference_type> iterator;
			typedef VectorIter<T, difference_type, const T*, const T&> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			explicit vector(const Allocator& alloc = Allocator()) {
				_alloc = alloc;
				_capacity = _INITIAL_CAPACITY;
				_size = 0;
				_data = _alloc.allocate(_capacity);
			}

			explicit vector(size_type count, 
							const T& value = T(),
							const Allocator& alloc = Allocator()) {
				_alloc = alloc;
				_capacity = count;
				_size = count;
				_data = _alloc.allocate(count);
				for (size_type i = 0 ; i < count ; i++)
					_alloc.construct(_data + i, value);
			}

			template<class InputIt>
				vector(typename std::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
						InputIt last,
						const Allocator& alloc = Allocator()) {
				_alloc = alloc;
				size_type count = last - first;
				_capacity = count;
				_size = count;
				_data = _alloc.allocate(count);
				size_type i = 0;
				for (InputIt it = first ; it != last ; it++, i++)
					_alloc.construct(_data + i, *it);
			}

			vector(const vector& other) {
				this->_alloc = other._alloc;
				this->_capacity = other._capacity;
				this->_size = other._size;
				this->_data = _alloc.allocate(_capacity);
				for (size_type i = 0 ; i < _size ; i++)
					_alloc.construct(_data + i, other._data[i]);
			}
			~vector() {
				for (size_type i = 0 ; i < _size ; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
			}

			vector& operator=(const vector& other) {
				for (size_type i = 0 ; i < _size ; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				_alloc = other._alloc;
				_size = other._size;
				_capacity = _size;
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0 ; i < _size ; i++)
					_alloc.construct(_data + i, other._data[i]);
				return *this;
			}

			void assign(size_type count, const T& value) {
				for (size_type i = 0 ; i < _size ; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				_size = count;
				_capacity = count;
				_data = _alloc.allocate(count);
				for (size_type i = 0 ; i < count ; i++)
					_alloc.construct(_data + i, value);
			}

			template<class InputIt>
				void assign(typename std::enable_if<!is_integral<InputIt>::value, InputIt>::type first,
							InputIt last) {
					for (size_type i = 0 ; i < _size ; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, _capacity);
					size_type count = last - first;
					_capacity = count;
					_size = count;
					_data = _alloc.allocate(count);
					size_type i = 0;
					for (InputIt it = first ; it != last ; it++, i++)
						_alloc.construct(_data + i, *it);
				}

			allocator_type get_allocator() const { return _alloc; }
	//element access
			reference at(size_type pos) {
				if (pos >= _size)
					throw std::out_of_range("vector");
				return _data[pos];
			}
			const_reference at(size_type pos) const {
				if (pos >= _size)
					throw std::out_of_range("vector");
				return _data[pos];
			}

			reference operator[](size_type n) {
				return _data[n];
			}
			const_reference operator[](size_type n) const {
				return _data[n];
			}

			reference front() { return _data[0]; }
			const_reference front() const { return _data[0]; }
			reference back() { return _data[_size - 1]; }
			const_reference back() const { return _data[_size - 1]; }
			pointer data() { return _data; }
			const_pointer data() const { return _data; }

	//iterators
			iterator begin() { return iterator(_data); }
			iterator end() { return iterator(&_data[_size]); }
			const_iterator begin() const { return const_iterator(_data); }
			const_iterator end() const { return const_iterator(&_data[_size]); }
			reverse_iterator rbegin() { return reverse_iterator(iterator(&_data[_size - 1])); }
			reverse_iterator rend() { return reverse_iterator(iterator(&_data[-1])); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(iterator(&_data[_size - 1])); }
			const_reverse_iterator rend() const { return const_reverse_iterator(iterator(&_data[-1])); }

	//Capacity
			bool empty() const { return _size == 0; }
			size_type size() const { return _size; }
			size_type max_size() const { return std::numeric_limits<size_type>::max(); }
			void reserve(size_type new_cap) {
				if (new_cap <= _capacity)
					return ;
				pointer tmp = _alloc.allocate(new_cap);
				memmove(tmp, _data, _size * sizeof(value_type));
				_alloc.deallocate(_data, _capacity);
				_capacity = new_cap;
				_data = tmp;
			}
			size_type capacity() const { return _capacity; }

			void clear() {
				for (size_type i = 0 ; i < _size ; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				_capacity = _INITIAL_CAPACITY;
				_size = 0;
				_data = _alloc.allocate(_capacity);
			}

	//modifiers
			//insert
			iterator insert(iterator pos, const T& value) {
				iterator it = _makeEmptySpace(pos, 1);
				*it = value;
				return it;
			}
			void insert(iterator pos, size_type count, const_reference value) {
				iterator it = _makeEmptySpace(pos, count);
				for (size_type i = 0 ; i < count ; i++, it++)
					*it = value;
			}
			template<class InputIt>
				void insert(iterator pos,
							typename std::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
							InputIt last) {
					size_type count = last - first;
					iterator it = _makeEmptySpace(pos, count);
					for (InputIt in = first ; in != last ; in++, it++)
						*it = *in;
				}

			//erase()
			iterator erase(iterator pos) {
				if (pos < begin())
					pos = begin();
				size_type n = pos - begin();
				if (n >= _size)
					return pos;
				_alloc.destroy(_data + n);
				memmove(_data + n, _data + n + 1, (_size - n - 1) * sizeof(value_type));
				_size--;
				return iterator(_data + n);
			}

			iterator erase(iterator first, iterator last) {
				if (first < begin() || first > end())
					return first;
				size_type count = 0;
				for (iterator it = first ; it != last && it != end() ; it++, count++)
					_alloc.destroy(_data + count); 	// the allocated objects are destroyed
				memmove(_data + (first - begin()), 	//dest of the tail end of the list; first - begin() gives the index of the first element to remove
						_data + (first - begin()) + count,  //org of the tail end of the list, count elements after the begining of the area to remove
						(_size - (begin() - first) - count) * sizeof(value_type)); //number of bytes to move
				_size -= count;
				return first;
			}
			void push_back(const T& value) {
				iterator it = iterator(_data + _size);
				it = _makeEmptySpace(it, 1);
				*it = value;
			}
			void pop_back() {
				if (_size == 0)
					return ;
				_alloc.destroy(_data + _size - 1); //the last element of the list is destructed
				_size--;
			}

			//resizes the array so it contains count elements. 
			//the capacity of the vector is not reduced, but may be made bigger
			void resize(size_type count, T value = T()) {
				if (_size < count) {
					size_type old_size = _size;
					_makeEmptySpace(iterator(_data + _size - 1), count - _size);
					for (size_type i = old_size ; i < count ; i++)
						_alloc.construct(_data + i, value);
				}
				else if (_size > count)
					for (size_type i = count ; i < _size ; i++)
						_alloc.destroy(_data + i);
				_size = count;
			}

			void swap(vector& other) {
				//Saving this’s attributes
				pointer tmp_data = this->_data;
				size_type tmp_size = this->_size;
				size_type tmp_capacity = this->_capacity;
				Allocator& tmp_alloc = this->_alloc;

				//Copying other’s attributes to this
				this->_data = other._data;
				this->_size = other._size;
				this->_capacity = other._capacity;
				this->_alloc = other._alloc;

				//Setting other’s attributes to the saved values of this
				other._data = tmp_data;
				other._size = tmp_size;
				other._capacity = tmp_capacity;
				other._alloc = tmp_alloc;
			}

			friend bool operator==(vector const & lhs,
									vector const & rhs) {
				return lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end(),
												vector::_value_operator_equ);
			}
			friend bool operator!=(vector const & lhs, vector const & rhs) {
				return lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end(),
												vector::_value_operator_diff);
			}
			friend bool operator<(vector const & lhs, vector const & rhs) {
				return lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end(),
												vector::_value_operator_less);
			}
			friend bool operator<=(vector const & lhs, vector const & rhs) {
				return lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end(),
												vector::_value_operator_less_equ);
			}
			friend bool operator>(vector const & lhs, vector const & rhs) {
				return lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end(),
												vector::_value_operator_more);
			}
			friend bool operator>=(vector const & lhs, vector const & rhs) {
				return lexicographical_compare(lhs.begin(), lhs.end(),
												rhs.begin(), rhs.end(),
												vector::_value_operator_more_equ);
			}

			friend void swap(vector const & lhs, vector const & rhs) {
				//Saving lhs’s attributes
				pointer tmp_data = lhs->_data;
				size_type tmp_size = lhs->_size;
				size_type tmp_capacity = lhs->_capacity;
				Allocator& tmp_alloc = lhs->_alloc;

				//Copying rhs’s attributes to lhs
				lhs->_data = rhs._data;
				lhs->_size = rhs._size;
				lhs->_capacity = rhs._capacity;
				lhs->_alloc = rhs._alloc;

				//Setting rhs’s attributes to the saved values of this
				rhs._data = tmp_data;
				rhs._size = tmp_size;
				rhs._capacity = tmp_capacity;
				rhs._alloc = tmp_alloc;
			}

		private:
			pointer _data;
			size_type _size;
			size_type _capacity;
			Allocator _alloc;

			//makes empty space at the iterator pos, and makes count free spaces.
			//manages the enlargement of the allocated space, as well as deallocation
			//of the old one, and the movement of the memory, wether it is shifted inside 
			//within the array, or copied to a new one
			//
			//returns an iterator to the first free slot created
			iterator _makeEmptySpace(iterator pos, size_type count) {
				size_type n = pos - begin();
				if (_capacity <= _size + count)
					reserve(_capacity * _MEMORY_ALLOWANCE);
				if (n < _size)
					memmove(_data + n + count, _data + n, (_size - n) * sizeof(value_type));
				_size += count;
				return iterator(_data + n);
			}
			inline static bool _value_operator_equ(const value_type a, const value_type b) { return a == b; }
			inline static bool _value_operator_diff(const value_type a, const value_type b) { return a != b; }
			inline static bool _value_operator_less(const value_type a, const value_type b) { return a < b; }
			inline static bool _value_operator_less_equ(const value_type a, const value_type b) { return a <= b; }
			inline static bool _value_operator_more(const value_type a, const value_type b) { return a > b; }
			inline static bool _value_operator_more_equ(const value_type a, const value_type b) { return a >= b; }
	};
}

#endif
