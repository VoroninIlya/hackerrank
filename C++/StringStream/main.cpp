#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
	// Complete this function
    stringstream ss(str);
    int i{0};
    char c{0};
    vector<int> v;
    while(1){
        if((ss >> i)) {
            v.push_back(i);
        }
        if((ss >> c)) {
            continue;
        } else {
            break;
        }
    }
    return v;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}