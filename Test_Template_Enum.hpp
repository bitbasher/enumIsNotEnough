#include <string>
#include "Template_Enum.h"

class Test_Enum_String:
  public Tmpl_Enum<std::string, Test_Enum_String> {

private:

  explicit Test_Enum_String(const std::string& Value):
    Tmpl_Enum<std::string, Test_Enum_String>(Value) { }

public:

  static const Test_Enum_String enum_Alpha;
  static const Test_Enum_String enum_Beta;
  static const Test_Enum_String enum_Delta;
  static const Test_Enum_String enum_Epsilon;
  static const Test_Enum_String enum_Omega;
};
