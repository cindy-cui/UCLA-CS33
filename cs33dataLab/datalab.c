/* 
 * CS:APP Data Lab 
 * 
 * Cindy Cui 105517813
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//1
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
       /*exploit de morgan's theorem, 2 variables nor'ed is equivalent to & of the two complements*/ 
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
  /*exploit the complement +1, which is the negative value of a number; sum of x and compliment of y + 1 would be 0 if they're equal */
  int a = (x + (~y + 1)); 
  return !a; // ! in order to return 1 when equal and 0 otherwise 
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
  /* exploit shifts and & to isolate desired bytes and other operators to replace the bytes*/

  int xnewn; 
  int xnewm; 
  int empty = 0; 
  int fill = 0; 

  xnewn = x >> (n<<3) & 0xFF; //shift desired byte to the right and isolate 
  xnewm = x >> (m<<3) & 0xFF; // shift m to the right and isolate 

  empty = (xnewn << (n<<3)) | (xnewm << (m<<3)); //use to empty the desired bytes in x 
  x = x^empty; //desired bytes 0 
  
  fill = (xnewn << (m<<3)) | (xnewm << (n<<3)); //swap position of bytes with the rest being 0's
  x = x|fill; //fill bytes with swapped version 

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
  /*exploit shifts, ^, and & operators to check if subtraction is possible without overflow*/
  int xsign;
  int ysign; 
  int result; 
  int input; 
  int correctSign; 

  xsign = (x>>31); //isolate sign of x parameter
  ysign = (y>>31); //isolate sign of y parameter

  result = x + (~y+1); // calculate result of subtraction 
  result = result>>31; //isolate sign of result 

  correctSign = xsign^result; //0 if the signs match  
  input = xsign^ysign; //only 1 in cases with potential overflow 

  return (!(input&correctSign)); //would return 0 if potential overflow case with wrong sign for result 

}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /*exploits shifts to compare signs and difference to evaluate x > y */
  int ysign = y>>31; //sign bit isolation 
  int xsign = x>>31; 
  int diffSigns = ((!xsign) & ysign); // 1 if x is positive and y is negative

  int sameSign =(xsign^ysign); //1 if signs match 
  int difference = x+~y; //x-y-1
  difference = difference >>31; //1 if x is greater thus negative difference

  return (diffSigns |! (sameSign | difference)); //true if x is pos and y is neg or same sign positive difference 

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
  /*exploits shifts to calculate 5/8ths with a determined bias*/
  int fivex; 
  int bias; 
  int result; 

  fivex = x + x + x + x + x; //5x 
  bias = (fivex>>31) & 7; 
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
  /*exploit shifts ability to obtain msb*/
  int xsign; 
  int absoluteValue; 
  int result; 

  xsign = x>>31; //get most significant bit 
  absoluteValue = (x+xsign)^(xsign); 
  result = xsign << 31; //get sign bit back to msg 

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
  /*exploit shifts and comparisons to compute minimum num of bits required*/

  int counter = 0; 
  int sign = (x>>31); 
  x = sign^x; //which bits are significant 
  sign = sign & 0x0f; //isolate msb 

  sign = !!(x>>16); //check first 16 
  x = x >> (sign << 4); //if not 0, shift 16 right 
  counter = counter + (sign << 4); //increment by 16 

  sign = !!(x>>8); //check 8
  x = x >> (sign << 3); //shift 8 right 
  counter = counter + (sign << 3); //increment by 8

  sign = !!(x>>4); //check 4 
  x = x >> (sign << 2); //shift 4 right 
  counter = counter + (sign << 2); //increment by 4 

  sign = !!(x>>2); //check 2 bits 
  x = x >> (sign << 1); //shift 2 right 
  counter = counter + (sign << 1); //increment by 2

  sign = !!(x>>1); //check 1 bit 
  x = x >> (sign); //shift 1 right 
  counter = counter + sign; 

  counter = counter + (!!x) + 1; 
  return counter; 

}
