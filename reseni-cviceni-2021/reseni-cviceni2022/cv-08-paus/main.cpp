#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include "classes.h"

#define UKOL1   // Container for CEquipmentI
#define UKOL2   // Name Sorting
#define UKOL3   // Power Sorting
#define UKOL4   // Count If

constexpr int n = 10;

class CPowerComparator
{
public:
    bool operator()(const CElectricalDevice* a, const CElectricalDevice* b) const
    {
        return a->getPower() < b->getPower();
    }
};

class CNameComparator
{
public:
    bool operator()(const CEquipmentI *a, const CEquipmentI *b) const
    {
        return a->getName() < b->getName();
    }
};

int main()
{
#ifdef UKOL1
    CEquipmentI * array[n];
    array[0] = new CEquipment(1000, "Rohozka");
    array[1] = new CFurniture(1001, "Ponk", 4);
    array[2] = new CLibrary(1002,"Knihovna 1", 4, 5);
    array[3] = new CElectricalDevice(1003, "Lampa", 60);
    array[4] = new CPrinter(1004, "BT-100", 40, 666);
    array[5] = new CScanner(1005, "Canon", 60);
    array[6] = new CCopier(1006, "Xerox 200", 100, 777);
    array[7] = new CPrinter(1007, "Epson 1234", 80, 666);
    array[8] = new CScanner(1008, "Minolta", 55);
    array[9] = new CCopier(1009, "Xerox 100", 99, 777);

    for (int i=0; i<n; i++)
    {
        array[i]->aboutMe();
        std::cout << std::endl;
    }

#endif

#ifdef UKOL2
    CNameComparator nc;

    std::sort(array, array+n, nc);
    std::cout << "Sorting..." << std::endl;

    for (int i = 0; i < n; i++)
    {
        array[i]->aboutMe();
        std::cout << std::endl;
    }

    assert(array[9]->getId()==1006);

    for (int i=0; i<n; i++) delete array[i];

#endif
    
std::cout << "----------------------------" << std::endl;

#ifdef UKOL3
    CPowerComparator pc;
    std::vector<CElectricalDevice*> devices;
    devices.push_back(new CElectricalDevice(1000, "Fen", 65));
    devices.push_back(new CElectricalDevice(1001, "Sbijecka", 230));
    devices.push_back(new CElectricalDevice(1002, "Sporak", 500));
    devices.push_back(new CElectricalDevice(1003, "Lampa", 60));
    devices.push_back(new CPrinter(1004, "BT-100", 40, 666));
    devices.push_back(new CScanner(1005, "Canon", 60));
    devices.push_back(new CCopier(1006, "Xerox 200", 100, 777));
    devices.push_back(new CPrinter(1007, "Epson 1234", 80, 666));
    devices.push_back(new CScanner(1008, "Minolta", 55));
    devices.push_back(new CCopier(1009, "Xerox 100", 99, 777));

    for (auto x : devices)
    {
        x->aboutMe();
        std::cout << std::endl;
    }

    std::cout << "Sorting..." << std::endl;
    std::sort(devices.begin(), devices.end(), pc);
    
    for (auto x : devices)
    {
        x->aboutMe();
        std::cout << std::endl;
    }

    assert(devices[9]->getId() == 1002);
#endif

#ifdef UKOL4

    for (auto x : devices) if ( x->getId()%2 ) x->switchOn();

    int c = std::count_if(devices.begin(), devices.end(), [](CElectricalDevice *x) { return x->running(); });

    std::cout << "Switched On: " <<c << std::endl;

    assert( c==5 );

    for (auto x : devices) delete x;

#endif

    return 0;
}
