#include <iostream>
#include <type_traits>

// possible implementation
// template<bool,typename T>
// struct enable_if
// {
// };

// template<typename T>
// struct enable_if<true,T>
// {
//   using type = T;
// };


// SFINAE --> std::enable_if 
namespace pn
{
  namespace enable_if_function
  {
    /*
    1. enable_if in template declaration is redifinition
    template<class T, typename = typename std::enable_if_t<!std::is_unsigned<T>::value>>
    void doSomething(T x)
    {
      std::cout << "Type is signed" << std::endl;
    }   

    template<class T, typename = typename std::enable_if_t<std::is_unsigned<T>::value>>
    void doSomething(T x)
    {
      std::cout << "Type is unsigned" << std::endl;
    }
    */

    // Enable if is perfectly fine as in fuction argument , second param can be unused
    // the reason is template type for enable_if is different for both functions
    // even thought they both end up giving same type bool
    template<class T>
    void doSomething(T x, typename std::enable_if_t<std::is_unsigned<T>::value,bool> = true)
    {
      std::cout << "Type is signed" << std::endl;
    }   

    template<class T>
    void doSomething(T x, typename std::enable_if_t<!std::is_unsigned<T>::value,bool> = true)
    {
      std::cout << "Type is unsigned" << std::endl;
    }


    // Enable if as return 
    template<class T>
    std::enable_if_t<std::is_unsigned<T>::value,bool>
    doSomethingRet(T x)
    {
      std::cout << "Type is signed" << std::endl;
      return true;
    }   

    // Enable if as return 
    template<class T>
    std::enable_if_t<!std::is_unsigned<T>::value,bool>
    doSomethingRet(T x)
    {
      std::cout << "Type is signed" << std::endl;
      return true;
    }  


  }
}   

namespace pn
{
  namespace enable_if_as_template_argument
  {
    // enable this type if type is int or double
    template<typename T, 
             typename = std::enable_if_t<
                          std::is_same<T,int>::value || std::is_same<T,double>::value
                          //, void
                        >     
    >
    struct sayHello
    {
      sayHello(const T& t) { std::cout << __PRETTY_FUNCTION__ << t << std::endl;}
      //sayHello(std::enable_if_t<!std::is_same<T>::value>) { std::cout << __PRETTY_FUNCTION__ << std::endl;}
      //sayHello(void) { std::cout << "Hello" ; }
    };
  }
}


namespace pn
{
  namespace enable_if_sfinae
  {
    class EnableIfDemo
    {
      public:
        //---------------------------------------------------------------------------------------------------
        // WRONG 
        // enable_if.cpp:111:9: error: 'template<class T, class> pn::enable_if_sfinae::EnableIfDemo::EnableIfDemo(const T&)' 
        // cannot be overloaded with 'template<class T, class> pn::enable_if_sfinae::EnableIfDemo::EnableIfDemo(const T&)'
        // This does not work because the declarations are treated as redeclarations of the same function template 
        // (default template arguments are not accounted for in function template equivalence).
        // template<typename T,
        //          typename = std::enable_if<std::is_same<T,int>::value>
        //         >
        // EnableIfDemo(const T& rhs) { std::cout << "Floating point constructor << std::endl";}
        
        // template<typename T,
        //          typename = std::enable_if<std::is_floating_point<T>::value>
        //         >
        // EnableIfDemo(const T& rhs) { std::cout << "Floating point constructor << std::endl";}
        //---------------------------------------------------------------------------------------------------

        // In both cases cases below ,
        // template <typename T, bool = true>
        // But , argument to enable_if_t are different, unlike above case
        // Substitution failure is not an error
        
        template <typename T,
                  //typename std::enable_if<std::is_same<T,int>::value, bool>::type = true
                  // OR
                  std::enable_if_t<std::is_same<T,int>::value, bool> = true
                 >
        EnableIfDemo(const T& t) 
        {
          static_assert(std::is_same<T,int>::value , "Must be of integer type");
          std::cout << "integer EnableIf" << std::endl;
        }

        template <typename T,
                  //typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true
                  // OR
                  std::enable_if_t<std::is_floating_point<T>::value, bool> = true
                 >
        EnableIfDemo(const T& t) 
        {
          static_assert(std::is_floating_point<T>::value , "Must be of floating point type");
          std::cout << "Floating point EnableIf" << std::endl;
        }
    };
  }
}
     
int main()
{
  int x = 0;
  pn::enable_if_function::doSomething(x);
  unsigned x1=2;
  pn::enable_if_function::doSomething(x1);
  float x2 = 0.0f;
  pn::enable_if_function::doSomething(x2);


  pn::enable_if_as_template_argument::sayHello<int> y(1);
  pn::enable_if_as_template_argument::sayHello<double> y1(2.0);
  //pn::enable_if_class::sayHello<std::string> s("won;t compile"s);

  pn::enable_if_sfinae::EnableIfDemo t(1);
  pn::enable_if_sfinae::EnableIfDemo t1(2.0f);

  return 0;
}