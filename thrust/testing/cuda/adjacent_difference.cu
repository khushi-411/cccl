#include <thrust/adjacent_difference.h>
#include <thrust/device_free.h>
#include <thrust/device_malloc.h>
#include <thrust/execution_policy.h>

#include <unittest/unittest.h>

#ifdef THRUST_TEST_DEVICE_SIDE
template <typename ExecutionPolicy, typename Iterator1, typename Iterator2>
__global__ void adjacent_difference_kernel(ExecutionPolicy exec, Iterator1 first, Iterator1 last, Iterator2 result)
{
  thrust::adjacent_difference(exec, first, last, result);
}

template <typename ExecutionPolicy, typename Iterator1, typename Iterator2, typename BinaryFunction>
__global__ void
adjacent_difference_kernel(ExecutionPolicy exec, Iterator1 first, Iterator1 last, Iterator2 result, BinaryFunction f)
{
  thrust::adjacent_difference(exec, first, last, result, f);
}

template <typename T, typename ExecutionPolicy>
void TestAdjacentDifferenceDevice(ExecutionPolicy exec, const size_t n)
{
  thrust::host_vector<T> h_input   = unittest::random_samples<T>(n);
  thrust::device_vector<T> d_input = h_input;

  thrust::host_vector<T> h_output(n);
  thrust::device_vector<T> d_output(n);

  thrust::adjacent_difference(h_input.begin(), h_input.end(), h_output.begin());
  adjacent_difference_kernel<<<1, 1>>>(exec, d_input.begin(), d_input.end(), d_output.begin());
  {
    cudaError_t const err = cudaDeviceSynchronize();
    ASSERT_EQUAL(cudaSuccess, err);
  }

  ASSERT_EQUAL(h_output, d_output);

  thrust::adjacent_difference(h_input.begin(), h_input.end(), h_output.begin(), ::cuda::std::plus<T>());
  adjacent_difference_kernel<<<1, 1>>>(exec, d_input.begin(), d_input.end(), d_output.begin(), ::cuda::std::plus<T>());
  {
    cudaError_t const err = cudaDeviceSynchronize();
    ASSERT_EQUAL(cudaSuccess, err);
  }

  ASSERT_EQUAL(h_output, d_output);

  // in-place operation
  thrust::adjacent_difference(h_input.begin(), h_input.end(), h_input.begin(), ::cuda::std::plus<T>());
  adjacent_difference_kernel<<<1, 1>>>(exec, d_input.begin(), d_input.end(), d_input.begin(), ::cuda::std::plus<T>());
  {
    cudaError_t const err = cudaDeviceSynchronize();
    ASSERT_EQUAL(cudaSuccess, err);
  }

  ASSERT_EQUAL(h_input, h_output); // computed previously
  ASSERT_EQUAL(d_input, d_output); // computed previously
}

template <typename T>
void TestAdjacentDifferenceDeviceSeq(const size_t n)
{
  TestAdjacentDifferenceDevice<T>(thrust::seq, n);
}
DECLARE_VARIABLE_UNITTEST(TestAdjacentDifferenceDeviceSeq);

template <typename T>
void TestAdjacentDifferenceDeviceDevice(const size_t n)
{
  TestAdjacentDifferenceDevice<T>(thrust::device, n);
}
DECLARE_VARIABLE_UNITTEST(TestAdjacentDifferenceDeviceDevice);
#endif

void TestAdjacentDifferenceCudaStreams()
{
  cudaStream_t s;
  cudaStreamCreate(&s);

  thrust::device_vector<int> input{1, 4, 6};
  thrust::device_vector<int> output(input.size());

  thrust::adjacent_difference(thrust::cuda::par.on(s), input.begin(), input.end(), output.begin());

  cudaStreamSynchronize(s);

  thrust::device_vector<int> ref{1, 3, 2};

  ASSERT_EQUAL(output, ref);

  cudaStreamDestroy(s);
}
DECLARE_UNITTEST(TestAdjacentDifferenceCudaStreams);

struct detect_wrong_difference
{
  using difference_type   = void;
  using value_type        = long long;
  using pointer           = void;
  using reference         = detect_wrong_difference;
  using iterator_category = ::cuda::std::output_iterator_tag;

  bool* flag;

  _CCCL_HOST_DEVICE detect_wrong_difference operator++() const
  {
    return *this;
  }
  _CCCL_HOST_DEVICE detect_wrong_difference operator*() const
  {
    return *this;
  }
  template <typename Difference>
  _CCCL_HOST_DEVICE detect_wrong_difference operator+(Difference) const
  {
    return *this;
  }
  template <typename Index>
  _CCCL_HOST_DEVICE detect_wrong_difference operator[](Index) const
  {
    return *this;
  }

  _CCCL_DEVICE void operator=(long long difference) const
  {
    if (difference != 1)
    {
      *flag = false;
    }
  }
};

void TestAdjacentDifferenceWithBigIndexesHelper(int magnitude)
{
  thrust::counting_iterator<long long> begin(1);
  thrust::counting_iterator<long long> end = begin + (1ll << magnitude);
  ASSERT_EQUAL(::cuda::std::distance(begin, end), 1ll << magnitude);

  thrust::device_ptr<bool> all_differences_correct = thrust::device_malloc<bool>(1);
  *all_differences_correct                         = true;

  detect_wrong_difference out = {thrust::raw_pointer_cast(all_differences_correct)};

  thrust::adjacent_difference(thrust::device, begin, end, out);

  bool all_differences_correct_h = *all_differences_correct;
  thrust::device_free(all_differences_correct);

  ASSERT_EQUAL(all_differences_correct_h, true);
}

void TestAdjacentDifferenceWithBigIndexes()
{
  TestAdjacentDifferenceWithBigIndexesHelper(30);
#ifndef THRUST_FORCE_32_BIT_OFFSET_TYPE
  TestAdjacentDifferenceWithBigIndexesHelper(31);
  TestAdjacentDifferenceWithBigIndexesHelper(32);
  TestAdjacentDifferenceWithBigIndexesHelper(33);
#endif
}
DECLARE_UNITTEST(TestAdjacentDifferenceWithBigIndexes);
