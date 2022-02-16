/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:25:09 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/02/16 17:16:20 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <iterator>
# include <exception>
# include <cstring>
# define _MEMORY_ALLOWANCE 2

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
				_capacity = 10;
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
					_data[i] = value;
			}

			template<class InputIt>
				vector(InputIt first,
						InputIt last,
						const Allocator& alloc = Allocator()) {
				_alloc = alloc;
				size_type count = 0;
				for (InputIt it = first ; it != last ; it++)
					count++;
				_capacity = count;
				_size = count;
				_data = _alloc.allocate(count);
				size_type i = 0;
				for (InputIt it = first ; it != last ; it++, i++)
					_data[i] = *it;
			}

			vector(const vector& other) {
				this->_alloc = other.alloc;
				this->_capacity = other._capacity;
				this->_size = other._size;
				this->_data = _alloc.allocate(_capacity);
				for (size_type i = 0 ; i < _size ; i++)
					this->_data[i] = other._data[i];
			}
			~vector() {
				_alloc.deallocate(_data, _capacity);
			}

			vector& operator=(const vector& other) {
				_alloc.deallocate(_data, _capacity);
				_size = other._size;
				_capacity = other._capacity;
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0 ; i < _size ; i++)
					_data[i] = other._data[i];
			}

			void assign( size_type count, const T& value ) {
				_alloc.deallocate(_data, _capacity);
				_size = count;
				_capacity = count;
				_data = _alloc.allocate(count);
				for (size_type i = 0 ; i < count ; i++)
					_data[i] = value;
			}

			template<class InputIt>
				void assign(InputIt first,
							InputIt last) {
				size_type count = 0;
				for (InputIt it = first ; it != last ; it++)
					count++;
				_capacity = count;
				_size = count;
				_data = _alloc.allocate(count);
				size_type i = 0;
				for (InputIt it = first ; it != last ; it++, i++)
					_data[i] = *it;
			}

			allocator_type get_allocator() const { return const_cast<const allocator_type>(_alloc); }

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

			iterator begin() { return VectorIter<T>(_data); }
			iterator end() { return VectorIter<T>(&_data[_size]); }
			const_iterator begin() const { return ConstVectorIter<T>(_data); }
			const_iterator end() const { return ConstVectorIter<T>(&_data[_size]); }
			reverse_iterator rbegin() { return ReverseVectorIter<T>(&_data[_size - 1]); }
			reverse_iterator rend() { return ConstReverseVectorIter<T>(&_data[-1]); }
			const_reverse_iterator rbegin() const { return ConstReverseVectorIter<T>(&_data[_size - 1]); }
			const_reverse_iterator rend() const { return ConstReverseVectorIter<T>(&_data[-1]); }

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
			size_type capacity() const {
				return _capacity;
			}

			void clear() {
				_alloc.deallocate(_data, _capacity);
				_capacity = 10;
				_size = 0;
				_data = _alloc.allocate(_capacity);
			}
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
			iterator erase(iterator pos) {
				size_type n;
				for (iterator it = begin(), n = 0 ; it != pos && it != end() ; it++)
					n++;
				if (n >= _size)
					return pos;
				memmove(_data + n, _data + n + 1, (_size - n - 1) * sizeof(value_type));
				_size--;
				return iterator(_data + n);
			}
			iterator erase(iterator first, iterator last);
			void push_back(const T& value) {
				iterator it = iterator(_data + _size);
				it = _makeEmptySpace(it, 1);
			}
			void pop_back();
			void resize(size_type count);
			void resize(size_type count, T value = T());
			void swap(vector& other);

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
			T* _data;
			size_type _size;
			size_type _capacity;
			Allocator& _alloc;

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

	template<typename T> class VectorIter {
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef typename ft::vector<T>::difference_type difference_type;
			typedef typename ft::vector<T>::value_type value_type;
			typedef typename ft::vector<T>::pointer pointer;
			typedef typename ft::vector<T>::reference reference;

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
}

#endif
