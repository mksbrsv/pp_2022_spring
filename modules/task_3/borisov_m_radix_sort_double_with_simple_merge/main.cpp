// Copyright 2022 Borisov Maxim

#include "../../../modules/task_3/borisov_m_radix_sort_double_with_simple_merge/radix_sort.h"
#include "gtest/gtest.h"

constexpr std::size_t n_threads = 6;

TEST(borisov_task3, test_size_10) {
  std::vector<double> par = random_vec(10);
  par = radix_sort_tbb(&par, n_threads);
  ASSERT_TRUE(std::is_sorted(par.begin(), par.end()));
}

TEST(borisov_task1, test_size_100) {
  std::vector<double> par = random_vec(100);
  par = radix_sort_tbb(&par, n_threads);
  ASSERT_TRUE(std::is_sorted(par.begin(), par.end()));
}

TEST(borisov_task1, test_size_500) {
  std::vector<double> par = random_vec(500);
  par = radix_sort_tbb(&par, n_threads);
  ASSERT_TRUE(std::is_sorted(par.begin(), par.end()));
}

TEST(borisov_task1, test_size_1000) {
  std::vector<double> par = random_vec(1000);
  par = radix_sort_tbb(&par, n_threads);
  ASSERT_TRUE(std::is_sorted(par.begin(), par.end()));
}

TEST(borisov_task1, test_size_2000) {
  std::vector<double> par = random_vec(2000);
  par = radix_sort_tbb(&par, n_threads);
  ASSERT_TRUE(std::is_sorted(par.begin(), par.end()));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
