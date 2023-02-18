#ifndef TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H
#define TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <memory>



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

};

struct Node
{
    PriceLevel l;
    std::unique_ptr<Node> next;
    std::unique_ptr<Node> prv;

    Node(PriceLevel pl) :
        l(std::move(pl))
    {}
        
};

template<typename T>
struct LinkedList
{

};


class OrderBook {

private:

    template<typename Op>
    void insert(std::unique_ptr<Node>& rr, PriceLevel pl, Op op)
    {
        if (!rr)
        {
            rr = std::make_unique<Node>(pl);
            return;
        } 

        Node *curr = rr.get();
        Node *prv = nullptr;

        while(curr)
        {
            if (pl.price == curr->l.price)
            {
                curr->l.size += pl.size; 
                return;
            }

            if (op(pl.price,curr->l.price))
            {
                break;
            }
            
            prv = curr;
            curr = curr->next.get();
        }

        auto node = std::make_unique<Node>(pl);
        node->next.reset(curr);
        node->prv = std::move(curr->prv);
        if (prv)
        {
            prv->next = std::move(node);
        }
    }

    void insert_bid(std::unique_ptr<Node>& rr, PriceLevel pl)
    {
        insert(m_bids,pl,std::greater<int>());
    }

    void insert_offer(std::unique_ptr<Node>& rr, PriceLevel pl)
    {
        insert(m_bids,pl,std::less<int>());
    }

private:
    void onNewOrder(const OrderUpdate& order_update)
    {
        auto pl = PriceLevel(order_update.price, order_update.size);
        if (Side::kBid == order_update.side)
            insert_bid(m_bids,pl);
        else
            insert_offer(m_offers,pl);
    }
    void onUpdate(const OrderUpdate& order_update)
    {

    }
    void onDelete(const OrderUpdate& order_update)
    {

    }
    

public:

    virtual void OnMessage(const OrderUpdate& order_update)
    {
        switch (order_update.action)
        {
            case Action::kNew:
                onNewOrder(order_update);
                break;
            
            case Action::kChange:
                onUpdate(order_update);
                break;

            case Action::kDelete:
                onDelete(order_update);
                break;

            default :
                std::runtime_error("Unsupported action");
        }
    }

    std::vector<PriceLevel> priceLevels(Node * root)
    {
        std::vector<PriceLevel> r;
        while(root)
        {
            r.emplace_back(root->l);
            root = root->next.get();
        }
        return r;
    }

    virtual std::vector<PriceLevel> Bids()
    {
        return priceLevels(m_bids.get());
    }
    virtual std::vector<PriceLevel> Offers()
    {
        return priceLevels(m_offers.get());
    }
    
private:
    std::unique_ptr<Node> m_bids;
    std::unique_ptr<Node> m_offers;

};


}  // namespace order_book

#endif // TALOS__CODING_INTERVIEW__CPP__ORDER_BOOK__ORDER_BOOK_H
