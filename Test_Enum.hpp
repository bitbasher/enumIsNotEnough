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
