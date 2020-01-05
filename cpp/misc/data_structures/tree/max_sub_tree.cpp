#include <iostream>
class Tree {
private:
  int _data;
  Tree *_left{nullptr};
  Tree *_right{nullptr};

public:
  Tree(const int &elem) : _data(elem) {}
  void setToLeft(const int &data) {
    if (_left)
      delete _left;

    _left = new Tree(data);
  }
  void setLeftSubTree(Tree *left) {
    if (_left)
      delete _left;
    _left = left;
  }
  void setRightSubTree(Tree *right) {
    if (_right)
      delete _right;
    _right = right;
  }
  void setToRight(const int &data) {
    if (_right)
      delete _right;
    _right = new Tree(data);
  }
  Tree *getSubTreeWithMaxSum() {
    int left_sum = 0;
    int right_sum = 0;
    sum_fn(_left, left_sum);
    sum_fn(_right, right_sum);
    return left_sum > right_sum ? _left : _right;
  }
  ~Tree() {
    if (_left) {
      delete _left;
      _left = nullptr;
    }

    if (_right) {
      delete _right;
      _left = nullptr;
    }
  }

private:
  void sum_fn(Tree *root, int &sum) {
    sum += root->_data;
    if (root->_left != nullptr) {
      sum_fn(root->_left, sum);
    }
    if (root->_right != nullptr) {
      sum_fn(root->_right, sum);
    }
  }
};
int main() {
  Tree t(1);
  Tree t1(2);
  Tree t2(3);

  // All are emplace functions
  t.setLeftSubTree(&t1);
  t1.setLeftSubTree(&t2);
  t.setToRight(4);

  Tree *max_subtree = t.getSubTreeWithMaxSum();

  if (max_subtree == &t1)
    std::cout << "Worked" << std::endl;
}
