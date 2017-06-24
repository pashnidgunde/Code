#ifndef __weightage_reader_h__
#define __weightage_reader_h__

#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"

#include "file_reader.h"
#include "weightage_info.h"

using namespace rapidxml;

namespace Reader
{
    class WeightageReader: public FileReader
    {
        public:

            WeightageReader(const std::string& config_file): 
                _file_name(config_file)
            {
            }

            virtual void read();
            virtual void print() const;
            const Config::WeightageInfo& getWeightageInfo();
        
		private:

            // Values are string by default , read and convert to float
            std::string get_node_value(xml_node<>* outer_node, const std::string& inner_node);
        
        private:
            Config::WeightageInfo _weightage;
            std::string _file_name;
    };

}



#endif
