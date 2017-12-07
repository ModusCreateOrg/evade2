// Constants
#ifndef RD_FAIL
#define RD_FAIL "Failed to load file"
#endif

#ifndef SZ_FAIL
#define SZ_FAIL "Image dimensions exceed 255px limit"
#endif

#ifndef WR_FAIL
#define WR_FAIL "Failed to write to file"
#endif

#ifndef NO_MEM
#define NO_MEM "Failed to allocate"
#endif

#ifdef _WIN32
#define PATH_SEP   "\\"
#else
#define PATH_SEP   "/"
#endif

#define STB_IMAGE_IMPLEMENTATION

// Colors
#define OK  "\x1b[32m"
#define INF "\x1b[36m"
#define RST "\x1b[0m"
#define ERR "\x1b[31m"

// Includes
#include <argp.h>
#include <libgen.h>
#include "stb_image.h"

// Typedefs
typedef struct Bytes Bytes;
typedef struct Arguments Arguments;

// Structs
struct Bytes {
    char *file;
    unsigned char *data;
    unsigned long int length;
};

struct Arguments {
  char **images;
  char *output;
  int verbosity;
};

static struct argp_option options[] = {
  {"verbosity", 'v', 0, 0, "Produce verbose output"},
  {"output", 'o', "DIR", 0, "Write output to file in DIR"},
  { 0 }
};

// Functions
Bytes *image_to_bytes(char *const filename);
void free_bytes(Bytes *bytes);
void print_bytes(const Bytes *bytes);
void export_bytes(const Bytes *bytes);
void bytes_to_ascii(const Bytes *bytes);

// Utils
char *build_path(const char *dir, const char *file);
char *replace_file_ext(const char *str, const char *rep);
static error_t parse_opt(int key, char *arg, struct argp_state *state);

// Variables
Arguments arguments;
static char args_doc[] = "[INPUT...]";
static char doc[] = "Convert image(s) to byte array";
const char *argp_program_version = "image2bytes 1.0";
static struct argp argp = {options, parse_opt, args_doc, doc};
