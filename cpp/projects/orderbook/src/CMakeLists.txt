project (OrderBook)

add_definitions(-std=c++11)
set(HEADER_FIELS OrderBook.h)
set(SOURCE_FILES OrderBook.cpp)


add_library(OrderBook STATIC ${SHOURCE_FILES} )