#include "board.hpp"

float board_ratio(BoardSize size)
{
    return static_cast<float>(size._width) /
           static_cast<float>(size._height);
}

//Conversion between positions in the window and cell index
void position_to_cell_index(const glm::vec2 position, CellIndex& cell, const BoardSize size, const p6::Context& ctx)
{
    cell._x = static_cast<int>(p6::map(position.x, -ctx.aspect_ratio(), ctx.aspect_ratio(), 0.f, static_cast<float>(size._width)));
    cell._y = static_cast<int>(p6::map(position.y, -1.f, 1.f, 0.f, static_cast<float>(size._height)));
}

glm::vec2 cell_index_to_position(const CellIndex& index, const BoardSize size) //const p6::Context& ctx
{
    const auto idx = glm::vec2{static_cast<float>(index._x),
                               static_cast<float>(index._y)};
    return p6::map(idx,
                   glm::vec2{0.f}, glm::vec2{static_cast<float>(size._width), static_cast<float>(size._height)},
                   glm::vec2{-board_ratio(size), -1.f}, glm::vec2{board_ratio(size), 1.f});
    //    glm::vec2{-1.f, -ctx.aspect_ratio()}, glm::vec2{1.f, ctx.aspect_ratio()});
}

//Drawing functions
void settings_to_draw_board(p6::Context& ctx)
{
    ctx.stroke_weight = 0.01f;
    ctx.use_fill      = true;
    ctx.stroke        = {.9f, .9f, .9f, .9f};
    ctx.fill          = {0.35f, 0.35f, 0.35f, 1.f};
}

void draw_cell(const BoardSize size, p6::Context& ctx, const CellIndex index)
{
    ctx.square(p6::BottomLeftCorner{p6::map(glm::vec2{static_cast<float>(index._x), static_cast<float>(index._y)},
                                            glm::vec2{0.f}, glm::vec2{static_cast<float>(size._width), static_cast<float>(size._height)},
                                            glm::vec2{-board_ratio(size), -1.f}, glm::vec2{board_ratio(size), 1.f})},
               p6::Radius{1.f / static_cast<float>(size._height)});
}

void draw_board(const BoardSize size, p6::Context& ctx)
{
    settings_to_draw_board(ctx);
    for (int x = 0; x < size._width; ++x) {
        for (int y = 0; y < size._height; ++y) {
            draw_cell(size, ctx, {x, y});
        }
    }
}