#include "Test_Enum.h"

Enum<Test_Enum>::instances_list Enum<Test_Enum>::s_instances;

const Test_Enum Test_Enum::enum_11(11);
const Test_Enum Test_Enum::enum_12(12);
const Test_Enum Test_Enum::enum_18(18);
const Test_Enum Test_Enum::enum_20(20);
const Test_Enum Test_Enum::enum_21(21);

Main.cpp

#include "Test_Enum.h"
int main()
{
  using std::cout;
  using std::endl;  
  int Cur_Elem = 0;
  for ( Test_Enum::const_iterator i = Test_Enum::begin();
        i != Test_Enum::end(); ++i )
  {
   Cur_Elem++;
   cout << "Test_Enum element #" << Cur_Elem << " value = "
   << (*i)->Get_Value() << endl;
  }

  cout << "Total #elements = " << Test_Enum::size() << endl;
  cout << "Min enum value = " << Test_Enum::Min() << endl;
  cout << "Max enum value = " << Test_Enum::Max() << endl;

  for ( int i = Test_Enum::Min(); i <= Test_Enum::Max(); ++i )
  {
   cout << i;
   if ( Test_Enum::Is_Valid_Value(i) ) cout << " is ";
   else cout << " isn't ";
   cout << "a valid value for Test_Enum." << endl;
  }

  Test_Enum E(Test_Enum::enum_11);
  cout << "Value of E = " << E.Get_Value() << endl;

  E = Test_Enum::enum_20;
  cout << "Value of E = " << E.Get_Value() << endl;

  // Illegal code
  // bool B = E; // won't compile, illegal implicit conversion
  // E++; // won't compile, cannot treat Test_Enum as an int
  // Test_Enum X(17); // won't compile, ctor is private

  return 0;
}
