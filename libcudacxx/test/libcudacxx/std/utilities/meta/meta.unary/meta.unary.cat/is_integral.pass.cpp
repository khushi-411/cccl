//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// type_traits

// is_integral

#include <cuda/std/cstddef> // for cuda::std::nullptr_t
#include <cuda/std/type_traits>

#include "test_macros.h"

template <class T>
__host__ __device__ void test_is_integral()
{
  static_assert(cuda::std::is_integral<T>::value, "");
  static_assert(cuda::std::is_integral<const T>::value, "");
  static_assert(cuda::std::is_integral<volatile T>::value, "");
  static_assert(cuda::std::is_integral<const volatile T>::value, "");
  static_assert(cuda::std::is_integral_v<T>, "");
  static_assert(cuda::std::is_integral_v<const T>, "");
  static_assert(cuda::std::is_integral_v<volatile T>, "");
  static_assert(cuda::std::is_integral_v<const volatile T>, "");
}

template <class T>
__host__ __device__ void test_is_not_integral()
{
  static_assert(!cuda::std::is_integral<T>::value, "");
  static_assert(!cuda::std::is_integral<const T>::value, "");
  static_assert(!cuda::std::is_integral<volatile T>::value, "");
  static_assert(!cuda::std::is_integral<const volatile T>::value, "");
  static_assert(!cuda::std::is_integral_v<T>, "");
  static_assert(!cuda::std::is_integral_v<const T>, "");
  static_assert(!cuda::std::is_integral_v<volatile T>, "");
  static_assert(!cuda::std::is_integral_v<const volatile T>, "");
}

class Empty
{};

class NotEmpty
{
  __host__ __device__ virtual ~NotEmpty();
};

union Union
{};

struct bit_zero
{
  int : 0;
};

class Abstract
{
  __host__ __device__ virtual ~Abstract() = 0;
};

enum Enum
{
  zero,
  one
};
struct incomplete_type;

typedef void (*FunctionPtr)();

int main(int, char**)
{
  test_is_integral<short>();
  test_is_integral<unsigned short>();
  test_is_integral<int>();
  test_is_integral<unsigned int>();
  test_is_integral<long>();
  test_is_integral<unsigned long>();
  test_is_integral<bool>();
  test_is_integral<char>();
  test_is_integral<signed char>();
  test_is_integral<unsigned char>();
  test_is_integral<wchar_t>();
#if defined(__cccl_lib_char8_t) && __cccl_lib_char8_t >= 201811L
  test_is_integral<char8_t>();
#endif

  test_is_not_integral<cuda::std::nullptr_t>();
  test_is_not_integral<void>();
  test_is_not_integral<int&>();
  test_is_not_integral<int&&>();
  test_is_not_integral<int*>();
  test_is_not_integral<double>();
  test_is_not_integral<const int*>();
  test_is_not_integral<char[3]>();
  test_is_not_integral<char[]>();
  test_is_not_integral<Union>();
  test_is_not_integral<Enum>();
  test_is_not_integral<FunctionPtr>();
  test_is_not_integral<Empty>();
  test_is_not_integral<bit_zero>();
  test_is_not_integral<NotEmpty>();
  test_is_not_integral<Abstract>();
  test_is_not_integral<incomplete_type>();

  return 0;
}
