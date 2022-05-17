//Scrycli by Sebastien MacDougall-Landry
//License is available at
//https://github.com/EmperorPenguin18/scrycli/blob/main/LICENSE

#pragma once
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <argp.h>
#include <scry/scry.h>

using namespace std;

class ScryCli {
  public:
    ScryCli(unsigned int, unsigned int);
    ~ScryCli();

    string multi(char*);
    string single(char*);
  private:
    void* scry_lib;
    Scry* (*create)();
    void (*destroy)(Scry*);

    Scry* scry;
    unsigned int m_space;
    unsigned int m_gap;
    struct cardstruct {
      string name;
      string mana_cost;
      string type_line;
      string oracle_text;
      string power;
      string toughness;
      string loyalty;
    };

    string linesize(string, int);
    string format(cardstruct);
    vector<string> explode(const string&, const char&);
    size_t maxsize(vector<vector<string>>);
    string combine(vector<string>);
    cardstruct construct_card(Card*);
};
