#include "enum_string.hpp"

#include <iostream>

void Validate_Str_Elem(const std::string& theString)
{
  using std::cout;
  using std::endl;
  cout << theString;
  if ( Test_Enum_String::Is_Valid_Value(theString) )
    cout << " is ";
  else
    cout << " isn't ";
  cout << "a valid value for Test_Enum_String." << endl;
}

int main()
{
  using std::cout;
  using std::endl;
  int Cur_Elem = 0;
  for ( Test_Enum_String::const_iterator
        i = Test_Enum_String::begin();
        i != Test_Enum_String::end(); ++i )
  {
    Cur_Elem++;
    cout << "Test_Enum_String element #" << Cur_Elem << " value = " << (*i)->Get_Value() << endl;
  }

  cout << "Total #elements = " << Test_Enum_String::size() << endl;

  cout << "Min enum value = " << Test_Enum_String::Min() << endl;
  cout << "Max enum value = " << Test_Enum_String::Max() << endl;

  Validate_Str_Elem("Alpha");
  Validate_Str_Elem("Gamma");
  Validate_Str_Elem("Beta");
  Validate_Str_Elem("BetA");

  Test_Enum_String E(Test_Enum_String::enum_Alpha);
  cout << "Value of E = " << E.Get_Value() << endl;

  E = Test_Enum_String::enum_Omega;
  cout << "Value of E = " << E.Get_Value() << endl;
  
  return 0;
}
