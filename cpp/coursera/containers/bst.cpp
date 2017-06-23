#include <iostream>
#include <memory>

template <typename T> struct Node {
  T data;
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;

  Node(const T &element) : data(element) {}
};

template <typename T> class BST {
public:
  void insert(const T &element) {
    auto node(std::make_unique<Node<T>>(element));
    if (!root) {
      root = std::move(node);
      return;
    }

    Node<T> *curr(root.get());
    Node<T> *prev(nullptr);

    while (curr) {
      prev = curr;
      curr = (element < curr->data) ? (curr->left).get() : (curr->right).get();
    }

    if (prev->data < element)
      prev->right = std::move(node);
    else
      prev->left = std::move(node);
  }

private:
  std::unique_ptr<Node<T>> root;
};

int main() {
  BST<int> t;
  t.insert(1);
  t.insert(2);
  t.insert(3);
}