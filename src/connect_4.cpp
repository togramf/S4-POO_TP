#include "connect_4.hpp"
#include <iostream>
#include "board.hpp"

enum class Player {
    Red,
    Yellow,
};

// //Play function
void play_connect_4()
{
    auto                       ctx   = p6::Context{{1200, 800, "Connect 4"}};
    static constexpr BoardSize size  = {7, 6};
    Board<size, Player>        board = Board<size, Player>{};
    // Player                     current_player = Player::Red;

    ctx.update = [&]() {
        ctx.background({0.f, 0.f, 0.f});

        //Drawing the board
        draw_board(size, ctx);
    };
    ctx.start();
}
