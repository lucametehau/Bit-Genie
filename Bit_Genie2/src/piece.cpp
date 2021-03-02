#include "piece.h"
#include "misc.h"
#include <string>

Piece::Color Piece::get_color() const
{
  return static_cast<Color>(data >> 3);
}

Piece::Type Piece::get_type() const
{
  return static_cast<Type>(data & 0b111);
}

Piece::Piece()
  : data(empty)
{}

Piece::Piece(const Type type, const Color color)
{
  create(type, color);
}

Piece::Piece(char label)
{
  create(get_type(label), get_color(label));
}

bool Piece::is_empty() const
{
  return data == empty;
}

void Piece::create(const Type type, const Color color)
{
  data = type | (color << 3);
}

Piece::Type Piece::get_type(char label)
{
  label = std::tolower(label);
  return
    label == 'p' ? Piece::pawn   : label == 'n' ? Piece::knight :
    label == 'b' ? Piece::bishop : label == 'r' ? Piece::rook :
    label == 'q' ? Piece::queen  : Piece::king;
}

Piece::Color Piece::get_color(const char label)
{
  return std::isupper(label) ? Piece::white : Piece::black;
}

char Piece::letter() const {
  if (is_empty())
    return '.';

  Type t = get_type();

  char c = t == Piece::pawn   ? 'p' : t == Piece::knight ? 'n' :
           t == Piece::bishop ? 'b' : t == Piece::rook   ? 'r' :
           t == Piece::queen  ? 'q' : 'k';
  return get_color() == white ? std::toupper(c) : c;
}

std::ostream& operator<<(std::ostream& o, const Piece piece) 
{
  static constexpr const char* color_labels[]
  {
    "White", "Black"
  };
  static constexpr const char* type_labels[]
  {
    "Pawn", "Knight", "Bishop", "Rook", "Queen", "King"
  };
  if (piece.is_empty()) return o << '-';
  return o << color_labels[piece.get_color()] << ' ' << type_labels[piece.get_type()];
}