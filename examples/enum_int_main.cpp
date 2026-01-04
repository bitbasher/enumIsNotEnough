#include "../enumIsEnough.hpp"
#include "enum_int.hpp"
#include <iostream>

int main()
{
  using std::cout;
  using std::endl;
  
  cout << "Starting test..." << endl;
  cout << "Size before loop: " << enum_int::size() << endl;
  
  int Cur_Elem = 0;
  for ( enum_int::const_iterator i = enum_int::begin();
        i != enum_int::end(); ++i )
  {
   Cur_Elem++;
   cout << "enum_int element #" << Cur_Elem << " value = "
   << (*i)->Get_Value() << endl;
  }

  cout << "Total #elements = " << enum_int::size() << endl;
  cout << "Min enum value = " << enum_int::Min() << endl;
  cout << "Max enum value = " << enum_int::Max() << endl;

  for ( int i = enum_int::Min(); i <= enum_int::Max(); ++i )
  {
   cout << i;
   if ( enum_int::Is_Valid_Value(i) ) cout << " is ";
   else cout << " isn't ";
   cout << "a valid value for enum_int." << endl;
  }

  enum_int E(enum_int::enum_11);
  cout << "Value of E = " << E.Get_Value() << endl;

  E = enum_int::enum_20;
  cout << "Value of E = " << E.Get_Value() << endl;

  // Illegal code
  // bool B = E; // won't compile, illegal implicit conversion
  // E++; // won't compile, cannot treat enum_int as an int
  // enum_int X(17); // won't compile, ctor is private

  return 0;
}
/*
Output:

enum_int element #1 value = 11
enum_int element #2 value = 12
enum_int element #3 value = 18
enum_int element #4 value = 20
enum_int element #5 value = 21
Total #elements = 5
Min enum value = 11
Max enum value = 21
11 is a valid value for enum_int.
12 is a valid value for enum_int.
13 isn't a valid value for enum_int.
14 isn't a valid value for enum_int.
15 isn't a valid value for enum_int.
16 isn't a valid value for enum_int.
17 isn't a valid value for enum_int.
18 is a valid value for enum_int.
19 isn't a valid value for enum_int.
20 is a valid value for enum_int.
21 is a valid value for enum_int.
Value of E = 11
Value of E = 20
*/
