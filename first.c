/*
Student: Lillian Ma - 201722465
Class: COMP 2655-002
Professor: Terrance Mok
*/

#define _DEFAULT_SOURCE 1  /* don't worry about this - simply needed for IO stuff */

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <time.h>


#define CR 13
#define LF 10

#define bool int
#define true 1
#define false 0


/* Note: read_char is written to simulate the 68000 implementation, where
         the high 24 bits of d0 are left in an undefined state after the
         call.
*/

void read_char();   /* output passed back in low 8 bits of d0 */
void write_char();  /* input passed in low 8 bits of d0 */

void cleanup();     /* don't worry about this */

                    /* don't worry about this */
struct termios orig;
                    /* simulate 68000 data registers */
int d0, d1, d2, d3, d4, d5, d6, d7;


int main()
{
  /* [TO DO] ALTER THE ALGORITHM IN main SO THAT IT SATISFIES THE ASSIGNMENT
             SPEC.  YOU ARE NOT ALLOWED TO CALL ANY FUNCTIONS OTHER THAN
             read_char AND write_char, AND YOU ARE NOT ALLOWED TO CODE ANY
             BRANCHES (i.e. NO DECISIONS, LOOPS, ETC).

             currently, reads a single character, then writes it back: 
  */

  /*
    Register Table:
    d0 - input - receives keyboard input
    d0 - output - holds character to be written

    d1 - input - receives AND result from d0 which represents the first character input
    d1 - arithmetic - stores result of d7 * d7 = x^2
    d1 - arithmetic - stores result of 288 * d1 = 288*x^2
    d1 - arithmetic - stores result of dividing y to isolate hundreds digit


    d2 - input - receives AND result from d0 which represents the second character input
    d2 - arithmetic - stores result of 3171 * d7 = 3171*x
    d2 - arithmetic - stores result of dividing y to isolate tens digit

    d3 - input - receives AND result from d0 which represents the third character input
    d3 - arithmetic - stores result of d2 / 73 = (3171*x)/73
    d3 - arithmetic - stores result of dividing y to isolate ones digit

    d4 - arithmetic - receives result of conversion of d1 ascii value to int
    d4 - arithmetic - stores int 5286 for use in computation
    
    d5 - arithmetic - receives result of conversion of d2 ascii value to int
    d5 - arithmetic - stores result of d1 - d3 = 288*x^2 - (3171*x)/73
    d5 - arithmetic - stores result of d4 + d5 = 288*x^2 - (3171*x)/73 + 5286

    d6 - arithmetic - receives result of conversion of d3 ascii value to int
    d6 - arithmetic - receives result of d5 % 10000 = (288*x^2 - (3171*x)/73 + 5286) % 10000
    d6 - arithmetic - receives result of d6 / 10 = ((288*x^2 - (3171*x)/73 + 5286) % 10000) / 10

    d7 - arithmetic - stores (x) result of performing horner's rule on ints stored in d4, d5, d6
  */

  //BEGIN INPUT SECTION
  read_char();      /* read character into d0*/
  d1 = d0 & 0x000000FF;          /* perform AND operation on d0 and stores results in d1*/

  d0 = CR;          /* go to a new line */
  write_char();   //write carriage return
  d0 = LF;
  write_char(); //write line feed

  d0 = d1;        //load d1 into d0 to to be written
  write_char();     /* echo character */

  d0 = CR;          /* go to a new line */
  write_char();     //write carriage return
  d0 = LF;
  write_char();     //write line feed

  //--------------------------------------------------

  read_char();      /* read character into d0*/
  d2 = d0 & 0x000000FF;          /* perform AND operation on contents of d0 and stores result in d2 */

  d0 = CR;          /* go to a new line */
  write_char();   //write carriage return
  d0 = LF;
  write_char(); //write line feed

  d0 = d1;        //load d1 into d0 to to be written
  write_char();     /* echo character */

  d0 = CR;          /* go to a new line */
  write_char();     //write carriage return
  d0 = LF;
  write_char();     //write line feed

  //--------------------------------------------------

  read_char();      /* read character */
  d3 = d0 & 0x000000FF; /*performs AND operation on contents of d0 and stores result in d3 */

  d0 = CR;          /* go to a new line */
  write_char();   //write carriage return
  d0 = LF;
  write_char(); //write line feed

  d0 = d1;        //load d1 into d0 to to be written
  write_char();     /* echo character */

  d0 = CR;          /* go to a new line */
  write_char();     //write carriage return
  d0 = LF;
  write_char();     //write line feed
  //END INPUT SECTION

  //BEGIN COMPUTATION SECTION
  //emulating horner's rule here
  d4 = d1 - '0';//converting d1 from ascii to int
  d5 = d2 - '0';//converting d2 from ascii to int
  d6 = d3 - '0';//converting d3 from ascii to int

  d7 = d4 * 10;//(a * 10) HORNERS RULE
  d7 = d7 + d5;//(a * 10) + b
  d7 = d7 * 10;//((a * 10) + b)10
  d7 = d7 + d6;//((a * 10) * b)10 + c

  d1 = d7 * d7; //d1 = x^2
  d1 = 288 * d1; //d1 = 288 * x^2
  
  d2 = 3171 * d7; //d2 = 3171 * x
  d3 = d2 / 73; //(3171 * x) / 73
  
  d4 = 5286;
  
  d5 = d1 - d3; //d5 = 288*x^2 - (3171*x)/73
  d5 = d4 + d5; //d5 = 288*x^2 - (3171*x)/73 + 5286

  d6 = d5 % 10000; //d5 = (288*x^2 - (3171*x)/73 + 5286) % 10000
  d6 = d6 / 10;
  //END COMPUTATION SECTION

  //BEGIN OUTPUT SECTION
  d1 = d6 / 100; //isolating hundreds digit and storing in d1
  d1 = d1 + '0'; //converting d1 int to ascii

  d2 = d6 / 10; //isolating tens digit and storing in d2
  d2 = d2 % 10;//isolating tens digit and storing in d2
  d2 = d2 + '0';//converting d2 int to ascii

  d3 = d6 % 10;//isolating ones digit and storing in d3
  d3 = d3 + '0';//converting d3 int to ascii

  d0 = d1;//moving hundreds digit to d0 for writing to screen
  write_char();

  d0 = d2;//moving tens digit to d0 for writing to screen
  write_char();

  d0 = d3;//moving ones digit to d0 for writing to screen
  write_char();
  //END OUTPUT SECTION
  return 0;         /* exit */
}


/* don't worry about how this works, just call it */
void read_char()
{
  static bool first_call = true;
  struct termios term;
  char ch;
  time_t now;

  if (first_call)
    {
      time(&now);
      srand((unsigned int)now);
      tcgetattr(0, &orig);
      term = orig;
      atexit(cleanup);
      cfmakeraw(&term);
      term.c_lflag |= ECHO;
      tcsetattr(0, 0, &term);
      first_call = false;
    }

  ch = (char) getchar();
  d0 = (int) ((rand() & 0x00FF0000) | (unsigned int)ch);

}


void write_char()
{
  putchar((int)d0);
}


/* don't worry about this */
void cleanup()
{
  tcsetattr(0, 0, &orig);
}