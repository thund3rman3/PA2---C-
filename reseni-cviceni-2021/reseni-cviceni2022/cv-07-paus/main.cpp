#include <iostream>
#include <cassert>
#include "classes.h"

//#define UKOL1   // CEquipment
//#define UKOL2   // CLibrary
//#define UKOL3   // CPrinter
//#define UKOL4   // CScanner
//#define UKOL5   // CCopier
#define UKOL6   // Pointery


int main()
{
#ifdef UKOL1
    CEquipment e(36);
    e.aboutMe();
    assert( e.getId() == 36 );
#endif
    
std::cout << "----------------------------" << std::endl;

#ifdef UKOL2
    CLibrary lib(11, 4, 6);
    lib.aboutMe();
    assert( lib.getShelves() == 6 );
    assert( lib.getLegs() == 4 );

    //CEquipment* p = new CLibrary(1,1,1);
    //p->aboutMe();
    //if (CLibrary* x = dynamic_cast<CLibrary*>(p)) std::cout << x->getShelves();
#endif

    std::cout << "----------------------------" << std::endl;

#ifdef UKOL3
    CPrinter print(1, 100, true, 666);
    print.setPrintParams(777);
    print.aboutMe();
    print.print(12345);
    assert(print.getId()==1);
    assert(print.getPower()==100);
#endif
    
    std::cout << "----------------------------" << std::endl;

#ifdef UKOL4
    CScanner scan(2, 222, true);
    scan.scan();
    scan.aboutMe();
    assert(scan.getId()==2);
    assert(scan.getPower()==222);
#endif

    std::cout << "----------------------------" << std::endl;

#ifdef UKOL5
    CCopier kopirka(9000, 333, 555);
    kopirka.copy();
    kopirka.aboutMe();
    //assert(kopirka.getPower()==333);
#endif
    
#ifdef UKOL6
    CCopier *ptr0 = new CCopier(1002, 100, 666);
    ptr0->aboutMe();
    ptr0->copy();
    assert(ptr0->getPower()==100);
    
    // ppriprava na polymorfizmus
    // pri dedeni muze odvozena trida zastoupit tu puvodni, takze toto lze:
    CEquipment *ptr1 = new CCopier(1003, 100, 777);
    assert(ptr1->getId()==1003);
    ptr1->aboutMe();                // co vypise?
    //ptr1->scan();                 // nelze, proc?
    
    CPrinter *ptr2 = new CCopier(1004,200,999);
    ptr2->aboutMe();                // co vypise?
    
    delete ptr0;
    //delete ptr1;        // segfault (bez virtualniho destruktoru), nutny polymorfizmus
    //delete ptr2;        // zase error;
    
#endif
    
    return 0;
}
