#pragma once

#include "enumIsEnough.hpp"

class Test_Enum: public enumIsEnough<Test_Enum, int> {

private:
 explicit Test_Enum(const int& Value): enumIsEnough<Test_Enum, int>(Value) { }

public:
  static const Test_Enum enum_11;
  static const Test_Enum enum_12;
  static const Test_Enum enum_18;
  static const Test_Enum enum_20;
  static const Test_Enum enum_21;
};

const Test_Enum Test_Enum::enum_11(11);
const Test_Enum Test_Enum::enum_12(12);
const Test_Enum Test_Enum::enum_18(18);
const Test_Enum Test_Enum::enum_20(20);
const Test_Enum Test_Enum::enum_21(21);