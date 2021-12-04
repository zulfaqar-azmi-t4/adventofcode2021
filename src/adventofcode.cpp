#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cassert>
class DocumentReader
{
public:
  void readFile(const std::string & filename, const char & sep)
  {
    std::ifstream file(filename);
    std::string row {};
    separator = sep;
    // return the headers first
    std::getline(file, row);
    std::string header{};
    std::stringstream ss(row);
    std::vector<std::string> headers {};
    while(std::getline(ss, header, separator))
      {
        headers.push_back(header);
      }
    std::size_t idx {0};

    std::vector<std::vector<int>> cell;
    while(std::getline(file, row))
      {
        std::vector<int> columns {};
        parseColumn(row, columns);
        cell.push_back(columns);
      }
    for(const auto & c:cell){
      for(size_t idx = 0; idx < headers.size(); ++idx)
        {
          cells[headers[idx]].push_back(c[idx]);
        }
    }
  }

  const void parseColumn(const std::string & row, std::vector<int> & columns) noexcept
  {
    std::istringstream ss(row);
    std::string column {};
    while(std::getline(ss, column, separator))
      {
        columns.push_back(stod(column));
      }
  }

  const auto getData() const noexcept {return cells;}
  private:
    char separator {};
    std::unordered_map<std::string, std::vector<int>> cells;
};

int main(){
  DocumentReader d;
  d.readFile("../input/input.txt", ' ');
  auto alldata = d.getData();

  const auto & data = alldata["Data1"];


  auto remainder = data.size() % 3;
  auto copied_data = data;
  while (remainder > 0) {
    copied_data.push_back(0);
    --remainder;
  }
  std::vector<int> sum_of_three{};

  for(size_t idx = 0; idx < copied_data.size() - 2; ++ idx)
    {
      sum_of_three.push_back(copied_data[idx] + copied_data[idx+1] + copied_data[idx + 2]);
    }
  auto old_data = sum_of_three[0];
  std::size_t counter = 0;
  assert(sum_of_three[0] == 569);
  assert(sum_of_three[sum_of_three.size() - 1] == 378);
  std::cout << sum_of_three[0] << " " << sum_of_three[sum_of_three.size() - 1] << '\n';
  for(const auto & d:sum_of_three){
    if(d > old_data)
      {
        counter++;
      }
    old_data = d;
  }
  std::cout << counter << '\n';
}
