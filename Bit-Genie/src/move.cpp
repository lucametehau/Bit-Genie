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
#include "move.h"
#include "position.h"
#include <sstream>

bool move_is_capture(Position const &position, Move move)
{
    return position.pieces.squares[move_to(move)] != Empty;
}

std::string print_move(Move move)
{
    std::stringstream o;
    o << move_from(move) << move_to(move);
    if (move_flag(move) == MoveFlag::promotion)
    {
        o << move_promoted(move);
    }
    return o.str();
}