#include "noughts_and_crosses.hpp"
#include <iostream>

struct CellIndex {
    int _x;
    int _y;
};

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

void position_to_cell_index(float x, float y, int size, p6::Context& ctx)
{
    CellIndex cell = {static_cast<int>(p6::map(x, -ctx.aspect_ratio(), ctx.aspect_ratio(), 0.f, static_cast<float>(size))),
                      static_cast<int>(p6::map(y, -1.f, 1.f, 0.f, static_cast<float>(size)))};

    std::cout << "( " << cell._x << " ; " << cell._y << " )\n";
}

void play_noughts_and_crosses()
{
    auto ctx = p6::Context{{800, 800, "Noughts and Crosses"}};
    // auto canvas             = p6::Canvas{ctx.framebuffer_size()};
    // ctx.framebuffer_resized = [&]() {
    //     canvas.resize(ctx.framebuffer_size()); // Make sure that the canvas still has the same size as the window's framebuffer even after it resizes
    // };
    int size   = 3;
    ctx.update = [&]() {
        ctx.background({0.f, 0.f, 0.f});
        ctx.stroke_weight = 0.01f;
        ctx.use_fill      = true;
        ctx.stroke        = {.9f, .9f, .9f, .9f};
        ctx.fill          = {0.35f, 0.35f, 0.35f, 1.f};
        draw_board(size, ctx);
        ctx.circle(p6::Center{ctx.mouse()}, p6::Radius{0.05f});
        // ctx.image(canvas);
    };
    ctx.mouse_moved = [&](auto) {
        position_to_cell_index(ctx.mouse().x, ctx.mouse().y, size, ctx);
    };
    ctx.start();
}