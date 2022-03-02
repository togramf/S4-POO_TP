#include <p6/p6.h>
#include <iostream>
#include "menu.h"

void draw_board(int size, p6::Context& ctx)
{
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            ctx.square(p6::BottomLeftCorner{p6::map(glm::vec2{static_cast<float>(x), static_cast<float>(y)},
                                                    glm::vec2{0.f}, glm::vec2{static_cast<float>(size)},
                                                    glm::vec2{-1.f}, glm::vec2{1.f})},
                       p6::Radius{1.f / static_cast<float>(size)});
        }
    }
}

int main()
{
    // show_menu();
    auto ctx   = p6::Context{{800, 800, "Noughts and Crosses"}};
    ctx.update = [&]() {
        ctx.background({.35f, 0.35f, 0.35f});
        ctx.stroke_weight = 0.01f;
        ctx.stroke        = {.9f, .9f, .9f, .9f};
        ctx.fill          = {0.f, 0.f, 0.f, 0.f};
        draw_board(3, ctx);
    };
    ctx.start();
}