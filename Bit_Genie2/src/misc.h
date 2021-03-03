#pragma once
#include <cassert>
#include <iostream>
#include <stdint.h>
#include <type_traits>

// Used for converting enum class types to its underlying type 
// Example: Square -> uint8_t
template <typename E>
constexpr typename std::underlying_type<E>::type to_int(E e) noexcept
{
  return static_cast<typename std::underlying_type<E>::type>(e);
}

// Global constants 
constexpr int total_pieces = 6;
constexpr int total_colors = 2;
constexpr int total_squares = 64;
constexpr int total_files = 8;
constexpr int total_castle_types = 2;

// Forward declarations for most enum(classes)
enum class Direction : int8_t;
enum class File : uint8_t;
enum class Rank : uint8_t;
enum class Square : uint8_t;

// Forward declarations for all classes
class Bitboard;
class CastleRights;
class Move;
class Piece;
class PieceManager;
class Position;
class PositionHistory;
class ZobristKey;