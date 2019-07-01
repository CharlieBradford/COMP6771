/*

  == Explanation and rational of testing ==

  Explain and justify how you approached testing, the degree
   to which you're certain you have covered all possibilities,
   and why you think your tests are that thorough.

*/

#include "assignments/wl/lexicon.h"
#include "assignments/wl/word_ladder.h"
#include "catch.h"

TEST_CASE("Word ladders are accurately computed", "[FindLadders]") {
  auto lexicon = GetLexicon("assignments/wl/words.txt");

  std::vector<std::string> empty;
  SECTION("No ladders found from words of different lengths") {
    REQUIRE(FindLadder("dumb", "smart", lexicon) == empty);
    REQUIRE(FindLadder("same", "opposite", lexicon) == empty);
    REQUIRE(FindLadder("easy", "difficult", lexicon) == empty);
  }

  SECTION("No ladders found from cases where no ladders exist") {
    REQUIRE(FindLadder("humans", "mutant", lexicon) == empty);
    REQUIRE(FindLadder("antonymous", "synonymous", lexicon) == empty);
  }

  SECTION("Correct ladders found") {
    std::vector<std::vector<std::string>> ladders = {
        {"play ploy plop slop stop ", "play slay slap slop stop "},
        {"work fork form foam flam flay play ", "work pork perk peak pean plan play ",
         "work pork perk peak peat plat play ", "work pork perk pert peat plat play ",
         "work pork porn pirn pian plan play ", "work pork port pert peat plat play ",
         "work word wood pood plod ploy play ", "work worm form foam flam flay play ",
         "work worn porn pirn pian plan play ", "work wort bort boat blat plat play ",
         "work wort port pert peat plat play ", "work wort wert pert peat plat play "}};
    REQUIRE(FindLadder("play", "stop", lexicon) == ladders[0]);
    REQUIRE(FindLadder("work", "play", lexicon) == ladders[1]);
  }
}
