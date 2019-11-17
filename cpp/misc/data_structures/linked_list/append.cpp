#include <iostream>
#include <memory>

struct Element {
  int _x;
  Element *next;
  Element *last;

  Element() {
    next = nullptr;
    last = nullptr;
  }

  Element(int x) {
    Element();
    _x = x;
  }

  void append(const int &x);
};

/* Traditional append
void Element::append(const int& x)
{
    Element *root = this;
    while (root->next != nullptr)
    {
        root = root->next;
    }
    //auto new_node = std::make_shared<Element>(x);
    Element *new_node = new Element(5);
    root->next = new_node;
}
*/

void Element::append(const int &x) {
  if (last) {
    Element *new_node = new Element(x);
    last->next = new_node;
    last = last->next;
  } else {
    _x = x;
    last = this;
    next = nullptr;
  }
}

void print_elements(Element *head) {
  while (head != nullptr) {
    std::cout << head->_x << " ";
    head = head->next;
  }
}

int main() {
  // This is a old approach to add elements at end
  // Element root(1);
  // root.append(2);
  // print_elements(&root);

  // Add last to hold the last element
  Element e;
  e.append(1);
  e.append(2);
  print_elements(&e);
}
