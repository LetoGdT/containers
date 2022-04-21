/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:57:18 by lgaudet-          #+#    #+#             */
/*   Updated: 2022/04/21 20:03:02 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP
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
			/*
			typedef typename ft::map<Key, T, Compare, Allocator>::value_type _entry;
			typedef typename ft::map<Key, T, Compare, Allocator>::size_type _size_type;
			*/
			typedef typename ft::pair<const Key, T> _entry;
			typedef typename std::size_t _size_type;
		public:

			class Node {
				public:
					Node(): _left(NULL),
							_right(NULL),
							_parent(NULL),
							_height(0),
							_balance_factor(0) {}
					Node(_entry content): _left(NULL),
										 _right(NULL),
										 _parent(NULL),
										 _height(0),
										 _balance_factor(0),
										 _content(content) {}
					Node(Node const & other): _left(other._left),
                                              _right(other._right),
                                              _parent(other._parent),
                                              _height(other._height),
                                              _balance_factor(other._balance_factor),
                                              _content(other._content) {}
					~Node() {}

					Node *_left;
					Node *_right;
					Node *_parent;
					_entry _content;
					_size_type _height;
					short _balance_factor;
			};

		private:
			typedef typename Allocator::template rebind<Node>::other allocator_type;
			Node * _rec_balance(Node *node) {
				if (node == NULL)
					return NULL;
				_rec_balance(node->_left);
				_rec_balance(node->_right);
				_update(node);
				return _balance(node);
			}

			// Balances *one* level of the subtree pointed by the parameter
			// Subtrees must be updated before the function is called
			// Returns the new updated top of the subtree, with both the forward and
			//backward relations updated
			Node * _balance(Node * node) {
				// Left heavy subtree
				if (node->_balance_factor == -2) {
					// Left left case
					if (node->_left->_balance_factor <= 0)
						return _rotate_right(node);
					// Left right case
					else {
						node->_left = _rotate_left(node->_left);
						return _rotate_right(node);
					}
				}
				// Right heavy subtree
				else if (node->_balance_factor == 2) {
					// Right left case
					if (node->_right->_balance_factor < 0){
						node->_right = _rotate_right(node->_right);
						return _rotate_left(node);
					}
					// Right right case
					else
						return _rotate_left(node);
				}
				return node;
			}

			Node* _rotate_left(Node *A) {
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
				_update(A);
				_update(tmp);
				return tmp;
			}
			Node* _rotate_right(Node *A) {
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
				_update(A);
				_update(tmp);
				return tmp;
			}

			// Updates the height and balance factor of the node given by the parameter
			void _update(Node * node) {
				_size_type left_height = 0;
				_size_type right_height = 0;
				if (node->_left != NULL)
					left_height = node->_left->_height;
				if (node->_right != NULL)
					right_height = node->_right->_height;
				node->_height = std::max(left_height, right_height);
				if (node->_left != NULL || node->_right != NULL)
					node->_height++;
				node->_balance_factor = right_height - left_height;
			}

			// Insert a copy of the entry into the subtree given as a parameter
			// The function is recursive, and the balancing is done at each step
			// The result is the new top of the subtree as given by the balance function
			Node * _insert(Node * node, _entry const & content) {
				// Case where the tree is empty
				if (node == NULL)
					return _make_node(content);
				// Case where the entry goes on the left child of the current node
				if (_comp(content.first, node->_content.first)) {
					// Case where the child is empty
					if (node->_left == NULL) {
						node->_left = _make_node(content);
						node->_left->_parent = node;
					}
					// Case where the child is not empty
					else
						node->_left = _insert(node->_left, content);
				}
				// Case where the entry goes on the right child of the current node
				else {
					// Case where the child is empty
					if (node->_right == NULL) {
						node->_right = _make_node(content);
						node->_right->_parent = node;
					}
					// Case where the child is not empty
					else
						node->_right = _insert(node->_right, content);
				}
				// Update and balance the tree as you go up the recursion
				_update(node);
				return _balance(node);
			}

			Node * _get_successor(Node *node) {
				Node * res = node->_left;
				while (res->_right != NULL)
					res = res->_right;
				return res;
			}

			void _bypass_target(Node * parent, Node * target, Node * child) {
				if (parent != NULL) {
					if (parent->_left == target)
						parent->_left = child;
					else
						parent->_right = child;
				}
			}

			void _exchange_nodes(Node * A, Node * B) {
				if (A == NULL || B == NULL)
					return ;
				Node tmp(*A);

				// Setting A’s parent relationship
				A->_parent = B->_parent;
				if (A->_parent != NULL) {
					if (A->_parent->_right == B)
						A->_parent->_right = A;
					else
						A->_parent->_left = A;
				}
				// Setting A’s children
				A->_left = B->_left;
				if (A->_left != NULL)
					A->_left->_parent = A;
				A->_right = B->_right;
				if (A->_right != NULL)
					A->_right->_parent = A;

				// Setting B’s parent relationship
				B->_parent = tmp._parent;
				if (B->_parent != NULL) {
					if (B->_parent->_right == A)
						B->_parent->_right = B;
					else
						B->_parent->_left = B;
				}
				// Setting B’s children
				B->_left = tmp._left;
				if (B->_left != NULL)
					B->_left->_parent = B;
				B->_right = tmp._right;
				if (B->_right != NULL)
					B->_right->_parent = B;

				A->_balance_factor = B->_balance_factor;
				B->_balance_factor = tmp._balance_factor;
				A->_height = B->_height;
				B->_height = tmp._height;
				if (_root == A)
					_root = B;
				else if (_root == B)
					_root = A;
			}

			// Remove the node given by the parameter
			// The function is recursive and properly updates and balances the tree as
			//it goes
			// The result is the pointer to the top of the tree, which has been
			//balanced and updated
			Node * _remove(Node * node, Key const & key) {
				Node * target = _find(node, key);
				if (target == NULL)
					return NULL;
				Node * parent = target->_parent;
				Node * successor;

				// Case where the node has only one or no children
				if (target->_left == NULL || target->_right == NULL) {
					// Select the proper successor of the node
					if (target->_left == NULL && target->_right == NULL)
						successor = NULL;
					else if (target->_right == NULL)
						successor = target->_left;
					else
						successor = target->_right;
					// Link the parent to the child
					_bypass_target(parent, target, successor);
					// Link the child to the parent
					if (successor != NULL)
						successor->_parent = parent;
					else
						successor = parent;
					// Destroy the target node
					target->_left = NULL;
					target->_right = NULL;
					_destroy_node(target);
					_nb_of_nodes--;
				}

				// Case where the node has children on both sides
				else {
					successor = _get_successor(target);
					_exchange_nodes(target, successor);
					successor = _remove(target, target->_content.first);
				}
				// Update and balance all the parents of the current node until
				// the parent of the entry node is reached
				for (Node * i = successor; i != node && i != NULL; i = i->_parent) {
					_update(i);
					i = _balance(i);
				}
				if (node == target)
					return parent;
				return node;
			}

			Node * _copy_node(Node const * other) {
				if (other == NULL)
					return NULL;
				Node * res;
				res = _make_node(other->_content);
				res->_left = _copy_node(other->_left);
				res->_right = _copy_node(other->_right);
				res->_balance_factor = other->_balance_factor;
				res->_height = other->_height;
				res->_parent = other->_parent;
				return res;
			}

			Node * _find(Node * node, const Key key) {
				if (node == NULL)
					return NULL;
				if (node->_content.first == key)
					return node;
				if (_comp(node->_content.first, key))
					return _find(node->_right, key);
				return _find(node->_left, key);
			}

			void _destroy_node(Node * node) {
				if (node == NULL)
					return ;
				_destroy_node(node->_left);
				_destroy_node(node->_right);
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}

			Node * _make_node(_entry content) {
				Node node(content);
				Node * res = _alloc.allocate(1);
				_alloc.construct(res, node);
				return res;
			}

			Node * _get_leftmost(Node * node) const {
				if (node == NULL)
					return NULL;
				while (node->_left != NULL)
					node = node->_left;
				return node;
			}

			Node * _get_rightmost(Node * node) const {
				if (node == NULL)
					return NULL;
				while (node->_left != NULL)
					node = node->_left;
				return node;
			}

			Compare _comp_entries(_entry const & e1, _entry const & e2) {
				return _comp(e1.first, e2.first);
			}

		// Fonctions de manipulation de l’arbre

		public:
			AVL_tree(): _root(NULL),
						_nb_of_nodes(0),
						_alloc(allocator_type()),
						_comp(Compare()) {
				_alloc = allocator_type();
			}
			AVL_tree(Compare const & comp, Allocator const & alloc): _root(NULL),
																	 _nb_of_nodes(0),
																	 _alloc(allocator_type()),
																	 _comp(comp) {}
			AVL_tree(AVL_tree const & other): _root(_copy_node(other._root)),
											  _nb_of_nodes(other._nb_of_nodes),
											  _alloc(other._alloc),
											  _comp(other._comp){}

			AVL_tree & operator=(AVL_tree const & other) {
				_root = _copy_node(other._root);
				_alloc = other._alloc;
				_nb_of_nodes = other._nb_of_nodes;
				//_comp = other._comp;
				return *this;
			}

			~AVL_tree() {
				_destroy_node(_root);
			}

			Node * insert(_entry const & content) {
				if (_find(_root, content.first) != NULL)
					return NULL;
				_root = _insert(_root, content);
				_nb_of_nodes++;
				return _find(_root, content.first);
			}

			Node * find(Key const key) {
				Node * res = _find(_root, key);
				if (res != NULL)
					return res;
				return NULL;
			}

			void erase(Key const & key) {
				_remove(_root, key);
			}

			void print_tree(Node * node, _size_type depth) {
				if (node == NULL)
					return ;
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

			bool compare_nodes(Node * const node1, Node * const node2) {
				return _comp(node1->_content.first, node2->_content.first);
			}

			Node * get_successor_iterator(Node * const current_node) const {
				if (current_node == NULL)
					return NULL;
				Node * res = _get_leftmost(current_node->_right);
				if (res == NULL)
					res = current_node->_parent;
				while (res != NULL && compare_nodes(res, current_node))
					res = res->_parent;
				return res;
			}

			Node* get_predecessor_iterator(Node * const current_node) const {
				if (current_node == NULL)
					return NULL;
				Node * res = _get_rightmost(current_node->_left);
				if (res == NULL)
					res = current_node->_parent;
				while (res != NULL && compare_nodes(res, current_node))
					res = res->_parent;
				return res;
			}

			_size_type get_size() const { return _nb_of_nodes; }
			void clear() {
				_nb_of_nodes = 0;
				_destroy_node(_root);
				_root = NULL;
			}

			Node * get_leftmost() {
				return _get_leftmost(_root);
			}

			Node * get_rightmost() {
				return _get_rightmost(_root);
			}

			void swap(AVL_tree& other) {
				AVL_tree tmp;

				// Save the value of this
				tmp._root = _root;
				tmp._alloc = _alloc;
				tmp._nb_of_nodes = _nb_of_nodes;
				tmp._comp = _comp;

				// Replace the value of this with the value of other
				_root = other._root;
				_alloc = other._alloc;
				_nb_of_nodes = other._nb_of_nodes;
				_comp = other._comp;

				// Replace the value of other with the saved value of this
				other._root = tmp._root;
				other._alloc = tmp._alloc;
				other._nb_of_nodes = tmp._nb_of_nodes;
				other._comp = tmp._comp;
			}

			// Returns a node pointer to a node containing a key greater than or equal 
			//to the parameter
			Node * lower_bound(const Key & key) {
				Node * current_node;
				Node * prev_node;

				prev_node = NULL;
				current_node = _root;
				while (current_node != NULL) {
					// Case where the node with the same key is found
					if (current_node->_content.first == key)
						return current_node;
					prev_node = current_node;
					// Case where the node might be found in the left child
					if (_comp(key, current_node->_content.first))
						current_node = current_node->_left;
					// Case whire the node might be found in the right child
					else
						current_node = current_node->_right;
				}
				// Case where the node with the same key was not found, so the closest
				//node with a greater key is selected
				if (prev_node != NULL)
					while (!_comp(key, prev_node->_content.first))
						prev_node = prev_node->_parent;
				return prev_node;
			}

			// Returns a node pointer to a node containing a key greater than the
			//parameter
			Node * upper_bound(const Key & key) {
				Node * bound = lower_bound(key);
				// If the key is found, the upper bound is the element following the
				//lower bound
				if (bound->_content.first == key)
					return get_successor_iterator(bound);
				// The upper bound is the same as the lower bound if the key is not
				//found
				return bound;
			}

			Compare get_comp() const { return _comp; }
			Compare get_entry_comp() const { return _comp_entries; }

			inline static bool value_operator_equ(const _entry a, const _entry b) { return a.first == b.first; }
			inline static bool value_operator_diff(const _entry a, const _entry b) { return a.first != b.first; }
			inline static bool value_operator_less(const _entry a, const _entry b) { return a.first < b.first; }
			inline static bool value_operator_less_equ(const _entry a, const _entry b) { return a <= b; }
			inline static bool value_operator_more(const _entry a, const _entry b) { return a > b; }
			inline static bool value_operator_more_equ(const _entry a, const _entry b) { return a >= b; }

			friend bool operator==(_entry const & lhs, _entry const & rhs) { return lhs.first == rhs.first; }
			friend bool operator!=(_entry const & lhs, _entry const & rhs) { return lhs.first != rhs.first; }
			friend bool operator<(_entry const & lhs, _entry const & rhs) { return rhs._comp(lhs.first, rhs.first); }
			friend bool operator<=(_entry const & lhs, _entry const & rhs) { return lhs == rhs || rhs._comp(lhs.first, rhs.first); }
			friend bool operator>=(_entry const & lhs, _entry const & rhs) { return !lhs._comp(lhs.first, rhs.first); }
			friend bool operator>(_entry const & lhs, _entry const & rhs) { return lhs != rhs && !rhs._comp(rhs.first, lhs.first); }

		private:
			Node *_root;
			allocator_type _alloc;
			_size_type _nb_of_nodes;
			Compare const _comp;
	};
}

#endif
