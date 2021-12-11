// #include "document_reader.h"
#include <DataFrame/DataFrame.h>
#include <fmt/core.h>
#include <range/v3/view.hpp>
#include <set>

using namespace hmdf;

int main() {
  using MyDataFrame = StdDataFrame<unsigned long>;
  MyDataFrame d;
  try {
    d.read("../input/day2.csv", io_format::csv2);
  } catch (const DataFrameError &ex) {
    fmt::print("{}\n", ex.what());
  }

  auto horizontal = 0;
  auto aim = 0;
  auto depth = 0;

  const auto direction = d.get_column<std::string>("direction");
  const auto input = d.get_column<int>("input");
  for (const auto &[dir, in] : ranges::views::zip(direction, input)) {
    if (dir == "forward") {
      horizontal = horizontal + in;
      depth = depth + aim * in;
    } else if (dir == "down") {
      aim = aim + in;
    } else if (dir == "up") {
      aim = aim - in;
    }
  }
  fmt::print("Total: {}\n", horizontal * depth);
}
