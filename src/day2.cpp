// #include "document_reader.h"
#include <DataFrame/DataFrame.h>
#include <set>
#include <fmt/core.h>
using namespace hmdf;

int main(){
  using MyDataFrame = StdDataFrame<unsigned long>;
  MyDataFrame d;
  try
    {
      d.read("../input/day2.csv",io_format::csv2);
    }
  catch (const DataFrameError & ex)
    {
      fmt::print("{}\n", ex.what());
    }

  auto horizontal = 0;
  auto aim = 0;
  auto depth = 0;

  const auto direction = d.get_column<std::string>("direction");
  const auto input = d.get_column<int>("input");
  
  for(std::size_t idx = 0; idx < direction.size(); ++idx)
    {
      if(direction[idx] == "forward")
        {
          horizontal = horizontal + input[idx];
          depth = depth + aim * input[idx];
        }
      if(direction[idx] == "down")
        {
          aim = aim + input[idx];
        }
      if(direction[idx] == "up")
        {
          aim = aim - input[idx];
        }
    }
  fmt::print("Total: {}\n", horizontal * depth);
}
