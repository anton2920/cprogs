#include <stdio.h>

#include "tree.h"

main() {
	f = fopen("input.txt", "r");

	build_AVL_Tree();

	node *treeRoot = headTree;

	balansTree(treeRoot);

	print_GVK(treeRoot, 0);

	return 0;
}

void print_GVK(node *root, int level) {

	/* Main part */
	if (root == NULL) {
		return;
	}

	printf("key: %d on level %d\n", root->key, level);

	print_GVK(root->s_left, level + 1);
	print_GVK(root->s_right, level + 1);
}