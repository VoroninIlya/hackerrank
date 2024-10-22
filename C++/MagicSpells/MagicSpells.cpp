// MagicSpells.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell {
private:
  string scrollName;
public:
  Spell() : scrollName("") { }
  Spell(string name) : scrollName(name) { }
  virtual ~Spell() { }
  string revealScrollName() {
    return scrollName;
  }
};

class Fireball : public Spell {
private: int power;
public:
  Fireball(int power) : power(power) { }
  void revealFirepower() {
    cout << "Fireball: " << power << endl;
  }
};

class Frostbite : public Spell {
private: int power;
public:
  Frostbite(int power) : power(power) { }
  void revealFrostpower() {
    cout << "Frostbite: " << power << endl;
  }
};

class Thunderstorm : public Spell {
private: int power;
public:
  Thunderstorm(int power) : power(power) { }
  void revealThunderpower() {
    cout << "Thunderstorm: " << power << endl;
  }
};

class Waterbolt : public Spell {
private: int power;
public:
  Waterbolt(int power) : power(power) { }
  void revealWaterpower() {
    cout << "Waterbolt: " << power << endl;
  }
};

class SpellJournal {
public:
  static string journal;
  static string read() {
    return journal;
  }
};
string SpellJournal::journal = "";

void findOptimal(const string& a, const string& b, size_t& n, size_t& m) {

  size_t minN = string::npos, minM = string::npos;
  size_t optN = string::npos, optM = string::npos;

  for(int i = n; i < a.length(); i++) {
    size_t posM = b.find_first_of(a[i], m);
    if(posM != string::npos) {

      if(minN > i)
        minN = i;

      if(minM > posM)
        minM = posM;

      if(optN > i - n || optM > posM) {
        optN = i;
        optM = posM;
      }
    }
  }
  n = optN;
  m = optM;
}

void counterspell(Spell* spell) {

  string type = typeid(*spell).name();
  /* Enter your code here */
  if (type.find("Fireball", 0) != string::npos) {
    Fireball* fb = dynamic_cast<Fireball*>(spell);
    fb->revealFirepower();
  } else
  if (type.find("Frostbite", 0) != string::npos) {
    Frostbite* fb = dynamic_cast<Frostbite*>(spell);
    fb->revealFrostpower();
  } else
  if (type.find("Waterbolt", 0) != string::npos) {
    Waterbolt* fb = dynamic_cast<Waterbolt*>(spell);
    fb->revealWaterpower();
  } else
  if (type.find("Thunderstorm", 0) != string::npos) {
    Thunderstorm* fb = dynamic_cast<Thunderstorm*>(spell);
    fb->revealThunderpower();
  } else {

    string sp = spell->revealScrollName();
    string jr = SpellJournal::read();

    int n = sp.size();
    int m = jr.size();

    // Create a 2D DP array initialized to 0
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (sp[i - 1] == jr[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Length of LCS is in dp[n][m]
    int lcs_length = dp[n][m];

    cout << lcs_length << endl;
  }
}

class Wizard {
public:
  Spell* cast() {
    Spell* spell;
    string s; cin >> s;
    int power; cin >> power;
    if (s == "fire") {
      spell = new Fireball(power);
    }
    else if (s == "frost") {
      spell = new Frostbite(power);
    }
    else if (s == "water") {
      spell = new Waterbolt(power);
    }
    else if (s == "thunder") {
      spell = new Thunderstorm(power);
    }
    else {
      spell = new Spell(s);
      cin >> SpellJournal::journal;
    }
    return spell;
  }
};

int main() {
  int T;
  cin >> T;
  Wizard Arawn;
  while (T--) {
    Spell* spell = Arawn.cast();
    counterspell(spell);
  }
  return 0;
}
