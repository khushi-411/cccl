//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// NOTE: nullptr_t emulation cannot handle a reinterpret_cast to an
// integral type
// XFAIL: c++98, c++03

// typedef decltype(nullptr) nullptr_t;

#include <cuda/std/cassert>
#include <cuda/std/cstddef>

#include "test_macros.h"

int main(int, char**)
{
  cuda::std::ptrdiff_t i = reinterpret_cast<cuda::std::ptrdiff_t>(nullptr);
  assert(i == 0);

  return 0;
}
