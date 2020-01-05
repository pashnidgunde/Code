

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
  if (node == NULL)
    return;

  // now deal with the node
  printf("%d ", node->data);

  // first recur on left subtree
  print(node->left);

  // then recur on right subtree
  print(node->right);
}

std::vector<std::list<int>> nodeLevelList;

int level = 0;
void createList(Node *node, int level) {
  if (node == nullptr) {
    return;
  }

  if (nodeLevelList.size() <= level) {
    nodeLevelList[level].push_back(node->data);
  } else {
    std::list<int> l;
    l.push_back(node->data);
    nodeLevelList.push_back(l);
  }

  std::cout << "Level: " << level << ", Data: " << node->data << std::endl;

  // first recur on left subtree
  createList(node->left, level + 1);

  // then recur on right subtree
  createList(node->right, level + 1);
}

void printList() {
  for (const auto &vec_element : nodeLevelList) {
    for (const auto &list_element : vec_element) {
      std::cout << list_element << " -> ";
    }
    std::cout << std::endl;
  }
}

Node *listptr = nullptr;
Node *startNode = nullptr;

void createListInOrder(Node *root) {
  if (root == nullptr)
    return;

  createListInOrder(root->left);

  if (listptr == nullptr) {
    listptr = root;
  } else {
    listptr->right = root;
    root->left = listptr;
    listptr = root;
  }

  createListInOrder(root->right);
}

void createListPreOrder(Node *root) {
  if (root == nullptr)
    return;

  if (listptr == nullptr) {
    listptr = root;
    startNode = root;
  } else {
    listptr->left = root;
    listptr = root;
  }

  createListPreOrder(root->left);
  createListPreOrder(root->right);
}

void createListPostOrder(Node *root) {
  if (root == nullptr)
    return;

  createListPostOrder(root->left);
  createListPostOrder(root->right);

  if (listptr == nullptr) {
    listptr = root;
    startNode = root;
  } else {
    listptr->left = root;
    listptr = root;
  }
}

void printInList(Node *listptr) {
  while (listptr != nullptr) {
    std::cout << listptr->data << "->";
    listptr = listptr->left;
  }
}

void printPreList(Node *listptr) {
  while (listptr != nullptr) {
    std::cout << listptr->data << "->";
    listptr = listptr->left;
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

  // print(root);
  // createList(root, 0);
  // std::cout << " InOrder List ";
  // createListInOrder(root);
  // printList(listptr);
  std::cout << std::endl;

  std::cout << " PreOrder List ";
  listptr = nullptr;
  createListPreOrder(root);
  printPreList(startNode);

  std::cout << std::endl;

  // printList();

  return 0;
}
