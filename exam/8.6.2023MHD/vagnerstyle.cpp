#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <memory>

using namespace std;

class CPublicTransport {
public:
    CPublicTransport() = default;

    CPublicTransport &addLine(unsigned cost, const vector<string> &stops) {
        vector<string> stops_on_line;

        for (const string &stop: stops) {
            for (const string &stop_on_line: stops_on_line) {
                auto it = m_vAllStops.find(make_pair(stop, stop_on_line));
                if (it == m_vAllStops.end()) {
                    m_vAllStops.emplace(make_pair(stop, stop_on_line), cost);
                    m_vAllStops.emplace(make_pair(stop_on_line, stop), cost);
                } else if (it != m_vAllStops.end() && it->second > cost) {
                    m_vAllStops[make_pair(stop, stop_on_line)] = cost;
                    m_vAllStops[make_pair(stop_on_line, stop)] = cost;
                }
            }
            stops_on_line.emplace_back(stop);
        }
        return *this;
    }

    CPublicTransport &optimize() {

        return *this;
    }

    unsigned findCheapest(const string &from, const string &to) {
        if (from == to)
            return 0;

        queue<string> nextvisit;
        map<string, unsigned> visited;
        nextvisit.push(from);
        visited.emplace(from, 0);
        while (!nextvisit.empty()) {
            auto elem = nextvisit.front();
            nextvisit.pop();
            for (auto it = m_vAllStops.lower_bound(make_pair(elem, ""));
                 it != m_vAllStops.end() && it->first.first == elem; ++it) {

                if (visited.count(it->first.second) == 0) {
                    visited.emplace(it->first.second, visited[elem] + it->second);
                    nextvisit.emplace(it->first.second);
                    
                } else if (visited.count(it->first.second) == 1 &&
                           visited[it->first.second] > visited[elem] + it->second) {
                    visited[it->first.second] = visited[elem] + it->second;
                }
            }
        }
        if (visited.count(to) == 0)
            throw logic_error(",");
        return visited[to];
    }


private:
    map<pair<string, string>, unsigned> m_vAllStops;
};

int main() {

    CPublicTransport t;

    t.addLine(3, {"Hlavni Nadrazi", "Orionka", "Baterie", "Petriny", "Jiriho z Podebrad"})
            .addLine(2, {"Kamenicka", "Letenske namesti", "Baterie", "Petriny", "Namesti Miru", "Malovanka"})
            .addLine(5, {"Dejvicka", "Muzeum"})
            .addLine(1, {"Staromestska", "Muzeum", "Mustek", "Namesti Miru", "Jiriho z Podebrad"})
            .optimize();

    assert(t.findCheapest("Staromestska", "Baterie") == 3);
    assert(t.findCheapest("Staromestska", "Staromestska") == 0);
    assert(t.findCheapest("Staromestska", "Namesti Miru") == 1);
    assert(t.findCheapest("Staromestska", "Hlavni Nadrazi") == 4);
    assert(t.findCheapest("Orionka", "Kamenicka") == 5);
    assert(t.findCheapest("Jiriho z Podebrad", "Namesti Miru") == 1);
    assert(t.findCheapest("Dejvicka", "Letenske namesti") == 8);

    t.addLine(6, {"Vitezne namesti", "I P Pavlova", "Andel"});
    t.addLine(9, {"Letenske namesti", "Vitezne namesti"});

    assert(t.findCheapest("Dejvicka", "Andel") == 23);
    assert(t.findCheapest("Andel", "Dejvicka") == 23);
    assert(t.findCheapest("Vitezne namesti", "Letenske namesti") == 9);
    assert(t.findCheapest("Orionka", "Andel") == 20);

    t.addLine(9, {"Terminal 1", "Terminal 2", "Terminal 3", "Nadrazi Veleslavin"});

    try {
        t.findCheapest("Namesti Miru", "Terminal 2");
    }
    catch (const logic_error &e) {
        // assert(e.what() != "");
        cout << "chyceno" << endl;
    }

    CPublicTransport t2;
    t2.addLine(2, {"A", "B", "C"})
            .addLine(2, {"C", "D", "E"})
            .addLine(2, {"E", "F", "G"})
            .addLine(2, {"G", "H", "I"})
            .addLine(2, {"I", "J", "K"})
            .addLine(2, {"K", "L", "M"})
            .optimize();

    assert(t2.findCheapest("A", "M") == 12);
    assert(t2.findCheapest("A", "G") == 6);
    assert(t2.findCheapest("A", "H") == 8);
    assert(t2.findCheapest("C", "K") == 8);
    assert(t2.findCheapest("B", "L") == 12);
    assert(t2.findCheapest("I", "C") == 6);

    t2.addLine(3, {"A", "Z", "M"}).optimize();

    assert(t2.findCheapest("A", "M") == 3);
    assert(t2.findCheapest("C", "K") == 7);
    assert(t2.findCheapest("B", "L") == 7);

    CPublicTransport t3;

    t3.addLine(1, {"A", "B", "C", "D", "E"})
            .addLine(2, {"F", "G", "H", "E", "I"})
            .addLine(3, {"J", "K", "L", "B", "M"})
            .addLine(2, {"N", "O", "P", "Q", "E"})
            .addLine(4, {"E", "R", "S", "T", "U"})
            .addLine(5, {"V", "W", "X", "Y", "Z"})
            .addLine(1, {"M", "N", "O", "P", "Q", "R", "S", "T", "U", "V"})
            .addLine(3, {"Z", "Y", "X", "W", "V", "U", "T", "S", "R", "Q", "P", "O", "N", "M"})
            .addLine(4, {"V", "W", "X", "Y", "Z", "A", "B", "C", "D", "E"})
            .addLine(2, {"Ac", "Gaa", "Hd", "Ee", "Ie"})
            .addLine(6, {"E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W",
                         "X", "Y", "Z"});

    try {
        t3.findCheapest("A", "Hd");
    }
    catch (const logic_error &e) {
        assert(string(e.what()) != "");
    }

    assert(t3.findCheapest("A", "E") == 1);
    assert(t3.findCheapest("A", "I") == 3);
    assert(t3.findCheapest("A", "M") == 4);
    assert(t3.findCheapest("A", "A") == 0);
    assert(t3.findCheapest("F", "R") == 5);
    assert(t3.findCheapest("S", "Z") == 3);
    assert(t3.findCheapest("S", "T") == 1);
    assert(t3.findCheapest("A", "V") == 4);
    assert(t3.findCheapest("A", "W") == 4);
    assert(t3.findCheapest("A", "Z") == 4);

    CPublicTransport newTransport;

    newTransport.addLine(1, {"Staromestska", "Muzeum", "Mustek", "Namesti Miru", "Jiriho z Podebrad"})
            .addLine(3, {"Hlavni Nadrazi", "Orionka", "Baterie", "Petriny", "Jiriho z Podebrad"})
            .addLine(2, {"Kamenicka", "Letenske namesti", "Baterie", "Petriny", "Namesti Miru", "Malovanka"})
            .addLine(6, {"Vitezne namesti", "I P Pavlova", "Andel"})
            .addLine(4, {"Pankrac", "Kacerov", "Budejovicka", "Prazskeho povstani", "I P Pavlova", "Mustek",
                         "Staromestska"})
            .addLine(5, {"Hlavni Nadrazi", "Florenc", "Bila labut", "Namesti Republiky", "Mustek", "Narodni trida"})
            .addLine(3, {"Muzeum", "Hlavni Nadrazi", "Florenc", "Krizikova", "Invalidovna"})
            .addLine(7, {"Jiriho z Podebrad", "Florenc", "Namesti Republiky", "Staromestska"})
            .addLine(8, {"Muzeum", "Nadrazi Holesovice", "Vltavska", "Strossmayerovo namesti", "Letenske namesti"})
            .addLine(9, {"Hlavni Nadrazi", "Nadrazi Holesovice", "Vltavska", "Florenc", "Bila labut"})
            .addLine(10, {"Staromestska", "Malostranska", "Hradcanska", "Dejvicka", "Vitezne namesti"})
            .addLine(2, {"Mustek", "Narodni trida", "Karlovo namesti", "I P Pavlova", "Namesti Miru"})
            .addLine(4, {"Krizikova", "Karlovo namesti", "Andel", "Radlicka", "Jinonice"})
            .addLine(3, {"Nadrazi Holesovice", "Kobylisy", "Ladvi", "Strizkov", "Prosek", "Letnany"})
            .addLine(5, {"Nadrazi Holesovice", "Vltavska", "Florenc", "Hlavni Nadrazi", "Muzeum", "I P Pavlova"})
            .addLine(6, {"Vitezne namesti", "Dejvicka", "Hradcanska", "Malostranska", "Staromestska"}).optimize();

    assert(newTransport.findCheapest("Staromestska", "Baterie") == 3);
    assert(newTransport.findCheapest("Staromestska", "Staromestska") == 0);
    assert(newTransport.findCheapest("Staromestska", "Namesti Miru") == 1);
    assert(newTransport.findCheapest("Staromestska", "Hlavni Nadrazi") == 4);
    assert(newTransport.findCheapest("Orionka", "Kamenicka") == 5);
    assert(newTransport.findCheapest("Vitezne namesti", "Andel") == 6);
    assert(newTransport.findCheapest("Pankrac", "Staromestska") == 4);
    assert(newTransport.findCheapest("Hlavni Nadrazi", "Narodni trida") == 5);
    assert(newTransport.findCheapest("Muzeum", "Invalidovna") == 3);
    assert(newTransport.findCheapest("Jiriho z Podebrad", "Staromestska") == 1);
    assert(newTransport.findCheapest("Mustek", "Strossmayerovo namesti") == 9);
    assert(newTransport.findCheapest("Vitezne namesti", "Bila labut") == 12);
    assert(newTransport.findCheapest("Hradcanska", "Karlovo namesti") == 9);
    assert(newTransport.findCheapest("Invalidovna", "Jinonice") == 7);
    assert(newTransport.findCheapest("Prosek", "Budejovicka") == 12);
    assert(newTransport.findCheapest("Baterie", "I P Pavlova") == 4);
    assert(newTransport.findCheapest("Krizikova", "Malostranska") == 10);
    assert(newTransport.findCheapest("Dejvicka", "Kacerov") == 10);
    assert(newTransport.findCheapest("Florenc", "Radlicka") == 7);
    assert(newTransport.findCheapest("Hradcanska", "Narodni trida") == 9);
    assert(newTransport.findCheapest("Invalidovna", "Letenske namesti") == 6);
    assert(newTransport.findCheapest("Vltavska", "Malostranska") == 12);
    assert(newTransport.findCheapest("Andel", "Kobylisy") == 14);
    assert(newTransport.findCheapest("Bila labut", "Prosek") == 12);
    assert(newTransport.findCheapest("Radlicka", "Vitezne namesti") == 10);
    assert(newTransport.findCheapest("Hradcanska", "Jiriho z Podebrad") == 7);
    assert(newTransport.findCheapest("Karlovo namesti", "Letnany") == 10);
    assert(newTransport.findCheapest("Letenske namesti", "Strizkov") == 11);

    t3.addLine(1, {"Staromestska", "Muzeum", "Mustek", "Namesti Miru", "Jiriho z Podebrad"})
            .addLine(3, {"Hlavni Nadrazi", "Orionka", "Baterie", "Petriny", "Jiriho z Podebrad"})
            .addLine(2, {"Kamenicka", "Letenske namesti", "Baterie", "Petriny", "Namesti Miru", "Malovanka"});

    assert(t3.findCheapest("Staromestska", "Baterie") == 3);
    assert(t3.findCheapest("Staromestska", "Staromestska") == 0);
    assert(t3.findCheapest("Staromestska", "Namesti Miru") == 1);
    assert(t3.findCheapest("Staromestska", "Hlavni Nadrazi") == 4);
    assert(t3.findCheapest("Orionka", "Kamenicka") == 5);

    t3.addLine(6, {"Vitezne namesti", "I P Pavlova", "Andel"});

    try {
        t3.findCheapest("Orionka", "Andel");
    }
    catch (const logic_error &e) {
        assert(string(e.what()) != "");
    }

    cout << "ALL ASSERTS PASSED!" << endl;
    return 0;
}