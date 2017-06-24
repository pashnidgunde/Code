#include <iostream>
#include <memory>

template <class T>
struct Node
{
    T _data;
    std::shared_ptr<Node> next;

    Node<T> (const T& data) : _data(data) , next (nullptr)
    {

    }
};




template<class T>
class LinkedList
{
    std::shared_ptr< Node<T> > begin;
    std::shared_ptr< Node<T> > end;

    public:
        void append(const T& data)
        {
            if (!end)
            {
                end.reset(new Node<T>(data));
                begin = end;
            }
            else
            {
                end->next.reset(new Node<T>(data));
                end=end->next;
            }
        }

        LinkedList<T>() : begin(nullptr) , end(nullptr)
        {

        }

        void print()
        {
            std::shared_ptr<Node<T>> start = begin;
            while(start != nullptr)
            {
                std::cout << start->_data << std::endl;
                start=start->next;
            }
            
        }

};








int main()
{

    LinkedList<int> l;
    l.append(0);
    l.append(0);
    l.append(0);
    l.append(0);
    l.append(0);
    l.print();


    return 0;

}