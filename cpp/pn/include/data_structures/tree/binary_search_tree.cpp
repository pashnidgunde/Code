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

class BinaryTree {
  Node *root;

  BinaryTree() : root(nullptr) {}

  void insert(Node *root, int data) {
    if (root->data < data) {
      if (root->right == nullptr) {
        root->right = new Node(data);
      } else {
        insert(root->right, data);
      }
    } else {
      if (root->left == nullptr) {
        root->left = new Node(data);
      } else {
        insert(root->left, data);
      }
    }
  }

  void insert(int data) {
    if (root == nullptr) {
      root = new Node(data);
    }
    insert(root, data);
  }
};

int main() {
  BinaryTree b;
  b.insert(1);
}
