// std::negate --> Unary function
//
// template <typename T>
// struct negate : public unary_function<T>
// {
//   constexpr T operator()(const T& arg)
//   { retrurn -arg; }
// };

#include <functional>
#include <iostream>

float square(float x) { return x * x ;}

template<typename X, typename UnaryOp1, typename UnaryOp2>
X apply_fg(X x, UnaryOp1 f1, UnaryOp2 f2)
{
    return f1(f2(x));
}


int main()
{
    std::cout << apply_fg(10.2,std::negate<float>(), square) << std::endl;
    return 0;
}