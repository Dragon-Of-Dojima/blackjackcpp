cmake_minimum_required(VERSION 3.10)
project(blackjack)

set(CMAKE_CXX_STANDARD 17)

add_executable(blackjack
    src/main.cpp
    src/Card.cpp
    src/CardValue.cpp
    src/Hand.cpp
    src/Deck.cpp
)

target_include_directories(blackjack PRIVATE include)