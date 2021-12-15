#include <string>
#include <fstream>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <iostream>
#include <sstream>
#include <vector>

struct Point{
  int x {0};
  int y {0};
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

    if(e.y == s.y)
      {
        if(e.x < s.x)
          {
            std::swap(e.x, s.x);
          }
      }
      if (e.x == s.x) {
        if (e.y < s.y) {
          std::swap(e.y, s.y);
        }
      }
      if ((e.x < s.x && e.y < s.y)) {
        std::swap(e, s);
      }

    lines.push_back(std::make_pair(s, e));
  }

  // const auto it = std::partition(lines.begin(), lines.end(),
  //                                [](std::pair<Point, Point> line) {
  //                                  return ((line.first.x == line.second.x) ||
  //                                          (line.first.y == line.second.y));
  //                                });
  // lines.erase(it, lines.end());

  std::transform(lines.begin(), lines.end(),
                 lines.begin(), [&min_x, &min_y](std::pair<Point, Point> p){
                   auto xs = p.first.x - min_x;
                   auto ys = p.first.y - min_y;
                   auto xe = p.second.x - min_x;
                   auto ye = p.second.y - min_y;
                   return std::make_pair(Point({xs, ys}), Point({xe, ye}));
                 });
  
  fmt::print("min {}, {}, max {}, {}\n", min_x, min_y, max_x, max_y);
  max_x = max_x - min_x + 1;
  max_y = max_y - min_y + 1;

  fmt::print("min {}, {}, max {}, {}\n", min_x, min_y, max_x, max_y);
  std::vector<std::vector<int>> grid(max_x, std::vector<int>(max_y, 0));
  for(const auto & [start_point, end_point]:lines)
    {
      auto current_x = start_point.x;
      auto current_y = start_point.y;
      grid[current_x][current_y] = grid[current_x][current_y] + 1;

      auto diff_x = end_point.x - start_point.x;
      auto diff_y = end_point.y - start_point.y;

      while(diff_x&& !diff_y){
          if(!std::signbit(diff_x)){
            current_x++;
            --diff_x;
          } else {
            current_x--;
            ++diff_x;
          }
          ++grid[current_x][current_y];
      }
      
      while (!diff_x && diff_y) {
        if (!std::signbit(diff_y)) {
          current_y++;
          --diff_y;
        } else {
          current_y--;
          ++diff_y;
        }
        ++grid[current_x][current_y];
      }
      
      while (diff_x && diff_y) {
        if (!std::signbit(diff_x) && !std::signbit(diff_y)) {
          current_x++;
          current_y++;
          --diff_x;
          --diff_y;
        } else if (!std::signbit(diff_x) && std::signbit(diff_y)) {
          current_x++;
          current_y--;
          --diff_x;
          ++diff_y;
        } else if (std::signbit(diff_x) && !std::signbit(diff_y)) {
          current_x--;
          current_y++;
          ++diff_x;
          --diff_y;
        }
        else {
          current_x--;
          current_y--;
          ++diff_y;
          ++diff_y;
        }
        ++grid[current_x][current_y];
      }
    }

  int overlapped {0};

for(int x = 0; x < grid.size(); ++x)
  {
      for(int y = 0; y < grid[0].size(); ++y)
        {
          if(grid[x][y] != 0 && grid[x][y] != 1)
            {
              ++overlapped;
            }
        }
  }

    fmt::print("overlapped: {}\n", overlapped);
}
