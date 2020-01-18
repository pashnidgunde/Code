/*
 * binary_search_tree.cpp
 *
 *  Created on: 16-Jan-2017
 *      Author: rupa
 */

#include <iostream>

struct Node {
  Node *left;
  Node *right;
  int data;

  Node(int d) : left(nullptr), right(nullptr), data(d) {}
};

class BST {
  Node *root;

  BST() : root(nullptr) {}

  void insertUtils(Node *node, int data) {
    if (node == nullptr) {
      node = new Node(data);
      return;
    }

    if (node->data >= data) {
      insertUtils(root->left, data);
    }
  }

  void insert(int data) { insertUtils(root, data); }
};

int main() {
  BST b;
  b.insert(1);
}
