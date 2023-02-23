#ifndef TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H
#define TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <memory>
#include <cmath>
#include <unordered_map>

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

template<typename T>
struct OrderPool
{
    OrderPool(size_t size)
    {
        front = std::make_shared<T>();
        last = front;
        for (size_t i=0; i< size; i++)
        {
            auto node = std::make_shared<T>();
            attachToEnd(node);
        }
    }

    std::shared_ptr<Node<T>>& front()
    {
        auto r = first;
        first = first->next;
        return r;
    }

    void attachToEnd(const std::shared_ptr<Node<T>>& node)
    {
        last->next = node;
        last = node;
    }

    private : 
        std::shared_ptr<Node<T>> first;
        std::shared_ptr<Node<T>> last;
};

template<typename E, typename T>
std::shared_ptr<Node<T>> fromE(const E& e)
{
    return nullptr;
}

template<>
std::shared_ptr<Node<PriceLevel>> fromE<OrderUpdate,PriceLevel>(const OrderUpdate& order_update)
{
    return std::shared_ptr<Node<PriceLevel>> (new Node<PriceLevel>(PriceLevel{order_update.price,order_update.size}));
    // TO DO
    // Use order pool    
}

template<typename T>
struct Key;

template<>
struct Key<OrderUpdate>
{
    using KeyType = decltype(OrderUpdate::order_id);
    static const KeyType& value(const OrderUpdate& order_update) 
    {
        return order_update.order_id;
    }
};

template<typename E, typename T>
struct LinkMap
{
    public:
        void add(const E& elem, const std::shared_ptr<Node<T>>& node)
        {
            lookup[Key<E>::value(elem)] = node;
        }

        void remove(const E& elem)
        {
            auto & key = Key<E>::value(elem);
            lookup.erase(key);
        }

        std::shared_ptr<Node<T>>& lookUp(const E& elem)
        {
            auto & key = Key<E>::value(elem);
            return lookup[key];
        }

    private:
        using KeyType = typename Key<E>::KeyType;
        std::unordered_map<KeyType, std::shared_ptr<Node<T>>> lookup;
};

template<typename E, typename T, typename C>
struct LinkedHashMap : public LinkMap<E,T>
{
    void add_node(const E& elem)
    {
        auto new_node = fromE<E,T>(elem);
        LinkMap<E,T>::add(elem, new_node);

        if (!head)
        {
            head = new_node;
            tail = new_node;
            return;
        }
        
        if (comparator(new_node->data,head->data))
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
            return;
        }

        if (comparator(tail->data,new_node->data))
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
            if (comparator(new_node->data,n->data))
            {
                new_node->next = n;
                new_node->prev = p;

                p->next = new_node;
                n->prev = new_node;

                break;
            }
            else if (new_node->data == n->data)
            {
                n->data += new_node->data;
                break;
            }
            else
            {
                p = n;
                n = n->next;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedHashMap& l)
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

    void remove_node(const E& elem)
    {
        auto node = LinkMap<E,T>::lookUp(elem);
        LinkMap<E,T>::remove(elem);

        if (!node) return;
        if (!node->prev) 
        {
            head = node->next;
            return;
        }
        
        node->prev->next = node->next;

        if (node->next)
            node->next->prev = node->prev;
     }

    private:
        C comparator{};
        std::shared_ptr<Node<T>> head;
        std::shared_ptr<Node<T>> tail;
};

class OrderBook {

public:

    virtual void OnMessage(const OrderUpdate& order_update)
    {
        switch (order_update.action)
        {
            case Action::kNew:
                if ((order_update.side == Side::kBid))
                    m_bids.add_node(order_update);
                else
                    m_offers.add_node(order_update);
                break;
            
            case Action::kChange:
                if ((order_update.side == Side::kBid))
                {
                    m_bids.remove_node(order_update);
                    m_bids.add_node(order_update);
                }
                else
                {
                    m_offers.remove_node(order_update);
                    m_offers.add_node(order_update);
                }
                break;

            case Action::kDelete:
                if ((order_update.side == Side::kBid))
                {
                    m_bids.remove_node(order_update);
                }
                else
                {
                    m_offers.remove_node(order_update);
                }
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
    LinkedHashMap<OrderUpdate,PriceLevel, std::greater<>> m_bids;
    LinkedHashMap<OrderUpdate,PriceLevel, std::less<>> m_offers;
};


}  // namespace order_book

#endif // TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H
