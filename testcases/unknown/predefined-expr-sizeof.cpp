// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template<typename T>
class TemplateClass {
public:
  void templateClassFunction() {
    int size = sizeof(__PRETTY_FUNCTION__);
  }
};

template<typename T>
void functionTemplate(T t) {
  int size = sizeof(__PRETTY_FUNCTION__);
}

int main() {
  TemplateClass<int> t1;
  t1.templateClassFunction();
  TemplateClass<double> t2;
  t2.templateClassFunction();

  functionTemplate<int>(0);
  functionTemplate(0.0);

  return 0;
}
