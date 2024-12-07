#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid, new_queue;
  
  if(argc != 2) {
    printf(2, "Usage: change_queue_test <new_queue>\n");
    exit();
  }
  
  new_queue = atoi(argv[1]);
  
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
    printf(1, "Parent attempting to change child's (PID: %d) queue to %d\n", pid, new_queue);
    
    int result = change_queue(pid, new_queue);
    
    if(result == 0) {
      printf(1, "Successfully changed queue for process %d to %d\n", pid, new_queue);
    } else {
      printf(2, "Failed to change queue for process %d\n", pid);
    }
    
    wait();  // Wait for child to exit
  }
  
  exit();
}
