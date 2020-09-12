/*
  Example of getopt_long usage

  Copyright 2010, James D. Teresco
  Mount Holyoke College
  Computer Science 322

  Updated for CSC 381, The College of Saint Rose, Fall 2015
  CSIS 330, Siena College, Fall 2020
*/

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/* first, some macros you might find useful for parsing params with
   integer values */

/* macros to simplify parameter parsing code */
#define PARSE_POSITIVE_PARAM(PARAMVAR, PARAMNAME) \
 { PARAMVAR = strtol(optarg, NULL, 10); \
      if (PARAMVAR < 1) { \
	fprintf(stderr, \
		"%s: WARNING: Invalid %s %s provided, assuming 1.\n", \
		argv[0], PARAMNAME, optarg); \
	PARAMVAR = 1; \
      } \
 }

#define PARSE_NONNEGATIVE_PARAM(PARAMVAR, PARAMNAME) \
 { PARAMVAR = strtol(optarg, NULL, 10); \
      if (PARAMVAR < 1) { \
	if (errno || PARAMVAR < 0) { \
	  fprintf(stderr, \
		  "%s: WARNING: Invalid %s %s provided, assuming 0.\n", \
		  argv[0], PARAMNAME, optarg); \
	  PARAMVAR = 0; \
        } \
      } \
 }

/* it's always nice to have a usage function to call when you find out
   that something isn't right on the command line */
static void usage(char *program) {
  printf("Usage: %s --num-iters i [--the-file filename] [--days-until-break n]\n",
	 program);
  printf("[--verbose] [--help]\n");
}


/* this is a silly little program that just takes some parameters
   and prints out information about the settings determined by 
   those parameters */

int main(int argc, char *argv[]) {

  /* a file name */
  char the_file[FILENAME_MAX] = "default.txt";

  /* other params we'll set */
  int days_until_break = 0;
  int num_iters = -1;  /* Here, the -1 is used to ensure we specify something.
			  If still -1 after parsing params, we issue an error */

  /* variable needed for getopt_long */
  int ch;

  /* define our "long" equivalents for the short options */

  struct option longopts[] = {
    { "the-file", required_argument, NULL, 'f' },
    { "num-iters", required_argument, NULL, 'i' },
    { "days-until-break", required_argument, NULL, 'b' },
    { "help", no_argument, NULL, 'h' },
    { "verbose", no_argument, NULL, 'v' },
    { 0, 0, 0, 0 }
  };

  int option_index = 0;

  /* was verbose specified?  Default of 0 will be overridden by -v */
  int verbose = 0;

  /* process command-line parameters */
  /* the string here has the short option names, which are followed
     by a colon if they take a parameter, no colon if they are standalone */
  /* if an value exists after the option, it is specified in char *optarg */
  while ((ch = getopt_long(argc, argv, "f:i:b:hv", 
			   longopts, &option_index)) != -1) {
    switch (ch) {

    case 'f':
      /* the file name */
      strcpy(the_file, optarg);
      break;

    case 'i':
      /* number of "iterations" -- must be a positive number */
      PARSE_POSITIVE_PARAM(num_iters, "--num-iters");
      break;

    case 'b':
      /* days until break -- non-negative integer */
      PARSE_NONNEGATIVE_PARAM(days_until_break, "--days-until-break");
      break;

    case 'h':
      /* print help message */
      printf("Help!  I'm a C programmer trying to understand getopt_long!\n");
      usage(argv[0]);
      return 0;

    case 'v':
      /* set verbose mode */
      verbose = 1;
      break;


    default:
      usage(argv[0]);
      return 1;
    }
  }

  /* make sure num_iters was specified */
  if (num_iters == -1) {
    fprintf(stderr, "Required --num-iters not specified.\n");
    usage(argv[0]);
    return 1;
  }

  printf("Well, you seemed to specify the following:\n");
  printf("the-file: %s\n", the_file);
  printf("num-iters: %d\n", num_iters);
  printf("days-until-break: %d\n", days_until_break);
  printf("verbose mode is %s\n", (verbose ? "on" : "off"));
  return 0;
}
