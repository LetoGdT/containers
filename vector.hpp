/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:25:09 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/02/23 20:12:12 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <iterator>
# include <exception>
# include <cstring>
# include "IteratorTraits.hpp"
# define _MEMORY_ALLOWANCE 2
# define _INITIAL_CAPACITY 10

namespace ft {
	template<typename T>
	class VectorIter;
	template<typename T>
	class ConstVectorIter;
	template<typename T>
	class ReverseVectorIter;
	template<typename T>
	class ConstReverseVectorIter;

	template<
		typename T,
		class Allocator = std::allocator<T>>
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
			typedef VectorIter<T> iterator;
			typedef ConstVectorIter<T> const_iterator;
			typedef ReverseVectorIter<T> reverse_iterator;
			typedef ConstReverseVectorIter<T> const_reverse_iterator;

			vector(): vector(Allocator()) {}
			explicit vector(const Allocator& alloc) {
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
				vector(InputIt first,
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
				this->_alloc = other.alloc;
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
				_size = other._size;
				_capacity = other._capacity;
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0 ; i < _size ; i++)
					_alloc.construct(_data + i, other._data[i]);
			}

			void assign( size_type count, const T& value ) {
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
				void assign(InputIt first,
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

			allocator_type get_allocator() const { return const_cast<const allocator_type>(_alloc); }
	//element access
			reference at(size_type pos) {
				if (pos >= _size)
					throw std::out_of_range("at: out of range");
				return _data[pos];
			}
			const_reference at(size_type pos) const {
				if (pos >= _size)
					throw std::out_of_range("at: out of range");
				return const_cast<const_reference>(_data[pos]);
			}

			reference front() { return _data[0]; }
			const_reference front() const { return const_cast<const_reference>(_data[0]); }
			reference back() { return _data[_size - 1]; }
			const_reference back() const { return const_cast<const_reference>(_data[_size - 1]); }
			T* data() { return _data; }
			const T* data() const { return const_cast<const_reference>(_data); }

	//iterators
			iterator begin() { return VectorIter<T>(_data); }
			iterator end() { return VectorIter<T>(&_data[_size]); }
			const_iterator begin() const { return ConstVectorIter<T>(_data); }
			const_iterator end() const { return ConstVectorIter<T>(&_data[_size]); }
			reverse_iterator rbegin() { return ReverseVectorIter<T>(&_data[_size - 1]); }
			reverse_iterator rend() { return ConstReverseVectorIter<T>(&_data[-1]); }
			const_reverse_iterator rbegin() const { return ConstReverseVectorIter<T>(&_data[_size - 1]); }
			const_reverse_iterator rend() const { return ConstReverseVectorIter<T>(&_data[-1]); }

	//Capacity
			bool empty() const { return _size == 0; }
			size_type size() const { return _size; }
			size_type max_size() const { return std::numeric_limits<size_type>::max(); }
			void reserve(size_type new_cap) {
				if (new_cap <= _capacity)
					return ;
				pointer tmp;
				tmp = _alloc.allocate(new_cap);
				memmove(tmp, const_cast<const_pointer>(_data), _size * sizeof(value_type));
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
			}
			void insert(iterator pos, size_type count, const_reference value) {
				iterator it = _makeEmptySpace(pos, count);
				for (size_type i = 0 ; i < count ; i++, it++)
					*it = value;
			}
			template<class InputIt>
				void insert(iterator pos,
							InputIt first,
							InputIt last) {
					size_type count;
					for (InputIt in = first, count = 1 ; in != last ; in ++)
						count++;
					iterator it = _makeEmptySpace(pos, count);
					for (InputIt in = first ; in != last ; in++, it++)
						*it = *in;
				}

			//erase()
			iterator erase(iterator pos) {
				if (pos < begin())
					return pos;
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
				size_type count;
				for (iterator it = first, count = 0 ; it != last && it != end() ; it++, count++)
					_alloc.destroy(_data + count); 	// the allocated objects are destroyed
				memmove(_data + first - begin(), 	//dest of the tail end of the list; first - begin() gives the index of the first element to remove
						_data + first - begin() + count,  //org of the tail end of the list, count elements after the begining of the area to remove
						(_size - (begin() - first) - count) * sizeof(value_type)); //number of bytes to move
				_size -= count;
				return first;
			}
			void push_back(const T& value) {
				iterator it = iterator(_data + _size);
				it = _makeEmptySpace(it, 1);
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
					_makeEmptySpace(iterator(_data + _size - 1), count - _size);
					for (size_t i = _size ; i < count ; i++)
						_alloc.allocate(_data + i, value);
				}
				else if (_size > count)
					for (size_t i = count ; i < _size ; i++)
						_alloc.destroy(_data + i);
				_size = count;
			}

			void swap(vector<T>& other) {
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
			friend bool operator==(const ft::vector<T,Allocator>& lhs,
					const ft::vector<T,Allocator>& rhs);
			friend bool operator!=(const ft::vector<T,Allocator>& lhs,
					const ft::vector<T,Allocator>& rhs);
			friend bool operator<(const ft::vector<T,Allocator>& lhs,
					const ft::vector<T,Allocator>& rhs);
			friend bool operator<=(const ft::vector<T,Allocator>& lhs,
					const ft::vector<T,Allocator>& rhs);
			friend bool operator>(const ft::vector<T,Allocator>& lhs,
					const ft::vector<T,Allocator>& rhs);
			friend bool operator>=(const ft::vector<T,Allocator>& lhs,
					const ft::vector<T,Allocator>& rhs);

			friend void swap(ft::vector<T, Allocator>& lhs,
							 ft::vector<T, Allocator>& rhs);

		private:
			pointer _data;
			size_type _size;
			size_type _capacity;
			Allocator& _alloc;

			//makes empty space at the iterator pos, and makes count free spaces.
			//manages the enlargement of the allocated space, as well as deallocation
			//of the old one, and the movement of the memory, wether it is shifted inside 
			//within the array, or copied to a new one
			//
			//returns an iterator to the first free slot created
			iterator _makeEmptySpace(iterator pos, size_type count) {
				size_type n;
				for (iterator it = begin(), n = 0 ; it != end() && it != pos; it++)
					n++;
				if (_capacity <= _size + count)
					reserve(_capacity * _MEMORY_ALLOWANCE);
				if (n < _size)
					memmove(_data + n + count, _data + n, n * sizeof(value_type));
				return iterator(_data + n);
			}
	};
	template
		<typename T,
		class Allocator = std::allocator<T>>
			bool operator==(const ft::vector<T,Allocator>& lhs,
			 const ft::vector<T,Allocator>& rhs);
	template
		<typename T,
		class Allocator = std::allocator<T>>
			bool operator!=(const ft::vector<T,Allocator>& lhs,
			 const ft::vector<T,Allocator>& rhs);
	template
		<typename T,
		class Allocator = std::allocator<T>>
			bool operator<(const ft::vector<T,Allocator>& lhs,
			 const ft::vector<T,Allocator>& rhs);
	template
		<typename T,
		class Allocator = std::allocator<T>>
			bool operator<=(const ft::vector<T,Allocator>& lhs,
			 const ft::vector<T,Allocator>& rhs);
	template
		<typename T,
		class Allocator = std::allocator<T>>
			bool operator>(const ft::vector<T,Allocator>& lhs,
			 const ft::vector<T,Allocator>& rhs);
	template
		<typename T,
		class Allocator = std::allocator<T>>
			bool operator>=(const ft::vector<T,Allocator>& lhs,
			 const ft::vector<T,Allocator>& rhs);

	template
		<typename T,
		class Allocator = std::allocator<T>>
			void swap(ft::vector<T, Allocator>& lhs,
							 ft::vector<T, Allocator>& rhs);
}

#endif
