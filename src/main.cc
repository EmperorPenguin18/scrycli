//Scrycli by Sebastien MacDougall-Landry
//License is available at
//https://github.com/EmperorPenguin18/scrycli/blob/main/LICENSE

#include "scrycli.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    ScryCli scrycli(35, 10);
    cout << scrycli.multi(argv[1]);
  }
  return 0;
}
