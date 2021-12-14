#include <string>
#include <fstream>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <iostream>
#include <sstream>
#include <vector>

struct Point{
  int x;
  int y;
};

int main(int argc, char *argv[])
{
  const std::string filename {"../input/day5.txt"};
  std::ifstream input(filename);

  if (!input.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  std::string first_column {};
  std::string second_column {};
  std::string third_column {};

  std::vector<std::pair<Point, Point>> lines {};

  int max_x = 0;
  int max_y = 0;
  while(input >> first_column >> second_column >> third_column)
    {
      Point s;
      std::string number {};
      std::stringstream ss(std::move(first_column));
      std::getline(ss, number, ',');
      s.x = stoi(number);
      std::getline(ss, number);
      s.y = stoi(number);
      max_x = std::max(max_x, s.x);
      max_y = std::max(max_y, s.y);

      Point e;
      std::stringstream ee(std::move(third_column));
      std::getline(ee, number, ',');
      e.x = stoi(number);
      std::getline(ee, number);
      e.y = stoi(number);
      max_x = std::max(max_x, e.x);
      max_y = std::max(max_y, e.y);

      lines.push_back(std::make_pair(s, e));
  }

  const auto it = std::partition(lines.begin(), lines.end(),
                                 [](std::pair<Point, Point> line) {
                                   return ((line.first.x == line.second.x) ||
                                           (line.first.y == line.second.y));
                                 });
  lines.erase(it, lines.end());
  
  max_x = max_x + 1;
  max_y = max_y + 1;
  std::vector<int> grid((max_x * max_y), 0);
  for(const auto & [start_point, end_point]:lines)
    {
      auto current_x = start_point.x;
      auto current_y = start_point.y;
      const auto idx = [&current_x, &current_y, &max_y](){
        return current_x + current_y * max_y;
      };
      ++grid[idx()];

      auto diff_x = end_point.x - start_point.x;
      auto diff_y = end_point.y - start_point.y;

      while(diff_x != 0 && diff_y == 0){
          if(!std::signbit(diff_x)){
            current_x++;
            ++grid[idx()];
            --diff_x;
          } else {
            current_x--;
            ++grid[idx()];
            ++diff_x;
          }
      }
      
      while (diff_x == 0 && diff_y != 0) {
        if (!std::signbit(diff_y)) {
          current_y++;
          ++grid[idx()];
          --diff_y;
        } else {
          current_y--;
          ++grid[idx()];
          ++diff_y;
        }
      }
  }

  for(int y = 0; y < max_y; ++y)
    {
      for(int x = 0; x < max_x; ++x)
        {
          const auto index = x + y * max_y;
            fmt::print("{} ", grid[index]);
        }
      fmt::print("\n");
    }
}
