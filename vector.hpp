/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:25:09 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/02/03 18:39:14 by lgaudet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <iterator>
# include <exception>

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
			friend class VectorIter<T>;
			friend class ConstVectorIter<T>;
			friend class ReverseVectorIter<T>;
			friend class ConstReverseVectorIter<T>;

			vector();
			explicit vector(const Allocator& alloc);
			explicit vector(size_type count, 
							const T& value = T(),
							const Allocator& alloc = Allocator());
			template<class InputIt>
				vector(InputIt first,
						InputIt last,
						const Allocator& alloc = Allocator());
			vector(const vector& other);
			~vector();

			vector& operator=(const vector& other);
			void assign( size_type count, const T& value );
			template<class InputIt>
				void assign(InputIt first,
							InputIt last);
			allocator_type get_allocator() const;

			reference at(size_type pos);
			const_reference at(size_type pos) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			T* data();
			const T* data() const;

			iterator begin() { return VectorIter<T>(*this, 0); }
			iterator end() { return VectorIter<T>(*this, _size); }
			const_iterator begin() const { return ConstVectorIter<T>(*this, 0); }
			const_iterator end() const { return ConstVectorIter<T>(*this, _size); }
			reverse_iterator rbegin() { return ReverseVectorIter<T>(*this, 0); }
			reverse_iterator rend() { return ConstReverseVectorIter<T>(*this, _size); }
			const_reverse_iterator rbegin() const { return ConstReverseVectorIter<T>(*this, 0); }
			const_reverse_iterator rend() const { return ConstReverseVectorIter<T>(*this, _size); }

			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			void reserve( size_type new_cap );
			size_type capacity() const;

			void clear();
			iterator insert(iterator pos, const T& value);
			template<class InputIt>
				void insert(iterator pos,
							InputIt first,
							InputIt last);
			iterator erase(iterator pos);
			iterator erase(iterator first, iterator last);
			void push_back(const T& value);
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
	};

	template<typename T> class VectorIter {
		public:
			VectorIter(typename ft::vector<T> & vect,
					   typename ft::vector<T>::size_type pos):
				_vect(vect), _pos(pos) {}
			bool operator==(VectorIter<T> & other) {
				return this->_vect == other._vect && this->pos == other._pos;
			}
			bool operator!=(VectorIter<T> & other) {
				return !operator==(other);
			}
			typename ft::vector<T>::reference operator*() {
				if (this->_pos < 0 || this->_pos >= this->_vect._size)
					throw std::out_of_range("Accesed element out of range of vector");
				return this->_vect.data[this->_pos];
			}
			VectorIter<T> & operator++() {
				this->_pos++;
				return *this;
			}
			VectorIter<T> operator++(int) { 
				VectorIter<T> iter(this->_vect, this->_pos);
				this->_pos++;
				return iter;
			}
		protected:
			typename ft::vector<T> & _vect;
			typename vector<T>::size_type _pos;
	};

	template<typename T>
	class ReverseVectorIter: public virtual VectorIter<T> {
		public:
			ReverseVectorIter(typename ft::vector<T> & vect,
					   typename ft::vector<T>::size_type pos):
				VectorIter<T>::_vect(vect), VectorIter<T>::_pos(VectorIter<T>::_size - pos) {}
			ReverseVectorIter<T> & operator++() {
				this->_pos--;
				return *this;
			}
			ReverseVectorIter<T> operator++(int) { 
				VectorIter<T> iter(this->_vect, this->_pos);
				this->_pos--;
				return iter;
			}
	};

	template<typename T>
	class ConstVectorIter: public virtual VectorIter<T> {
		public:
			ConstVectorIter(typename ft::vector<T> & vect,
					   typename ft::vector<T>::size_type pos):
				VectorIter<T>(vect, pos) {}
			typename ft::vector<T>::reference operator*() {
				return const_cast<T>(VectorIter<T>::operator*());
			}
	};

	template<typename T>
	class ConstReverseVectorIter: public ConstVectorIter<T>, public ReverseVectorIter<T> {
		public:
			ConstReverseVectorIter(typename ft::vector<T> & vect,
					   typename ft::vector<T>::size_type pos):
				ReverseVectorIter<T>(vect, pos) {}
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
