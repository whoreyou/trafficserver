//
// Created by zk on 3/14/22.
//

#include <benchmark/benchmark.h>
#include <array>
#include "P_Cache.h"


constexpr int len = 6;

// constexpr function具有inline属性，你应该把它放在头文件中
constexpr auto my_pow(const int i)
{
  return i * i;
}

// 使用operator[]读取元素，依次存入1-6的平方
static void bench_array_operator(benchmark::State& state)
{
  std::array<int, len> arr;
  constexpr int i = 1;
  for (auto _: state) {
    arr[0] = my_pow(i);
    arr[1] = my_pow(i+1);
    arr[2] = my_pow(i+2);
    arr[3] = my_pow(i+3);
    arr[4] = my_pow(i+4);
    arr[5] = my_pow(i+5);
  }
}
BENCHMARK(bench_array_operator);

void test_put() {
  CacheKey key;
  Vol *vol = theCache->key_to_vol(&key, "example.com", sizeof("example.com") - 1);
  RamCache *cache = new_RamCacheLRU();
  std::vector<Ptr<IOBufferData>> data;
  int64_t cache_size = 1LL << 28;
  cache->init(cache_size, vol);

  for (int l = 0; l < 10; l++) {
    for (int i = 0; i < 200; i++) {
      IOBufferData *d = THREAD_ALLOC(ioDataAllocator, this_thread());
      CryptoHash hash;

      d->alloc(BUFFER_SIZE_INDEX_16K);
      data.push_back(make_ptr(d));
      hash.u64[0] = (static_cast<uint64_t>(i) << 32) + i;
      hash.u64[1] = (static_cast<uint64_t>(i) << 32) + i;
      cache->put(&hash, data[i].get(), 1 << 15);
      // More hits for the first 10.
      for (int j = 0; j <= i && j < 10; j++) {
        Ptr<IOBufferData> data;
        CryptoHash hash;

        hash.u64[0] = (static_cast<uint64_t>(j) << 32) + j;
        hash.u64[1] = (static_cast<uint64_t>(j) << 32) + j;
        cache->get(&hash, &data);
      }
    }
  }

}

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    test_put();
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);
// Run the benchmark
BENCHMARK_MAIN();