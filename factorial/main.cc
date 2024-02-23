#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

/* factorial function */
/* uint64 : 0ULL ~  18446744073709551615ULL */
/* n! < 18446744073709551615  -->  n <= 20  */
uint64_t factorial(uint8_t n){
  if(n < 0){
    fprintf(stderr, "[Error] negative arg is invalid !\n");
    return UINT64_MAX;
  }
  if(n > 20){
    fprintf(stderr, "[Error]  n > 20, factorial exceeds uint64_t range.\n");
    return UINT64_MAX;
  }
  if(n==0){
    return 1;
  }
  return n*factorial(n-1);
}

int main(int argc, char *argv[]){

  uint8_t i=0ULL;
  for(i=0; i < 30; i++){
    printf("%d!=%" PRIu64 "\n", i, factorial(i));
  }

  return 0;
}