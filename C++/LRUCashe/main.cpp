#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache {
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache  {
public:
   LRUCache(int capacity) { 
      tail = nullptr;
      head = nullptr;
      cp = capacity; 
      }

   virtual void set(int key, int val) override {

      // try to find key in cache
      if(mp.count(key)) {
         swapLastUsedNode(mp[key], head);
         head->value = val;
         return;
      }

      if(mp.size() == cp)
         removeFromTail();

      addToHead(key, val);
   }

   virtual int get(int key) override {
      if(mp.count(key)) {
         return mp[key]->value;
      }
      else
         return -1;
   }
private:

   void removeFromTail() {
      // remove last element from tail
      Node* prevTail = tail;
      Node* newTail = tail->next;
      newTail->prev = NULL;
      mp.erase(prevTail->key);
      tail = newTail;
      delete prevTail;
   }

   void addToHead(int key, int val) { 
      // insert new element to head
      
      if(tail == nullptr && head == nullptr) {
         Node* newHead = new Node(NULL, NULL, key, val);
         tail = newHead;
         head = newHead;
         mp[key] = newHead;
      } else {
         Node* newHead = new Node(head, NULL, key, val);
         head->next = newHead;
         head = newHead;
         mp[key] = newHead;
      }
   }

   void swapLastUsedNode(Node* used, Node* h) {

      if(tail == used)
         tail = h;
      head = used;

      h->next = used->next;
      if(used->next)
         used->next->prev = h;
      if(used->prev)
         used->prev->next = h;

      Node* tmpUsedPrev = used->prev;
      used->prev = h->prev;
      h->prev = tmpUsedPrev;
      used->next = NULL;
      if(used->prev)
         used->prev->next = used;
   }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}