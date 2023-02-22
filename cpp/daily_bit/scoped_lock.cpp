#include <vector>
#include <thread>
#include <mutex>
#include <ranges>
#include <algorithm>
#include <random>
#include <utility>
#include <iostream>

struct Player
{
    Player(const std::string name, uint64_t seed) : _name(name),
        _re(seed)
    {        
    }

    void play(Player* other)
    {
        if (this == other) return;

        std::scoped_lock(this->_mutex, other->_mutex);

        int our = 0;
        int them = 0;

        do
        {
            our = roll();
            them = other->roll();
        } while(our != them);

        if (our > them)
            this->win();
        else
            other->win();

        // lock released
    }

    int roll() { return _dist(_re); }
    void win() { _score++; }
    int score() const { return _score; }
    const std::string& name() const { return _name; }

    std::string _name;
    std::default_random_engine _re;
    std::uniform_int_distribution<int> _dist{1,6};
    std::mutex _mutex;
    int _score = 0;
   
};

int main()
{
    std::vector<std::unique_ptr<Player>> players;
    auto names = {"p1","p2","p3","p4","p5","p6","p7","p8"};

    std::random_device r;
    std::ranges::transform(names.begin(),names.end(), std::back_inserter(players),
        [&](const char *name) 
        {
            return std::make_unique<Player>(name,r());
        });

    std::vector<std::jthread> rounds;
    for (const auto& player : players)
    {
        auto jthread = std::jthread([&player,&players]()
            {
                for (const auto& opponent : players)
                {
                    player->play(opponent.get());
                }
            }   
        );
        rounds.push_back(std::move(jthread));
    }

    rounds.clear(); // join all threads

    std::ranges::sort(players,
        std::greater<int>(),
        [](const auto& player) { return player->score(); });

    //std::sort(players.begin(), 
    //    players.end(), 
    //    [](const auto& player, const auto& player2) { return player->score() > player2->score(); });

    for (const auto&player : players)
    {
        std::cout << player->name() << " : " << player->score() << '\n';
    }

    return 0;;
}