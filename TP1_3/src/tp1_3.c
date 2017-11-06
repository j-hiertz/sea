/**
 * \file skeleton.c
 * \brief Basic parsing options skeleton.
 * \author Pierre L. <pierre1.leroy@orange.com>
 * \version 0.1
 * \date 10 septembre 2016
 *
 * Basic parsing options skeleton exemple c file.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#include<getopt.h>


#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096

#define USAGE_SYNTAX "[path/to/directory]"
#define USAGE_PARAMS "OPTIONS:\n\
  -i, --input  INPUT_FILE  : input file\n\
***\n\
  -a, --all : do not ignore entries starting with .\n\
  -c, --color : colorize the output; WHEN can be 'always' (default if omitted), 'auto', or 'never\n\
  -l, --long : use a long listing format\n\
  -t, --time : sort by modification time, newest first\n\
  -s, --size : print the allocated size of each file, in blocks\n\
  -v, --verbose : enable *verbose* mode\n\
  -h, --help    : display this help\n\
"

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
  dprintf(1, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}


/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* to_free pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void free_if_needed(void* to_free)
{
  if (to_free != NULL) free(to_free);  
}


/**
 *
 * \see man 3 strndup
 * \see man 3 perror
 * \return
 */
char* dup_optarg_str()
{
  char* str = NULL;

  if (optarg != NULL)
  {
    str = strndup(optarg, MAX_PATH_LENGTH);
    
    // Checking if ERRNO is set
    if (str == NULL) 
      perror(strerror(errno));
  }

  return str;
}


/**
 * Binary options declaration
 * (must end with {0,0,0,0})
 *
 * \see man 3 getopt_long or getopt
 * \see struct option definition
 */
static struct option binary_opts[] = 
{
  { "all",     no_argument,       0, 'a' },
  { "color",   optional_argument, 0, 'c' },
  { "long",    no_argument,       0, 'l' },
  { "size",    no_argument,       0, 's' },
  { "time",    no_argument,       0, 't' },
  { "help",    no_argument,       0, 'h' },
  { "verbose", no_argument,       0, 'v' },
  { 0,         0,                 0,  0  } 
};

/**
 * Binary options string
 * (linked to optionn declaration)
 *
 * \see man 3 getopt_long or getopt
 */ 
const char* binary_optstr = "ac:lsthv";



/**
 * Binary main loop
 *
 * \return 1 if it exit successfully 
 */
int main(int argc, char** argv)
{
  /**
   * Binary variables
   * (could be defined in a structure)
   */
  short int is_verbose_mode = 0;
  short int print_all_file = 0;
  char* color_mode = NULL;
  short int print_long_information = 0;
  short int print_size = 0;
  short int print_by_last_modification = 0;
  char* bin_input_param = NULL;

  // Parsing options
  int opt = -1;
  int opt_idx = -1;

  while ((opt = getopt_long(argc, argv, binary_optstr, binary_opts, &opt_idx)) != -1)
  {
    switch (opt)
    {
      case 'a':
        //all param
        print_all_file = 1;
        break;
      case 'c':
        //color param
        if (optarg)
        {
          color_mode = dup_optarg_str();         
        }
        break;
      case 'l':
        //list param
        print_long_information = 1;
        break;
      case 's':
        //list param
        print_size = 1;
        break;
      case 't':
        //list param
        print_by_last_modification = 1;
        break;
      case 'v':
        //verbose mode
        is_verbose_mode = 1;
        break;
      case 'h':
        print_usage(argv[0]);

        free_if_needed(bin_input_param);
 
        exit(EXIT_SUCCESS);
      default :
        break;
    }
  } 

  if (color_mode == NULL)
  {
    color_mode = "always";
  }


  // Printing params
  dprintf(1, "** PARAMS **\n%-8s: %d\n%-8s: %s\n%-8s: %d\n%-8s: %d\n%-8s: %d\n%-8s: %d\n", 
          "all",   print_all_file,
          "color",   color_mode, 
          "long",   print_long_information,
          "size",   print_size, 
          "time",   print_by_last_modification, 
          "verbose", is_verbose_mode);


  // Freeing allocated data
  free_if_needed(bin_input_param);


  return EXIT_SUCCESS;
}