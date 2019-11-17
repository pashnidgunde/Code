#include <iostream>
#include <memory>

template <class T> struct Tree {
  T _data;
  Tree *_left = nullptr;
  Tree *_right = nullptr;

  Tree(const T &data) : _data(data) {}

  void set_data(const T &data) { _data = data; }

  void print() {
    std::cout << _data << " ";

    if (_left)
      _left->print();

    if (_right)
      _right->print();
  }

  void set_left(Tree *left_tree) { _left = left_tree; }

  void set_right(Tree *right_tree) { _right = right_tree; }

  bool is_BST() { return isBST(this); }

private:
  bool validate_left_subtree(Tree *p, T &val) {
    if (!p)
      return true;
    return (p->_data < val && validate_left_subtree(p->_left, val) &&
            validate_left_subtree(p->_right, val));
  }

  bool validate_right_subtree(Tree *p, T &val) {
    if (!p)
      return true;
    return (p->_data > val && validate_right_subtree(p->_left, val) &&
            validate_right_subtree(p->_right, val));
  }

public:
  bool isBST(Tree *p) {
    if (!p)
      return true;
    return validate_left_subtree(p->_left, p->_data) &&
           validate_right_subtree(p->_right, p->_data) && isBST(p->_left) &&
           isBST(p->_right);
  }
};

int main() {
  std::unique_ptr<Tree<int>> root(new Tree<int>(0));
  // root->left =  std::make_unique<Tree<int>(1);  // cpp-14 only
  std::unique_ptr<Tree<int>> l1(new Tree<int>(1));
  root->set_left(l1.get());
  std::unique_ptr<Tree<int>> l2(new Tree<int>(2));
  l1->set_left(l2.get());
  root->print();

  std::cout << std::endl;

  std::cout << root->is_BST() << std::endl; // false
  std::cout << l1->is_BST() << std::endl;   // true
  std::cout << l2->is_BST() << std::endl;   // false
  std::cout << "---------------------------" << std::endl;

  std::unique_ptr<Tree<int>> root1(new Tree<int>(1));
  // root->left =  std::make_unique<Tree<int>(1);  // cpp-14 only
  std::unique_ptr<Tree<int>> l11(new Tree<int>(0));
  root1->set_left(l11.get());
  std::unique_ptr<Tree<int>> l21(new Tree<int>(2));
  root1->set_right(l21.get());
  root1->print();

  std::cout << std::endl;
  std::cout << root1->is_BST() << std::endl; // true
  std::cout << l11->is_BST() << std::endl;   // true
  std::cout << l21->is_BST() << std::endl;   // true

  return 0;
}
