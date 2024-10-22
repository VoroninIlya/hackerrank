
#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
  int T; cin >> T;
  cout << setiosflags(ios::uppercase);
  cout << setw(0xf) << internal;
  while (T--) {
    double A; cin >> A;
    double B; cin >> B;
    double C; cin >> C;

    /* Enter your code here */
    printf("0x%llx\n", (long long)A);

    char buff[256]{ 0 };

    if (B >= 0)
      sprintf(buff, "+%.2f", B);
    else
      sprintf(buff, "-%.2f", B);

    string s(buff);

    std::cout << std::setfill('_') << std::setw(15) << std::right << s << endl;

    printf("%.9E\n", C);

  }
  return 0;

}
