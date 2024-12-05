#include "types.h"
#include "user.h"

int
main(){
    for(int i = 0 ; i < 5 ; ++i){
        int pid = fork();
        if(pid == 0){
            sleep(5000);
            for(int j = 0 ; j < 100000000000 ; ++j){
                int x  = 1;
                for(long k = 0 ; k < 100000000000; ++k){
                    x++;
                }
                exit();
            }
        }
    }
    for(int i = 0 ; i<5 ; ++i){
        wait();
    }
    exit();
}