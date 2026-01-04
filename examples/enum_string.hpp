#include <string>
#include "../enumIsEnough.hpp"

class Test_Enum_String:
  public enumIsEnough<Test_Enum_String, std::string> {

private:

  explicit Test_Enum_String(const std::string& Value):
    enumIsEnough<Test_Enum_String, std::string>(Value) { }

public:

  static const Test_Enum_String enum_Alpha;
  static const Test_Enum_String enum_Beta;
  static const Test_Enum_String enum_Delta;
  static const Test_Enum_String enum_Epsilon;
  static const Test_Enum_String enum_Omega;
};
