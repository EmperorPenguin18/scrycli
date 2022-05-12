//Scrycli by Sebastien MacDougall-Landry
//License is available at
//https://github.com/EmperorPenguin18/scrycli/blob/main/LICENSE

#include "scrycli.h"

using namespace std;

const char *argp_program_version = "scrycli 0.2";
const char *argp_program_bug_address = "https://github.com/EmperorPenguin18/scrycli/issues";
static char doc[] = "scrycli uses libscry to fetch card data from Scryfall and cache it. Works as a terminal counterpart to the Scryfall website.";
static char args_doc[] = "SEARCH...";
static struct argp_option options[] = { 
    { "image", 'i', 0, 0, "Show images of cards in the terminal"},
    { "random", 'r', 0, 0, "See a random card"},
    { "advanced", 'a', 0, 0, "Input search terms interactively"},
    { "set", 's', 0, 0, "Look at a list of sets"},
    { 0 } 
};

enum modes{ NORMAL_MODE, SINGLE_MODE, IMAGE_MODE, RANDOM_MODE, ADVANCED_MODE, SET_MODE };
struct arguments {
    enum modes mode;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = (struct arguments*)state->input;
  switch (key) {
    case 'i': arguments->mode = IMAGE_MODE; break;
    case 'r': arguments->mode = RANDOM_MODE; break;
    case 'a': arguments->mode = ADVANCED_MODE; break;
    case 's': arguments->mode = SET_MODE; break;
    case ARGP_KEY_ARG: return 0;
    default: return ARGP_ERR_UNKNOWN;
  }   
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

static char* cat_args(int argc, char **argv) {
  char* output = (char*)calloc(1, 1);
  size_t length = 0;
  for (int i = 1; i < argc; i++) {
    length += strlen(argv[i])+1;
    output = (char*)realloc(output, length+1);
    strcat(output, argv[i]);
    strcat(output, " ");
  }
  return output;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    struct arguments arguments;
    arguments.mode = NORMAL_MODE;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    ScryCli scrycli(35, 10);
    char* search = cat_args(argc, argv);
#ifdef DEBUG
    printf("Query: %s\n", search);
#endif
    
    if (arguments.mode == NORMAL_MODE) {
      cout << scrycli.multi(search);
    }

    free(search);
  }
  return 0;
}
