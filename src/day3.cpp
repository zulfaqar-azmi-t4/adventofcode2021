#include <DataFrame/DataFrame.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
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

  const auto diagnostic = d.get_column<std::string>("diagnostic");

  int ptr = 0;
  std::array<int, 2> hash {};
  constexpr int bits = 12;
  std::bitset<bits> gamma{};

  while (ptr < diagnostic[0].size())
    {
      hash = {};
      for (const auto &diag : diagnostic) {
        hash[diag[ptr] - 48]++;
      }
      if (hash[0] > hash[1]) {
        gamma[bits - ptr - 1] = 0;
      } else {
        gamma[bits - ptr - 1] = 1;
      }
      ++ptr;
    }
  decltype(gamma) epsilon = gamma.flip();
  fmt::print("gamma: {}, epsilon: {}\n", gamma.to_ulong(), epsilon.to_ulong());
  /**
   * gamma: 0b10111101 epsilon:3906 result:738234
   */
  // std::vector<std::bitset<bits>> common{};
  // for (const auto & diag:diagnostic)
  //   {
  //     common.push_back(std::bitset<bits>(diag));
  //   }

  std::array<std::basic_string<char>, 2> filtered{};
}
