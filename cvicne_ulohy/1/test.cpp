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

bool read_input(ifstream &ifs, vector<record> &phonebook, record &citizen)
{
  string line, rest;
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
  return true;
}

void read_input2(ifstream &ifs, vector<string> &inputs, string &input)
{
  string line;
  while (getline(ifs,line))
  {
    stringstream temp(line);
    temp >> input;
    inputs.push_back(input);
    if(ifs.eof())
      break;
    
  }
}

void resolve(ifstream &ifs, vector<record> &phonebook, ostream &out, vector<string> &inputs)
{
  for (string x : inputs)
  {
    int cnt = 0;

    for (size_t i = 0; i < phonebook.size(); i++)
    {
      if (x == phonebook[i].name || x == phonebook[i].surname)
      {
        cnt++;
        out << phonebook[i].name << " " << phonebook[i].surname << " " << phonebook[i].phone << endl;
      }
    }
    out << "-> " << cnt << endl;
  }
}

bool report(const string &fileName, ostream &out)
{
  // TODO
  ifstream ifs(fileName, ifstream::in);
  // ifs.open(fileName);
  vector<record> phonebook;
  vector<string> inputs;
  string input;
  record citizen;

  if (ifs.is_open())
  {
    if (read_input(ifs, phonebook, citizen) == false)
      return false;

    read_input2(ifs, inputs, input);

    resolve(ifs, phonebook, out, inputs);

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
  // report("tests/test0_in.txt", oss);
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
  //
  // report("tests/in.txt",oss);*/
  oss.str("");
  assert(report("tests/in.txt", oss) == true);
  assert(oss.str() == "Carly Johnson 355562144\n"
                      "-> 1\n"
                      "Christen Day 711567172\n"
                      "-> 1\n");
  return 0;
}
#endif /* __PROGTEST__ */
