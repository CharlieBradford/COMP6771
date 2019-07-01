#include "assignments/wl/word_ladder.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::string> FindLadder(const std::string& start,
                                    const std::string& dest,
                                    const std::unordered_set<std::string>& fullLexicon) {
  std::unordered_set<std::string> lexicon;
  std::unordered_map<std::string, std::unordered_set<std::string>> g;
  BuildGraph(start.length(), fullLexicon, lexicon, g);

  std::unordered_map<std::string, std::vector<std::string>> reachable;
  std::vector<std::vector<std::string>> allLadders;
  std::unordered_set<std::string> startWords, destWords;
  startWords.insert(start);
  destWords.insert(dest);

  if (LadderPossible(startWords, destWords, lexicon, g, false, reachable)) {
    GetPaths(start, dest, std::vector<std::string>(1, start), allLadders, reachable);
  }

  return PathToString(allLadders);
}

// Build full adjacency graph for all words in fullLexicon that are of the same length as start
void BuildGraph(std::size_t length,
                const std::unordered_set<std::string>& fullLexicon,
                std::unordered_set<std::string>& lexicon,
                std::unordered_map<std::string, std::unordered_set<std::string>>& g) {
  for (const auto& word : fullLexicon) {
    if (word.length() == length) {
      lexicon.insert(word);
    }
  }

  for (const auto& word : lexicon) {
    std::unordered_set<std::string> genericWords;
    for (std::size_t i = 0; i < length; ++i) {
      g[word.substr(0, i) + "*" + word.substr(i + 1, word.length() - i)].insert(word);
    }
  }
}

// Use two directional bfs to simultaneously determine if ladder is possible and build smallest
// graph necessary to find all paths of
bool LadderPossible(std::unordered_set<std::string>& startWords,
                    std::unordered_set<std::string>& destWords,
                    std::unordered_set<std::string>& lexicon,
                    std::unordered_map<std::string, std::unordered_set<std::string>>& g,
                    bool alternate,
                    std::unordered_map<std::string, std::vector<std::string>>& reachable) {
  if (startWords.empty()) {
    return false;
  }
  if (startWords.size() > destWords.size()) {
    return LadderPossible(destWords, startWords, lexicon, g, !alternate, reachable);
  }

  for (const auto& word : startWords) {
    lexicon.erase(word);
  }
  for (const auto& word : destWords) {
    lexicon.erase(word);
  }

  std::unordered_set<std::string> midWords;
  bool pathFound = false;
  for (const auto& word : startWords) {
    auto l = word.length();
    for (std::size_t i = 0; i < l; ++i) {
      for (const auto& reachableWord : g[word.substr(0, i) + "*" + word.substr(i + 1, l - i)]) {
        if (destWords.count(reachableWord) != 0) {
          pathFound = true;
          alternate ? reachable[reachableWord].push_back(word)
                    : reachable[word].push_back(reachableWord);
        } else if (!pathFound && lexicon.count(reachableWord) != 0) {
          midWords.insert(reachableWord);
          alternate ? reachable[reachableWord].push_back(word)
                    : reachable[word].push_back(reachableWord);
        }
      }
    }
  }
  return pathFound || LadderPossible(destWords, midWords, lexicon, g, !alternate, reachable);
}

// Search smaller graph for all possible path
void GetPaths(const std::string& word,
              const std::string& dest,
              std::vector<std::string> ladder,
              std::vector<std::vector<std::string>>& allLadders,
              std::unordered_map<std::string, std::vector<std::string>>& reachable) {
  if (word == dest) {
    allLadders.push_back(ladder);
  } else {
    for (const auto& reachableWord : reachable[word]) {
      ladder.push_back(reachableWord);
      GetPaths(reachableWord, dest, ladder, allLadders, reachable);
      ladder.pop_back();
    }
  }
}

// Converts vector of vector of words to vector of word ladders + sorts final vector
// lexicographically
std::vector<std::string> PathToString(std::vector<std::vector<std::string>> ladders) {
  std::vector<std::string> allLadders;
  if (ladders.empty()) {
    return allLadders;
  }

  auto length = (*ladders.begin()).size();
  for (const auto& ladder : ladders) {
    if (ladder.size() < length) {
      length = ladder.size();
    }
  }

  for (const auto& ladder : ladders) {
    std::stringstream str;
    copy(ladder.begin(), ladder.end(), std::ostream_iterator<std::string>(str, " "));
    allLadders.push_back(str.str());
  }

  std::unordered_set<std::string> s;
  std::remove_if(allLadders.begin(), allLadders.end(),
                 [&s](const std::string& i) { return !s.insert(i).second; });

  sort(allLadders.begin(), allLadders.end());
  return allLadders;
}
