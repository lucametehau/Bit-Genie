/*
  Bit-Genie is an open-source, UCI-compliant chess engine written by
  Aryan Parekh - https://github.com/Aryan1508/Bit-Genie

  Bit-Genie is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Bit-Genie is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include "move.h"
#include "position.h"
#include "movelist.h"
#include <array>
#include <cstring>

class SHistory
{
public:
    SHistory()
    {
        std::memset(&history[0][0][0], 0, sizeof(history));
    }

    int16_t &get(Position const &position, Move move) noexcept
    {
        return history[position.side][move_from(move)][move_to(move)];
    }

    void add(Position &position, Move move, int bonus) noexcept
    {
        // History bonus formula copied from weiss
        auto& cur = get(position, move);
        cur += 32 * bonus - cur * abs(bonus) / 512;
    }

    void penalty(Position& position, Movelist& quiet, Move good, int depth) 
    {
        for(auto move : quiet)
        {
            if (move_without_score(move) == move_without_score(good))
                continue;

            add(position, move, -(depth * depth));
        }
    }

private:
    int16_t history[2][64][64]{0};
};