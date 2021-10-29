#include <dlfcn.h>
#include <iostream>
#include <libscry.h>

using namespace std;

int main(int argc, char **argv)
{
  void* handle = dlopen("/usr/lib/libscry.so", RTLD_LAZY);

  Scry* (*create)();
  void (*destroy)(Scry*);

  create = (Scry* (*)())dlsym(handle, "create_object");
  destroy = (void (*)(Scry*))dlsym(handle, "destroy_object");

  Scry* scry = (Scry*)create();
  vector island_search = scry->cards_search("commander:g");
  cout << island_search[5000]->name() << endl;
  Card * island = scry->cards_named("island");
  cout << island->getName() << endl;
  vector prime = scry->cards_autocomplete("prime");
  cout << prime[0] << endl;
  Card * random = scry->cards_random();
  cout << random->name() << endl;
  destroy(scry);
}
