#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <mutex>
#include <vector>
#include <random>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <inttypes.h>


#define PERIOD_TIME_us (0)

std::mutex mutex;

struct DataFrame{
  uint8_t  a;
  uint16_t b;
  uint32_t c;
  uint64_t d;
  std::string str;
  uint64_t e[1000];
};

void FillDataToDataFrame(struct DataFrame * frame){
  frame->a = UINT8_MAX;
  frame->b = UINT16_MAX;
  frame->c = UINT32_MAX;
  frame->d = UINT64_MAX;
  frame->str = "sample";
  for (int i = 0; i < sizeof(frame->e) / sizeof(frame->e[0]); ++i) {
    frame->e[i] = UINT64_MAX;
  }

}


class ContainerTest{
private:
  std::vector<struct DataFrame> commonContainer;
  struct DataFrame tmpframe;

public:
  ContainerTest(){
      FillDataToDataFrame(&tmpframe);
  }
  void StoreDataToContainer(int threadNo){

    while(1){

      //----- mutex start
      mutex.lock();
      commonContainer.push_back(tmpframe);
      mutex.unlock();
      //----- mutex end

      usleep(PERIOD_TIME_us);
    }
    printf("Thread-%d finished !\n",threadNo);


  }
  
  
  void PrintDataSize(){
    mutex.lock();
    std::cout << "container size : " << commonContainer.size() << std::endl;
    mutex.unlock();
  }
  
  void PrintDataBytes(){
    mutex.lock();
    std::cout << "container byte : " << commonContainer.size() * sizeof(DataFrame) << std::endl;
    mutex.unlock();
  }
};


int main(int argc, char *argv[]){
  
  printf("-------------- start main app --------------\n");

  ContainerTest instance;

  std::thread th0([&instance](){instance.StoreDataToContainer(0);});
  std::thread th1([&instance](){instance.StoreDataToContainer(1);});
  std::thread th2([&instance](){instance.StoreDataToContainer(2);});
  std::thread th3([&instance](){instance.StoreDataToContainer(3);});
  std::thread th4([&instance](){instance.StoreDataToContainer(4);});
  std::thread th5([&instance](){instance.StoreDataToContainer(5);});
  std::thread th6([&instance](){instance.StoreDataToContainer(6);});
  std::thread th7([&instance](){instance.StoreDataToContainer(7);});

  while(1){
    instance.PrintDataSize();
    instance.PrintDataBytes();
    printf("-----------------------------\n");
    sleep(1);
  }

  th0.join();
  th1.join();
  th2.join();
  th3.join();
  th4.join();
  th5.join();
  th6.join();
  th7.join();

  return 0;
}