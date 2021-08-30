
#include <stdio.h>



int main(int argc, const char * argv[]) {
 
    
    int a = ((4 << 1 | 3)^~3); 

    
    printf("%d\n", a);
  



}
/*
 edge cases
 
 umin : 0
 umax : 255 or 4,294,967,295 (11111111)
 tmax : 127 or 2,147,483,647 (0111....)
 tmin : -128 or -2,147,483,648 (1000...)
 -1 : 1111....1111
 0 : 0000....0000
 
 umax = 2*tmax + 1
 */
