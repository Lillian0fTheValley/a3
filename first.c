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

  read_char();      /* read character into d0*/
  d1 = d0 & 0x000000FF;          /* perform AND operation on d0 and stores results in d1*/
  printf("%d", d1);

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
  d3 = d0 & 0x000000FF;          /*performs AND operation on contents of d0 and stores result in d3 */

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

  printf("%d, %d, %d", d1, d2, d3);
  //eeeeee

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