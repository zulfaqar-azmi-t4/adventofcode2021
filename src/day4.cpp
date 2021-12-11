#include<vector>
#include <fmt/core.h>
#include <unordered_map>

bool win_check(const std::vector<int> board)
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
  bool l11 =  (board[0] && board[6] && board[12] && board[18] && board[24]);
  if(l1 || l2 || l3 || l4 || l5 || l6 || l7 || l8 || l9 || l10 || l11)
    {
      return true;
    }

  return false;
}

int main(){
  std::vector<int> numbers {
     7,  4,  9,  5, 11,
    17, 23,  2,  0, 14,
    21, 24, 10, 16, 13,
     6, 15, 25, 12, 22,
    18, 20,  8, 19,  3,
    26,  1};

  std::vector<int> board1{
    22, 13, 17, 11,  0,
     8,  2, 23,  4, 24,
    21,  9, 14, 16,  7,
     6, 10,  3, 18,  5,
     1, 12, 20, 15, 19};

  std::vector<int> board2{
    3, 15, 0, 2, 22,
    9, 18, 13, 17, 5,
    19, 8, 7, 25, 23,
    20, 11, 10, 24, 4,
    14, 21, 16, 12, 6};

  std::vector<int> board3{
    14, 21, 17, 24,  4,
    10, 16, 15,  9, 19,
    18,  8, 23, 26, 20,
    22, 11, 13,  6,  5,
     2,  0, 12,  3,  7};

  int win_step_counter{-1};
  bool win {false};
  std::vector<int> temp_board(25, 0);
  int ptr{0};
  while(ptr < numbers.size() && !win)
    {
      ++win_step_counter;
      for (int j = 0; j < 5; ++j) {
        for (int i = 0; i < 5; ++i) {
          const int idx = i + j * 5;
          if(numbers[ptr] == board3[idx])
            {
              temp_board[idx] = 1;
            }
          if(win_check(temp_board)){
            win = true;
            break;
          };
          if(win)
            {
              break;
            }
        }
      }
      ++ptr;
  }
  fmt::print("Win at step no {} with last number {}\n", win_step_counter, numbers[win_step_counter]);

  int sum {0};
  for (int j = 0; j < 5; ++j) {
    for (int i = 0; i < 5; ++i) {
      const int idx = i + j * 5;
      if(!temp_board[idx]){
        sum = sum + board3[idx];
      }
    }
  }

  int final_score = sum * numbers[win_step_counter];
  fmt::print("Final score = {}\n", final_score);
}
