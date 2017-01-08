
#include <sstream>
#include <iostream>

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

#include "weightage_reader.h"
#include "file_utils.h"

using namespace rapidxml;

namespace Reader
{
    void WeightageReader::read()
    {
        // throws if file not found
        if ( Utils::FileUtils::fileExists(_file_name) )
        {
            xml_document<> doc; 
            file<> xmlFile(_file_name.c_str()); 
            doc.parse<0>(xmlFile.data()); 
            xml_node<>* config_node = doc.first_node("Config");

            if ( ! config_node )
            {
                throw std::runtime_error("Invalid configuration settings");
            }

            try
            {
            	_weightage.setTeacherName(get_node_value(config_node,"Teacher"));
                _weightage.setAssignmentWeightage(std::stof(get_node_value(config_node, "Assignment")));
                _weightage.setExamWeightage(std::stof(get_node_value(config_node, "Exam")));
                _weightage.setExtraCreditPoints(std::stof(get_node_value(config_node, "ExtraCredit")));
            }
            catch (std::invalid_argument& e)
            {
                throw std::runtime_error("Invalid configuration values in Config file" );
            }
        }
    }

    void WeightageReader::print() const
    {
        std::cout << "Config values :: " 
        	<< " Teacher Name ==> " << _weightage.getTeacherName()
            << " Assignment Weightage ==> " << _weightage.getAssignmentWeightage()
            << " Exam Weightage ==> " << _weightage.getExamWeightage()
            << " Extra Credits/Per assignment ==> " << _weightage.getExtraCreditPoints()
            << std::endl;
    }


	const Config::WeightageInfo& WeightageReader::getWeightageInfo()
    {
        return _weightage;
    }

    std::string WeightageReader::get_node_value(xml_node<>* outer_node, const std::string& inner_node)
    {
        xml_node<>* internal_node = outer_node->first_node(inner_node.c_str()); 
        if ( ! internal_node)
        {
            std::stringstream s;
            s << "Node :: " << inner_node << " is not available in Config file" << std::endl;
            throw std::runtime_error(s.str());
        }

        return internal_node->value();
    }

}

