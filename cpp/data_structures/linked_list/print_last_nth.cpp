#include <iostream>

struct Element
{
    int _x;
    Element *next;
    
    Element(int x)
    {
        next = nullptr;
        _x=x;
    }

    void append ( int& x);

};

void Element::append(const int& x)
{
    Element *new_node = std::make_shared<int>(new int(x));
    Element *root = this;
    while (root->next != nullptr)
    {
        root = root->next;     
    }
   
    root->next = new_node;
}


void read_elements(int num_of_elem,Element** head)
{
    std::cout << "Please enter elements : " << std::endl;

    Element *last = *head;
    
    int x;
    for(int i = 0; i<num_of_elem; i++)
    {
       std::cin >> x;
       Element *e = new Element(x);
       if ( *head == nullptr )
       {
           *head = e;
           last = e;
           continue;
       }
        
       last->next = e;
       last = e;
    }
}

void print_elements(Element* head)
{
    while ( head != nullptr )
    {
        std::cout << head->_x << " ";
        head = head->next;
    }
}

void print_last_nth(int x,Element *head)
{
    Element *h = head;
    int count = 0;
    while ( head != nullptr )
    {
        count++;
        head = head->next;
    }

    if ( count < x )
    {
        std::cerr << "Total number of elements are less than the number requested" << std::endl;
        return;
    }

    int index = 0;
    while ( index < (count - x ) )
    {
        h = h->next;
        index++;
    }

    std::cout << "Nth element from last is " << h->_x << std::endl;
}

void print_last_nth_iterate_once(int x, Element* head)
{
   int count = 0;
   Element* main_ptr = head;
   Element* ref_ptr = head;

   while ( count < x )
   {
        if ( ref_ptr == nullptr )
        {
            std::cerr << "Total number of elements are less than the number requested" << std::endl;
            return;
        }
        count++;
        ref_ptr = ref_ptr->next;
   }

   while ( ref_ptr != nullptr )
   {
       ref_ptr = ref_ptr->next;
       main_ptr = main_ptr->next;
   }

    std::cout << "Nth element from last is " << main_ptr->_x << std::endl;
}

/*
int main()
{
    int num_of_elem;
    std::cout << "How many elements do you want to enter: ";
    std::cin >> num_of_elem;

    if ( num_of_elem < 0 )
    {
        std::cerr << "Please enter valid number : " << std::endl;
        return 1;
    }
    
    Element *head = nullptr;
    read_elements(num_of_elem,&head);
    print_elements(head);

    int x;
    std::cout << "Which element from last do you want to print ? " << std::endl;
    std::cin >> x;
    print_last_nth(x,head);
    print_last_nth_iterate_once(x,head);

    return 0;
}

*/


int main()
{
    Element root(1);
    root.append(2); 
}
