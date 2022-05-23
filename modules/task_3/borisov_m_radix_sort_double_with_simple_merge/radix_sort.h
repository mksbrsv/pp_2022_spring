// Copyright 2022 Borisov Maxim

#ifndef MODULES_TASK_3_BORISOV_M_RADIX_SORT_DOUBLE_WITH_SIMPLE_MERGE_RADIX_SORT_H_
#define MODULES_TASK_3_BORISOV_M_RADIX_SORT_DOUBLE_WITH_SIMPLE_MERGE_RADIX_SORT_H_

// #include <omp.h>
#include <tbb/tbb.h>

#include <algorithm>
#include <random>
#include <utility>
#include <vector>

std::vector<double> random_vec(int size);
std::vector<double> merge(const std::vector<double>& arr1,
                          const std::vector<double>& arr2);
std::vector<double> merge_omp(const std::vector<double>& arr1,
                              const std::vector<double>& arr2);

void count_sort(double* in, double* out, int len, int exp);
std::vector<double> radix_sort_seq(const std::vector<double>& data1);
std::vector<double> radix_sort_seq_n(const std::vector<double>& data1,
                                     std::vector<double>::iterator beg,
                                     std::vector<double>::iterator end);
std::vector<double> radix_sort_omp(const std::vector<double>& data,
                                   std::size_t n_threads);
std::vector<double> radix_sort_tbb(std::vector<double>* data,
                                   std::size_t n_threads);

#endif  // MODULES_TASK_3_BORISOV_M_RADIX_SORT_DOUBLE_WITH_SIMPLE_MERGE_RADIX_SORT_H_
