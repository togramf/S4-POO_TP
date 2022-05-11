#include "connect_4.hpp"
#include <iostream>
#include "board.hpp"

enum class Player {
    Red,
    Yellow,
};

std::optional<CellIndex> hovered_cell(const glm::vec2 position, const BoardSize size, const p6::Context& ctx)
{
    CellIndex index;
    position_to_cell_index(position, index, size, ctx);
    if (index._x >= 0 && index._x < size._width && index._y >= 0 && index._y < size._height) {
        return std::make_optional(index);
    }
    return std::nullopt;
}

//Drawing functions
void settings_to_draw_coin(p6::Context& ctx, Player state)
{
    ctx.stroke_weight = 0.01f;
    ctx.stroke        = {.0f, .0f, .0f, 1.f};
    ctx.use_fill      = true;
    if (state == Player::Red)
        ctx.fill = {1.f, .0f, .0f, 1.f};
    else
        ctx.fill = {1.f, 1.f, .0f, 1.f};
}

//FONCTION A REVOIR
void draw_coin(BoardSize size, p6::Context& ctx, glm::vec2 position, Player state)
{
    settings_to_draw_coin(ctx, state);
    ctx.circle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size._width), board_ratio(size) / static_cast<float>(size._height)}},
               p6::Radius{.8f / static_cast<float>(size._height)});
}

template<BoardSize size>
void draw_coins(const Board<size, Player>& board, p6::Context& ctx)
{
    for (int x = 0; x < size._width; ++x) {
        for (int y = 0; y < size._height; ++y) {
            const auto cell = board[{x, y}];
            if (cell.has_value()) {
                draw_coin(size, ctx, cell_index_to_position({x, y}, size), *cell);
            }
        }
    }
}

//Play function
void play_connect_4()
{
    auto                       ctx            = p6::Context{{1200, 800, "Connect 4"}};
    static constexpr BoardSize size           = {7, 6};
    Board<size, Player>        board          = Board<size, Player>{};
    Player                     current_player = Player::Yellow;

    ctx.update = [&]() {
        ctx.background({0.f, 0.f, 0.f});

        //Drawing the board
        draw_board(size, ctx);
        draw_coins(board, ctx);

        //Drawing the hovered cell
        if (hovered_cell(ctx.mouse(), size, ctx).has_value()) {
            if (!board[*hovered_cell(ctx.mouse(), size, ctx)].has_value()) {
                settings_to_draw_board(ctx);
                ctx.fill = {0.50f, 0.35f, 0.35f, 1.f};
                draw_cell(size, ctx, *hovered_cell(ctx.mouse(), size, ctx));
                draw_coin(size, ctx, cell_index_to_position(*hovered_cell(ctx.mouse(), size, ctx), size), current_player);
            }
        }
    };
    ctx.mouse_pressed = [&](auto) {
        CellIndex index;
        position_to_cell_index(ctx.mouse(), index, size, ctx);

        //Drawing the shape on the click
        if (!board[index].has_value()) {
            board[{index._x, index._y}] = current_player;
            current_player              = (current_player == Player::Yellow) ? Player::Red : Player::Yellow;
            // if (is_the_game_finished(board))
            //     ctx.stop();
        }
    };
    ctx.start();
}
