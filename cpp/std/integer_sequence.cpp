//https://en.cppreference.com/w/cpp/utility/integer_sequence

#include<iostream>
#include <utility>
#include <tuple>
#include <array>

template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '),...);
    std::cout << '\n';
}

// Below is an error 
// a template argument list is not allowed in a declaration of a primary templateC/C++(840)
//template<typename T, T... indexes>
//struct SequencePrinter<T,T... indexes>
//{
//
//};

// Therefore, first create a generic template
template<typename>
struct SequencePrinter;

// Now specialize
template<typename T, T... indexes>
struct SequencePrinter<std::integer_sequence<T, indexes...>>
{
    void print()

};


// // specialized template
// template<typename T, T... index>
// struct SequencePrinter<std::integer_sequence<T,index...>>
// {
//     void print()
//     {
//         ((std::cout << index),...);
//     }
// };


int main()
{
    print_sequence(std::make_integer_sequence<int,10>{});
    print_sequence(std::make_index_sequence<10>{});
    print_sequence(std::integer_sequence<int,9,8,7,6,5>{});

    SequencePrinter<std::integer_sequence<int,9,8,7,6,5>> seq;
    seq.print();


    return 0;
}