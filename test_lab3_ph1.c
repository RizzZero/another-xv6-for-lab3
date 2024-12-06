#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_CHILDREN 3

int main(int argc, char*argv[]) {
  int pid;
  int i;

  printf(1, "Parent process (PID: %d)\n", getpid());

  for (i = 0; i < NUM_CHILDREN; i++) {
    pid = fork();
    if (pid < 0) {
      printf(1, "Fork failed\n");
      exit();
    } else if (pid == 0) {
      // Child process
      int child_pid = getpid();
      int burst_time = (i + 1) * 10;
      int confidence = 70 + i * 10;

      printf(1, "Child %d setting process info...\n", child_pid, child_pid);
      
      int result = set_proc_sched(child_pid, burst_time, confidence);
      
      if (result == 1) {
        printf(1, "Child %d: Successfully set process info (Burst: %d, Confidence: %d)\n", 
               child_pid, burst_time, confidence);
      } else {
        printf(1, "Child %d: Failed to set process info\n", child_pid);
      }

      sleep(100);
      exit();
    }
  }
  for (i = 0; i < NUM_CHILDREN; i++) {
    wait();
  }

  printf(1, "All children have completed. Parent exiting.\n");
  exit();
}
