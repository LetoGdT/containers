/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:57:18 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/03/16 19:39:47 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP
# include <memory>
# include <algorithm>
# include "pair.hpp"
#include <iostream>

namespace ft {
	template <
		class Key,
		class T,
		class Compare,
		class Allocator>
	class AVL_tree {
		private:
			typedef pair<Key, T> entry;

			class Node {
				public:
					Node(): _left(NULL), _right(NULL), _parent(NULL), _height(0), _balance_factor(0) {}
					Node(entry content): _left(NULL), _right(NULL), _parent(NULL), _height(0), _balance_factor(0), _content(content) {}
					~Node() {}

					Node *_left;
					Node *_right;
					Node *_parent;
					entry _content;
					std::size_t _height;
					std::ptrdiff_t _balance_factor;
			};
			Node * balance(Node * node) {
				// Left heavy subtree
				if (node->_balance_factor == -2) {
					// Left left case
					if (node->_left->_balance_factor <= 0)
						return rotate_right(node);
					// Left right case
					else {
						node->_left = rotate_left(node->_left);
						return rotate_right(node);
					}
				}
				// Right heavy subtree
				else if (node->_balance_factor == 2) {
					// Right left case
					if (node->_right->_balance_factor < 0){
						node->_right = rotate_right(node->_right);
						return rotate_left(node);
					}
					// Right right case
					else
						return rotate_left(node);
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
				node->_balance_factor = right_height - left_height;
			}

			Node * insert(Node * node, entry const & content, Compare const & comp) {
				if (node == NULL)
					return make_node(content);
				if (comp(content.first, node->_content.first)) {
					if (node->_left == NULL) {
						node->_left = make_node(content);
						node->_left->_parent = node;
					}
					else
						node->_left = insert(node->_left, content, comp);
				}
				else {
					if (node->_right == NULL) {
						node->_right = make_node(content);
						node->_right->_parent = node;
					}
					else
						node->_right = insert(node->_right, content, comp);
				}
				update(node);
				return balance(node);
			}

			std::size_t remove(const Key key);
			entry * find(Node * node, const Key key, Compare const & comp) {
				if (node == NULL)
					return NULL;
				if (node->_content.first == key)
					return &node->_content;
				if (comp(node->_content.first, key))
					return find(node->_left, key, comp);
				return find(node->_right, key, comp);
			}

			Node* rotate_left(Node *A) {
				Node *tmp = A->_right;
				A->_right = tmp->_left;
				if (tmp->_left != NULL)
					tmp->_left->_parent = A;
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
					tmp->_right->_parent = A;
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

			Node * copy_node(Node const * other) {
				if (other == NULL)
					return NULL;
				Node * res;
				res = make_node(other->_content);
				res->_left = copy_node(other->_left);
				res->_right = copy_node(other->_right);
				res->_balance_factor = other->_balance_factor;
				res->_height = other->_height;
			}

			void destroy_node(Node * node) {
				if (node == NULL)
					return ;
				destroy_node(node->_left);
				destroy_node(node->_right);
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}

			Node * make_node(entry content) {
				Node node(content);
				Node * res = _alloc.allocate(1);
				_alloc.construct(res, node);
				return res;
			}
			typedef typename Allocator::template rebind<Node>::other allocator_type;

		public:
			AVL_tree(): _root(NULL),
						_nb_of_nodes(0),
						_alloc(allocator_type()),
						_comp(Compare()) {
				_alloc = allocator_type();
						}
			AVL_tree(AVL_tree const & other): _root(copy_node(other._root)),
											  _nb_of_nodes(other._nb_of_nodes),
											  _alloc(other._alloc),
											  _comp(other.comp){}

			AVL_tree & operator=(AVL_tree const & other) {
				_root = copy_node(other._root);
				_alloc = other._alloc;
				_nb_of_nodes = other._nb_of_nodes;
				_comp = other.comp;
			}

			~AVL_tree() {
				destroy_node(_root);
			}

			void insert(entry const & content) {
				if (find(_root, content.first, _comp) != NULL)
					return ;
				_root = insert(_root, content, _comp);
				_nb_of_nodes++;
			}

			entry * find(Key const key) {
				return find(_root, key, _comp);
			}

			void print_tree(Node * node, std::size_t depth) {
				if (node->_right != NULL)
					print_tree(node->_right, depth + 1);
				for (int i = 1 ; i < depth ; i++)
					std::cout << " ";
				if (node->_parent != NULL) {
					if (node->_parent->_right == node)
						std::cout << "/";
					else
						std::cout << "\\";
				}
				std::cout << node->_content.second << std::endl;
				if (node->_left != NULL)
					print_tree(node->_left, depth + 1);
			}

			void print() {
				print_tree(_root, 0);
			}


		private:
			Node *_root;
			allocator_type _alloc;
			std::size_t _nb_of_nodes;
			Compare _comp;
	};
}

#endif
