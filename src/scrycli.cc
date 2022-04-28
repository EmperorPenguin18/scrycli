//Scrycli by Sebastien MacDougall-Landry
//License is available at
//https://github.com/EmperorPenguin18/scrycli/blob/main/LICENSE

#include "scrycli.h"

using namespace std;

ScryCli::ScryCli(unsigned int space, unsigned int gap) : m_space(space), m_gap(gap) {
  scry_lib = dlopen("libscry.so", RTLD_LAZY);
  if (!scry_lib) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }
  create = (Scry* (*)())dlsym(scry_lib, "create_object");
  scry = (Scry*)create();
}

ScryCli::~ScryCli() {
  destroy = (void (*)(Scry*))dlsym(scry_lib, "destroy_object");
  destroy(scry);
  dlclose(scry_lib);
}

ScryCli::cardstruct ScryCli::construct_card(Card* card) {
  cardstruct output;
  output.name = card->name();
  output.mana_cost = card->mana_cost();
  output.type_line = card->type_line();
  output.oracle_text = card->oracle_text();
  output.power = card->power();
  output.toughness = card->toughness();
  output.loyalty = card->loyalty();
  return output;
}

string ScryCli::multi(char* arg) {
  List* list = scry->cards_search_cache(arg);
  if (!list) {
    cerr << "Search failed" << endl;
    exit(EXIT_FAILURE);
  }
  vector<Card*> cards = list->cards();
  string output = "";
  if (cards.size() > 1) output += to_string(cards.size()) + " results returned\n\n";
  winsize w;
  for (int i = 0; i < cards.size(); i+=(w.ws_col/(m_space+m_gap)) ) {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    vector<string> cardstr;
    for (int j = 0; j < w.ws_col/(m_space+m_gap); j++) {
      if (i+j == cards.size()) break;
      if (cards[i+j]->dual_sided()) {
	vector<Card*> splitcard = scry->split(cards[i+j]);
	cardstruct card;
	string output = "";
	for (int k = 0; k < splitcard.size(); k++) {
	  card = construct_card(splitcard[k]);
          if (k != splitcard.size()-1)
	    output += format(card) + "//\n";
	  else output += format(card) + "\n";
	}
	cardstr.push_back(output);
      } else {
        cardstruct card = construct_card(cards[i+j]);
        cardstr.push_back(format(card) + "\n");
      }
    }
    output += combine(cardstr) + "\n\n";
  }
  return output;
}

string ScryCli::linesize(string line, int size) {
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

string ScryCli::format(cardstruct card) {
  string tab(m_gap/2, ' ');
  regex dash("—");
  regex sub("−");
  regex dot("•");
  string output = linesize(card.name + tab + 
    card.mana_cost, m_space) + "\n";
  output += linesize(card.type_line, m_space) + "\n";
  output += linesize(card.oracle_text, m_space) + "\n";
  if (card.power.size() > 0)
    output += tab + tab + tab + tab + card.power + "/" + 
      card.toughness + "\n";
  if (card.loyalty.size() > 0)
    output += tab + tab + tab + tab + card.loyalty + "\n";
  output = regex_replace(output, dash, "-");
  output = regex_replace(output, sub, "-");
  output = regex_replace(output, dot, "-");
  return output;
}

vector<string> ScryCli::explode(const string& str, const char& ch) {
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

size_t ScryCli::maxsize(vector<vector<string>> input) {
  size_t output = 0;
  for (int i = 0; i < input.size(); i++) {
    if (input[i].size() > output) output = input[i].size();
  }
  return output;
}

string ScryCli::combine(vector<string> strs) {
  vector<vector<string>> exploded;
  for (int i = 0; i < strs.size(); i++) {
    exploded.push_back(explode(strs[i], '\n'));
  }
  string output = "";
  for (int i = 0; i < maxsize(exploded); i++) {
    for (int j = 0; j < exploded.size(); j++) {
      if (exploded[j].size() == i) exploded[j].push_back("");
      int num = m_space+m_gap-exploded[j][i].length();
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
