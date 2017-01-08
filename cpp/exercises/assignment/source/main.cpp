#include<iostream>
#include<stdexcept>

#include "weightage_reader.h"
#include "student_info_reader.h"

int main(int argc,char* argv[])
{
    if ( argc != 3 )
    {
        std::cerr << "Invalid input. Usage :: ./find_grades config_file input_file" 
                  << std::endl;
        exit(1);
    }

    std::cout << "Setup :: Configuration file ==> " << argv[1] 
              << " and Input file ==> " << argv[2] 
              << std::endl;

    try
    {
        Reader::WeightageReader weightage_reader(argv[1]);
        weightage_reader.read();
        weightage_reader.print();
        
        Calculator::GradeCalculator calculator(weightage_reader.getWeightageInfo());
        Reader::StudentInfoReader student_info_reader(argv[2],calculator) ;       
        student_info_reader.read();
        student_info_reader.print();
               
    }
    catch(std::exception const& exception)
    {
        std::cerr << "Exception :: " << exception.what() << std::endl;
    }


}
