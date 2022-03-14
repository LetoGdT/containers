/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:57:18 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/14 23:27:38 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP
# include <memory>
# include <algorithm>
# include "pair.hpp"

namespace ft {
	template <
		class Key,
		class T,
		class Compare,
		class Allocator>
	class AVL_tree {
		typedef pair<Key, T> entry;

		class Node {
			public:
				Node(): _left(NULL), _right(NULL), _parent(NULL), _height(0) {}
				Node(entry content): _left(NULL), _right(NULL), _parent(NULL), _height(0), _content(content) {}
				~Node() {}

				Node *_left;
				Node *_right;
				Node *_parent;
				entry _content;
				std::size_t _height;
				std::ptrdiff_t _blance_factor;
		};
				Node * balance(Node * node) {
					// Left heavy subtree
					if (node->balance_factor == -2) {
						// Left left case
						if (node->_left->_blance_factor <= 0)
							return rotate_right(node);
						// Left right case
						else {
							node->_left = rotate_left(node->_left);
							return rotate_right(node);
						}
					}
					// Right heavy subtree
					else if (node->balance_factor == 2) {
						// Right left case
						if (node->_right->_blance_factor >= 0){
							node->_right = rotate_right(node->_right);
							return rotate_left(node);
						}
						// Right right case
						else
							rotate_left(node);
					}
					return node;
				}
				void update(Node * node) {
					std::size_t left_height = 0;
					std::size_t right_height = 0;
					if (node->_left != NULL)
						left_height = node->_left->_height;
					if (node->_right != NULL)
						right_height = node->_right->_height;
					node->_height = std::max(left_height, right_height) + 1;
					node->_blance_factor = right_height - left_height;
				}

				Node & insert(Node & node, entry const & content, Compare const & comp) {
					if (node._height == -1) {
						node._content = content;
						node._height = 0;
					}
					else if (comp(content.first, node._content.first)) {
						if (node._left == NULL) {
							node._left = _make_node(content);
							node._left->_parent = this;
						}
						else
							node._left = insert(content, comp);
					}
					else {
						if (node._right == NULL) {
							node._right = _make_node(content);
							node._right->_parent = this;
						}
						else
							node._right = insert(content, comp);
					}
					update();
					return balance();
				}

				std::size_t remove(const Key key);
				entry & find(Node & node, const Key key, Compare const & comp) {
					if (node._content.first == key)
						return node._content;
					if (comp(node._content.first, key))
						return node._left->find(key, comp);
					return node._right->find(key, comp);
				}

				Node* rotate_left(Node *A) {
					Node *tmp = A->_right;
					A->_right = tmp->_left;
					if (tmp->_left != NULL)
						tmp->_left->parent = A;
					tmp->_left = A;
					tmp->_parent = A->_parent;
					A->_parent = tmp;
					if (tmp->_parent != NULL) {
						if (tmp->_parent->_left == A)
							tmp->_parent->_left = tmp;
						else
							tmp->_parent->_right = tmp;
					}
					update(A);
					update(tmp);
					return tmp;
				}
				Node* rotate_right(Node *A) {
					Node *tmp = A->_left;
					A->_left = tmp->_right;
					if (tmp->_right != NULL)
						tmp->_right->parent = A;
					tmp->_right = A;
					tmp->_parent = A->_parent;
					A->_parent = tmp;
					if (tmp->_parent != NULL) {
						if (tmp->_parent->_left == A)
							tmp->_parent->_left = tmp;
						else
							tmp->_parent->_right = tmp;
					}
					update(A);
					update(tmp);
					return tmp;
				}

		public:
			AVL_tree();
			AVL_tree(AVL_tree const & other);
			AVL_tree & operator=(AVL_tree const & other);
			~AVL_tree() {
			}


		private:
			Node *_root;
			Allocator _alloc;
			std::size_t _nb_of_nodes;
			
			Node * _make_node(entry content) {
				Node node(content);
				Node * res = _alloc.allocate(1);
				_alloc.construct(res, node);
				return res;
			}
	};
}

#endif
