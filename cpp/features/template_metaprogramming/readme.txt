# to print call stack 
std::cout << __PRETTY_FUNCTION__ << std::endl;

# to check compiler memory usage and compile time of templated code
time g++ ...

# for optimizations -03 / -O0

# for checking call stack
# nm ./a.out | c++filt | less

# -------------------
g++ -fdump-rtl-all c++file --> dump each compiler Step

#-------------------
sfinae :

1. During template instantiation, the compiler will
    1. Obtain ( figure out ) the template arguments by
        i. Taken verbatim if explicitly supplied at templates's point of usage
        ii. Else deduced from function arguments at point of call --> for function templates
        iii. Else taken from the declaration's default template arguments
    2. Replace each template parameter throught the template by its corresponding template arguments
    3. Step 2 succeeds
    4. If ill formed code, substitution has failed and is silently discarded and is not an error

Questions:

1. std::rank how does it work
2. 