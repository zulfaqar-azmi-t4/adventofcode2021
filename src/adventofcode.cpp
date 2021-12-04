#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
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

    std::vector<std::vector<double>> cell;
    while(std::getline(file, row))
      {
        std::vector<double> columns {};
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

  const void parseColumn(const std::string & row, std::vector<double> & columns) noexcept
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
    std::unordered_map<std::string, std::vector<double>> cells;
};

int main(){
  DocumentReader d;
  d.readFile("../input/day1.txt", ' ');
  auto alldata = d.getData();

  const auto & data = alldata["Data1"];

  auto old_data = data[0];
  std::size_t counter = 0;
  for(const auto & d:data){
    if(d > old_data)
      {
        counter++;
      }
    old_data = d;
  }
  std::cout << "Number of increasing = " << counter << '\n';
}
