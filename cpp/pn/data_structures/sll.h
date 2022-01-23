#ifndef PN_DATA_STRUCTURE_SLL_HPP
#define PN_DATA_STRUCTURE_SLL_HPP

#include <iostream>
#include <memory>

namespace pn
{
  namespace ds
  {
    template <class T> 
    struct Node 
    {
      T _data;
      std::shared_ptr<Node> _next;

      Node<T>(const T &data) : 
        _data(data), 
        _next(nullptr) 
      {
      }
    };

    template <class T> 
    class Sll 
    {
      std::shared_ptr<Node<T>> _begin;
      std::shared_ptr<Node<T>> _end;
      size_t _size = 0;

    public:
      void append(const T &data) 
      {
        if (!_end) 
        {
          // first element
          _end.reset(new Node<T>(data));
          _begin = _end;
        } 
        else 
        {
          // next element
          _end->_next.reset(new Node<T>(data));
          _end = _end->_next;
        }
        _size++;
      }

      void print() 
      {
        auto start = _begin;
        while (start != nullptr) 
        {
          std::cout << start->_data << std::endl;
          start = start->_next;
        }
      }

      size_t size() { return _size;}
    };
  }
}

#endif