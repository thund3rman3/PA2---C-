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

struct record
{
  string name;
  string surname;
  string phone;
};

bool report(const string &fileName, ostream &out)
{
  // TODO
  ifstream ifs(fileName, ifstream::in);
  // ifs.open(fileName);
  vector<record> phonebook;
  record citizen;
  string line, rest;
  if (ifs.is_open())
  {
    while (ifs.good())
    {
      getline(ifs, line);
      if (line.empty())
        break;

      stringstream sstr(line);
      sstr >> citizen.name >> citizen.surname >> citizen.phone >> rest;

      if (citizen.phone[0] == '0' || citizen.phone.length() != 9 || rest.empty() == false)
      {
        return false;
      }
      for (int i = 0; i < 9; i++)
      {
        if (isdigit(citizen.phone[i]) == false)
          return false;
      }

      phonebook.push_back(citizen);
    }
    while (ifs.good()==true)
    {
      string input;
      ifs >> input;
	//cout<<"l  "<<input<<endl;
      if(input.empty()==true)
        break;  
      int cnt = 0;
      // cout<<phonebook.size();
      for (size_t i = 0; i < phonebook.size(); i++)
      {
        if (input == phonebook[i].name || input == phonebook[i].surname)
        {
          cnt++;
          out << phonebook[i].name << " " << phonebook[i].surname << " " << phonebook[i].phone << endl;
        }
      }
        out << "-> " << cnt << endl;
    }
    ifs.close();
    return true;
  }
  return false;
}

#ifndef __PROGTEST__
int main()
{
  ostringstream oss;
  oss.str("");
   //report("tests/test0_in.txt", oss);
  assert(report("tests/test0_in.txt", oss) == true);
  assert(oss.str() ==
         "John Christescu 258452362\n"
         "John Harmson 861647702\n"
         "-> 2\n"
         "-> 0\n"
         "Josh Dakhov 264112084\n"
         "Dakhov Speechley 865216101\n"
         "-> 2\n"
         "John Harmson 861647702\n"
         "-> 1\n");
  oss.str("");
  assert(report("tests/test1_in.txt", oss) == false);
  //report("tests/in.txt",oss);
  return 0;
}
#endif /* __PROGTEST__ */
