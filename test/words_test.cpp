/**
 * Unit tests for words.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include "words/words.h"

#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>

// Test readURL
TEST(Words, readURL) {
  const char* url =
      "https://raw.githubusercontent.com/a8fdf820/misc/main/words2";
  std::string s0(readURL(url));
  std::string s1("This is a\ntest text.\n");
  EXPECT_EQ(0, s0.compare(s1));  // the two strings match
}

// Test parse
TEST(Words, parse) {
  std::string s0("It's a topsy-turvy world.");
  const char* delimiters = " -";
  std::string symbolsToKeep("'");
  std::vector<std::string> v0(parse(s0, delimiters, symbolsToKeep));
  EXPECT_EQ(v0[0], std::string("it's"));  // lower case, "'" is kept
  EXPECT_EQ(v0[1], std::string("a"));
  EXPECT_EQ(v0[2], std::string("topsy"));  // "-" removed
  EXPECT_EQ(v0[3], std::string("turvy"));  // topsy turvy are two words
  EXPECT_EQ(v0[4], std::string("world"));  // "." removed
  EXPECT_EQ(v0.size(), size_t(5));         // 5 words in total
}

// Test filter
TEST(Words, filter) {
  std::vector<std::string> v0;
  v0.push_back(std::string("it's"));
  v0.push_back(std::string("a"));
  v0.push_back(std::string("topsy"));
  v0.push_back(std::string("turvy"));
  v0.push_back(std::string("world"));
  std::ofstream of("stop");
  of << "it's" << std::endl << "a";
  of.close();
  std::vector<std::string> v1 = filter(v0, "stop");
  // The words in the file are not in the returned vector.
  EXPECT_EQ(v1[0], std::string("topsy"));
  EXPECT_EQ(v1[1], std::string("turvy"));
  EXPECT_EQ(v1[2], std::string("world"));
  EXPECT_EQ(v1.size(),size_t(3));
  remove("stop");
}

// Test sortWords
TEST(Words, sortWords) {
  std::vector<std::string> v0;
  v0.push_back(std::string("one"));
  v0.push_back(std::string("two"));
  v0.push_back(std::string("two"));
  v0.push_back(std::string("duo"));
  v0.push_back(std::string("duo"));
  v0.push_back(std::string("three"));
  v0.push_back(std::string("three"));
  v0.push_back(std::string("three"));
  // Keep word of occurance greater than 1, meaning start from 2
  std::vector<std::pair<std::string, unsigned int>> pairs(sortWords(v0, 1U));
  EXPECT_EQ(pairs[0].first, "three");
  EXPECT_EQ(pairs[0].second, 3U);  // most occured word precedes others
  EXPECT_EQ(pairs[1].first, "duo");  // duo and two have the same occurance
  EXPECT_EQ(pairs[1].second, 2U);
  EXPECT_EQ(pairs[2].first, "two");  // duo is before two alphabetically
  EXPECT_EQ(pairs[2].second, 2U);
  EXPECT_EQ(pairs.size(), size_t(3));  // 3 words left as one is ignored
}