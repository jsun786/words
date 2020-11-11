# Words

Write a C++ program that takes a URL as an argument, extracts the words in the corresponding page, and prints the words along with their frequency.

1. Consider only words comprising the letters a-z, A-Z, and the single quote ('). E.g., below is a line and the words in it. Note that *It's* is a single word and *topsy-turvy* are two separate words.
```
It's a topsy-turvy world.

    It's
    a
    topsy
    turvy
    world
```
2. Ignore case. I.e., *Class* and *class* should be considered to be the same word.
3. Some filler words, called **stopwords** (like *It's* and *a* above), don't contribute to the distinctiveness of the text, so are typically ignored in tasks like machine learning. Ignore these words in your analysis. E.g., assess the above text to contain only 3 words (*topsy*, *turvy*, and *world*), each with a frequency of 1. Use the list of stopwords in the **stopwords** file.
4. Print the results as word/frequency pairs. Each word should be 24 characters long and right justified, each frequency should be 6 digits long and left justified, and both should be separated by one space. Ignore words for which frequencies are 3 or lower.
4. Sort words in the descending order of frequencies. If there are multiple words at the same frequency, sort them in ascending alphabetical order.

Structure your project in the standard way presented in this class through the previous projects. Specifically:
1. Create a folder to hold your logic (header and source files).
2. Write unit tests in a folder of its own (like *match_test.cpp* in *Match*), using Google Test like in the projects - you may copy the bazel code to simplify the setup.
3. Build an integration test for the program end-to-end (e.g., like *report.cpp* in *Match*).