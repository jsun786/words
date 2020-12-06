/**
 * Implementation for Words.
 *
 * Copyright (c) 2020, Jiayue Sun.
 */

#include "words.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

// Need to install third party libraries: libcurl and curlpp, which may
// require different installations depending on the running platform. This
// program was written and tested on Ubuntu.
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

// Take a URL and return a string containing the content of the webpage.
std::string readURL(const char* url) {
  std::stringstream sstream;
  try {
    curlpp::Cleanup cleanup;  // Memory release
    sstream << curlpp::options::Url(url);
  } catch (curlpp::LogicError& err) {
    std::cout << err.what() << std::endl;
  } catch (curlpp::RuntimeError& err) {
    std::cout << err.what() << std::endl;
  }
  return sstream.str();
}

// Take a string and parse its content into a vector of words using demiliters
// provided in delimiterList, and each word contains only lower case
// alphabetic characters and symbols in keepList.
std::vector<std::string> parse(std::string str, const char* delimiterList,
                               std::string keepList) {
  std::vector<std::string> words;
  if (str.size() == 0) {
    return words;
  } else {
    // Elements that are neither alphabetic nor in keepList are replaced
    // by space
    std::replace_if(
        str.begin(), str.end(),
        [keepList](char c) {
          return ((!std::isalpha(c)) &&
                  (keepList.find_first_of(c) == std::string::npos));
        },
        ' ');
    size_t prev = 0, next = 0;
    while ((next = str.find_first_of(delimiterList, prev)) !=
           std::string::npos) {
      if (next > prev) {
        std::string substr = str.substr(prev, next - prev);
        // Remove "words" started with a kept symbol
        if (std::isalpha(substr[0])) {
          words.push_back(str.substr(prev, next - prev));
        }
      }
      prev = next + 1;
    }
    if (prev < str.length()) {
      words.push_back(str.substr(prev, std::string::npos));
    }
  }
  for (auto& word : words) {
    // Turn words into lower case
    std::transform(word.begin(), word.end(), word.begin(),
                   [](char c) { return std::tolower(c); });
  }
  return words;
}

// Remove stopwords from the vector, the stopwords are stored in lower case line
// by line in a file whose address is given by the input cstring.
std::vector<std::string> filter(std::vector<std::string> words,
                                const char* address) {
  if (words.size() == 0) {
    return words;
  } else {
    std::ifstream in(address);
    std::vector<std::string> stopwords;
    std::vector<std::string> result;
    std::string line;
    if (in.fail()) {
      printf("Failed to open the file.");
    } else {
      while (std::getline(in, line)) {
        stopwords.push_back(line);
      }
    }
    in.close();
    if (stopwords.size() > 0) {
      for (auto word : words) {
        if (std::find(stopwords.begin(), stopwords.end(), word) ==
            stopwords.end()) {
          result.push_back(word);
        }
      }
    }
    return result;
  }
}

// Return a vector of <word, occurence> pairs, which are sorted in the
// descending order of occurence, and words of the same occurance are sorted
// alphabetically. Words with an occurance of occurLimit or lower are discarded.
std::vector<std::pair<std::string, unsigned int>> sortWords(
    std::vector<std::string> words, unsigned int occurLimit) {
  std::vector<std::pair<std::string, unsigned int>> result;
  if (words.size() == 0) {
    return result;
  } else {
    std::sort(words.begin(), words.end());
    std::map<std::string, int> map;  // Automatically sorted alphabetically
    for (auto word : words) {
      if (!map.insert(std::pair<std::string, unsigned int>(word, 1U)).second) {
        map[word]++;
      }
    }
    for (auto pair : map) {
      if (pair.second > occurLimit) {
        result.push_back(pair);
      }
    }
    std::sort(result.begin(), result.end(),
              [](const std::pair<std::string, unsigned int>& a,
                 const std::pair<std::string, unsigned int>& b) {
                return a.second > b.second;
              });
    return result;
  }
}

// Print the word-occurance pairs. Words are 24 characters long and right
// justified, and occurances are 6 digits long and left justified, and each
// word and its occurance are separated by one space.
void display(std::vector<std::pair<std::string, unsigned int>> pairs) {
  printf("%24s %-6s\n", "Word", "Freq");
  printf("-------------------------------\n");
  if (pairs.size() > 0) {
    for (auto& pair : pairs) {
      printf("%24s %-6u\n", pair.first.c_str(), pair.second);
    }
  }
}