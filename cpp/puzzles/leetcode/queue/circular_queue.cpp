#include <vector>
#include <iostream>

class MyCircularQueue {
public:
    MyCircularQueue(int k) {
        q.resize(k);
        _k = k;
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        rear =  ((rear+1) % _k);
        q[rear] = value;
        if(front == -1) front = 0;
        return true;        
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else if (front == _k -1) 
        {
            front = 0; 
            return true;
        }
        else 
        {
            front++;
        }
        
        return true;
    }
    
    int Front() {
        return (isEmpty()) ? -1 : q[front];
    }
    
    int Rear() {
        return (isEmpty()) ? -1 : q[rear];
    }
    
    bool isEmpty() {
        return (front == -1 && rear == -1);
    }
    
    bool isFull() {
        return (front == 0 && rear == _k - 1) || (front == rear + 1);
    }
    
    std::vector<int> q;
    int front = -1;
    int rear = -1;
    int _k = 0;
};


int main()
{
    MyCircularQueue* obj = new MyCircularQueue(3);
    std::cout << obj->enQueue(6) << std::endl;
    std::cout << obj->Rear() << std::endl;
    std::cout << obj->Rear() << std::endl;
    std::cout << obj->deQueue() << std::endl;
    std::cout << obj->enQueue(5) << std::endl;
    // std::cout << obj->deQueue() << std::endl;

    return 0;
}

