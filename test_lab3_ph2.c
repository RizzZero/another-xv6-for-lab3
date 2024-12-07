#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid, queue;
  
  if(argc != 3) {
    printf(2, "please give a pid and a queue in the command line please!\n");
    exit();
  }
  
  queue = atoi(argv[2]);
  pid = atoi(argv[1]);
  if(pid < 0) {
    printf(2, "pid should be positive\n");
    exit();
    return -1;
  }
      
  int result = change_queue(pid, queue);
    
  if(result == 1) {
    printf(1, "Successfully changed queue for process %d to %d\n", pid, queue);
  } else {
    printf(2, "Failed to change queue for process %d\n", pid);
  }
    
  wait(); 
  exit();
}
