#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <exception>
#include <inttypes.h>
#include <cassert>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <iostream>


class MemoryMappedFile
{
    private:

        char * m_buffer = nullptr;
        int m_offset = 0;
        long m_size = 0;

        template<typename T>
        T read()
        {
            assert(m_offset + sizeof(T) <= m_size);
            T temp = *(reinterpret_cast<T *>(m_buffer));
            m_buffer += sizeof(T);
            return temp;
        }

    public :
        MemoryMappedFile(char * buffer, long size, int offset = 0) :
            m_buffer(buffer),
            m_offset(offset),
            m_size(size)
        {        
        }

        MemoryMappedFile() = delete;

        void advance(uint16_t number_of_bytes) { 
            assert(m_offset + number_of_bytes <= m_size);
            m_buffer += number_of_bytes; 
        }
        int offset() const { return m_offset; }
        char * buffer_ptr() { return m_buffer; }

        uint16_t read_2_bytes()
        {
            return read<uint16_t>();
        } 

        uint32_t read_4_bytes()
        {
            return read<uint32_t>();
        }
       
};

class PacketReader
{
    public:
        PacketReader(MemoryMappedFile& mmfile) :
            _mmfile(mmfile)
        {
            
        }
        
        PacketReader() = delete;
        uint16_t packet_identifier() const { return _mmfile.read_2_bytes(); }
        uint32_t packet_length() const { return _mmfile.read_4_bytes();}

    private:
        MemoryMappedFile& _mmfile;
};


class OutchParser
{
    private:
        PacketReader& m_packet_reader;

    public:
        OutchParser(PacketReader& packet_reader) :
            m_packet_reader(packet_reader)
    {
    }
    void parse()
    {

    }
    
};

int main()
{
    int fd = open("./OUCHLMM2.incoming.packets", O_RDONLY, S_IRUSR);
    struct stat sb;
    if (fstat(fd,&sb) == -1)
    {
        std::runtime_error("Couldn't get file size");
    }
    std::cout << "File size is : " << sb.st_size;

    char *file_buffer = (char*) mmap(NULL,sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    MemoryMappedFile mmfile(file_buffer,sb.st_size,0);
    PacketReader outch_packet_reader(mmfile);
    OutchParser op (outch_packet_reader);
    op.parse();

}