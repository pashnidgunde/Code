#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Utils 
{
    class FileUtils
    {
        public:
        static bool fileExists(const std::string& file_name)
        {
            std::ifstream file_stream(file_name.c_str());
            bool exists = file_stream.good();
            file_stream.close();

            if ( !exists )
            {
                std::stringstream s;
                s << "File : " << file_name << " does not exist." << std::endl;
                throw std::runtime_error(s.str());
            }

            return exists;
        }
    };
}

