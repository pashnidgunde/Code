#include <utility>
#include <type_traits>
#include <cstdint>
#include <cassert>

enum Color
{
    RED,
    GREEN,
    BLUE
};

enum Info {
    LIMIT = UINT64_MAX
};

enum class MyColor {
    RED,
    GREEN,
    BLUE
};

int main()
{
    int a = std::to_underlying(Color::RED);
    static_assert(sizeof(a) == sizeof(int));

    auto b = std::to_underlying(Info::LIMIT);
    static_assert(std::is_same_v<decltype(b),uint64_t>);

    auto c = static_cast<std::underlying_type<Info>::type>(LIMIT);
    auto d = static_cast<std::underlying_type_t<Info>>(LIMIT);

    assert(c==d);
}