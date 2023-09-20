#include <iostream>
#include <string>

template <typename T>
concept ComplexConcept =
    requires(const T &t) {
      { t.hash() } -> std::convertible_to<long>;
      { t.toString() } -> std::same_as<std::string>;
      !std::has_virtual_destructor<T>::value;
    }

template <ComplexConcept T>
void concept_method(const T &obj) {
  std::cout << "ToString: " << obj.toString() << std::endl;
  std::cout << "Hash: " << obj.hash() << std::endl;
}

class NewTest {
public:
  long hash() const { return 32; }
  std::string toString() const { return "testestes"; }
};

class NewTest2 {
  int something_;

public:
  long hash() const { return something_; }
  std::string toString() const { return std::to_string(something_); }
  NewTest2(int something) : something_(something) {}
};

int main() {
  NewTest obj;
  NewTest2 obj2(1);

  std::cout << obj.toString() << std::endl << obj2.hash() << std::endl;
  return 0;
}
