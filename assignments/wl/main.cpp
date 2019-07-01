#include <iostream>
#include <string>
#include <vector>

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"

int main() {
  auto lexicon = GetLexicon("assignments/wl/words.txt");
  std::string start;
  std::string destination;
  std::cout << "Enter start word (RETURN to quit): " << std::flush;
  std::cin >> start;
  std::cout << "Enter destination word: " << std::flush;
  std::cin >> destination;

  auto ladders = FindLadder(start, destination, lexicon);
  if (ladders.size() != 0) {
    std::cout << "Found ladder: ";
    for (const auto& ladder : ladders) {
      std::cout << ladder << "\n";
    }
  } else {
    std::cout << "No ladders found.\n";
  }

  std::cout << std::flush;
  return 0;
}
