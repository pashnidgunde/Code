#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <fstream>
#include <cassert>
#include <functional>
#include <cstdint>
#include <bitset>

struct Tetris
{
    uint8_t MAX_WIDTH = 10;
    uint8_t MAX_HEIGHT = 100;
    
    std::vector<std::bitset<10>> _grid = std::vector<std::bitset<10>>(10);
    std::vector<uint8_t> height_at_column = std::vector<uint8_t>(MAX_HEIGHT,0);
    uint8_t _max_height = 0;

    std::unordered_map<char,std::function<uint8_t(uint8_t)>> shape_to_action {
            {'I', std::bind(&Tetris::on_I, this, std::placeholders::_1)},
            {'Q', std::bind(&Tetris::on_Q, this, std::placeholders::_1)},
            {'Z', std::bind(&Tetris::on_Z, this, std::placeholders::_1)},
            // {'S', std::bind(&Tetris::on_S, this, std::placeholders::_1)},
            // {'T', std::bind(&Tetris::on_T, this, std::placeholders::_1)},
            // {'L', std::bind(&Tetris::on_I, this, std::placeholders::_1)},
            {'J', std::bind(&Tetris::on_I, this, std::placeholders::_1)}};

    void reset()
    {
        height_at_column = std::vector<uint8_t>(MAX_HEIGHT,0);
        for(auto& e : _grid) { e.reset(); }
        _max_height = 0;
    }

    void print()
    {
        for(uint8_t j= 0; j <= MAX_WIDTH; j++ )
        {
            std::cout << int(height_at_column[j]) << ",";
        }
        std::cout << std::endl;
        for(uint8_t j= _max_height; j > 0; j-- )
        {
            auto s = _grid[j].to_string();
            std::cout << int(j) << " : ";
            std::reverse(s.begin(), s.end());
            //std::replace(s.begin(),s.end(),'1',(char)254u);
            for (size_t i =0; i<s.size();i++)
            {
                std::cout << ((s[i] == '1') ? "\u25A0" : "\u25A1");
            }
            std::cout << std::endl;
        }
    }


    void adjust_height()
    {
        // if (width_at_height[current_height] == MAX_WIDTH)
        // {
        //     print();
        //     std::for_each(height_at_column.begin(), height_at_column.end(), [&](uint8_t& n){ n--; });
        //     width_at_height[current_height] = 0;
        //     new_height--;
        //     max_height--;
        // }
    }

    void set_bits(uint8_t height, uint8_t column, uint8_t width)
    {
        std::bitset<10> &bs = _grid[height];
        for (uint8_t i=column; i< (column + width); i++)
        {
            bs.set(i);
        }
    }

    uint8_t on_I(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto end = begin + 4;
        uint8_t nh = *(std::max_element(begin, end)) + 1;
        std::for_each(begin, end, [&](uint8_t& n){ n = std::max(n, nh); });
        set_bits(nh,column,4);
        return *(std::max_element(begin, end));
    };

    uint8_t on_Q(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto end = begin + 2;
        uint8_t nh = *(std::max_element(begin, end)) + 2;
        std::for_each(begin, end, [&](uint8_t& n){ n = std::max(n, nh); });
        set_bits(nh,column,2);
        set_bits(nh-1,column,2);
        return *(std::max_element(begin, end));
    };

    uint8_t on_Z(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto mid = begin + 1;
        auto end = mid + 1;
        uint8_t current_height = *(std::max_element(begin, end+1));
        //std::cout << "PN :" << int(current_height) << std::endl;
        if (*end == current_height)
        {
            *begin = std::max(*begin,uint8_t(current_height+2));
            *mid = std::max(*mid, uint8_t(current_height+2));
            *end = std::max(*end, uint8_t(current_height+1));

            set_bits(current_height+2,column,1);
            set_bits(current_height+2,column+1,1);
            set_bits(current_height+1,column+1,1);
            set_bits(current_height+1,column+2,1);
        
            return current_height+2;
        }

        if (*mid == current_height)
        {
            *begin = std::max(*begin,uint8_t(current_height+2));
            *end = std::max(*end, uint8_t(current_height+1));
            *mid = std::max(*mid, uint8_t(current_height+2));
            
            set_bits(current_height+2,column,1);
            set_bits(current_height+2,column+1,1);
            set_bits(current_height+1,column+1,1);
            set_bits(current_height+1,column+2,1);
            return current_height + 2;
        }

        // max at begin
        *begin = std::max(*begin,uint8_t(current_height+1));
        *mid = std::max(*mid, uint8_t(current_height+1));
        *end = std::max(*end, current_height);

        set_bits(current_height+1,column+1,1);
        set_bits(current_height+1,column,1);
        set_bits(current_height,column+1,1);
        set_bits(current_height,column+2,1);                       
        
        return current_height + 1;
    }

    // uint8_t on_S(uint8_t column)
    // {
    //     auto begin = height_at_column.begin() + column;
    //     auto mid = begin + 1;
    //     auto end = mid + 1;
    //     *mid = std::max((*mid) + 2, *mid);
    //     *begin = std::max(*end, *mid - 1);
    //     *end = std::max(*begin, *mid);
            
    //     print();
    //     return  *end;
    // }

    // uint8_t on_T(uint8_t column)
    // {
    //     auto begin = height_at_column.begin() + column;
    //     auto mid = begin + 1;
    //     auto end = mid + 1;
    //     *mid = std::max((*mid) + 2, *mid);
    //     *begin = std::max(*end, *mid - 1);
    //     *end = std::max(*begin, *mid);
            
    //     print();
    //     return  *end;
    // }


    uint8_t process_line(const std::string& line)
    {
        reset();
        for (size_t i=0; i< line.length();)    
        {
            char shape = line[i];
            uint8_t column = line[++i] - '0'; 
            std::cout << shape << int(column) << " : ";
            _max_height = std::max(_max_height,shape_to_action[shape](column));
            i+=2;
            print();
        }
        std::cout << " ----------------" << std::endl;
        return _max_height;
    }

    // The interface uses vector because its easy to for unit testing
    std::vector<uint8_t> process_lines(std::vector<std::string>& lines)
    {
        if (lines.empty()) return std::vector<uint8_t>{};
    
        std::vector<uint8_t>result;
        for (const auto& line : lines)
        {
            result.push_back(process_line(line));
        }
        return result;
    }
};




int main()
{
    // // Unit tests
    // Reset
    {
        Tetris t;
        t.reset();
        assert(t._max_height == 0);
        std::for_each(t._grid.begin(), t._grid.end(), [](const auto &n){ assert(n.none()); });
        std::for_each(t.height_at_column.begin(), t.height_at_column.end(), [](uint8_t &n){ assert(n == 0); }); 
    }

    // I
    {
        Tetris t;
        assert(1 == t.process_line("I0"));
        assert(1 == t.process_line("I0,I4"));
        assert(2 == t.process_line("I1,I0"));
        assert(2 == t.process_line("I1,I3"));
        assert(1 == t.process_line("I1,I6"));
        assert(2 == t.process_line("I1,I4"));
        assert(6 == t.process_line("I1,I2,I3,I4,I5,I6"));
        assert(6 == t.process_line("I1,I2,I3,I4,I5,I6,I1"));
    }

    // Q
    {
        Tetris t;
        assert(2 == t.process_line("Q0"));
        assert(2 == t.process_line("Q0,Q4"));
        assert(4 == t.process_line("Q1,Q0"));
        assert(10 == t.process_line("Q1,Q2,Q3,Q4,Q5"));
        assert(10 == t.process_line("Q1,Q2,Q3,Q4,Q5"));
        assert(10 == t.process_line("Q1,Q2,Q3,Q4,Q5,Q0"));
    }

    // Z
    {
        Tetris t;
        assert(2 == t.process_line("Z0"));
        assert(2 == t.process_line("Z0,Z4"));
        assert(4 == t.process_line("Z1,Z0"));
        assert(6 == t.process_line("Z1,Z2,Z3,Z4,Z5"));
        assert(6 == t.process_line("Z1,Z2,Z3,Z4,Z5,Z0"));

    }

    // // // S
    // // {
    // //     Tetris t;
    // //     assert(2 == t.process_line("S0"));
    // //     assert(2 == t.process_line("S0,S4"));
    // //     assert(3 == t.process_line("S1,S0"));
    // //     assert(10 == t.process_line("S1,S2,S3,S4,S5"));
    // //     assert(10 == t.process_line("S1,S2,S3,S4,S5,S0"));
    // // }

    // // Combinations
    // {
    //      // Tetris t;
    // //     // assert(1 == t.process_line("I0,I4,Q8"));
    //         assert(6 == t.process_line("I1,I2,Z0"));
    //                 assert(4 == t.process_line("I1,I2,Z4"));
    //         assert(4 == t.process_line("I1,I2,Z3"));
            

    // // }

    // // Reductions
    // {
    //     // assert(0 == t.process_line("I0,I4,I0,I4,Q8"));
    //     // assert(0 == t.process_line("Q0,Q2,Q4,Q6,Q8"));
    //     // //t.assert(1 == t.process_line("Z0,Z3,Z5,Z8"));
    // }

    

    

}

/*
uint8_t main(uint8_t argc, char *argv[])
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