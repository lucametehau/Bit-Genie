#pragma once
#include "misc.h"

#define CreateMove(from, to, type, promoted) (Move(((from)) | ((to) << 6) | ((to_int(type)) << 12) | (((promoted) - 1) << 14)))


enum class MoveFlag : uint8_t
{
	normal, enpassant, castle, promotion
};

enum Move : uint32_t {
	NullMove
};

inline int16_t move_score(Move move)
{
	return static_cast<int16_t>(move >> 16);
}

constexpr Move move_without_score(Move m)
{
	return Move(m & 0xFFFF);
}

inline bool operator<(Move rhs, Move lhs)
{
	return move_score(rhs) < move_score(lhs);
}

inline bool operator>(Move rhs, Move lhs)
{
	return move_score(rhs) > move_score(lhs);
}

constexpr Square move_from(Move move)
{
	return static_cast<Square>(move & 0x3f);
}

constexpr Square move_to(Move move)
{
	return static_cast<Square>((move >> 6) & 0x3f);
}

constexpr MoveFlag move_flag(Move move)
{
	return static_cast<MoveFlag>((move >> 12) & 0x3);
}

constexpr PieceType move_promoted(Move move)
{
	return static_cast<PieceType>(((move >> 14) & 0x3) + 1);
}

inline void set_move_score(Move& move, int16_t score)
{
	move = static_cast<Move>(move | (score << 16));
}

bool move_is_capture(Position const& positio, Move);
std::string print_move(Move);