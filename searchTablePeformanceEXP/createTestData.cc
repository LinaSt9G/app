#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <stdint.h>
#include <set>

#define DATANUM 10000

int main() {

    // For store random INPUT data
    std::vector<uint64_t> RandomValsCache;

  /*-------------------------------
      Create random INPUT data(uint64_t)
  -------------------------------*/
    // setting random number generator
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);

    std::set<uint64_t> numbers;

    for(int i=0; i < DATANUM; i++){
        uint64_t rand_num = dis(gen);
        RandomValsCache.push_back(rand_num);  // store random datas
    }

    std::string FILE_PATH;  // Use this variable in multiple places
  /*-------------------------------
      create INPUT_DATA list file
  -------------------------------*/
    // File Open
    FILE_PATH = "../autogen/f_INPUT_DATA.txt";
    std::ofstream fs(FILE_PATH);
    if (!fs) {
        std::cerr << "Cannot open " << FILE_PATH << std::endl;
        return -1;
    }

    // add source code to File
    for (int i = 0; i < DATANUM; ++i) {
        fs << std::setw(20) << std::setfill(' ') << RandomValsCache[i] << "ULL\n";
    }

    // File Close
    fs.close();

  /*-------------------------------
      create OUTPUT_DATA list file
  -------------------------------*/
    // File Open
    FILE_PATH = "../autogen/f_OUPUT_DATA.txt";
    std::ofstream fs2(FILE_PATH);
    if (!fs2) {
        std::cerr << "Cannot open " << FILE_PATH << std::endl;
        return -1;
    }

    // add source code to File
    for (int i = 0; i < DATANUM; ++i) {
        fs2 << std::setw(20) << std::setfill(' ') << i << "ULL\n";
    }

    // File Close
    fs2.close();

  /*-------------------------------
      create switch.h 
  -------------------------------*/
    // File Open
    FILE_PATH = "../autogen/switch.h";
    std::ofstream fs_sw(FILE_PATH);
    if (!fs_sw) {
        std::cerr << "Cannot open " << FILE_PATH << std::endl;
        return -1;
    }

    // add source code to File
    fs_sw << "#include <cstdint>\n"
          << "#include <stdio.h>\n"
          << "uint64_t f_sw(uint64_t x){\n"
          << "  uint64_t y=0ULL;\n"
          << "  switch(x){\n";
    for (int i = 0; i < DATANUM; ++i) {
        fs_sw << "    case "  
              << std::setw(20) << std::setfill(' ') << RandomValsCache[i] << "ULL:" 
              << "  y = " 
              << std::setw(20) << std::setfill(' ') << i << "ULL;"<< " break;\n";
    }
    fs_sw << "  default: printf(\"switch() ERROR\\n\");\n"
          << "  }\n"
          << "  return y;\n"
          << "}\n";
    fs_sw << std::endl;

    // File Close
    fs_sw.close();

  /*-------------------------------
      create if.h 
  -------------------------------*/
    // File Open
    FILE_PATH = "../autogen/if.h";
    std::ofstream fs_if(FILE_PATH);
    if (!fs_if) {
        std::cerr << "Cannot open " << FILE_PATH << std::endl;
        return -1;
    }

    fs_if << "#include <cstdint>\n"
          << "#include <stdio.h>\n"
          << "uint64_t f_if(uint64_t x){\n"
          << "  uint64_t y=0ULL;\n";
    for (int i = 0; i < DATANUM; ++i) {
        fs_if << "  if( x == "  
              << std::setw(20) << std::setfill(' ') << RandomValsCache[i] << "ULL){" 
              << "  y = " 
              << std::setw(20) << std::setfill(' ') << i << "ULL;}\n";
    }

    fs_if << "  return y;\n"
          << "}\n";

    fs_if << std::endl;

    // File Close
    fs_if.close();

  /*-------------------------------
      create map.h 
  -------------------------------*/
    // File Open
    FILE_PATH = "../autogen/map.h";
    std::ofstream fs_map(FILE_PATH);
    if (!fs_map) {
        std::cerr << "Cannot open " << FILE_PATH << std::endl;
        return -1;
    }

    fs_map << "#include <unordered_map>\n"
          << "#include <cstdint>\n"
          << "std::unordered_map<uint64_t, uint64_t> map = {\n";
    for (int i = 0; i < DATANUM; ++i) {
        fs_map << "  {"  
              << std::setw(20) << std::setfill(' ') << RandomValsCache[i] << "ULL, " 
              << std::setw(20) << std::setfill(' ') << i << "ULL},\n";
    }

    fs_map << "};\n";
          

    fs_map << std::endl;

    // File Close
    fs_map.close();


  /*-------------------------------
      create cmp.h 
  -------------------------------*/
    // File Open
    FILE_PATH = "../autogen/cmp.h";
    std::ofstream fs_cmp(FILE_PATH);
    if (!fs_cmp) {
        std::cerr << "Cannot open " << FILE_PATH << std::endl;
        return -1;
    }

    fs_cmp << "#include <cstdint>\n"
           << "#include <stdio.h>\n"
           << "uint64_t f_cmp(uint64_t x){\n"
           << "  uint64_t y=0ULL;\n"
           << "  y = \n" ;
    for (int i = 0; i < DATANUM; ++i) {
        fs_cmp << "    (x == "
              << std::setw(20) << std::setfill(' ') << RandomValsCache[i] << "ULL)*" 
              << std::setw(20) << std::setfill(' ') << i << "ULL + \n";
    }

    fs_cmp << "  0;\n"
           << "  return y;\n"
           << "}\n";
          

    fs_cmp << std::endl;

    // File Close
    fs_cmp.close();

    return 0;
}
