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

  int min_x = std::numeric_limits<int>::max();
  int min_y = std::numeric_limits<int>::max();
  int max_x = std::numeric_limits<int>::min();
  int max_y = std::numeric_limits<int>::min();
  while (input >> first_column >> second_column >> third_column) {
    Point s;
    std::string number{};
    std::stringstream ss(std::move(first_column));
    std::getline(ss, number, ',');
    s.x = stoi(number);
    std::getline(ss, number);
    s.y = stoi(number);
    
    min_x = std::min(min_x, s.x);
    min_y = std::min(min_y, s.y);

    max_x = std::max(max_x, s.x);
    max_y = std::max(max_y, s.y);

    Point e;
    std::stringstream ee(std::move(third_column));
    std::getline(ee, number, ',');
    e.x = stoi(number);
    std::getline(ee, number);
    e.y = stoi(number);
    min_x = std::min(min_x, e.x);
    min_y = std::min(min_y, e.y);
    max_x = std::max(max_x, e.x);
    max_y = std::max(max_y, e.y);

    lines.push_back(std::make_pair(s, e));
  }
  fmt::print("{}",lines.size());

  const auto it = std::partition(lines.begin(), lines.end(),
                                 [](std::pair<Point, Point> line) {
                                   return ((line.first.x == line.second.x) ||
                                           (line.first.y == line.second.y));
                                 });
  lines.erase(it, lines.end());

  std::transform(lines.begin(), lines.end(),
                 lines.begin(), [&](std::pair<Point, Point> p){
                   auto xs = p.first.x - min_x;
                   auto ys = p.first.y - min_y;
                   auto xe = p.second.x - min_x;
                   auto ye = p.second.y - min_y;
                   return std::make_pair(Point({xs, ys}), Point({xe, ye}));
                 });
  
  fmt::print("min {}, {}, max {}, {}\n", min_x, min_y, max_x, max_y);
  max_x = max_x - min_x ;
  max_y = max_y - min_y ;

  fmt::print("min {}, {}, max {}, {}\n", min_x, min_y, max_x, max_y);
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
      
      while (diff_x != 0 && diff_y != 0) {
        if (!std::signbit(diff_y)) {
          current_x++;
          current_y++;
          ++grid[idx()];
          --diff_x;
          --diff_y;
        } else {
          current_x--;
          current_y--;
          ++grid[idx()];
          ++diff_y;
          ++diff_y;
        }
      }
  }

  int overlapped {0};

  for(int y = 0; y < max_y; ++y)
    {
      for(int x = 0; x < max_x; ++x)
        {
          const auto index = x + y * max_y;
          if(grid[index] != 0 && grid[index] != 1)
            {
              ++overlapped;
            }
        }
    }
    const auto its =
      std::min_element(grid.begin(), grid.end());

    fmt::print("min = {}\n", std::distance(grid.begin(), its));
    fmt::print("overlapped: {}\n", overlapped);
}
