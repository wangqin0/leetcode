#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        if (!m.contains(key)) { return -1; }
        l.splice(l.begin(), l, m[key]);
        return l.begin()->second;
    }
    
    void put(int key, int value) {
        if (m.contains(key)) {
            l.splice(l.begin(), l, m[key]);
            l.begin()->second = value;
            return;
        }
        if (l.size() == capacity) {
            m.erase(l.back().first);
            l.pop_back();
        }
        l.emplace_front(key, value);
        m[key] = l.begin();
    }

private:
    list<pair<int, int>> l;
    unordered_map<int, list<pair<int, int>>::iterator> m;
    int capacity;
};
