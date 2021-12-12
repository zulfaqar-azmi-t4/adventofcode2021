#pragma once

#include <algorithm>
#include <cassert>
#include <cctype>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

struct DocumentReader
{
  void readFile(const std::string & filename)
  {
    std::ifstream file(filename);
    std::string row {};
    // return the draws first
    std::getline(file, row);
    std::string number_draw{};
    std::stringstream ss(row);
    while(std::getline(ss, number_draw, ','))
      {
        draws.push_back(stod(number_draw));
      }
    int board_number {-1};

    std::vector<int> board {};
    while(std::getline(file, row))
        {
          fmt::print("{}\n", row);
          std::vector<int> columns {};
          parseColumn(row, columns);
          board.insert(board.end(), columns.begin(), columns.end());
          if(board.size() == 25){
            ++board_number;
            boards[board_number] = board;
            board.clear();
          }
        }
  }

  const void parseColumn(const std::string & row, std::vector<int> & columns) noexcept
  {
    std::istringstream ss(row);
    std::string column {};
    while(std::getline(ss, column, ' '))
      {
        column.erase(std::remove_if(column.begin(), column.end(), ::isspace), column.end());
        if(column.size())
          {
            columns.push_back(stoi(column));
            
          }
      }
  }
  
  const auto getData() const noexcept {return boards;}
  std::vector<int> draws;
  std::map<int, std::vector<int>> boards;
};
