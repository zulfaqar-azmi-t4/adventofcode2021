#include<fmt/core.h>
#include <fstream>
#include <fmt/ranges.h>
#include <boost/range/adaptor/indexed.hpp>
#include "day4.h"
#include <numeric>

bool isWinner(const std::vector<int> & board)
{
  bool l1 = (board[0] && board[1] && board[2] && board[3] && board[4]);
  bool l2 = (board[5] && board[6] && board[7] && board[8] && board[9]);
  bool l3 = (board[10] && board[11] && board[12] && board[13] && board[14]);
  bool l4 = (board[15] && board[16] && board[17] && board[18] && board[19]);
  bool l5 =  (board[20] && board[21] && board[22] && board[23] && board[24]);
  bool l6 =  (board[0] && board[5] && board[10] && board[15] && board[20]);
  bool l7 =  (board[1] && board[6] && board[11] && board[16] && board[21]);
  bool l8 =  (board[2] && board[7] && board[12] && board[17] && board[22]);
  bool l9 =  (board[3] && board[8] && board[13] && board[18] && board[23]);
  bool l10 =  (board[4] && board[9] && board[14] && board[19] && board[24]);
  if(l1 || l2 || l3 || l4 || l5 || l6 || l7 || l8 || l9 || l10)
    {
      return true;
    }

  return false;
}

bool findBingo(const std::vector<int> & draws, const std::vector<int> & board, const int & draw_ptr, std::vector<int> & temp){
  for (int row = 0; row < 5; ++row) {
    for (int col = 0; col < 5; ++col) {
      int itr_board = col + row * 5;
      if (draws[draw_ptr] == board[itr_board]) {
        temp[itr_board] = 1;
      }
      if (isWinner(temp))
        {
          return true;
        }
    }
  }
  return false;
}

int main(){
  DocumentReader file;
  file.readFile("../input/day4.txt");
  const auto data = file.getData();
  const auto draws = file.draws;
  const auto boards = file.getData();
  std::array<int, 2> current_winner {-1, std::numeric_limits<int>::min()};
  std::vector<int> current_winner_log;
  int i = 0;
  for(const auto & b:boards | boost::adaptors::indexed(0))
    {
      const auto & board = b.value().second;
      fmt::print("board : {}", board);
      int draw_ptr = 0;
      bool win {false};
      int num_step_to_win {-1};
      std::vector<int> temp(25, 0);
      while(draw_ptr < draws.size())
        {
          if(!win)
            {
              win = findBingo(draws, board, draw_ptr, temp);
              num_step_to_win = draw_ptr;
            }
          ++draw_ptr;
        }
      if(current_winner[1] < num_step_to_win)
        {
          current_winner_log = temp;
          current_winner[0] = b.value().first;
          current_winner[1] = num_step_to_win;
      }
      fmt::print("board no: {} leading in {} steps.\n", current_winner[0], current_winner[1]);
      ++i;
    }

  // fmt::print("Board {} win at step no {} with last number {}\n", winner_board, win_step_counter, draws[win_step_counter]);

  int sum {0};
  std::vector<int> winner = boards.at(current_winner[0]);
  fmt::print("Winner = {}\n", current_winner_log);
  int ptr {0};
  bool win {false};

  for(int j = 0; j < 5; ++j)
    {
      for(int i = 0; i < 5; ++i)
        {
          const int idx = i + j*5;
          if(!current_winner_log[idx])
            {
              fmt::print("{}. ", winner[idx]);
              sum = sum + winner[idx];
            }
        }
    }


  int final_score = sum * draws[current_winner[1]];
  fmt::print("Sum = {}, Draw = {}, Final score, {}\n", sum, draws[current_winner[1]], final_score);

  }
