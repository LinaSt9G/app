#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

unsigned int randomUINT_4dig(){
  unsigned int random = (rand() + 1 )% 10000; // random = [0,9999]
  return random;
}

bool compStrInt(std::string a, std::string b){
  unsigned int aa = std::stoi(a);
  unsigned int bb = std::stoi(b);
  if(aa > bb){
    return false;
  }else{
    return true;
  }
}


int main(int argc, char *argv[]){
  
  // Create Random int array[10]
  std::vector<std::string> vector;
  for(int i=0; i < 10; ++i){
    vector.push_back(std::to_string(randomUINT_4dig()));
  }

  // Print Random int array[10]
  for(auto elm : vector){
    std::cout << elm << std::endl;
  }

  std::cout << "-----------" << std::endl;

  // Sort
  std::sort(vector.begin(), vector.end(), compStrInt);

  // Print Sorted array[10]
  for(auto elm : vector){
    std::cout << elm << std::endl;
  }


  return 0;
}