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

template<BoardSize size>
std::optional<int> lowest_empty_row_index(const Board<size, Player>& board, const int column_index)
{
    for (int y = 0; y < size._height; ++y) {
        if (!board[{column_index, y}].has_value())
            return std::make_optional(y);
    }
    return std::nullopt;
}

//Functions for the end of the game
template<BoardSize size>
int number_of_coin_in_direction(const Board<size, Player>& board, const Player player, const CellIndex new_coin, const CellIndex direction, int orientation)
{
    CellIndex position;
    int       nb_of_coins_in_orientation = 0;
    int       i                          = 1;

    while (i > 0) {
        position = {new_coin._x + i * orientation * direction._x, new_coin._y + i * orientation * direction._y};
        if (board[position].has_value() && (board[position] == player)) {
            nb_of_coins_in_orientation++;
            i++;
        }
        else
            i = -1;
    }
    return nb_of_coins_in_orientation;
}

template<BoardSize size>
bool check_for_winner_in_direction(const Board<size, Player>& board, const Player player, const CellIndex new_coin, const CellIndex direction)
{
    int nb_of_coins_in_direction = 1 + number_of_coin_in_direction(board, player, new_coin, direction, 1) + number_of_coin_in_direction(board, player, new_coin, direction, -1);
    return (nb_of_coins_in_direction >= 4) ? true : false;
}

template<BoardSize size>
bool has_the_player_won(const Board<size, Player>& board, const Player player, const CellIndex new_coin)
{
    //check for an alignment of 4 coins around the new coin played in 4 directions
    return (check_for_winner_in_direction(board, player, new_coin, {1, 0}) || check_for_winner_in_direction(board, player, new_coin, {0, 1}) || check_for_winner_in_direction(board, player, new_coin, {1, 1}) || check_for_winner_in_direction(board, player, new_coin, {1, -1}));
}

template<BoardSize size>
bool is_the_game_finished(const Board<size, Player>& board, const Player player, const CellIndex new_coin)
{
    if (board.is_the_board_full())
        std::cout << "It's a draw ! \n";
    return (has_the_player_won(board, player, new_coin) || board.is_the_board_full());
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

void draw_coin(BoardSize size, p6::Context& ctx, glm::vec2 position, Player state)
{
    settings_to_draw_coin(ctx, state);
    ctx.circle(p6::Center{position + glm::vec2{board_ratio(size) / static_cast<float>(size._width), 1.f / static_cast<float>(size._height)}},
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

    //On click, if possible draw the coin and change player
    ctx.mouse_pressed = [&](auto) {
        CellIndex index;
        position_to_cell_index(ctx.mouse(), index, size, ctx);
        std::optional<int> y = lowest_empty_row_index(board, index._x);

        if (y.has_value()) {
            board[{index._x, *y}] = current_player;
            if (is_the_game_finished(board, current_player, {index._x, *y}))
                ctx.stop();
            current_player = (current_player == Player::Yellow) ? Player::Red : Player::Yellow;
        }
    };

    ctx.start();
}
