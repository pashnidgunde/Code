#ifndef __file_reader_h_
#define __file_reader_h_

namespace Reader
{
    class FileReader
    {
        public:
	    virtual ~FileReader()
        {
        }
        virtual void read() = 0;
        virtual void print() const = 0;
    };
}

#endif
