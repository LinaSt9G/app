#include <cstdint>
#include <stdio.h>
#include <string> 
#include <vector> 
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <time.h>

// Auto generated source code
#include "cmp.h"
#include "map.h"
#include "if.h"
#include "switch.h"

int main(int argc, char *argv[]){

  // test INPUT(random uint64_t) data list
  std::vector<uint64_t> testvalist;

  // Read test data & store data to testvalist
  std::ifstream file("../autogen/f_INPUT_DATA.txt");
  std::string line;
  std::regex pattern(R"((\d+)ULL)");
  while (std::getline(file, line)) {
      std::smatch matches;
      if (std::regex_search(line, matches, pattern)) {
          if (matches.size() > 1) {
              uint64_t number = std::stoull(matches[1].str());
              testvalist.push_back(number);
          }
      }
  }

  // Shuffle testvalist
  /* Prepare a random number generator (using the current time as the seed value) */
  std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
  /* Random shuffling of vectors */
  std::shuffle(testvalist.begin(), testvalist.end(), rng);



  // Start Test
  printf("== test start\n");
  printf("\n");
  struct timespec start, end;
  double time_spent;


  clock_gettime(CLOCK_REALTIME, &start);  // Start Time
  printf("[1] map\n");
  for(uint64_t testval : testvalist){
    map[testval];
    //printf("map[%lu]=%lu\n",testval, map[testval]);
  }
  clock_gettime(CLOCK_REALTIME, &end);  // End Time
  time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  printf("[1] map end. Time spent: %.9f seconds\n", time_spent);
  printf("\n");


  clock_gettime(CLOCK_REALTIME, &start);  // Start Time
  printf("[2] if\n");
  for(uint64_t testval : testvalist){
    f_if(testval);
    //printf("hello No.%ld\n",f_if(testval));
  }
  clock_gettime(CLOCK_REALTIME, &end);  // End Time
  time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  printf("[2] if end. Time spent: %.9f seconds\n", time_spent);
  printf("\n");


  clock_gettime(CLOCK_REALTIME, &start);  // Start Time
  printf("[3] switch\n");
  for(uint64_t testval : testvalist){
    f_sw(testval);
    //printf("hello No.%ld\n",f_sw(testval));
  }
  clock_gettime(CLOCK_REALTIME, &end);  // End Time
  time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  printf("[3] switch end. Time spent: %.9f seconds\n", time_spent);
  printf("\n");


  clock_gettime(CLOCK_REALTIME, &start);  // Start Time
  printf("[4] compare\n");
  for(uint64_t testval : testvalist){
    f_cmp(testval);
    //printf("hello No.%ld\n",f_cmp(testval));
  }
  clock_gettime(CLOCK_REALTIME, &end);  // 終了時刻
  time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  printf("[4] compare end. Time spent: %.9f seconds\n", time_spent);
  printf("\n");
  
  
  

  return 0;
}