// Copyright 2022 Borisov Maxim

#include "../../../modules/task_3/borisov_m_radix_sort_double_with_simple_merge/radix_sort.h"

std::vector<double> random_vec(int size) {
  std::vector<double> data(size);
  std::mt19937 gen;
  gen.seed(static_cast<uint32_t>(time(0)));
  std::uniform_real_distribution<double> buf(1, 1000);
  std::transform(data.begin(), data.end(), data.begin(),
                 [&](double x) { return buf(gen); });
  return data;
}

std::vector<double> merge(const std::vector<double>& arr1,
                          const std::vector<double>& arr2) {
  int len1 = arr1.size();
  int len2 = arr2.size();
  std::vector<double> out;
  out.resize(len1 + len2);
  int x = 0, y = 0;
  for (int i = 0; i < len1 + len2; i++) {
    if (x >= len1) {
      out[i] = arr2[y++];
    } else if (y >= len2) {
      out[i] = arr1[x++];
    } else if (arr1[x] < arr2[y]) {
      out[i] = arr1[x++];
    } else {
      out[i] = arr2[y++];
    }
  }
  return out;
}
void count_sort(double* in, double* out, int len, int exp) {
  unsigned char* buf = reinterpret_cast<unsigned char*>(in);
  int count[257] = {0};
  int val = 0;
  for (int i = 0; i < len; i++) {
    count[buf[8 * i + exp]]++;
  }
  int j = 0;
  for (; j < 256; j++) {
    if (count[j] != 0) break;
  }
  val = count[j];
  count[j] = 0;
  j++;
  for (; j < 256; j++) {
    int tmp = count[j];
    count[j] = val;
    val += tmp;
  }
  for (int i = 0; i < len; i++) {
    out[count[buf[8 * i + exp]]] = in[i];
    count[buf[8 * i + exp]]++;
  }
}

std::vector<double> radix_sort_seq(const std::vector<double>& data1) {
  int len1 = static_cast<int>(data1.size());

  std::vector<double> in1 = data1;
  std::vector<double> out1(data1.size());

  for (int i = 0; i < 4; i++) {
    count_sort(in1.data(), out1.data(), len1, 2 * i);
    count_sort(out1.data(), in1.data(), len1, 2 * i + 1);
  }
  return in1;
}

std::vector<double> radix_sort_seq_n(const std::vector<double>& data1,
                                     std::vector<double>::iterator beg,
                                     std::vector<double>::iterator end) {
  int len1 = static_cast<int>(end - beg);

  std::vector<double> out1(len1);

  for (int i = 0; i < 4; i++) {
    count_sort(&*beg, out1.data(), len1, 2 * i);
    count_sort(out1.data(), &*beg, len1, 2 * i + 1);
  }
  return std::vector<double>(beg, end);
}

std::vector<double> radix_sort_tbb(std::vector<double>* data,
                                   std::size_t n_threads) {
  std::vector<std::vector<double>> results;
  std::vector<std::vector<double>> semi_results;
  std::vector<double> result;
  int local_size = data->size() / n_threads;
  tbb::task_arena arena_s(static_cast<int>(n_threads));
  tbb::spin_mutex mutex1;
  for (std::size_t i = 0; i < n_threads - 1; i++) {
    arena_s.execute([&results, &data, &mutex1, i, local_size]() {
      std::vector<double> local;
      local = radix_sort_seq_n(*data, data->begin() + local_size * i,
                               data->begin() + local_size * (i + 1));
      tbb::spin_mutex::scoped_lock lock;
      lock.acquire(mutex1);
      results.push_back(local);
      lock.release();
    });
  }
  arena_s.execute([&results, &data, &mutex1, n_threads, local_size]() {
    std::vector<double> local;
    local = radix_sort_seq_n(*data, data->begin() + local_size * n_threads,
                             data->end());
    tbb::spin_mutex::scoped_lock lock;
    lock.acquire(mutex1);
    results.push_back(local);
    lock.release();
  });
  tbb::spin_mutex mutex2;
  tbb::task_arena arena_m(static_cast<int>(n_threads));
  for (std::size_t i = 0; i < n_threads; i++) {
    arena_m.execute([&results, &mutex2, &semi_results, i]() {
      std::vector<double> sas;
      if (i == 0 || i == 2 || i == 4) {
        sas = merge(results[i], results[i + 1]);
      }
      tbb::spin_mutex::scoped_lock lock;
      lock.acquire(mutex2);
      semi_results.push_back(sas);
      lock.release();
    });
  }
  for (int i = 0; i < static_cast<int>(semi_results.size()); i++) {
    result = merge(result, semi_results[i]);
  }
  return result;
}
