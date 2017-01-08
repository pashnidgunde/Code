#include <iostream>
#include <sstream>

#include "student_info_reader.h"
#include "file_utils.h"

namespace Reader
{
    void StudentInfoReader::readXMLNode(const xml_node<>* student_node)
    {
        std::cout << "----------------------------------------------------------------" << std::endl;
        Config::StudentInformation student;
        for ( const xml_node<>* inner_node = student_node->first_node() ; inner_node ; inner_node =
                inner_node->next_sibling() )
        {
            float weightage = 0.0;
            auto temp = 0.0;
            std::string node_name = inner_node->name();
            if ( node_name == "Name" )
            {
                std::cout << "Weightage calculation for " << inner_node->value() << std::endl;
                student.setStudentName(inner_node->value());
            }
            else if ( node_name == "Assignment")
            {
            	student.addAssignmentMarks(std::stof(inner_node->value()));
                weightage = _calculator.calculate_grade(student.getAssignments(),student.getExams(),student.getExtraCredits()); 
                printIntermediateResults(node_name,student.getAssignments().size(),weightage);
            }
            else if ( node_name == "Exam")
            {
                student.addExamMarks(std::stof(inner_node->value()));
                weightage = _calculator.calculate_grade(student.getAssignments(),student.getExams(),student.getExtraCredits());
                printIntermediateResults(node_name,student.getExams().size(),weightage);
            }

            else if ( node_name == "ExtraCredit")
            {
                student.addExtraCredits();
                weightage = _calculator.calculate_grade(student.getAssignments(),student.getExams(),student.getExtraCredits());
                printIntermediateResults(node_name,student.getExtraCredits(),weightage);
            }
            else
            {
                std::cerr << "Ignoring :: Invalid tag in Input, please correct " << std::endl;
            }

            student.setGrade(weightage);

        }
        
        _students.push_back(student);
    }
   
   	     
    void StudentInfoReader::printIntermediateResults(const std::string& operation, int count, const float& weight)
    {
        std::cout << "After " << operation << " #" << count << " is logged in the system: " << weight << std::endl;
    }

    void StudentInfoReader::read()
    {
        _students.clear();
        if ( Utils::FileUtils::fileExists(_file_name) )
        {
            xml_document<> doc; 
            file<> xmlFile(_file_name.c_str()); 
            doc.parse<0>(xmlFile.data()); 
            xml_node<>* students_node = doc.first_node("Students");

            if ( ! students_node )
            {
                throw std::runtime_error("Students Node not found in input file");
            }
            
            xml_node<>* student_node = students_node->first_node("Student");
            
            if ( ! student_node )
            {
                throw std::runtime_error("Student Node not found under Students node in input file");
            }
      
            // traverse through list of students and calculate weightage

           for ( const xml_node<>* student_node = students_node->first_node() ; 
                 student_node ; 
                 student_node = student_node->next_sibling() )
           {
               try
               {
                    readXMLNode(student_node);
               }
               catch(std::invalid_argument& e)
               {
                   std::stringstream s;
                   s << "Invalid values in input file" << std::endl;
                   throw std::runtime_error(s.str());
               }
            }
        }
    }       

    void StudentInfoReader::print() const
    {
        std::cout << "======================================== "  << std::endl;
        std::cout << "               Grade reports "              << std::endl;
        std::cout << "======================================== "  << std::endl;

        for (Config::StudentInformation student : _students)
        {
            std::cout << "Final grade for " << student.getStudentName() << ":: " << student.getGrade() << std::endl; 
        }
    }
 
}

