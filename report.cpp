/**
 * Gnereate report for an integration test.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include <iostream>

#include "words/words.h"

const char* DELIMITERS = " -";  // used to split the whole string into words
const std::string SYMBOLS_TO_KEEP = "'";  // symbols that are kept in a word
const unsigned int OCCUR_LIMIT =
    3U;  // words of this occurance of lower will be ignored
const char* STOPWORDS_FILE = "stopwords";  // Address of stopwords file

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << argv[0] << ": Wrong number of arguments" << std::endl
              << argv[0] << ": Usage: "
              << " url " << std::endl;
    return EXIT_FAILURE;
  }
  const char* url = argv[1];
  display(sortWords(
      filter(parse(readURL(url), DELIMITERS, SYMBOLS_TO_KEEP), STOPWORDS_FILE),
      OCCUR_LIMIT));
}