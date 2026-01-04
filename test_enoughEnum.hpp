#pragma once

#include "enumIsEnough.hpp"

class test_enoughEnum: public enumIsEnough<test_enoughEnum, int> {

private:
 explicit test_enoughEnum(const int& Value): enumIsEnough<test_enoughEnum, int>(Value) { }

public:
  static const test_enoughEnum enum_11;
  static const test_enoughEnum enum_12;
  static const test_enoughEnum enum_18;
  static const test_enoughEnum enum_20;
  static const test_enoughEnum enum_21;
};
