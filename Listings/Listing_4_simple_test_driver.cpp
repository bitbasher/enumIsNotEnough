// Listing 4: Using the enumeration classes in a simple test driver
// Test_Enum.h
class Test_Enum: public Enum<Test_Enum> {

private:
 explicit Test_Enum(int Value): Enum<Test_Enum>(Value) { }

public:
  static const Test_Enum enum_11;
  static const Test_Enum enum_12;
  static const Test_Enum enum_18;
  static const Test_Enum enum_20;
  static const Test_Enum enum_21;
};

// Test_Enum.cpp

#include "Test_Enum.h"

Enum<Test_Enum>::instances_list Enum<Test_Enum>::s_instances;

const Test_Enum Test_Enum::enum_11(11);
const Test_Enum Test_Enum::enum_12(12);
const Test_Enum Test_Enum::enum_18(18);
const Test_Enum Test_Enum::enum_20(20);
const Test_Enum Test_Enum::enum_21(21);

// Main.cpp

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
/*
Output:

Test_Enum element #1 value = 11
Test_Enum element #2 value = 12
Test_Enum element #3 value = 18
Test_Enum element #4 value = 20
Test_Enum element #5 value = 21
Total #elements = 5
Min enum value = 11
Max enum value = 21
11 is a valid value for Test_Enum.
12 is a valid value for Test_Enum.
13 isn't a valid value for Test_Enum.
14 isn't a valid value for Test_Enum.
15 isn't a valid value for Test_Enum.
16 isn't a valid value for Test_Enum.
17 isn't a valid value for Test_Enum.
18 is a valid value for Test_Enum.
19 isn't a valid value for Test_Enum.
20 is a valid value for Test_Enum.
21 is a valid value for Test_Enum.
Value of E = 11
Value of E = 20
*/
