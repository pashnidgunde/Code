#include <iostream>
#include <vector>

struct Node {
  int data;
  Node *next;

  Node(int d) : data(d), next(nullptr) {}
};

// 1->2->3->4->|

// b = 1 n = 2 p = null
// p = 1, b = 2, b->n = 1 , n = 3
// p = 2 ,

class LinkedList {
  Node *begin;
  Node *end;

 public:
  LinkedList() : begin(nullptr), end(nullptr) {}

  void reverse() {
    Node *b = begin;
    Node *n = nullptr;
    Node *p = nullptr;
    end = b;
    while (b != nullptr) {
      n = b->next;
      b->next = p;
      p = b;
      b = n;
    }

    begin = p;
  }

  void append(const std::vector<int> &v) {
    for (const auto &element : v) {
      Node *newNode = new Node(element);

      if (nullptr == end) {
        begin = newNode;
        end = newNode;
      } else {
        end->next = newNode;
        end = end->next;
      }
    }
  }

  void print() {
    Node *b = begin;
    while (b != nullptr) {
      std::cout << b->data << " --> ";
      b = b->next;
    }
    std::cout << std::endl;
  }

  void middle() {
    Node *b = begin;
    Node *m = b;

    if (b != nullptr) {
      while (b && b->next) {
        m = m->next;
        b = b->next->next;
      }
    }

    std::cout << "Mid ::" << m->data << std::endl;
  }

  void del(int data) {
    if (begin != nullptr) {
      Node *b = begin->next;

      if (begin->data == data) {
        delete begin;
        begin = b;
      } else {
        Node *p = begin;
        while (b != nullptr) {
          if (b->data == data) {
            p->next = b->next;
            delete b;
          }
          p = p->next;
          b = b->next;
        }
      }
    }
  }
};

int main() {
  LinkedList l;
  std::vector<int> v{1, 2, 3, 4, 5};
  l.append(v);
  l.del(1);
  l.print();
  l.del(5);
  l.print();
  l.middle();
  l.reverse();
  l.print();
  std::vector<int> v1{6, 7, 8, 9, 10};
  l.append(v1);
  l.print();
  l.reverse();
  l.print();
}
