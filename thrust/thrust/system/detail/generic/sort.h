/*
 *  Copyright 2008-2013 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <thrust/detail/config.h>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header
#include <thrust/system/detail/generic/tag.h>

THRUST_NAMESPACE_BEGIN
namespace system
{
namespace detail
{
namespace generic
{

template <typename DerivedPolicy, typename RandomAccessIterator>
_CCCL_HOST_DEVICE void
sort(thrust::execution_policy<DerivedPolicy>& exec, RandomAccessIterator first, RandomAccessIterator last);

template <typename DerivedPolicy, typename RandomAccessIterator, typename StrictWeakOrdering>
_CCCL_HOST_DEVICE void
sort(thrust::execution_policy<DerivedPolicy>& exec,
     RandomAccessIterator first,
     RandomAccessIterator last,
     StrictWeakOrdering comp);

template <typename DerivedPolicy, typename RandomAccessIterator1, typename RandomAccessIterator2>
_CCCL_HOST_DEVICE void sort_by_key(
  thrust::execution_policy<DerivedPolicy>& exec,
  RandomAccessIterator1 keys_first,
  RandomAccessIterator1 keys_last,
  RandomAccessIterator2 values_first);

template <typename DerivedPolicy,
          typename RandomAccessIterator1,
          typename RandomAccessIterator2,
          typename StrictWeakOrdering>
_CCCL_HOST_DEVICE void sort_by_key(
  thrust::execution_policy<DerivedPolicy>& exec,
  RandomAccessIterator1 keys_first,
  RandomAccessIterator1 keys_last,
  RandomAccessIterator2 values_first,
  StrictWeakOrdering comp);

template <typename DerivedPolicy, typename RandomAccessIterator>
_CCCL_HOST_DEVICE void
stable_sort(thrust::execution_policy<DerivedPolicy>& exec, RandomAccessIterator first, RandomAccessIterator last);

// XXX it is an error to call this function; it has no implementation
template <typename DerivedPolicy, typename RandomAccessIterator, typename StrictWeakOrdering>
_CCCL_HOST_DEVICE void stable_sort(
  thrust::execution_policy<DerivedPolicy>& exec,
  RandomAccessIterator first,
  RandomAccessIterator last,
  StrictWeakOrdering comp);

template <typename DerivedPolicy, typename RandomAccessIterator1, typename RandomAccessIterator2>
_CCCL_HOST_DEVICE void stable_sort_by_key(
  thrust::execution_policy<DerivedPolicy>& exec,
  RandomAccessIterator1 keys_first,
  RandomAccessIterator1 keys_last,
  RandomAccessIterator2 values_first);

// XXX it is an error to call this function; it has no implementation
template <typename DerivedPolicy,
          typename RandomAccessIterator1,
          typename RandomAccessIterator2,
          typename StrictWeakOrdering>
_CCCL_HOST_DEVICE void stable_sort_by_key(
  thrust::execution_policy<DerivedPolicy>& exec,
  RandomAccessIterator1 keys_first,
  RandomAccessIterator1 keys_last,
  RandomAccessIterator2 values_first,
  StrictWeakOrdering comp);

template <typename DerivedPolicy, typename ForwardIterator>
_CCCL_HOST_DEVICE bool
is_sorted(thrust::execution_policy<DerivedPolicy>& exec, ForwardIterator first, ForwardIterator last);

template <typename DerivedPolicy, typename ForwardIterator, typename Compare>
_CCCL_HOST_DEVICE bool
is_sorted(thrust::execution_policy<DerivedPolicy>& exec, ForwardIterator first, ForwardIterator last, Compare comp);

template <typename DerivedPolicy, typename ForwardIterator>
_CCCL_HOST_DEVICE ForwardIterator
is_sorted_until(thrust::execution_policy<DerivedPolicy>& exec, ForwardIterator first, ForwardIterator last);

template <typename DerivedPolicy, typename ForwardIterator, typename Compare>
_CCCL_HOST_DEVICE ForwardIterator is_sorted_until(
  thrust::execution_policy<DerivedPolicy>& exec, ForwardIterator first, ForwardIterator last, Compare comp);

} // namespace generic
} // namespace detail
} // namespace system
THRUST_NAMESPACE_END

#include <thrust/system/detail/generic/sort.inl>
