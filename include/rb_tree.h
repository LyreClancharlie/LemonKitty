#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int key_t;
typedef int value_t;

typedef enum color_t {
	RED = 0,
	BLACK = 1
} color_t;

//define the struct of tree_node;
typedef struct rb_tree_node_t {
	struct rb_tree_node_t *left, *right, *parent;
	key_t key;
	value_t value;
	color_t color;
} rb_tree_node_t;

//pre-declaration of the functions that should be used
rb_tree_node_t* insert(key_t key, value_t value, rb_tree_node_t* root);
rb_tree_node_t* erase(key_t key, rb_tree_node_t* root);
rb_tree_node_t* search(key_t key, rb_tree_node_t* root);

//new node
static rb_tree_node_t* rb_new_node(key_t key, value_t value) {
	rb_tree_node_t *node = (rb_tree_node_t*)malloc(sizeof(struct rb_tree_node_t));

	if(!node) {
		printf("Malloc error!\n");
		exit(-1);
	}

	node->key = key;
	node->value = value;
	node->color = RED;
	
	return node;
}

//check if a node exists, if not, use this_parent to represent the parent of this new node if the node should be inserted
static rb_tree_node_t* rb_node_check(key_t key, rb_tree_node_t *root, rb_tree_node_t** this_parent) {
	rb_tree_node_t *node = root, *parent = NULL;
	int cmp;

	while (node) {
		parent = node;
		cmp = node->key - key;
		if (cmp < 0)
			node = node->left;
		else if (cmp > 0)
			node = node->right;
		else
			return node;
	}

	if (this_parent)
		*this_parent = parent;

	return NULL;
}

static rb_tree_node_t* rb_tree_rot_left(rb_tree_node_t* node, rb_tree_node_t* root) {
	rb_tree_node_t* right = node->right;

	if ((node->right = right->left))
		right->left->parent = node;

	right->left = node;

	if ((right->parent = node->parent))
		if (node->parent->left == node)
			node->parent->left = right;
		else
			node->parent->right = right;
	else
		root = right;

	node->parent = right;

	return root;
}

static rb_tree_node_t* rb_tree_rot_right(rb_tree_node_t* node, rb_tree_node_t* root) {
	rb_tree_node_t* left = node->left;

	if ((node->left = left->right))
		left->right->parent = node;

	left->right = node;

	if ((left->parent = node->parent))
		if (node->parent->left == node)
			node->parent->left = left;
		else
			node->parent->right = left;
	else
		root = left;

	node->parent = left;

	return root;
}

static rb_tree_node_t* rb_insert_rebalance(rb_tree_node_t* root, rb_tree_node_t* node) {
	rb_tree_node_t *parent, *grandparent, *uncle, *tmp;
	while ((parent = node->parent) && (parent->color == RED)) {
		grandparent = parent->parent;

		if (parent == grandparent->left) {
			uncle = grandparent->right;

			if (uncle && uncle->color == RED) {
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			} else {
				if (parent->right == node) {
					root = rb_tree_rot_left(parent, root);
					tmp = parent;
					parent = node;
					node = tmp;
				}

				parent->color = BLACK;
				grandparent->color = RED;
				root = rb_tree_rot_right(grandparent, root);
			}
		} else {
			uncle = grandparent->left;

			if (uncle && uncle->color == RED) {
				grandparent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandparent;
			} else {
				if (parent->left == node) {
					root = rb_tree_rot_right(parent, root);
					tmp = parent;
					parent = node;
					node = tmp;
				}

				parent->color = BLACK;
				grandparent->color = RED;
				root = rb_tree_rot_left(grandparent, root);
			}
		}
	}

	root->color = BLACK;
	return root;
}

rb_tree_node_t* rb_erase_rebalance(rb_tree_node_t* node, rb_tree_node_t* parent, rb_tree_node_t* root) {
	rb_tree_node_t *brother, *bro_left, *bro_right;

	while ((!node || node->color == BLACK) && node != root) {
		if (parent->left == node) {
			brother = parent->right;

			if (brother->color == RED) {
				brother->color = BLACK;
				parent->color = RED;
				root = rb_tree_rot_left(parent, root);
				brother = parent->right;
			}

			if ((!brother->left || brother->left->color == BLACK) && (!brother->right || brother->right->color == BLACK)) {
				brother->color = RED;
				node = parent;
				parent = parent->parent;
			} else {
				if (!brother->right || brother->right->color == BLACK) {
						brother->left->color = BLACK;
						brother->color = RED;
						root = rb_tree_rot_right(brother, root);
						brother = parent->right;
				}
				brother->color = parent->color;
				parent->color = BLACK;
				if (brother->right)
					brother->right->color = BLACK;
				root = rb_tree_rot_left(parent, root);
				node = root;
				break;
			}
		} else {
			brother = parent->left;

			if (brother->color == RED) {
				brother->color = BLACK;
				parent->color = RED;
				root = rb_tree_rot_right(parent, root);
				brother = parent->left;
			}

			if ((!brother->left || brother->left->color == BLACK) && (!brother->right || brother->right->color == BLACK)) {
				brother->color = RED;
				node = parent;
				parent = parent->parent;
			} else {
				if (!brother->left || brother->left->color == BLACK) {
						brother->right->color = BLACK;
						brother->color = RED;
						root = rb_tree_rot_left(brother, root);
						brother = parent->left;
				}
				brother->color = parent->color;
				parent->color = BLACK;
				if (brother->left)
					brother->left->color = BLACK;
				root = rb_tree_rot_right(parent, root);
				node = root;
				break;
			}
		}
	}

	if (node)
		node->color = BLACK;

	return root;
}

//insert a node if not existed, or do nothing (appending: How to return error value if existed)
rb_tree_node_t* rb_insert(key_t key, value_t value, rb_tree_node_t* root) {
	rb_tree_node_t *node, *parent = NULL;

	if ((node = rb_node_check(key, root, &parent)))
		return root;
	node = rb_new_node(key, value);
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	if (parent)
		if (parent->key > key)
			parent->left = node;
		else
			parent->right = node;
	else
		node = root;

//reprint the tree to make it balance
	return rb_insert_rebalance(root, node);
}

rb_tree_node_t* rb_search(key_t key, rb_tree_node_t* root) {
	return rb_node_check(key, root, NULL);
}

rb_tree_node_t* rb_erase(key_t key, rb_tree_node_t* root) {
	rb_tree_node_t *node, *parent, *child, *deletethis, *precursor;
	color_t color;

	if (!(node = rb_node_check(key, root, NULL))) {
		printf("Erase error: key%d not existed\n", key);
		return root;
	}

	deletethis = node;

	if (node->left && node->right) {
		node = node->left;

		while ((precursor = node->right) != NULL) {
			node = precursor;
		}
		child = node->left;
		parent = node->parent;
		color = node->color;

		if (child) {
			child->parent = parent;
		}

		if (parent) {
			if ((parent->right = node))
				parent->right = child;
			else
				parent->left = child;
		} else
			root = child;

		if (node->parent == deletethis)
			parent = node;

		node->parent = deletethis->parent;
		node->left = deletethis->left;
		node->right = deletethis->right;
		node->color = deletethis->color;

		if (deletethis->parent) {
			if (deletethis->parent->left == deletethis)
				deletethis->parent->left = node;
			else
				deletethis->parent->right = node;
		} else
			root = node;

		deletethis->right->parent = node;
		if (deletethis->left)
			deletethis->left->parent = node;
	} else {
		if (!node->left)
			child = node->right;
		else if (!node->right)
			child = node->left;

		parent = node->parent;
		color = node->color;

		if (child)
			child->parent = node;
		if (parent)
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		else
			root = child;
	}

	free(deletethis);

	if (color == BLACK)
		rb_erase_rebalance(child, parent, root);

	return root;
}

