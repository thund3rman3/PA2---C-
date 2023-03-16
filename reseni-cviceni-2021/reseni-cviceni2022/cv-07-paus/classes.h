#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>

class CEquipment
{
protected:
    int m_id;
public:
    CEquipment(int id) : m_id(id) { std::cout << "CEquipment(" << id << ");" << std::endl; }
    int getId() {return m_id;}
    void aboutMe() {std::cout << "I am CEquipment, id=" << m_id << std::endl;}
    ~CEquipment() { std::cout << "CEquipment says bye bye" << std::endl; }
};

class CFurniture: public CEquipment
{
protected:
    int m_legs;
public:
    CFurniture(int id, int legs):CEquipment(id), m_legs(legs)
        {
            std::cout << "CFurniture(" << id << ", " << legs << ");" << std::endl;
        }
    int getLegs() {return m_legs;}
    void aboutMe() { std::cout << "I am CFurniture, id=" << m_id << ", legs=" << m_legs << std::endl; }
    ~CFurniture() { std::cout << "CFurniture says bye bye" << std::endl; }
};

class CLibrary : public CFurniture
{
    int m_shelves;

public:
    CLibrary(int id, int legs, int shelves) : CFurniture(id, legs), m_shelves(shelves)
    {
        std::cout << "CLibrary(" << id << ", " << legs << ", " << shelves << ");" << std::endl;
    }
    int getShelves() { return m_shelves; }
    void aboutMe() { std::cout << "I am CLibrary, id=" << m_id << ", legs=" << m_legs
                               << ", shelves=" << m_shelves << std::endl; }
    ~CLibrary() { std::cout << "CLibrary says bye bye" << std::endl; }
};

class CElectricalDevice : public CEquipment
{
protected:
    int m_power;
    bool m_running;

public:
    CElectricalDevice(int id, int power, bool running) : CEquipment(id), m_power(power), m_running(running)
    {
        std::cout << "CElectricalDevice(" << id << ", " << power << ", " << running << ");" << std::endl;
    }
    int getPower() { return m_power; }
    bool running() { return m_running; }
    void switchOn() { m_running = true;}
    void switchOff() { m_running = false; }
    void aboutMe() { std::cout << "I am CElectricalDevice, id=" << m_id << ", power=" << m_power << ", running=" << m_running << std::endl; }
    ~CElectricalDevice() { std::cout << "CElectricalDevice says bye bye" << std::endl; }
};

class CPrinter : public virtual CElectricalDevice
{
protected:
    int m_printParams;

public:
    CPrinter(int id, int power, bool running, int params) : CElectricalDevice(id, power, running), m_printParams(params)
    {
        std::cout << "CPrinter(" << id << ", " << power << ", " << running << ", " << params << ");" << std::endl;
    }
    void setPrintParams(int params) { m_printParams = params; }
    void print(int data) {std::cout << data << std::endl;}
    void aboutMe() { std::cout << "I am CPrinter, id=" << m_id << ", power=" << m_power << ", running=" << m_running << ", params=" << m_printParams << std::endl; }
    ~CPrinter() { std::cout << "CPrinter says bye bye" << std::endl; }
};

class CScanner : public virtual CElectricalDevice
{
protected:
    int m_scannedData;

public:
    CScanner(int id, int power, bool running) : CElectricalDevice(id, power, running)
    {
        std::cout << "CScanner(" << id << ", " << power << ", " << running << ");" << std::endl;
    }
    int getScannedData() { return m_scannedData; }
    void scan() { m_scannedData = 42; }
    void aboutMe() { std::cout << "I am CScanner, id=" << m_id << ", power=" << m_power << ", running=" << m_running << ", scannedData=" << m_scannedData << std::endl; }
    ~CScanner() { std::cout << "CScanner says bye bye" << std::endl; }
};

class CCopier: public CPrinter, public CScanner
{
public:
    CCopier(int id, int power, int params) : 
    CElectricalDevice(id, power, false),
    CPrinter(id, power, false, params),
    CScanner(id, power, false)
    {
        std::cout << "CCopier(" << id << ", " << power << ", " <<  params << ");" << std::endl;
    }
    void copy() { scan(); print(m_scannedData); }
    void aboutMe() { std::cout << "I am CCopier, id=" << m_id << ", power=" << m_power << ", running=" << m_running << ", scannedData=" << m_scannedData << ", params=" << m_printParams << std::endl; }
    ~CCopier() { std::cout << "CCopier says bye bye" << std::endl; }
};

#endif
