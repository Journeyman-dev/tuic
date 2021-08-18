#include <TUIC/tuic.h>
#include <string>
#include <catch2/catch.hpp>
#define TO_STRING(value) #value

TEST_CASE("tuiDetailFlagToString") {
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_GLYPH_8)) == std::string(TO_STRING(TUI_DETAIL_FLAG_GLYPH_8)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_GLYPH_16)) == std::string(TO_STRING(TUI_DETAIL_FLAG_GLYPH_16)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_0)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_0)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_4)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_4)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_8)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_8)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_8NFG)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_8NFG)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_8NBG)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_8NBG)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_24)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_24)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_24NFG)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_24NFG)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_24NBG)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_24NBG)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_32)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_32)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_32NFG)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_32NFG)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_COLOR_32NBG)) == std::string(TO_STRING(TUI_DETAIL_FLAG_COLOR_32NBG)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_LAYOUT_FULL)) == std::string(TO_STRING(TUI_DETAIL_FLAG_LAYOUT_FULL)));
    REQUIRE(std::string(tuiDetailFlagToString(TUI_DETAIL_FLAG_LAYOUT_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_FLAG_LAYOUT_SPARSE)));
}

TEST_CASE("tuiStringToDetailFlag") {
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_GLYPH_8)) == TUI_DETAIL_FLAG_GLYPH_8);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_GLYPH_16)) == TUI_DETAIL_FLAG_GLYPH_16);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_0)) == TUI_DETAIL_FLAG_COLOR_0);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_4)) == TUI_DETAIL_FLAG_COLOR_4);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_8)) == TUI_DETAIL_FLAG_COLOR_8);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_8NFG)) == TUI_DETAIL_FLAG_COLOR_8NFG);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_8NBG)) == TUI_DETAIL_FLAG_COLOR_8NBG);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_24)) == TUI_DETAIL_FLAG_COLOR_24);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_24NFG)) == TUI_DETAIL_FLAG_COLOR_24NFG);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_24NBG)) == TUI_DETAIL_FLAG_COLOR_24NBG);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_32)) == TUI_DETAIL_FLAG_COLOR_32);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_32NFG)) == TUI_DETAIL_FLAG_COLOR_32NFG);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_COLOR_32NBG)) == TUI_DETAIL_FLAG_COLOR_32NBG);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_LAYOUT_FULL)) == TUI_DETAIL_FLAG_LAYOUT_FULL);
    REQUIRE(tuiStringToDetailFlag(TO_STRING(TUI_DETAIL_FLAG_LAYOUT_SPARSE)) == TUI_DETAIL_FLAG_LAYOUT_SPARSE);
}
