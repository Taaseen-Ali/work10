#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int get_rand(){
  int rand; 
  int rand_file = open("/dev/random", O_RDONLY);
  if(rand_file==-1)
    printf("Error opening file: %s\n", strerror(errno));
  read(rand_file, &rand, 8);
  close(rand_file);
  return rand;
}

int main(){
  printf("------------------------\n");
  printf("Creating random array...\n");
  printf("------------------------\n\n");

  int nums[10];
  for(int i=0; i<10; i++)
    nums[i]=get_rand();

  printf("--> [");
  for(int i=0; i<10; i++)
    printf("%d, ", nums[i]);
  printf("]\n\n");

  printf("------------------------\n");
  printf("Copying array to file...\n");
  printf("------------------------\n");
  printf("Opening...\n");
  int save_file = open("save.txt", O_CREAT|O_WRONLY, 0700);
  
  if(save_file == -1){
    printf("--> Error opening save file: %s\n", strerror(errno));
    return 1;
  }

  printf("--> Open successful\n\n");
  printf("Attempting copy from array to file...\n");

  int w = write(save_file, nums, 10*sizeof(int));
  
  if(w==-1){
    printf("--> Error writing save file: %s\n", strerror(errno));
    return 2;
  }
  
  printf("--> Write successful\n\n");
  printf("Closing file...\n\n");
  close(save_file);

  printf("--------------------------------\n");
  printf("Copying file content to array...\n");
  printf("--------------------------------\n");
  printf("Opening...\n");
  save_file = open("save.txt", O_RDONLY, 0700);
  
  if(save_file == -1){
    printf("--> Error opening save file: %s\n", strerror(errno));
    return 3;
  }

  printf("--> Open successful\n\n");
  printf("Attempting copy from file to array...\n");

  int new_nums[10];
  int r = read(save_file, new_nums, 10*sizeof(int));
  
  if(r==-1){
    printf("--> Error reading save file: %s\n", strerror(errno));
    return 4;
  }
  
  printf("--> read successful\n");
  printf("--> printing array new_nums:\n");
  printf("    --> [");
   for(int i=0; i<10; i++)
     printf("%d, ", new_nums[i]);
  printf("]\n\n");
  

  printf("Closing file...\n");
  close(save_file);

  return 0;
}
