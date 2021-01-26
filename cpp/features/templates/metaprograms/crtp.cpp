// Curiously recurring template pattern
// template ==> Parametric polymorphism

#include <iostream>
#include <string>
#include <vector>

namespace pn
{
    namespace no_crtp
    {
        //Before CRTP 
        //Note repetition of clone , and only difference is type
        struct Shape {
            virtual Shape* clone() = 0;
        };

        struct Rectangle : public Shape{
            Rectangle* clone() override {
                std::cout << "Rectangle clone " << std::endl;
                return new Rectangle();
            }
        };

        struct Circle : public Shape{
            Circle* clone() override {
                std::cout << "Circle clone " << std::endl;
                return new Circle();
            }
        };

        void createSomeShapes()
        {
            Shape *rectangle  = new Rectangle();
            Shape *circle = new Circle();
            std::vector<Shape*> shapes;
            shapes.reserve(10);
            for (size_t i = 0; i < 5;++i)
            {
                shapes.emplace_back(rectangle->clone());
                shapes.emplace_back(circle->clone());
            } 
        }

    }
}
//----------------------------------------------------------
// CRTP
namespace pn
{
    namespace crtp
    {
        struct Shape {
            virtual Shape* clone() = 0;
            virtual ~Shape() = default;
        };

        template<typename T>
        struct ShapeCRTP : public Shape {
            Shape * clone() override {
                 //return static_cast<Shape*>(new T);
                 //return new T(*this);
                 // this => ShapeCRTP ? or Shape ?
                 return new T(*static_cast<T*>(this));
            }
        };

        struct Rectangle : public ShapeCRTP<Rectangle>
        {
            int x = 10;
        };

        struct Circle : public ShapeCRTP<Circle>
        {
            int y;
        };

        void createSomeShapes()
        {
            Rectangle* r = new Rectangle();
            Shape* r1 = r->clone();
            std::cout << dynamic_cast<Rectangle*>(r1)->x;
        }
    }
}





int main()
{
    pn::no_crtp::createSomeShapes();
    pn::crtp::createSomeShapes();
    return 0;
}