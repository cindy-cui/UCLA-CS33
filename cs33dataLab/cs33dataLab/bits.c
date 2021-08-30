
 
#include <stdio.h>


/*
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
    /* exploit de morgan's theorem, 2 variables nor'ed is the same as & of the two ~'s */
    return (~x & ~y);
    
}



//2
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
    /*exploit the complement + 1, which is the negative of a number; if x and y are equal, the compliment of y + 1 plus x would be 0*/
    
    int a = (x + (~y + 1));
    return !a; // return !a to return 1 if equal 
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    int xnewn;
    int xnewm;
    int empty = 0;
    int fill = 0;
    
    xnewn = x >> (n<<3) & 0xFF;

    xnewm = x >> (m<<3) & 0xFF;

    empty = ((xnewn << (n<<3)) | (xnewm << (m<<3)));
    
    fill = ((xnewn << (m<<3)) | (xnewm << (n<<3)));
    x = x^empty;
    x = x|fill;
    return x;
}
//3
/* 
 * subtractionOK - Determine if can compute x-y without overflow
 *   Example: subtractionOK(0x80000000,0x80000000) = 1,
 *            subtractionOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subtractionOK(int x, int y) {
    int xsign;
    int ysign;
    int result;
    int input;
    int correctSign; // 0 if correct 1 if not
    
    xsign = (x>>31); // get sign of x parameter
    ysign = (y>>31);
    

    result = x + (~y+1); // subtraction
    result = result>>31; //isolate sign of result
    
    correctSign = xsign^result; //0 if the signs match
    input = xsign^ysign; // only 1 in cases where there might be overflow

    
    return (!(input & correctSign)); // would return 0 if it's a potential overflow case w/ incorrect sign in the result
    
}
/*
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    int ysign = y>>31; //sign bit of y
    int xsign = x>>31; //sign bit of x
    int diffSigns = (!xsign) & (ysign); //1 if x is positive and y is negative
    int sameSign = (xsign^ysign); //0 if the signs match
    int result = x + (~y); // subtraction -1 
    result = result>>31; //isolate sign of result
  
    
    return (diffSigns | !(sameSign|result)); // true if x is positive y is negative or the difference is positive
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
    int fivex;
    int bias;
    int result;
    
    fivex = x + x + x + x + x; //5x
    bias = (fivex>>31) & 8;
    result = (fivex + bias) >> 3; //divide by 8
    
    return result;
}
//4
/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
    int xsign;
    int absoluteValue;
    int result;
    
    xsign = x>>31; //get most significant bit
    absoluteValue = (x+xsign)^(xsign); //obtain the absolute value
    result = xsign <<31; //get the sign bit back to msb
    
    return (result|absoluteValue);


}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int counter = 0;
    
    int sign = (x>>31);
    x = sign ^x;
    sign = sign & 0xf;
    
    sign = !!(x>>16); //check 16 bits
    x = x>>(sign<<4); //if not 0, shift 16 right
    counter = counter + (sign<<4);
    
    sign = !!(x>>8); //check 8 bits
    x = x>>(sign<<3); //if not 0, shift 8 right
    counter = counter + (sign<<3);
    
    sign = !!(x>>4); //check 4 bits
    x = x>>(sign<<2); //if not 0, shift 4 right
    counter = counter + (sign<<2);
    
    sign = !!(x>>2); //check 2 bits
    x = x>>(sign<<1); //if not 0, shift 2 right
    counter = counter + (sign<<1);
    
    sign = !!(x>>1); //check 1 bits
    x = x>>(sign); //if not 0, shift 1 right
    counter = counter + (sign);
    
    counter = counter + (!!x) + 1;
    return counter;
    
    
}
