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
    static constexpr uint8_t MAX_WIDTH = 10;
    static constexpr uint8_t MAX_HEIGHT = 100;
    
    std::vector<std::bitset<10>> _grid = std::vector<std::bitset<MAX_WIDTH>>(MAX_HEIGHT);
    std::vector<uint8_t> height_at_column = std::vector<uint8_t>(MAX_HEIGHT,0);
    std::vector<uint8_t> width_at_height = std::vector<uint8_t>(MAX_HEIGHT,0);
    uint8_t _max_height = 0;

    std::unordered_map<char,std::function<uint8_t(uint8_t)>> shape_to_action {
            {'I', std::bind(&Tetris::on_I, this, std::placeholders::_1)},
            {'Q', std::bind(&Tetris::on_Q, this, std::placeholders::_1)},
            {'Z', std::bind(&Tetris::on_Z, this, std::placeholders::_1)},
            {'S', std::bind(&Tetris::on_S, this, std::placeholders::_1)},
            {'T', std::bind(&Tetris::on_T, this, std::placeholders::_1)},
            {'L', std::bind(&Tetris::on_L, this, std::placeholders::_1)},
            {'J', std::bind(&Tetris::on_J, this, std::placeholders::_1)}};

    void reset()
    {
        height_at_column = std::vector<uint8_t>(MAX_HEIGHT,0);
        width_at_height = std::vector<uint8_t>(MAX_WIDTH,0);
        for(auto& e : _grid) { e.reset(); }
        _max_height = 0;
    }

    void print()
    {
        for(uint8_t j= 0; j < MAX_WIDTH; j++ )
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
            for (char ch : s)
            {
                std::cout << ((ch == '1') ? "\u25A0" : "\u25A1");
            }
            std::cout << std::endl;
        }
    }

    void adjust_height()
    {
        uint8_t count = 0;
        uint8_t reduced_count = 0;
        while(count <= 3 && _max_height - count >= 1)
        {
            if (width_at_height[_max_height - count] == MAX_WIDTH)
            {
                width_at_height[_max_height-count] = 0;
                _grid[_max_height-count].reset();
                std::for_each(height_at_column.begin(), height_at_column.end(), [&](uint8_t& n){ n--; });
                reduced_count++;
            }
            count++;
        }
        _max_height -= reduced_count;
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
        uint8_t current_height = *(std::max_element(begin, end));
        std::for_each(begin, end, [&](uint8_t& n){ n = std::max(n, uint8_t(current_height + 1)); });
        width_at_height[current_height+1]+=4;
        set_bits(current_height+1,column,4);
        return current_height + 1;
    };

    uint8_t on_Q(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto end = begin + 2;
        uint8_t current_height = *(std::max_element(begin, end));
        std::for_each(begin, end, [&](uint8_t& n){ n = std::max(n, uint8_t(current_height + 2)); });
        set_bits(current_height+1,column,2);
        set_bits(current_height+2,column,2);
        width_at_height[current_height+1]+=2;
        width_at_height[current_height+2]+=2;
        return current_height+2;
    };

    uint8_t on_Z(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto mid = begin + 1;
        auto end = mid + 1;
        uint8_t current_height = *(std::max_element(begin, end+1));
        if (*end == current_height || *mid == current_height)
        {
            *begin = std::max(*begin,uint8_t(current_height+2));
            *mid = std::max(*mid, uint8_t(current_height+2));
            *end = std::max(*end, uint8_t(current_height+1));

            set_bits(current_height+2,column,1);
            set_bits(current_height+2,column+1,1);
            set_bits(current_height+1,column+1,1);
            set_bits(current_height+1,column+2,1);
        
            width_at_height[current_height+1]+=2;
            width_at_height[current_height+2]+=2;

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
        
        width_at_height[current_height]+=2;
        width_at_height[current_height+1]+=2;
        
        return current_height + 1;
    }

    uint8_t on_S(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto mid = begin + 1;
        auto end = mid + 1;
        uint8_t current_height = *(std::max_element(begin, end+1));

        // current max at begin
        if (*begin == current_height || *mid == current_height)
        {
            *begin = std::max(*begin, uint8_t(current_height+1));
            *mid = std::max(*mid, uint8_t(current_height+2));
            *end = std::max(*end,uint8_t(current_height+2));
                        
            set_bits(current_height+1,column,1);
            set_bits(current_height+1,column+1,1);
            set_bits(current_height+2,column+1,1);
            set_bits(current_height+2,column+2,1);

            width_at_height[current_height+1]+=2;
            width_at_height[current_height+2]+=2;

            return current_height+2;
        }
        
        // max at end
        *begin = std::max(*begin, uint8_t(current_height));
        *mid = std::max(*mid, uint8_t(current_height+1));
        *end = std::max(*end,uint8_t(current_height+1));

        set_bits(current_height,column,1);
        set_bits(current_height,column+1,1);
        set_bits(current_height+1,column+1,1);
        set_bits(current_height+1,column+2,1);

        width_at_height[current_height]+=2;
        width_at_height[current_height+1]+=2;

        return current_height+1;
        
    }

    uint8_t on_T(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto mid = begin + 1;
        auto end = mid + 1;
        uint8_t current_height = *(std::max_element(begin, end+1));

        if (*mid == current_height)
        {
            *begin = std::max(*begin, uint8_t(current_height+2));
            *mid = std::max(*mid, uint8_t(current_height+2));
            *end = std::max(*end,uint8_t(current_height+2));

            set_bits(current_height+2,column,1);
            set_bits(current_height+2,column+1,1);
            set_bits(current_height+1,column+1,1);
            set_bits(current_height+2,column+2,1);

            width_at_height[current_height+2]+=3;
            width_at_height[current_height+1]+=1;
        
            return current_height+2;
        }

        // current max at begin
        
        *begin = std::max(*begin, uint8_t(current_height+1));
        *mid = std::max(*mid, uint8_t(current_height+1));
        *end = std::max(*end,uint8_t(current_height+1));
                    
        set_bits(current_height+1,column,1);
        set_bits(current_height+1,column+1,1);
        set_bits(current_height+1,column+2,1);
        set_bits(current_height,column+1,1);

        width_at_height[current_height+1]+=3;
        width_at_height[current_height]+=1;

        return current_height+1;
    
    }

    uint8_t on_L(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto end = begin + 1;
        uint8_t current_height = *(std::max_element(begin, end+1));

        *begin = std::max(*begin, uint8_t(current_height+3));
        *end = std::max(*end, uint8_t(current_height+1));

        set_bits(current_height+1,column,1);
        set_bits(current_height+1,column+1,1);
        set_bits(current_height+2,column,1);
        set_bits(current_height+3,column,1);
        
        width_at_height[current_height+1]+=2;
        width_at_height[current_height+2]+=1;
        width_at_height[current_height+3]+=1;
    
        return current_height+3;
    }

    uint8_t on_J(uint8_t column)
    {
        auto begin = height_at_column.begin() + column;
        auto end = begin + 1;
        uint8_t current_height = *(std::max_element(begin, end+1));

        *begin = std::max(*begin, uint8_t(current_height+1));
        *end = std::max(*end, uint8_t(current_height+3));

        set_bits(current_height+1,column+1,1);
        set_bits(current_height+1,column,1);
        set_bits(current_height+2,column+1,1);
        set_bits(current_height+3,column+1,1);
    
        width_at_height[current_height+1]+=2;
        width_at_height[current_height+2]+=1;
        width_at_height[current_height+3]+=1;
        
        return current_height+3;
    }

    uint8_t process_line(const std::string& line)
    {
        reset();
        for (size_t i=0; i< line.length();)    
        {
            char shape = line[i];
            uint8_t column = line[++i] - '0'; 
            std::cout << shape << int(column) << " : ";
            _max_height = std::max(_max_height, shape_to_action[shape](column));
            adjust_height();
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

    // S
    {
        Tetris t;
        assert(2 == t.process_line("S0"));
        assert(2 == t.process_line("S0,S4"));
        assert(3 == t.process_line("S1,S0"));
        assert(10 == t.process_line("S1,S2,S3,S4,S5"));
        assert(10 == t.process_line("S1,S2,S3,S4,S5,S0"));
    }

    // T
    {
        Tetris t;
        assert(2 == t.process_line("T0"));
        assert(2 == t.process_line("T0,T3"));
        assert(3 == t.process_line("T0,T2"));
        assert(5 == t.process_line("T0,T2,T3"));
        assert(10 == t.process_line("T1,T2,T3,T4,T5"));
        assert(10 == t.process_line("T1,T2,T3,T4,T5,T0"));
    }

    // L
    {
        Tetris t;
        assert(3 == t.process_line("L0"));
        assert(4 == t.process_line("L0,L1"));
        assert(3 == t.process_line("L0,L2"));
        assert(4 == t.process_line("L0,L2,T0"));
        assert(6 == t.process_line("L0,L2,L2"));
    }

    // J
    {
        Tetris t;
        assert(3 == t.process_line("J0"));
        assert(6 == t.process_line("J0,J1"));
        assert(3 == t.process_line("J0,J2"));
        assert(4 == t.process_line("J0,J2,T1"));
        assert(6 == t.process_line("J0,J2,J2"));
    }

    // Combinations
    {
        Tetris t;
        assert(6 == t.process_line("T0,T2,T3,Q6,Q6,Q6"));
        assert(7 == t.process_line("T0,T2,T3,Q6,Q6,Q6,T4"));
        assert(1 == t.process_line("I0,I4,Q8"));
        assert(4 == t.process_line("I1,I2,Z0"));
        assert(4 == t.process_line("I1,I2,Z4"));
        assert(4 == t.process_line("I1,I2,Z3"));
        assert(4 == t.process_line("T1,Z3,I4"));
    }

    // Reductions
    {
        Tetris t;
        assert(0 == t.process_line("I0,I4,I0,I4,Q8"));
        assert(0 == t.process_line("Q0,Q2,Q4,Q6,Q8"));
    }


    // Examples from exercise
    {
        Tetris t;
        assert(4 == t.process_line("T1,Z3,I4"));
        assert(3 == t.process_line("Q0,I2,I6,I0,I6,I6,Q2,Q4"));
    }

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