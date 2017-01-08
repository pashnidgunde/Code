#ifndef __student_info_reader_h
#define __student_info_reader_h

#include <list>

#include "file_reader.h"
#include "student_information.h"
#include "grade_calculator.h"

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
using namespace rapidxml;

namespace Reader
{
    class StudentInfoReader : public FileReader
    {
        public:
	        StudentInfoReader ( const std::string& file_name, Calculator::GradeCalculator& calc ) 
					: _file_name(file_name) ,
					  _calculator(calc)
	        {
	        }
	
	        
	        virtual void read();
	        virtual void print() const;
	        
        private:
	        std::list<Config::StudentInformation> _students;
	        Calculator::GradeCalculator& _calculator;
            std::string _file_name;
	
	        void readXMLNode(const xml_node<>* student_node);
	        void printIntermediateResults(const std::string& operation, int count, const float& weight);
          
 	};
}

#endif
