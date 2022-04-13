#include "noughts_and_crosses.hpp"
#include <iostream>
#include <optional>

enum class Player {
    Noughts,
    Crosses,
};

struct CellIndex {
    int _x;
    int _y;
};

template<int size>
class Board {
public:
    Board()
        : _state(size * size, std::nullopt)
    {
    }
    std::optional<Player>& operator[](CellIndex index)
    {
        return _state[index._x + size * index._y];
    }

    const std::optional<Player>& operator[](CellIndex index) const
    {
        return _state[index._x + size * index._y];
    }

private:
    std::vector<std::optional<Player>> _state;
};

//Function for the board
template<int size>
bool is_the_board_full(const Board<size>& board)
{
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            if (!board[{x, y}].has_value()) {
                return false;
            }
        }
    }
    return true;
}

//Conversion between positions in the window and cell index
void position_to_cell_index(const glm::vec2 position, CellIndex& cell, const int size, const p6::Context& ctx)
{
    cell._x = static_cast<int>(p6::map(position.x, -ctx.aspect_ratio(), ctx.aspect_ratio(), 0.f, static_cast<float>(size)));
    cell._y = static_cast<int>(p6::map(position.y, -1.f, 1.f, 0.f, static_cast<float>(size)));
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

void settings_to_draw_board(p6::Context& ctx)
{
    ctx.stroke_weight = 0.01f;
    ctx.use_fill      = true;
    ctx.stroke        = {.9f, .9f, .9f, .9f};
    ctx.fill          = {0.35f, 0.35f, 0.35f, 1.f};
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
    settings_to_draw_board(ctx);
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            draw_cell(size, ctx, {x, y});
        }
    }
}

void settings_to_draw_shapes(p6::Context& ctx)
{
    ctx.stroke_weight = 0.1f;
    ctx.use_fill      = false;
    ctx.stroke        = {.0f, .0f, .0f, 1.f};
}

void draw_nought(int size, p6::Context& ctx, glm::vec2 position)
{
    ctx.circle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size), ctx.aspect_ratio() / static_cast<float>(size)}},
               p6::Radius{0.3f});
}

void draw_cross(int size, p6::Context& ctx, glm::vec2 position)
{
    glm::vec2 cell_size = glm::vec2{1.f / static_cast<float>(size), ctx.aspect_ratio() / static_cast<float>(size)};
    ctx.rectangle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size), ctx.aspect_ratio() / static_cast<float>(size)}},
                  p6::Radii{cell_size.x * 0.8f, cell_size.y * 0.2f}, p6::Rotation{0.80_radians});
    ctx.rectangle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size), ctx.aspect_ratio() / static_cast<float>(size)}},
                  p6::Radii{cell_size.x * 0.8f, cell_size.y * 0.2f}, p6::Rotation{-0.80_radians});
}

void draw_shape(int size, p6::Context& ctx, glm::vec2 position, Player state)
{
    settings_to_draw_shapes(ctx);
    if (state == Player::Noughts)
        draw_nought(size, ctx, position);
    else if (state == Player::Crosses) {
        ctx.use_fill = true;
        ctx.fill     = {.0f, .0f, .0f, 1.f};
        draw_cross(size, ctx, position);
    }
}

template<int size>
void draw_noughts_and_crosses(const Board<size>& board, p6::Context& ctx)
{
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            const auto cell = board[{x, y}];
            if (cell.has_value()) {
                draw_shape(size, ctx, cell_index_to_position({x, y}, size, ctx), *cell);
            }
        }
    }
}

void play_noughts_and_crosses()
{
    auto                 ctx            = p6::Context{{800, 800, "Noughts and Crosses"}};
    static constexpr int size           = 3;
    Board<size>          board          = Board<size>{};
    Player               current_player = Player::Crosses;

    ctx.update = [&]() {
        ctx.background({0.f, 0.f, 0.f});

        //Drawing the board
        draw_board(size, ctx);
        draw_noughts_and_crosses(board, ctx);

        //Drawing the hovered cell
        if (cell_hovered(ctx.mouse(), size, ctx).has_value()) {
            if (!board[*cell_hovered(ctx.mouse(), size, ctx)].has_value()) {
                settings_to_draw_board(ctx);
                ctx.fill = {0.50f, 0.35f, 0.35f, 1.f};
                draw_cell(size, ctx, *cell_hovered(ctx.mouse(), size, ctx));
                draw_shape(size, ctx, cell_index_to_position(*cell_hovered(ctx.mouse(), size, ctx), size, ctx), current_player);
            }
        }

        //Drawing the mouse
        draw_mouse(ctx.mouse(), ctx);
    };
    ctx.mouse_moved = [&](auto) {
    };
    ctx.mouse_pressed = [&](auto) {
        CellIndex index;
        position_to_cell_index(ctx.mouse(), index, size, ctx);

        //Drawing the shape on the click
        if (!board[index].has_value()) {
            board[{index._x, index._y}] = current_player;
            current_player              = (current_player == Player::Crosses) ? Player::Noughts : Player::Crosses;
            std::cout << is_the_board_full(board) << std::endl;
        }
    };
    ctx.start();
}