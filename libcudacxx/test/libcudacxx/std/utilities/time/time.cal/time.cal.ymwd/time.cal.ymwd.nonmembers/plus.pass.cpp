//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <chrono>
// class year_month_weekday;

// constexpr year_month_weekday operator+(const year_month_weekday& ymd, const months& dm) noexcept;
//   Returns: (ymd.year() / ymd.month() + dm) / ymd.day().
//
// constexpr year_month_weekday operator+(const months& dm, const year_month_weekday& ymd) noexcept;
//   Returns: ymd + dm.
//
//
// constexpr year_month_weekday operator+(const year_month_weekday& ymd, const years& dy) noexcept;
//   Returns: (ymd.year() + dy) / ymd.month() / ymd.day().
//
// constexpr year_month_weekday operator+(const years& dy, const year_month_weekday& ymd) noexcept;
//   Returns: ym + dm.

#include <cuda/std/cassert>
#include <cuda/std/chrono>
#include <cuda/std/type_traits>

#include "test_macros.h"

__host__ __device__ constexpr bool testConstexprYears(cuda::std::chrono::year_month_weekday ym)
{
  cuda::std::chrono::years offset{23};
  if (static_cast<int>((ym).year()) != 1)
  {
    return false;
  }
  if (static_cast<int>((ym + offset).year()) != 24)
  {
    return false;
  }
  if (static_cast<int>((offset + ym).year()) != 24)
  {
    return false;
  }
  return true;
}

__host__ __device__ constexpr bool testConstexprMonths(cuda::std::chrono::year_month_weekday ym)
{
  cuda::std::chrono::months offset{6};
  if (static_cast<unsigned>((ym).month()) != 1)
  {
    return false;
  }
  if (static_cast<unsigned>((ym + offset).month()) != 7)
  {
    return false;
  }
  if (static_cast<unsigned>((offset + ym).month()) != 7)
  {
    return false;
  }
  return true;
}

int main(int, char**)
{
  using year               = cuda::std::chrono::year;
  using month              = cuda::std::chrono::month;
  using weekday            = cuda::std::chrono::weekday;
  using weekday_indexed    = cuda::std::chrono::weekday_indexed;
  using year_month_weekday = cuda::std::chrono::year_month_weekday;
  using years              = cuda::std::chrono::years;
  using months             = cuda::std::chrono::months;

  constexpr weekday Tuesday = cuda::std::chrono::Tuesday;
  constexpr month January   = cuda::std::chrono::January;

  { // year_month_weekday + months (and switched)
    static_assert(noexcept(cuda::std::declval<year_month_weekday>() + cuda::std::declval<months>()));
    static_assert(noexcept(cuda::std::declval<months>() + cuda::std::declval<year_month_weekday>()));

    static_assert(
      cuda::std::is_same_v<year_month_weekday,
                           decltype(cuda::std::declval<year_month_weekday>() + cuda::std::declval<months>())>);
    static_assert(
      cuda::std::is_same_v<year_month_weekday,
                           decltype(cuda::std::declval<months>() + cuda::std::declval<year_month_weekday>())>);

    static_assert(testConstexprMonths(year_month_weekday{year{1}, January, weekday_indexed{Tuesday, 1}}), "");

    year_month_weekday ym{year{1234}, January, weekday_indexed{Tuesday, 3}};
    for (int i = 0; i <= 10; ++i) // TODO test wrap-around
    {
      year_month_weekday ym1 = ym + months{i};
      year_month_weekday ym2 = months{i} + ym;
      assert(static_cast<int>(ym1.year()) == 1234);
      assert(static_cast<int>(ym2.year()) == 1234);
      assert(ym1.month() == month(1 + i));
      assert(ym2.month() == month(1 + i));
      assert(ym1.weekday() == Tuesday);
      assert(ym2.weekday() == Tuesday);
      assert(ym1.index() == 3);
      assert(ym2.index() == 3);
      assert(ym1 == ym2);
    }
  }

  { // year_month_weekday + years (and switched)
    static_assert(noexcept(cuda::std::declval<year_month_weekday>() + cuda::std::declval<years>()));
    static_assert(noexcept(cuda::std::declval<years>() + cuda::std::declval<year_month_weekday>()));

    static_assert(
      cuda::std::is_same_v<year_month_weekday,
                           decltype(cuda::std::declval<year_month_weekday>() + cuda::std::declval<years>())>);
    static_assert(
      cuda::std::is_same_v<year_month_weekday,
                           decltype(cuda::std::declval<years>() + cuda::std::declval<year_month_weekday>())>);

    static_assert(testConstexprYears(year_month_weekday{year{1}, January, weekday_indexed{Tuesday, 1}}), "");

    year_month_weekday ym{year{1234}, cuda::std::chrono::January, weekday_indexed{Tuesday, 3}};
    for (int i = 0; i <= 10; ++i)
    {
      year_month_weekday ym1 = ym + years{i};
      year_month_weekday ym2 = years{i} + ym;
      assert(static_cast<int>(ym1.year()) == i + 1234);
      assert(static_cast<int>(ym2.year()) == i + 1234);
      assert(ym1.month() == January);
      assert(ym2.month() == January);
      assert(ym1.weekday() == Tuesday);
      assert(ym2.weekday() == Tuesday);
      assert(ym1.index() == 3);
      assert(ym2.index() == 3);
      assert(ym1 == ym2);
    }
  }

  return 0;
}
