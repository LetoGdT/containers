/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:57:18 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/09 17:49:37 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP
# include <memory>
# include "pair.hpp"

namespace ft {
	template <
		class Key,
		class T,
		class Compare,
		class Allocator>
	class AVL_tree {
		public:
			typedef pair<Key, T> entry;
			AVL_tree();
			AVL_tree(AVL_tree const & other);
			AVL_tree & operator=(AVL_tree const & other);
			~AVL_tree();

			void balance();
			entry & insert(entry & content, Compare const & comp);
			void remove(const Key key);
			entry& find(const Key key, Compare const & comp) {
				if (_content.first == key)
					return _content;
				if (comp(_content.first, key))
					return _left->find(key, comp);
				return _right->find(key, comp);
			}

			entry* rotate_left() {
				entry *tmp = _right;
				_right = tmp->_left;
				tmp->_left = this;
				return tmp;
			}
			entry* rotate_right() {
				entry *tmp = _left;
				_left = tmp->right;
				tmp->right = this;
				return tmp;
			}

		private:
			AVL_tree *_left;
			AVL_tree *_right;
			entry _content;
			std::size_t _height;
	};
}

#endif
