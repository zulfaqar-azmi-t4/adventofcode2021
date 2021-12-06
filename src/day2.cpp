// #include "document_reader.h"
#include <DataFrame/DataFrame.h>
#include <set>
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
      std::cout << ex.what() << '\n';
    }

  auto horizontal = 0;
  auto depth = 0;

  const auto direction = d.get_column<std::string>("direction");
  const auto input = d.get_column<int>("input");
  
  for(std::size_t idx = 0; idx < direction.size(); ++idx)
    {
      if(direction[idx] == "forward")
        {
          horizontal = horizontal + input[idx];
        }
      if(direction[idx] == "down")
        {
          depth = depth + input[idx];
        }
      if(direction[idx] == "up")
        {
          depth = depth - input[idx];
        }
    }
  std::cout << horizontal * depth << '\n';
}
