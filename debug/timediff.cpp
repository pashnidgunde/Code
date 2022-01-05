#include <iostream>
#include <string>
#include <cassert>
using namespace std;
#include <vector>
#include <sstream>

// Convert time to minutes past midnight
int toMin(int hour, int min, bool pm)
{
    if (hour == 12)
        hour = 0;
    int calc = hour*60 + min;
    if (pm)
        calc += 12*60;
    return calc;
}

int timeDiff(int h1, int h2, int m1, int m2, bool pm1, bool pm2)
{
    int calc1 = toMin(h2, m2, pm2);
    int calc2 = toMin(h1, m1, pm1);
    if (calc2 > calc1)
    {
        return calc2 - calc1;
    }
    return calc1 - calc2;
    
}

void getHrsMins(std::string s, int& h, int& m, bool& pm)
{
    pm = false;

    if (s[s.size()-2] == 'p') 
        pm = true;

    auto pos = (pm) ? s.find('p') : s.find('a');
    auto pos1 = pos;
    auto bt = s.substr(0,pos);
    pos = bt.find(':');
    auto hs = s.substr(0,pos);
    auto ms = s.substr(pos+1,pos);

    //std::cout << "h : " << h << " m  : " << m << std::endl;

    h = std::atoi(hs.c_str());
    m = std::atoi(ms.c_str());
}


string StringChallenge(string str)
{
    //"12:30pm-12:00am"
    std::size_t pos = str.find("-");      // position of "live" in str
    std::string b = str.substr(0,pos);     // get from "live" to the end
    std::string e = str.substr(pos+1);     // get from "live" to the end
    //std::cout << "bs : " << b << " es : " << e << std::endl;
    
    int bh,bm;
    bool bpm;
    getHrsMins(b,bh,bm,bpm);
    
    int eh,em;
    bool epm;
    getHrsMins(e, eh,em, epm);

    auto td = timeDiff(bh,eh,bm,em,bpm,epm);
    std::stringstream ss;
    ss << td;

    std::cout << ss.str() << std::endl;

    return ss.str();
}

int main()
{
    assert(StringChallenge("12:30pm-12:00am") == "690");
    return 0;
}