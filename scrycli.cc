//Scrycli by Sebastien MacDougall-Landry
//License is available at
//https://github.com/EmperorPenguin18/scrycli/blob/main/LICENSE

#include <dlfcn.h>
#include <iostream>
#include <libscry.h>

using namespace std;

struct cardstruct {
	string name;
	string mana_cost;
	string type_line;
	string oracle_text;
	string power;
	string toughness;
};

string format(cardstruct card) {
  string output = card.name + "\t" + 
    card.mana_cost + "\n";
  output += card.type_line + "\n";
  output += card.oracle_text + "\n";
  if (card.power.size() > 0)
    output += "\t\t" + card.power + "/" + 
      card.toughness + "\n";
  return output;
}

int main(int argc, char **argv)
{
  void* handle = dlopen("/usr/lib/libscry.so", RTLD_LAZY);
  Scry* (*create)();
  void (*destroy)(Scry*);
  create = (Scry* (*)())dlsym(handle, "create_object");
  destroy = (void (*)(Scry*))dlsym(handle, "destroy_object");

  if (argc > 1) {
    Scry* scry = (Scry*)create();
    List * list = scry->cards_search_cache(argv[1]);
    vector<Card *> cards = list->allcards();
    for (int i = 0; i < cards.size(); i++) {
      if (cards[i]->dual_sided()) {
	vector<Card *> splitcard = scry->split(cards[i]);
	cardstruct card;
	for (int j = 0; j < splitcard.size(); j++) {
	  card.name = splitcard[j]->name();
          card.mana_cost = splitcard[j]->mana_cost();
          card.type_line = splitcard[j]->type_line();
          card.oracle_text = splitcard[j]->oracle_text();
          card.power = splitcard[j]->power();
          card.toughness = splitcard[j]->toughness();
          if (j != splitcard.size()-1)
	    cout << format(card) << "//\n";
	  else cout << format(card) << endl;
	}
      } else {
        cardstruct card;
        card.name = cards[i]->name();
        card.mana_cost = cards[i]->mana_cost();
        card.type_line = cards[i]->type_line();
        card.oracle_text = cards[i]->oracle_text();
        card.power = cards[i]->power();
        card.toughness = cards[i]->toughness();
        cout << format(card) << endl;
      }
    }
    destroy( scry );
  }
}
