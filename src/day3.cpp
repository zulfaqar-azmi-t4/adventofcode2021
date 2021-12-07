#include <DataFrame/DataFrame.h>
#include <fmt/core.h>
#include <range/v3/view.hpp>
#include <array>
#include <string>

using namespace hmdf;

int main() {
  using MyDataFrame = StdDataFrame<unsigned long>;
  MyDataFrame d;
  try {
    d.read("../input/day3.csv", io_format::csv2);
  } catch (const DataFrameError &ex) {
    fmt::print("{}\n", ex.what());
  }

  std::size_t ptr = 0;
  std::array<int, 2> hash {};
  uint16_t gamma {0};
  const auto diagnostic = d.get_column<std::string>("diagnostic");
  while (ptr < diagnostic[0].size())
    {
      hash = {};
      for (const auto & diag:diagnostic)
        {
          hash[diag[ptr] - 48]++;
        }
      gamma = gamma << 1;
      if(hash[0] > hash[1])
        {
          gamma+=0;
        }
      else
        {
          gamma++;
        }
      ++ptr;
    }
  uint16_t mask {0b0000111111111111};
  uint16_t epsilon = (~gamma) & mask;
  fmt::print("gamma: {} epsilon:{} result:{} \n", gamma, epsilon, gamma*epsilon);
}
