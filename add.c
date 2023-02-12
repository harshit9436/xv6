#include "types.h"
#include "stat.h"
#include "user.h"

 
int main(int argc, char** argv) {
    if(argc != 3){
        printf(1,"Wrong number of arguments %d give, 3 required",argc);
        exit();
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int result = add(a,b);
    printf(1, "%d + %d = %d\n", a, b, result);

    
    exit();
 }