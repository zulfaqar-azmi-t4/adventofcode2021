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
  std::array<std::basic_string<char>, 2> filtered{};

  std::vector<std::basic_string<char>> o2 = diagnostic;
  for (int i = 0; i < bits; ++i) {
    std::array<std::vector<std::basic_string<char>>, 2> arr{};
    for (const auto & diag : o2) {
      arr[diag[i]-48].push_back(diag);
    }
    o2 = (arr[0].size() > arr[1].size()) ? arr[0] : arr[1];
  }
  fmt::print("{}\n", o2.front());

  std::vector<std::basic_string<char>> co2 = diagnostic;
  for (int i = 0; i < bits; ++i) {
    std::array<std::vector<std::basic_string<char>>, 2> arr{};
    for (const auto &diag : co2) {
      arr[diag[i] - 48].push_back(diag);
    }
    co2 = (arr[0].size() > arr[1].size()) ? arr[1] : arr[0];
  }
  fmt::print("{}\n", co2.front());

  std::bitset<bits> o2_{o2.front()};
  std::bitset<bits> co2_{co2.front()};
  fmt::print("o2: {}, co2: {}, multiply = {}\n", o2_.to_ulong(),
             co2_.to_ulong(), o2_.to_ulong() * co2_.to_ulong());
}
