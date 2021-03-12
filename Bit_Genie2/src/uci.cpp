#include "uci.h"
#include "position.h"
#include "search.h"
#include "uciparse.h"
#include "tt.h"
#include <thread>
#include <chrono>
#include <fstream>

static void benchmark_perft(Position position, int depth)
{
  using namespace std::chrono;
  uint64_t nodes = 0;

  auto start = high_resolution_clock::now();
  position.perft(depth, nodes);
  auto stop = high_resolution_clock::now();
  auto time_taken = duration_cast<milliseconds>(stop - start);

  std::cout << "nodes: " << nodes << std::endl;
  std::cout << "time : " << time_taken.count() << " ms" << std::endl;
}

std::vector<const char*> test_game{
  "e2e4", "e7e5", "g1f3", "g8f6", "f1c4", "d7d6",
  "e1g1", "b8c6", "d2d3", "f8e7", "c1g5", "e8g8",
  "b1c3", "a7a6", "c4b3", "b7b5", 
};

void uci_input_loop()
{
  std::cout << "Bit Genie by Aryan Parekh" << std::endl;
  UciParser command;
  Position position;
  TTable table(2);

  while (true)
  {
    command.take_input();

    if (command == UciCommands::quit)  break;

    else if (command == UciCommands::isready)
      std::cout << "readyok" << std::endl;

    else if (command == UciCommands::uci)
    {
      std::cout << "id name Bit Genie" << std::endl;
      std::cout << "id author Aryan Parekh" << std::endl;
      std::cout << "uciok" << std::endl;
    }

    else if (command == UciCommands::position)
    {
      auto [fen, moves] = command.parse_position_command();

      if (!position.set_fen(fen))
      {
        std::cout << fen << std::endl;
        std::cout << "Invalid FEN string" << std::endl;
        continue;
      }

      for (std::string move : moves)
      {
        if (!position.apply_move(move))
        {
          std::cout << "Invalid move in movelist" << std::endl;
          continue;
        }
      }
    }

    else if (command == UciCommands::print)
      std::cout << position << std::endl;

    else if (command == UciCommands::perft)
    {
      int depth = command.parse_perft();
      if (depth <= 0)
      {
        std::cout << "Invalid perft depth" << std::endl;
        continue;
      }

      benchmark_perft(position, depth);
    }

    else if (command == UciCommands::go)
    {
      std::cout << position << std::endl;

      UciGo options = command.parse_go();

      Search search;
      search.limits.max_depth = std::min(options.depth, 64);
      search.limits.stopwatch.go();
      search.limits.stopped = false;
      search.limits.time_set = false;

      if (options.movetime != -1)
      {
        search.limits.movetime = options.movetime;
        search.limits.time_set = true;
      } 

      search_position(position, search, table);
    }
  }
}