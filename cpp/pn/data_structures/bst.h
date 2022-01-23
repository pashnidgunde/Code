#ifndef PN_DATA_STRUCTURE_BST_HPP
#define PN_DATA_STRUCTURE_BST_HPP

#include <memory>

namespace pn
{
    namespace ds
    {
        template<typename T>
        struct Node 
        {
            std::unique_ptr<Node> _left;
            std::unique_ptr<Node> _right;
            T _element;
            Node(T element) : _element(element) {}
        };

        template<typename T>
        class Bst
        {
            private:
                std::unique_ptr<Node<T>> _root;
                size_t _size = 0;

            public: 
                Bst()=default;
                void insert(T element)
                {
                    if(!_root)
                    {
                        _root = std::make_unique<Node<T>>(element);
                        _size++;
                        return;
                    }

                    auto node = _root.get();
                    auto parent = _root.get();
                    //while(node && element < node->_element) { parent = node; node = node->_left; }
                    //while(node && element > node->_element) { parent = node; node = node->_right; }
                    while(node)
                    {
                        parent = node;
                        node = (element < node->_element) ? 
                            node->_left.get() : 
                            node->_right.get() ;
                    }
                    if (element > parent->_element) parent->_right = std::make_unique<Node<T>>(element);
                    if (element < parent->_element) parent->_left = std::make_unique<Node<T>>(element);
                    _size++;
                }

                size_t size() const { return _size; };
                bool find(T elem);
                bool empty() const { return size==0; }
        };
    }
}


#endif