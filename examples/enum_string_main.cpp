#include "enum_string.hpp"

#include <iostream>

void Validate_Str_Elem(const std::string& theString)
{
  using std::cout;
  using std::endl;
  cout << theString;
  if ( enum_string::Is_Valid_Value(theString) )
    cout << " is ";
  else
    cout << " isn't ";
  cout << "a valid value for enum_string." << endl;
}

int main()
{
  using std::cout;
  using std::endl;
  int Cur_Elem = 0;
  for ( enum_string::const_iterator
        i = enum_string::begin();
        i != enum_string::end(); ++i )
  {
    Cur_Elem++;
    cout << "enum_string element #" << Cur_Elem << " value = " << (*i)->Get_Value() << endl;
  }

  cout << "Total #elements = " << enum_string::size() << endl;

  cout << "Min enum value = " << enum_string::Min() << endl;
  cout << "Max enum value = " << enum_string::Max() << endl;

  Validate_Str_Elem("Alpha");
  Validate_Str_Elem("Gamma");
  Validate_Str_Elem("Beta");
  Validate_Str_Elem("BetA");

  enum_string E(enum_string::enum_Alpha);
  cout << "Value of E = " << E.Get_Value() << endl;

  E = enum_string::enum_Omega;
  cout << "Value of E = " << E.Get_Value() << endl;
  
  return 0;
}
