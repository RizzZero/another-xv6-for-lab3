#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_CHILDREN 3

int main(void) {
  int pid;
  int i;

  printf(1, "Parent process (PID: %d) starting...\n", getpid());

  for (i = 0; i < NUM_CHILDREN; i++) {
    pid = fork();
    if (pid < 0) {
      printf(1, "Fork failed\n");
      exit();
    } else if (pid == 0) {
      // Child process
      int child_pid = getpid();
      int burst_time = (i + 1) * 10;  // Different burst time for each child
      int confidence = 70 + i * 10;   // Different confidence for each child
      int arrival_time = i * 5;       // Different arrival time for each child

      printf(1, "Child %d (PID: %d) setting process info...\n", i, child_pid);
      
      int result = set_process_info(child_pid, burst_time, confidence, arrival_time);
      
      if (result == 0) {
        printf(1, "Child %d: Successfully set process info (Burst: %d, Confidence: %d, Arrival: %d)\n", 
               i, burst_time, confidence, arrival_time);
      } else {
        printf(1, "Child %d: Failed to set process info\n", i);
      }

      // Sleep to allow parent to read info before child exits
      sleep(100);
      exit();
    }
  }

  // Parent process
  for (i = 0; i < NUM_CHILDREN; i++) {
    wait();
  }

  printf(1, "All children have completed. Parent exiting.\n");
  exit();
}
