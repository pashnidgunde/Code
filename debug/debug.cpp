#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <fstream>
#include <cassert>
#include <functional>


class Tetris
{
    private:
        int MAX_WIDTH = 10;
        int MAX_HEIGHT = 100;
        std::vector<int> count_at_height = std::vector<int>(MAX_WIDTH,0);
        std::vector<int> height_at_column = std::vector<int>(MAX_HEIGHT,0);
        int max_height = 0;
        std::unordered_map<char,std::function<int(int)>> shape_to_action {
                {'I', std::bind(&Tetris::on_i, this, std::placeholders::_1)},
                {'Q', std::bind(&Tetris::on_q, this, std::placeholders::_1)},
                {'Z', std::bind(&Tetris::on_i, this, std::placeholders::_1)},
                {'S', std::bind(&Tetris::on_i, this, std::placeholders::_1)},
                {'T', std::bind(&Tetris::on_i, this, std::placeholders::_1)},
                {'L', std::bind(&Tetris::on_i, this, std::placeholders::_1)},
                {'J', std::bind(&Tetris::on_i, this, std::placeholders::_1)}};

    public:
        void reset()
        {
            count_at_height = std::vector<int>(MAX_WIDTH,0);
            height_at_column = std::vector<int>(MAX_HEIGHT,0);
            max_height = 0;
        }

        // helper for unit testing
        int get_max_height() const
        {
            return max_height;
        }

        int on_i(int column)
        {
            //std::cout << column << std::endl;
            auto begin = height_at_column.begin() + column;
            auto end = height_at_column.begin() + column + 3;
            int height = *(std::max_element(begin, end));
            std::for_each(begin, end, [](int &n){ n++; });
            count_at_height[height]+=4;
            int new_height = height + 1;
            if (count_at_height[height] == 10) 
            {
                count_at_height[height] = 0;
                new_height --;
            }
            return new_height;
        };

        int on_q(int column)
        {
            //std::cout << column << std::endl;
            auto begin = height_at_column.begin() + column;
            auto end = height_at_column.begin() + column + 1;
            int height = *(std::max_element(begin, end));
            std::for_each(begin, end, [](int &n){ n++; });
            count_at_height[height]+=2;
            count_at_height[height+1]+=2;
            int new_height = height + 2;
            if (count_at_height[height] == 10)
            {
                count_at_height[height] = 0;
                new_height --;
            }
            if (count_at_height[height+1] == 10)
            {
                count_at_height[height+1] = 0;
                new_height --;
            }
            return new_height;
        };


        int process_line(const std::string& line)
        {
            reset();
            for (size_t i=0; i< line.length();)    
            {
                char shape = line[i];
                int column = line[++i] - '0'; 
                //std::cout << shape << ":" << column;
                max_height = std::max(max_height,shape_to_action[shape](column));
                i+=2;
            }
            return max_height;
        }

        // The interface uses vector because its easy to for unit testing
        std::vector<int> process_lines(std::vector<std::string>& lines)
        {
            if (lines.empty()) return std::vector<int>{};
        
            std::vector<int>result;
            for (const auto& line : lines)
            {
                result.push_back(process_line(line));
            }
            return result;
        }
};




int main()
{
    // Unit tests
    // Reset
    {
        Tetris t;
        t.reset();
        assert(t.get_max_height() == 0);
    }


    {
        Tetris t;
        assert(1 == t.process_line("I0"));
        assert(2 == t.process_line("I1,I0"));
        assert(1 == t.process_line("I0,I4"));
        assert(2 == t.process_line("I1,I2"));
    }
}

/*
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage : ./tetris <input.txt>";
        return 1;
    }
   
    std::fstream file;
    file.open(argv[1],std::ios::in);  
    if (!file){
        std::cout << "Failed to open file : " << argv[1];
        return 1;
    }

    std::string line;
    std::vector<std::string> lines;
    while(getline( file, line ))
    {
        lines.push_back(line);
    }

    auto results = process_lines(lines);
    for (const auto result : results)
    {
        std::cout << result << std::endl;
    }
    
    return 0;
}

*/