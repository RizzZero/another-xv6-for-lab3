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
  
  pid = fork();
  
  if(pid < 0) {
    printf(2, "Fork failed\n");
    exit();
  } else if(pid == 0) {
    // Child process
    printf(1, "Child process (PID: %d) created\n", getpid());
    sleep(100);  // Give parent time to change queue
    exit();
  } else {
    // Parent process
    printf(1, "Parent attempting to change child's (PID: %d) queue to %d\n", pid, queue);
    
    int result = change_queue(pid, queue);
    
    if(result == 1) {
      printf(1, "Successfully changed queue for process %d to %d\n", pid, queue);
    } else {
      printf(2, "Failed to change queue for process %d\n", pid);
    }
    
    wait();  // Wait for child to exit
  }
  
  exit();
}
