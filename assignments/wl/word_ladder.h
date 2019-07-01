#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

// TODO(students): Add some stuff here
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>


std::vector<std::string> FindLadder(const std::string& start, const std::string& destination,
                                    const std::unordered_set<std::string>& lexicon);

std::vector<std::string> PathToString(std::vector<std::vector<std::string>> ladders);

bool LadderPossible(std::unordered_set<std::string> &startWords,
                    std::unordered_set<std::string> &destWords,
                    std::unordered_set<std::string> &lexicon,
                    std::unordered_map<std::string, std::unordered_set<std::string>> &g,
                    bool alternate,
                    std::unordered_map<std::string,std::vector<std::string>>& reachable);

void BuildGraph(std::size_t length, const std::unordered_set<std::string>& fullLexicon,
                std::unordered_set<std::string>& lexicon,
                std::unordered_map<std::string, std::unordered_set<std::string>>& g);

void GetPaths(const std::string& word, const std::string& dest, std::vector<std::string> ladder,
              std::vector<std::vector<std::string>>& allLadders,
              std::unordered_map<std::string, std::vector<std::string>>& reachable);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_
