//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: msvc-19.16

// class cuda::std::ranges::subrange;

#include <cuda/std/cassert>
#include <cuda/std/ranges>

#include "test_iterators.h"
#include "test_macros.h"
#include "types.h"

__host__ __device__ constexpr bool test()
{
  int buff[8] = {};
  cuda::std::ranges::subrange<int*> a(buff, buff + 8, 8);
  auto a1 = a.next();
  assert(a1.begin() == buff + 1);
  assert(a1.size() == 7);
  auto a5 = a.next(5);
  assert(a5.begin() == buff + 5);
  assert(a5.size() == 3);
  auto a4 = a5.prev();
  assert(a4.begin() == buff + 4);
  assert(a4.size() == 4);

  cuda::std::ranges::subrange<InputIter, sentinel_wrapper<InputIter>> b(
    InputIter(buff), sentinel_wrapper<InputIter>(InputIter(buff + 8)));
  auto b1 = cuda::std::move(b).next();
  assert(base(b1.begin()) == buff + 1);

  cuda::std::ranges::subrange<BidirIter> c(BidirIter(buff + 4), BidirIter(buff + 8));
  auto c1 = c.prev();
  assert(base(c1.begin()) == buff + 3);
  auto c2 = c.prev(4);
  assert(base(c2.begin()) == buff);

  cuda::std::ranges::subrange<BidirIter> d(BidirIter(buff + 4), BidirIter(buff + 8));
  auto d1 = d.advance(4);
  assert(base(d1.begin()) == buff + 8);
  assert(d1.empty());
  auto d2 = d1.advance(-4);
  assert(base(d2.begin()) == buff + 4);

  return true;
}

int main(int, char**)
{
  test();
  static_assert(test());

  return 0;
}
