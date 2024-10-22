#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <stack>
#include <algorithm>
#include <regex>

using namespace std;

struct Tag 
{
    std::string name;
    map<string, string> attr;
    map<string, Tag> nested;
};

vector<string> splitTags(const string& s) {
    // split tags
    vector<string> tagsInLine;
    
    size_t start { s.find_first_not_of("<") }; 
    
    while (start != std::string::npos) {
        size_t end = s.find_first_of(">", start + 1);
        if (end == std::string::npos)
            end = s.length();
        tagsInLine.push_back(s.substr(start, end - start));
        start = s.find_first_not_of("<", end + 1);
    }

    return tagsInLine;
}

bool parseTag(Tag& t, const string& s) {
    // split statements
    vector<string> statementsInTag;
    
    size_t start { s.find_first_not_of(" ") }; 

    bool closeStatement = false;
    if(start != std::string::npos && s[start] == '/') {
        closeStatement = true;
        start++;
    }

    size_t end { s.find_first_of({' ', '>'}, start + 1) }; 

    t.name = s.substr(start, end - start);

    // parse attributes
    regex wregex("([\\w\\d]*)\\s*=\\s*\"([\\w\\d\\S]*)\"");

    while (start != string::npos) {
        size_t end = s.find_first_of(" ", start + 1);
        if (end == string::npos)
            end = s.length();

        auto words_begin = sregex_iterator(s.begin(), s.end(), wregex);
        auto words_end = sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i)
        {
            smatch match = *i;
            t.attr[match[1].str()] = match[2].str();
        }

        start = s.find_first_not_of(" ", end + 1);
    }

    return closeStatement;
}

void parseQuiery(const string& s, vector<string>& tags, string& val) {

    size_t start { s.find_first_not_of(' ') }; 

    while (start != std::string::npos) {
        size_t end = s.find_first_of('.', start + 1);
        if (end != std::string::npos) {
            tags.push_back(s.substr(start, end - start));
            start = s.find_first_not_of('.', end + 1);
        } else {
            size_t end = s.find_first_of('~', start + 1);
            if (end != std::string::npos) {
                tags.push_back(s.substr(start, end - start));
                start = s.find_first_not_of('.', end + 1);
            } else {
                end = s.length();
                val = s.substr(start, end - start);
                break;
            }
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    stack<Tag*> enclosure;
    map<string, Tag> tags;
    
    int n{0}, q{0};
    
    scanf("%d %d", &n, &q);
    cin.ignore();

    int i = 0;
    while(i < n) {
        string line;
        getline(cin, line);

        vector<string> tagsInLine{splitTags(line)};

        for(auto& t : tagsInLine) {
            Tag tag;
            bool closeStatement = parseTag(tag, t);

            if(enclosure.empty()) {
                tags[tag.name] = tag;
                enclosure.push(&tags[tag.name]);
            } else {
                if(closeStatement) {
                    enclosure.pop();
                }
                else {
                    enclosure.top()->nested[tag.name] = tag;
                    enclosure.push(&enclosure.top()->nested[tag.name]);
                }
            }
        }
        i++;
    }

    i = 0;
    while(i < q) {

        string line;
        getline(cin, line);

        vector<string> ts;
        string val;

        parseQuiery(line, ts, val);

        auto it1 = tags.find(ts.at(0));
        if(it1 == tags.end()) {
            printf("Not Found!\n");
        } else {
            Tag* curr = &(*it1).second;

            for(int i = 1; i < ts.size(); i++) {
                auto it = curr->nested.find(ts.at(i));

                if(it == curr->nested.end()) {
                    curr = nullptr;
                    break;
                } else {
                    curr = &(*it).second;
                }
            }
            
            if(curr != nullptr) {
                auto it = curr->attr.find(val);
                if(it == curr->attr.end()) {
                    printf("Not Found!\n");
                } else {
                    printf("%s\n",(*it).second.c_str());
                }
            } else {
                printf("Not Found!\n");
            }
        }

        i++;
    }
    
    return 0;
}