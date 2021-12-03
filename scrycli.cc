//Scrycli by Sebastien MacDougall-Landry
//License is available at
//https://github.com/EmperorPenguin18/scrycli/blob/main/LICENSE

#include <dlfcn.h>
#include <iostream>
#include <libscry.h>
#include <sys/ioctl.h>
#include <regex>
#define SPACE 35
#define GAP 10

using namespace std;

struct cardstruct {
  string name;
  string mana_cost;
  string type_line;
  string oracle_text;
  string power;
  string toughness;
  string loyalty;
};

string linesize(string line, int size) {
  string output = "";
  while (line.length() > size) {
    int num = line.find(' ', size);
    if (num < 0) break;
    output += line.substr(0, num+1) + "\n";
    line = line.substr(num+1, line.length()-num-1);
  }
  output += line;
  return output;
}

string format(cardstruct card) {
  string tab(GAP/2, ' ');
  regex dash("—");
  string output = linesize(card.name + tab + 
    card.mana_cost, SPACE) + "\n";
  output += linesize(card.type_line, SPACE) + "\n";
  output += linesize(card.oracle_text, SPACE) + "\n";
  if (card.power.size() > 0)
    output += tab + tab + tab + tab + card.power + "/" + 
      card.toughness + "\n";
  if (card.loyalty.size() > 0)
    output += tab + tab + tab + tab + card.loyalty + "\n";
  output = regex_replace(output, dash, "-");
  return output;
}

vector<string> explode(const string& str, const char& ch) {
  string next;
  vector<string> result;
  for (string::const_iterator it = str.begin(); it != str.end(); it++) {
    if (*it == ch) {
      if (!next.empty()) {
        result.push_back(next);
        next.clear();
      }
    } else next += *it;
  }
  if (!next.empty()) result.push_back(next);
  return result;
}

size_t maxsize(vector<vector<string>> input) {
  size_t output = 0;
  for (int i = 0; i < input.size(); i++) {
    if (input[i].size() > output) output = input[i].size();
  }
  return output;
}

string combine(vector<string> strs) {
  vector<vector<string>> exploded;
  for (int i = 0; i < strs.size(); i++) {
    exploded.push_back(explode(strs[i], '\n'));
  }
  string output = "";
  for (int i = 0; i < maxsize(exploded); i++) {
    for (int j = 0; j < exploded.size(); j++) {
      if (exploded[j].size() == i) exploded[j].push_back("");
      int num = SPACE+GAP-exploded[j][i].length();
      string * whitespace;
      if (num > 0) whitespace = new string(num, ' ');
      else whitespace = new string("");
      output.append(exploded[j][i] + *whitespace);
      delete(whitespace);
    }
    output += "\n";
  }
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
    struct winsize w;
    for (int i = 0; i < cards.size(); i+=(w.ws_col/(SPACE+GAP)) ) {
      ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
      vector<string> cardstr;
      for (int j = 0; j < w.ws_col/(SPACE+GAP); j++) {
	if (i+j == cards.size()) break;
        if (cards[i+j]->dual_sided()) {
	  vector<Card *> splitcard = scry->split(cards[i+j]);
	  cardstruct card;
	  string output = "";
	  for (int k = 0; k < splitcard.size(); k++) {
	    card.name = splitcard[k]->name();
            card.mana_cost = splitcard[k]->mana_cost();
            card.type_line = splitcard[k]->type_line();
            card.oracle_text = splitcard[k]->oracle_text();
            card.power = splitcard[k]->power();
            card.toughness = splitcard[k]->toughness();
	    card.loyalty = splitcard[k]->loyalty();
            if (k != splitcard.size()-1)
	      output += format(card) + "//\n";
	    else output += format(card) + "\n";
	  }
	  cardstr.push_back(output);
        } else {
          cardstruct card;
          card.name = cards[i+j]->name();
          card.mana_cost = cards[i+j]->mana_cost();
          card.type_line = cards[i+j]->type_line();
          card.oracle_text = cards[i+j]->oracle_text();
          card.power = cards[i+j]->power();
          card.toughness = cards[i+j]->toughness();
	  card.loyalty = cards[i+j]->loyalty();
          cardstr.push_back(format(card) + "\n");
        }
      }
      cout << combine(cardstr) << endl << endl;
    }
    destroy( scry );
  }
}
