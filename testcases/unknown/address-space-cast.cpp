// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

#define __private__ __attribute__((address_space(5)))

void func_pchar(__private__ char *x);
void func_pvoid(__private__ void *x);
void func_pint(__private__ int *x);

class Base {
};

class Derived : public Base {
};

void fn(Derived *p) {
  __private__ Base *b = (__private__ Base *)p;
}

void test_cast(char *gen_char_ptr, void *gen_void_ptr, int *gen_int_ptr) {
  __private__ char *priv_char_ptr = (__private__ char *)gen_char_ptr;

  priv_char_ptr = (__private__ char *)gen_void_ptr;

  priv_char_ptr = (__private__ char *)gen_int_ptr;

  __private__ void *priv_void_ptr = (__private__ void *)gen_char_ptr;

  priv_void_ptr = (__private__ void *)gen_void_ptr;

  priv_void_ptr = (__private__ void *)gen_int_ptr;

  __private__ int *priv_int_ptr = (__private__ int *)gen_void_ptr;

  func_pchar((__private__ char *)gen_char_ptr);

  func_pchar((__private__ char *)gen_void_ptr);

  func_pchar((__private__ char *)gen_int_ptr);

  func_pvoid((__private__ void *)gen_char_ptr);

  func_pvoid((__private__ void *)gen_void_ptr);

  func_pvoid((__private__ void *)gen_int_ptr);

  func_pint((__private__ int *)gen_void_ptr);
}
