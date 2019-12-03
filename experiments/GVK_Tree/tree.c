#include "tree.h"

node *headTree = NULL;

FILE *f = NULL;

static int max(int a, int b) {
	return (a < b) ? b : a;
}

void addNode(int keyNode, node **node_pointer) {

	node *newnode;
	newnode = (node *) malloc(sizeof(node));

	newnode->s_left = NULL;
	newnode->s_right = NULL;
	newnode->key = keyNode;
	*node_pointer = newnode;
}

void makeTree(node *head) {

	int temp;
	node *search;

	while (!feof(f)) {
		fscanf(f, "%d", &temp);
		search = head;
		while (1) {
			if (temp < search->key) {
				if (search->s_left) search = search->s_left;
				else { addNode(temp, &search->s_left); break; }
			}
			else if (temp > search->key)
				if (search->s_right) search = search->s_right;
				else { addNode(temp, &search->s_right); break; }
			else
				break;
		}
	}
}

void build_AVL_Tree() {

	int temp;
	fseek(f, 0, 0);
	if (feof(f)) { printf("файл содержит пустое дерево!"); getchar(); exit(1); }
	fscanf(f, "%d", &temp);

	headTree = (sheet *) malloc(sizeof(sheet));
	headTree->key = temp;
	headTree->s_left = NULL;
	headTree->s_right = NULL;

	makeTree(headTree);
}

/*int high(node *node) {

}*/

int high_p(node *node) {

	/* Main part */
	if (node == NULL) {
		return -1;
	}

	/* Returning value */
	return max(high_p(node->s_left), high_p(node->s_right)) + 1;
}

/*int checkNode(node *node) {

}*/

int checkTree(node *node) {

	/* Main part */
	if (node == NULL) {
		return 0;
	} else if (abs(high_p(node->s_right) - high_p(node->s_left)) > 1) {
		return node->key;
	}

	/* Returning value */
	return max(checkTree(node->s_left), checkTree(node->s_right));
}

node *search_rod(int key_, node *node) {

	/* Main part */
	while (node != NULL) {
		if (key_ == node->s_right->key || key_ == node->s_left->key) {
			return node;
		} else {
			node = (key_ < node->key) ? node->s_left : node->s_right;
		}
	}

	/* Returning value */
	return NULL;
}

node *search(int key_, node *node) {

	struct _node *current = node;

	while (current != NULL)
		if (key_ == current->key)
			return current;
		else
			current = (key_ < current->key) ? current->s_left : current->s_right;

	return (0);
}

node *search_left(node *node) {

	/* Main part */
	while (node->s_left != NULL) {
		node = node->s_left;
	}

	/* Returning value */
	return node;
}

void addKey(int temp, node *head) {

	node *search;
	search = head;
	while (1) {
		if (temp < search->key) {
			if (search->s_left) search = search->s_left;
			else { addNode(temp, &search->s_left); break; }

		}
		else
			if (search->s_right) search = search->s_right;
			else { addNode(temp, &search->s_right); break; }
	}
}

int delKey(int key) {

	sheet *node, *node_rod;
	node = search(key, headTree);

	node_rod = search_rod(node->key, headTree);
	if (!node->s_left) {
		if ((node_rod->s_left)->key == node->key)
		node_rod->s_left = node->s_right;
		else node_rod->s_right = node->s_right;
		return 1;
	}

	if (!node->s_right) {
		if ((node_rod->s_left)->key == node->key)
		node_rod->s_left = node->s_left;
		else node_rod->s_right = node->s_left;
		return 1;
	}

	search_left(node->s_right)->s_left = (node->s_left)->s_right;
	(node->s_left)->s_right = node->s_right;
	if (key == headTree->key) headTree = node->s_left;
	else {
		if ((node_rod->s_left)->key == node->key)
		node_rod->s_left = node->s_left;
		else node_rod->s_right = node->s_left;
	}
	free(node);
}

int balans(node *node) {

	int k, k_p;
	struct _node *temp;

	if (!node) return NULL;

	k = high_p(node->s_right) - high_p(node->s_left);

	if (k > 0) {
		k_p = high_p((node->s_right)->s_right) - high_p((node->s_right)->s_left);
		if (k_p >= 0) {
			temp = node->s_right;
			node->s_right = temp->s_left;
			temp->s_left = node;
			if (headTree->key == node->key) headTree = temp;
		else
		if ((search_rod(node->key, headTree)->s_left)->key == node->key)
				search_rod(node->key, headTree)->s_left = temp;
				else search_rod(node->key, headTree)->s_right = temp;
		}
		else {
			temp = (node->s_right)->s_left;
			(node->s_right)->s_left = temp->s_right;
			temp->s_right = node->s_right;
			node->s_right = temp->s_left;
			temp->s_left = node;
			if (headTree->key == node->key) headTree = temp;
		else
			if ((search_rod(node->key, headTree)->s_left)->key == node->key)
				search_rod(node->key, headTree)->s_left = temp;
				else search_rod(node->key, headTree)->s_right = temp;
		}
	}
	else if (k < 0) {
		k_p = high_p((node->s_left)->s_right) - high_p((node->s_left)->s_left);
		if (k_p < 0) {
			temp = node->s_left;
			node->s_left = temp->s_right;
			temp->s_right = node;
			if (headTree->key == node->key) headTree = temp;
		else 
			if ((search_rod(node->key, headTree)->s_left)->key == node->key)
				search_rod(node->key, headTree)->s_left = temp;
				else search_rod(node->key, headTree)->s_right = temp;
		}
		else {
			temp = (node->s_left)->s_right;
		(node->s_left)->s_right = temp->s_left;
			temp->s_left = node->s_left;
			node->s_left = temp->s_right;
			temp->s_right = node;
			if (headTree->key == node->key) headTree = temp;
		else
			if ((search_rod(node->key, headTree)->s_left)->key == node->key)
				search_rod(node->key, headTree)->s_left = temp;
				else search_rod(node->key, headTree)->s_right = temp;
		}
	}
	else { printf("узел сбалансирован"); getchar(); exit(1); }
}

int balansTree(node *node) {

	while (checkTree(node)) {
		if (node->s_right)
		if (checkTree(node->s_right)) balans(search(checkTree(node->s_right), node->s_right));

		if (node->s_left)
		if (checkTree(node->s_left)) balans(search(checkTree(node->s_left), node->s_left));

		balans(search(checkTree(node), node));
	}
}
