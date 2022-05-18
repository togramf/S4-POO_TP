#include "noughts_and_crosses.hpp"
#include <iostream>
#include "board.hpp"

enum class Player {
    Noughts,
    Crosses,
};

//Function for the board and the end of the game
// template<BoardSize size>
// bool is_the_board_full(const Board<size, Player>& board)
// {
//     for (int x = 0; x < size._width; ++x) {
//         for (int y = 0; y < size._height; ++y) {
//             if (!board[{x, y}].has_value()) {
//                 return false;
//             }
//         }
//     }
//     std::cout << "It's a draw, congratulations to all !\n";
//     return true;
// }

template<BoardSize size>
std::optional<Player> check_for_winner_on_line(const Board<size, Player>& board, const CellIndex cell, const CellIndex direction)
{
    std::optional<Player> player_value;
    CellIndex             cell2 = {cell._x + direction._x, cell._y + direction._y};
    CellIndex             cell3 = {cell._x + 2 * direction._x, cell._y + 2 * direction._y};

    if (board[cell].has_value() && board[cell2].has_value() && board[cell3].has_value()) {
        player_value = board[cell];
        if (board[cell2] == player_value && board[cell3] == player_value) {
            if (player_value.value() == Player::Crosses)
                std::cout << "Congratulations ! 'Crosses' won the game !\n";
            else
                std::cout << "Congratulations ! 'Noughts' won the game !\n";
            return player_value;
        }
    }
    return std::nullopt;
}

template<BoardSize size>
bool has_a_player_won(const Board<size, Player>& board)
{
    // check for a complete diagonal on (0,1) and (0,2)
    // check for a complete column   on every (x,0)
    // check for a complete line     on every (0,y)

    bool a_player_has_won = false;
    if (check_for_winner_on_line(board, {0, 0}, {1, 1}).has_value() || check_for_winner_on_line(board, {0, 2}, {1, -1}).has_value())
        a_player_has_won = true;
    else {
        for (int x = 0; x < size._width; ++x) {
            if (check_for_winner_on_line(board, {x, 0}, {0, 1}).has_value() || check_for_winner_on_line(board, {0, x}, {1, 0}).has_value())
                a_player_has_won = true;
        }
    }
    return a_player_has_won;
}

template<BoardSize size>
bool is_the_game_finished(const Board<size, Player>& board)
{
    return (has_a_player_won(board) || board.is_the_board_full());
}

std::optional<CellIndex> cell_hovered(const glm::vec2 position, const BoardSize size, const p6::Context& ctx)
{
    CellIndex index;
    position_to_cell_index(position, index, size, ctx);
    if (index._x >= 0 && index._x < size._width && index._y >= 0 && index._y < size._height) {
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

void settings_to_draw_shapes(p6::Context& ctx)
{
    ctx.stroke_weight = 0.1f;
    ctx.use_fill      = false;
    ctx.stroke        = {.0f, .0f, .0f, 1.f};
}

void draw_nought(BoardSize size, p6::Context& ctx, glm::vec2 position)
{
    ctx.circle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size._width), ctx.aspect_ratio() / static_cast<float>(size._height)}},
               p6::Radius{.8f / static_cast<float>(size._height)});
}

void draw_cross(BoardSize size, p6::Context& ctx, glm::vec2 position)
{
    glm::vec2 cell_size = glm::vec2{1.f / static_cast<float>(size._width), ctx.aspect_ratio() / static_cast<float>(size._height)};
    ctx.rectangle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size._width), ctx.aspect_ratio() / static_cast<float>(size._height)}},
                  p6::Radii{cell_size.x * 0.8f, cell_size.y * 0.2f}, p6::Rotation{0.80_radians});
    ctx.rectangle(p6::Center{position + glm::vec2{1.f / static_cast<float>(size._width), ctx.aspect_ratio() / static_cast<float>(size._height)}},
                  p6::Radii{cell_size.x * 0.8f, cell_size.y * 0.2f}, p6::Rotation{-0.80_radians});
}

void draw_shape(BoardSize size, p6::Context& ctx, glm::vec2 position, Player state)
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

template<BoardSize size>
void draw_noughts_and_crosses(const Board<size, Player>& board, p6::Context& ctx)
{
    for (int x = 0; x < size._width; ++x) {
        for (int y = 0; y < size._height; ++y) {
            const auto cell = board[{x, y}];
            if (cell.has_value()) {
                draw_shape(size, ctx, cell_index_to_position({x, y}, size), *cell);
            }
        }
    }
}

void play_noughts_and_crosses()
{
    auto                       ctx            = p6::Context{{800, 800, "Noughts and Crosses"}};
    static constexpr BoardSize size           = {3, 3};
    Board<size, Player>        board          = Board<size, Player>{};
    Player                     current_player = Player::Crosses;

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
                draw_shape(size, ctx, cell_index_to_position(*cell_hovered(ctx.mouse(), size, ctx), size), current_player);
            }
        }

        //Drawing the mouse
        draw_mouse(ctx.mouse(), ctx);
    };

    ctx.mouse_pressed = [&](auto) {
        CellIndex index;
        position_to_cell_index(ctx.mouse(), index, size, ctx);

        //Drawing the shape on the click
        if (!board[index].has_value()) {
            board[{index._x, index._y}] = current_player;
            current_player              = (current_player == Player::Crosses) ? Player::Noughts : Player::Crosses;
            if (is_the_game_finished(board))
                ctx.stop();
        }
    };
    ctx.start();
}