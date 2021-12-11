#include "document_reader.h"

int main(){
  DocumentReader d;
  d.readFile("../input/day1.txt", ' ');
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
