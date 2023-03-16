#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

class CTimeStamp
{
  /*
  CTimeStamp, tato třída bude realizovat jednoduché zapouzdření časového razítka.
   Musí mít konstruktor,
   ve kterém bude inicializovat své složky
   (rok, měsíc, den, hodina, minuta, sekunda).
  Můžete se spolehnout, že jsou zadávané pouze platné hodnoty data a času.
  */
public:
  CTimeStamp(int y, int m, int d, int h, int min, int s)
      : year(y), month(m), day(d), hour(h), minute(min), second(s) {}

  int time_sum() const
  {
    int res = second + minute * 60 + hour * 60 * 60 + day * 60 * 60 * 24;
    return res;
  }

  int year;
  int month;

  private:
    int day;
    int hour;
    int minute;
    int second;
};

class CContact
{
  /*
  CContact je třída, která zapouzdřuje jeden kontakt mezi dvojicí uživatelů.
   Uživatelé jsou identifikováni svým telefonním číslem,
  okamžik kontaktu je zaznamenán v podobě časového razítka CTimeStamp.
  */
public:
  CContact(CTimeStamp a, int tel1, int tel2)
      : mCC_cts(a), mCC_phone1(tel1), mCC_phone2(tel2)
  {
  }

  int get_contact1() const
  {
    return mCC_phone1;
  }
  int get_contact2() const
  {
    return mCC_phone2;
  }
  CTimeStamp getTS() const
  {
    return mCC_cts;
  }

private:
  CTimeStamp mCC_cts;
  int mCC_phone1;
  int mCC_phone2;
};

class CEFaceMask
{
  /*
  CEFaceMask je třída,
  která sdružuje zaznamenané kontakty.
  Kontakty se přidávají pomocí metody addContact
  (volání metody lze řetězit),
  vyhledání kontaktů pak probíhá pomocí metody listContacts
  (metoda by neměla upravovat objekt, měla by být tedy const).
  Vyhledávací metodu lze zavolat s jedním parametrem (telefonním číslem nakaženého)
  nebo s trojicí parametrů (telefonním číslem nakaženého, počátek a konec časového intervalu).
   Metoda vrátí seznam čísel, se kterými byl dotazovaný v kontaktu
   (v druhém případě navíc ve vymezeném časovém intervalu).
  */

public:
  CEFaceMask &addContact(CContact a)
  {
    mCE_contacts.push_back(a);
    return *this;
  }
  bool is_in(vector<int> &contactos, int search) const
  {
    bool in = false;
    for (int v_c : contactos)
    {
      if (search == v_c)
        in = true;
    }
    return in;
  }

  vector<int> listContacts(int tel) const
  {
    vector<int> contactos;

    for (CContact x : mCE_contacts)
    {
      int tel1 = x.get_contact1();
      int tel2 = x.get_contact2();

      if (tel1 == tel2)
        continue;

      else if (tel1 == tel)
      {
        if (is_in(contactos, tel2) == false)
          contactos.push_back(tel2);
      }
      else if (tel2 == tel)
      {
        if (is_in(contactos, tel1) == false)
          contactos.push_back(tel1);
      }
    }

    return contactos;
  }

  vector<int> listContacts(int tel, CTimeStamp a, CTimeStamp b) const
  {
    vector<int> contactos;
    for (CContact x : mCE_contacts)
    {
      int tel1 = x.get_contact1();
      int tel2 = x.get_contact2();
      int x_year = x.getTS().year;
      int x_month = x.getTS().month;
      int x_time = x.getTS().time_sum();
      int a_time = a.time_sum();
      int b_time = b.time_sum();

      if ((a.year > x_year || b.year < x_year ) ||
          (b.year == x_year && b.month == x_month && (x_time > b_time)) ||
          (a.year == x_year && a.month == x_month && (x_time < a_time)) ||
          (tel1 == tel2) ||
          (b.year==x_year && b.month < x_month ) ||
          (a.month >x_month && a.year==x_year))
      {
        continue;
      }
      else if (tel1 == tel)
      {
        if (is_in(contactos, tel2) == false)
        {
          contactos.push_back(tel2);
        }
      }
      else if (tel2 == tel)
      {
        if (is_in(contactos, tel1) == false)
        {
          contactos.push_back(tel1);
        }
      }
    }
    return contactos;
  }

private:
  vector<CContact> mCE_contacts;
};

#ifndef __PROGTEST__
int main()
{
  CEFaceMask test;

  test.addContact(CContact(CTimeStamp(2021, 1, 10, 12, 40, 10), 123456789, 999888777));
  test.addContact(CContact(CTimeStamp(2021, 1, 12, 12, 40, 10), 123456789, 111222333))
      .addContact(CContact(CTimeStamp(2021, 2, 5, 15, 30, 28), 999888777, 555000222));
  test.addContact(CContact(CTimeStamp(2021, 2, 21, 18, 0, 0), 123456789, 999888777));
  test.addContact(CContact(CTimeStamp(2021, 1, 5, 18, 0, 0), 123456789, 456456456));
  test.addContact(CContact(CTimeStamp(2021, 2, 1, 0, 0, 0), 123456789, 123456789));
  assert(test.listContacts(123456789) == (vector<int>{999888777, 111222333, 456456456}));
  assert(test.listContacts(999888777) == (vector<int>{123456789, 555000222}));
  assert(test.listContacts(191919191) == (vector<int>{}));
  assert(test.listContacts(123456789, CTimeStamp(2021, 1, 5, 18, 0, 0), CTimeStamp(2021, 2, 21, 18, 0, 0)) == (vector<int>{999888777, 111222333, 456456456}));
  assert(test.listContacts(123456789, CTimeStamp(2021, 1, 5, 18, 0, 1), CTimeStamp(2021, 2, 21, 17, 59, 59)) == (vector<int>{999888777, 111222333}));
  assert(test.listContacts(123456789, CTimeStamp(2021, 1, 10, 12, 41, 9), CTimeStamp(2021, 2, 21, 17, 59, 59)) == (vector<int>{111222333}));
  return 0;
}
#endif /* __PROGTEST__ */
