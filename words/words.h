/**
 * Words declarations.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#ifndef WORDS_WORDS_H_
#define WORDS_WORDS_H_

#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::string readURL(const char*);
std::vector<std::string> parse(std::string, const char*, std::string);
std::vector<std::string> filter(std::vector<std::string>, const char*);
std::vector<std::pair<std::string, unsigned int>> sortWords(
    std::vector<std::string>, unsigned int);
void display(std::vector<std::pair<std::string, unsigned int>>);

#endif  // WORDS_WORDS_H_