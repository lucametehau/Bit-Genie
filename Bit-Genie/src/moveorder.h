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
#include "movegen.h"

class MovePicker
{
    enum class Stage
    {
        HashMove,
        GenNoisy,
        GiveGoodNoisy,
        Killer1,
        Killer2,
        GiveBadNoisy,
        GenQuiet,
        GiveQuiet
    };

public:
    MovePicker(Position &, Search &, TTable &);

    bool next(Move &);

    MoveGenerator<true> gen;

private:
    Position *position;
    Search *search;
    TTable *table;

    Stage stage = Stage::HashMove;
    Movelist::iterator current;
};

void sort_qmovelist(Movelist &, Position &, Search &search);