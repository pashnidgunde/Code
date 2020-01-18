#include <iostream>
class Tree {
private:
  int _data;
  Tree *_left;
  Tree *_right;

public:
  Tree(const int &elem) : data(elem), left(nullptr), _right(nullptr) {}

  void addLeft(const int &data) { this->_left = new Tree(data); }

  void addRight(const int &data) { this->_right = new Tree(data); }

  Tree *getSubTreeWithMaxSum() {
    int left_sum = 0;
    int right_sum = 0;

    sum_fn(_left, left_sum);
    sum_fn(_right, right_sum);

    return left_sum > right_sum ? left : right;
  }

private:
  void sum_fn(Tree *root, int &sum) {
    sum += this->_data;

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
  t.addLeft(2);
  t.addLeft(3);
  t.addRight(10);
  Tree *max_subtree = t.getSubTreeWithMaxSum();
}
