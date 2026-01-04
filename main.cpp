#include "enumIsEnough.hpp"
#include "test_enoughEnum.hpp"
#include <iostream>

int main()
{
  using std::cout;
  using std::endl;
  
  cout << "Starting test..." << endl;
  cout << "Size before loop: " << test_enoughEnum::size() << endl;
  
  int Cur_Elem = 0;
  for ( test_enoughEnum::const_iterator i = test_enoughEnum::begin();
        i != test_enoughEnum::end(); ++i )
  {
   Cur_Elem++;
   cout << "test_enoughEnum element #" << Cur_Elem << " value = "
   << (*i)->Get_Value() << endl;
  }

  cout << "Total #elements = " << test_enoughEnum::size() << endl;
  cout << "Min enum value = " << test_enoughEnum::Min() << endl;
  cout << "Max enum value = " << test_enoughEnum::Max() << endl;

  for ( int i = test_enoughEnum::Min(); i <= test_enoughEnum::Max(); ++i )
  {
   cout << i;
   if ( test_enoughEnum::Is_Valid_Value(i) ) cout << " is ";
   else cout << " isn't ";
   cout << "a valid value for test_enoughEnum." << endl;
  }

  test_enoughEnum E(test_enoughEnum::enum_11);
  cout << "Value of E = " << E.Get_Value() << endl;

  E = test_enoughEnum::enum_20;
  cout << "Value of E = " << E.Get_Value() << endl;

  // Illegal code
  // bool B = E; // won't compile, illegal implicit conversion
  // E++; // won't compile, cannot treat test_enoughEnum as an int
  // test_enoughEnum X(17); // won't compile, ctor is private

  return 0;
}
/*
Output:

test_enoughEnum element #1 value = 11
test_enoughEnum element #2 value = 12
test_enoughEnum element #3 value = 18
test_enoughEnum element #4 value = 20
test_enoughEnum element #5 value = 21
Total #elements = 5
Min enum value = 11
Max enum value = 21
11 is a valid value for test_enoughEnum.
12 is a valid value for test_enoughEnum.
13 isn't a valid value for test_enoughEnum.
14 isn't a valid value for test_enoughEnum.
15 isn't a valid value for test_enoughEnum.
16 isn't a valid value for test_enoughEnum.
17 isn't a valid value for test_enoughEnum.
18 is a valid value for test_enoughEnum.
19 isn't a valid value for test_enoughEnum.
20 is a valid value for test_enoughEnum.
21 is a valid value for test_enoughEnum.
Value of E = 11
Value of E = 20
*/
