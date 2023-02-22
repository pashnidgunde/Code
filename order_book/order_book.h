#ifndef TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H
#define TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <memory>
#include <cmath>

namespace order_book {

enum class Side {kBid, kOffer};

enum class Action {kNew, kChange, kDelete};

struct OrderUpdate  {
    std::string order_id;
    Side side;
    double price;
    double size;
    Action action;
};

struct PriceLevel {
    double price;
    double size;
    PriceLevel(double p, double s) : price(p), size(s) {}
    bool operator == (const PriceLevel& rhs)
    {
        return std::fabs(this->price - rhs.price) <= std::numeric_limits<double>::epsilon();
    }
    
    void operator += (const PriceLevel& rhs)
    {
        this->size+= rhs.size;
    }

    friend bool operator > (const PriceLevel& lhs, const PriceLevel& rhs)
    {
        return lhs.price > rhs.price;
    }

    friend bool operator < (const PriceLevel& lhs, const PriceLevel& rhs)
    {
        return lhs.price < rhs.price;
    }
};

template<typename T>
struct Node
{
    T data;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;

    Node(T elem) :
        data(std::move(elem))
    {

    }
};

template<typename T, typename C, typename D>
struct LinkedList
{
    void add(T elem)
    {
        auto new_node = std::make_shared<Node<T>>(elem);
        if (!head)
        {
            head = new_node;
            tail = new_node;
            return;
        }
        
        if (comparator(elem,head->data))
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
            return;
        }

        if (comparator(tail->data,elem))
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
            return;
        }

        auto n = head;
        auto p = head;
        while(n)
        {
            if (comparator(elem,n->data))
            {
                new_node->next = n;
                new_node->prev = p;

                p->next = new_node;
                n->prev = new_node;

                break;
            }
            else if (elem == n->data)
            {
                n->data += elem;
                break;
            }
            else
            {
                p = n;
                n = n->next;
            }
        }

        //static_cast<D*>(this)->onAdd(elem,new_node);
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& l)
    {
        auto n = l.head;
        while(n)
        {
            os << n->data;
            n=n->next;
        }

        return os;
    }

    std::vector<T> transform()
    {
        std::vector<T> result;
        auto n = head;
        while(n)
        {
            result.emplace_back(n->data);
            n=n->next;
        }
        return result;
    }

    private:
        C comparator{};
        std::shared_ptr<Node<T>> head;
        std::shared_ptr<Node<T>> tail;
};



template<typename T>
struct OrderBids : public LinkedList<T, std::greater<T>, OrderBids<T>>
{
      


};

template<typename T>
struct OrderOffers : public LinkedList<T, std::less<T>, OrderOffers<T>>
{
    void onAdd(const T& elem, std::shared_ptr<Node<T>> node_ptr)
    {

    }


};


class OrderBook {

public:

    virtual void OnMessage(const OrderUpdate& order_update)
    {
        switch (order_update.action)
        {
            case Action::kNew:
            {
                if (order_update.side == Side::kBid)
                    m_bids.add({order_update.price, order_update.size});
                else
                    m_offers.add({order_update.price, order_update.size});
            }
            break;
            
            case Action::kChange:
                
                break;

            case Action::kDelete:
                
                break;

            default :
                std::runtime_error("Unsupported action");
        }
    }

    virtual std::vector<PriceLevel> Bids()
    {
        return m_bids.transform();
    }

    virtual std::vector<PriceLevel> Offers()
    {
         return m_offers.transform();
    }
    
private:
    OrderBids<PriceLevel> m_bids;
    OrderOffers<PriceLevel> m_offers;

};


}  // namespace order_book

#endif // TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H
