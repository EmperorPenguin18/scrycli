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
  Card island = scry->cards_named("island");
  cout << island.getName() << endl;
  scry->cleanup();
  destroy( scry );
}
