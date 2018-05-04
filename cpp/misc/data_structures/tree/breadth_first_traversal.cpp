

#include <iostream>
#include <list>
#include <vector>

struct Node {
  struct Node *left;
  struct Node *right;
  int data;

  Node(const int &d) : data(d), left(nullptr), right(nullptr) {}
};

void print(Node *node) {
  if (node == NULL) return;

  // now deal with the node
  printf("%d ", node->data);

  // first recur on left subtree
  print(node->left);

  // then recur on right subtree
  print(node->right);
}

int heightOfTree(Node *node) {
  if (node != nullptr) {
    int hl = heightOfTree(node->left);
    int hr = heightOfTree(node->right);

    if (hl > hr) {
      return hl + 1;
    } else {
      return hr + 1;
    }
  }
  return 0;
}

void printLevel(Node *node, int height) {
  if (node == nullptr) return;
  if (height == 1)
    std::cout << node->data << "-->";
  else {
    printLevel(node->left, height - 1);
    printLevel(node->right, height - 1);
  }
}

void level_order_traversal(Node *root, int height) {
  for (int i = 1; i <= height; i++) {
    printLevel(root, i);
  }
}

int main() {
  Node *root = new Node(1);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(5);
  root->right->left = new Node(6);
  root->right->right = new Node(7);

  int height = heightOfTree(root);
  // std::cout << "Height of Tree:: " << height;
  level_order_traversal(root, height);

  return 0;
}
