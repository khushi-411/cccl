//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// type_traits

// aligned_union<size_t Len, class ...Types>

//  Issue 3034 added:
//  The member typedef type shall be a trivial standard-layout type.

#include <cuda/std/type_traits>

#include "test_macros.h"

int main(int, char**)
{
  {
    typedef cuda::std::aligned_union<10, char>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<10, char>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 1, "");
    static_assert(sizeof(T1) == 10, "");
  }
  {
    typedef cuda::std::aligned_union<10, short>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<10, short>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 2, "");
    static_assert(sizeof(T1) == 10, "");
  }
  {
    typedef cuda::std::aligned_union<10, int>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<10, int>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 4, "");
    static_assert(sizeof(T1) == 12, "");
  }
  {
    typedef cuda::std::aligned_union<10, double>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<10, double>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 8, "");
    static_assert(sizeof(T1) == 16, "");
  }
  {
    typedef cuda::std::aligned_union<10, short, char>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<10, short, char>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 2, "");
    static_assert(sizeof(T1) == 10, "");
  }
  {
    typedef cuda::std::aligned_union<10, char, short>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<10, char, short>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 2, "");
    static_assert(sizeof(T1) == 10, "");
  }
  {
    typedef cuda::std::aligned_union<2, int, char, short>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<2, int, char, short>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 4, "");
    static_assert(sizeof(T1) == 4, "");
  }
  {
    typedef cuda::std::aligned_union<2, char, int, short>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<2, char, int, short>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 4, "");
    static_assert(sizeof(T1) == 4, "");
  }
  {
    typedef cuda::std::aligned_union<2, char, short, int>::type T1;
    static_assert(cuda::std::is_same_v<T1, cuda::std::aligned_union_t<2, char, short, int>>);
    static_assert(cuda::std::is_trivial<T1>::value, "");
    static_assert(cuda::std::is_standard_layout<T1>::value, "");
    static_assert(cuda::std::alignment_of<T1>::value == 4, "");
    static_assert(sizeof(T1) == 4, "");
  }

  return 0;
}
