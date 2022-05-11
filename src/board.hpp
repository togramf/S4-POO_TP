#pragma once

#include <p6/p6.h>
#include <optional>

struct CellIndex {
    int _x;
    int _y;
};

struct BoardSize {
    int _width;
    int _height;
};

template<BoardSize size, typename Player>
class Board {
public:
    Board()
        : _state(size._width * size._height, std::nullopt)
    {
    }
    std::optional<Player>& operator[](CellIndex index)
    {
        return _state[index._x + size._width * index._y];
    }

    const std::optional<Player>& operator[](CellIndex index) const
    {
        return _state[index._x + size._width * index._y];
    }

private:
    std::vector<std::optional<Player>> _state;
};

float     board_ratio(BoardSize size);
void      position_to_cell_index(const glm::vec2 position, CellIndex& cell, const BoardSize size, const p6::Context& ctx);
glm::vec2 cell_index_to_position(const CellIndex& index, const BoardSize size);
void      draw_cell(const BoardSize size, p6::Context& ctx, const CellIndex index);
void      draw_board(const BoardSize size, p6::Context& ctx);
void      settings_to_draw_board(p6::Context& ctx);
