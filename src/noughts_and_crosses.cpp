#include "noughts_and_crosses.hpp"
#include <iostream>
#include <optional>

struct CellIndex {
    int _x;
    int _y;
};

//Conversion between positions in the window and cell index
void print_position_to_cell_index(float x, float y, int size, p6::Context& ctx)
{
    CellIndex cell = {static_cast<int>(p6::map(x, -ctx.aspect_ratio(), ctx.aspect_ratio(), 0.f, static_cast<float>(size))),
                      static_cast<int>(p6::map(y, -1.f, 1.f, 0.f, static_cast<float>(size)))};

    std::cout << "( " << cell._x << " ; " << cell._y << " )\n";
}

void position_to_cell_index(const glm::vec2 position, CellIndex& cell, const int size, const p6::Context& ctx)
{
    cell._x = static_cast<int>(p6::map(position.x, -ctx.aspect_ratio(), ctx.aspect_ratio(), 0.f, static_cast<float>(size)));
    cell._y = static_cast<int>(p6::map(position.y, -1.f, 1.f, 0.f, static_cast<float>(size)));
}

void print_cell_index_to_position(const CellIndex& index, const int size, const p6::Context& ctx)
{
    float x = static_cast<float>(p6::map(static_cast<float>(index._x), 0.f, static_cast<float>(size), -ctx.aspect_ratio(), ctx.aspect_ratio()));
    float y = static_cast<float>(p6::map(static_cast<float>(index._y), 0.f, static_cast<float>(size), -1.f, 1.f));

    std::cout << "( " << x << " ; " << y << " )\n";
}

glm::vec2 cell_index_to_position(const CellIndex& index, const int size, const p6::Context& ctx)
{
    const auto idx = glm::vec2{static_cast<float>(index._x),
                               static_cast<float>(index._y)};
    return p6::map(idx,
                   glm::vec2{0.f}, glm::vec2{static_cast<float>(size)},
                   glm::vec2{-1.f, -ctx.aspect_ratio()}, glm::vec2{1.f, ctx.aspect_ratio()});
}

std::optional<CellIndex> cell_hovered(const glm::vec2 position, const int size, const p6::Context& ctx)
{
    CellIndex index;
    position_to_cell_index(position, index, size, ctx);
    if (index._x >= 0 && index._x < size && index._y >= 0 && index._y < size) {
        return std::make_optional(index);
    }
    return std::nullopt;
}

//Drawing functions
void draw_mouse(glm::vec2 position, p6::Context& ctx)
{
    ctx.use_fill = false;
    ctx.stroke   = {.9f, .9f, .9f, .9f};
    ctx.circle(p6::Center{position}, p6::Radius{0.05f});
}

void draw_cell(const int size, p6::Context& ctx, const CellIndex index)
{
    ctx.square(p6::BottomLeftCorner{p6::map(glm::vec2{static_cast<float>(index._x), static_cast<float>(index._y)},
                                            glm::vec2{0.f}, glm::vec2{static_cast<float>(size)},
                                            glm::vec2{-1.f}, glm::vec2{1.f})},
               p6::Radius{1.f / static_cast<float>(size)});
}

void draw_board(const int size, p6::Context& ctx)
{
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            draw_cell(size, ctx, {x, y});
        }
    }
}

void draw_noughts(int size, p6::Context& ctx, CellIndex index)
{
    ctx.stroke_weight  = 0.1f;
    ctx.use_fill       = false;
    ctx.stroke         = {.0f, .0f, .0f, 1.f};
    glm::vec2 position = cell_index_to_position(index, size, ctx);
    ctx.circle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size), ctx.aspect_ratio() / static_cast<float>(size)}},
               p6::Radius{0.3f});
    // (p6::Center = {{{(0.0F)}, {(0.0F)}}}, p6::Radius = {(1.0F)})
}

void draw_crosses(int size, p6::Context& ctx, CellIndex index)
{
    ctx.stroke_weight   = 0.1f;
    ctx.use_fill        = false;
    ctx.stroke          = {.0f, .0f, .0f, 1.f};
    glm::vec2 position  = cell_index_to_position(index, size, ctx);
    glm::vec2 cell_size = glm::vec2{1.f / static_cast<float>(size), ctx.aspect_ratio() / static_cast<float>(size)};
    ctx.rectangle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size), ctx.aspect_ratio() / static_cast<float>(size)}},
                  p6::Radii{cell_size.x * 0.8f, cell_size.y * 0.2f}, p6::Rotation{0.80_radians});
    ctx.rectangle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size), ctx.aspect_ratio() / static_cast<float>(size)}},
                  p6::Radii{cell_size.x * 0.8f, cell_size.y * 0.2f}, p6::Rotation{-0.80_radians});
}

void play_noughts_and_crosses()
{
    auto ctx = p6::Context{{800, 800, "Noughts and Crosses"}};
    // auto canvas             = p6::Canvas{ctx.framebuffer_size()};
    // ctx.framebuffer_resized = [&]() {
    //     canvas.resize(ctx.framebuffer_size()); // Make sure that the canvas still has the same size as the window's framebuffer even after it resizes
    // };
    static constexpr int size = 3;
    ctx.update                = [&]() {
        ctx.background({0.f, 0.f, 0.f});
        //Drawing the board
        ctx.stroke_weight = 0.01f;
        ctx.use_fill      = true;
        ctx.stroke        = {.9f, .9f, .9f, .9f};
        ctx.fill          = {0.35f, 0.35f, 0.35f, 1.f};
        draw_board(size, ctx);

        //Drawing the hovered cell
        if (cell_hovered(ctx.mouse(), size, ctx).has_value()) {
            ctx.fill = {0.9f, 0.35f, 0.35f, 1.f};
            draw_cell(size, ctx, *cell_hovered(ctx.mouse(), size, ctx));
            draw_crosses(size, ctx, *cell_hovered(ctx.mouse(), size, ctx));
        }
        //Drawing the mouse
        draw_mouse(ctx.mouse(), ctx);

        // ctx.image(canvas);
    };
    ctx.mouse_moved = [&](auto) {
    };
    ctx.mouse_pressed = [&](auto) {

    };
    ctx.start();
}