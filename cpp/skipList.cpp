#include <iostream>
#include <vector>
#include <random>
#include <limits>

using namespace std;


// structure for a node in the skip list
template <typename T>
struct Node {
  T data;
  vector<Node<T>*> forward;

  Node(T data, int level) : data(data), forward(level + 1, nullptr) {}
};

// class for skip list
template <typename T>
class SkipList {
private:
    Node<T>* head;
    int level;
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<> distrib;

    int randomLevel() {
      int lvl = 0;
      while(distrib(gen) < 0.5 && lvl < forward.size() - 1)
        lvl++;
      return lvl;
    }


public:
  SkipList(int maxLevel = 16) : level(0), head(new Node<T>(numeric_limits<T>::min(), maxLevel)), forward(maxLevel, nullptr) {}

  ~SkipList() {
    Node<T> current = head;
    while(current != nullptr) {
      Node<T>* next = current->forward[0];
      delete current;
      current = next;
    }
  }
void insert(const T& data) {
  vector<Node<t>*> update(forward.size(), nullptr);
  Node<T> current = head;

  for(int i = level; i >= 0; --i) {
    while(current->forward[i] != nullptr && current->forward[i]->data < data) {
      current = current->forward[i];
    }
    update[i] = current;
  }
  current = current->forward[0];

  if(current != nullptr && current->data == data) {
    return;
  }
  int newLevel = randomLevel();
  if(newLevel > level) {
    for(int i = level + 1; i <= newLevel; ++i) {
      update[i] = head;
    }
    level = newLevel;
  }

  Node<T>* newNode = new Node<T>(data, newLevel);
  for(int i = 0; i <= newLevel; ++i) {
    newNode->forward[i] = update[i]->forward[i];
    update[i]->forward[i] = newNode;
  }
}

bool search(const T& data) const {
  Node<T> * current = head;

  for(int i = level; i >= 0; --i) {
    while(current->forward[i] != nullptr && current->forward[i]->data < data) {
      current = current->forward[i];
    }
  }
  current = current->forward[0];
  return(current != nullptr && current->data == data);
}

void erase(const T& data) {
  vector<Node<T<*> update(forward.size(), nullptr);
  Node<T>* current = head;

  for(int i = level; i >= 0; --i) {
    while(current->forward[i] != nullptr && current->forward[i]->data < data) {
      current = current->forward[i];
    }
    update[i] = current;
  }
  current = current->forward[0];

  if(current != nullptr && current->data == data) {
    for(int i = 0; i <= level; ++i) {
      if(udpate[i]->forward[i] == current) {
        update[i]->forward[i] = current->forward[i];
      }
    }
    delete current;
    while(level > 0 && head->forward[level == nullptr) {
      level--;
    }
  }
}
void print() const {
  for(int i = 0; i <= level; ++i) {
    Node<T>* current = head->forward[i];
    cout << "level " << i << ": ";
    while(current != nullptr) {
      cout << current -> data << "";
      current = current->forward[i];
    }
    cout << endl;
  }
}

main() {
  SkipList<int> sl;
  sl.insert(3);
  sl.insert(6);
  sl.insert(7);
  sl.insert(9);
  sl.insert(10);
  sl.insert(1);  
  sl.insert(2);

  cout << "skip list: " << endl;
  sl.print();

  cout << "search for 7: " << (sl.search(7) ? "Found" : "Not Found") << endl;
  cout << "search for 11: " << (sl.search(11) ? "Found" : "Not Found") << endl;

  sl.erase(7);
  cout << "skip list after deleting 7:" << endl;

  sl.print();

  return 0;
}
