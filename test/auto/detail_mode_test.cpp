#include <TUIC/tuic.h>
#include <string>
#include <catch2/catch.hpp>
#define TO_STRING(value) #value

TEST_CASE("tuiDetailModeToString") {
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C0_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C0_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C4_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C4_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C8_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C8_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C8NBG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C8NBG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C8NFG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C8NFG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C24_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C24_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C24NBG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C24NBG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C24NFG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C24NFG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C32_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C32_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C32NBG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C32NBG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C32NFG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G8_C32NFG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C0_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C0_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C4_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C4_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C8_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C8_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C8NBG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C8NBG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C8NFG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C8NFG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C24_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C24_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C24NBG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C24NBG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C24NFG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C24NFG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C32_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C32_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C32NBG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C32NBG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C32NFG_FULL)) == std::string(TO_STRING(TUI_DETAIL_G16_C32NFG_FULL)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C0_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C0_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C4_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C4_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C8_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C8_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C8NBG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C8NBG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C8NFG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C8NFG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C24_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C24_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C24NBG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C24NBG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C24NFG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C24NFG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C32_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C32_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C32NBG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C32NBG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G8_C32NFG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G8_C32NFG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C0_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C0_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C4_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C4_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C8_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C8_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C8NBG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C8NBG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C8NFG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C8NFG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C24_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C24_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C24NBG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C24NBG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C24NFG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C24NFG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C32_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C32_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C32NBG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C32NBG_SPARSE)));
    REQUIRE(std::string(tuiDetailModeToString(TUI_DETAIL_G16_C32NFG_SPARSE)) == std::string(TO_STRING(TUI_DETAIL_G16_C32NFG_SPARSE)));
}

TEST_CASE("tuiStringToDetailMode") {
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C0_FULL)) == TUI_DETAIL_G8_C0_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C4_FULL)) == TUI_DETAIL_G8_C4_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C8_FULL)) == TUI_DETAIL_G8_C8_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C8NBG_FULL)) == TUI_DETAIL_G8_C8NBG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C8NFG_FULL)) == TUI_DETAIL_G8_C8NFG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C24_FULL)) == TUI_DETAIL_G8_C24_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C24NBG_FULL)) == TUI_DETAIL_G8_C24NBG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C24NFG_FULL)) == TUI_DETAIL_G8_C24NFG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C32_FULL)) == TUI_DETAIL_G8_C32_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C32NBG_FULL)) == TUI_DETAIL_G8_C32NBG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C32NFG_FULL)) == TUI_DETAIL_G8_C32NFG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C0_FULL)) == TUI_DETAIL_G16_C0_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C4_FULL)) == TUI_DETAIL_G16_C4_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C8_FULL)) == TUI_DETAIL_G16_C8_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C8NBG_FULL)) == TUI_DETAIL_G16_C8NBG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C8NFG_FULL)) == TUI_DETAIL_G16_C8NFG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C24_FULL)) == TUI_DETAIL_G16_C24_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C24NBG_FULL)) == TUI_DETAIL_G16_C24NBG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C24NFG_FULL)) == TUI_DETAIL_G16_C24NFG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C32_FULL)) == TUI_DETAIL_G16_C32_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C32NBG_FULL)) == TUI_DETAIL_G16_C32NBG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C32NFG_FULL)) == TUI_DETAIL_G16_C32NFG_FULL);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C0_SPARSE)) == TUI_DETAIL_G8_C0_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C4_SPARSE)) == TUI_DETAIL_G8_C4_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C8_SPARSE)) == TUI_DETAIL_G8_C8_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C8NBG_SPARSE)) == TUI_DETAIL_G8_C8NBG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C8NFG_SPARSE)) == TUI_DETAIL_G8_C8NFG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C24_SPARSE)) == TUI_DETAIL_G8_C24_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C24NBG_SPARSE)) == TUI_DETAIL_G8_C24NBG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C24NFG_SPARSE)) == TUI_DETAIL_G8_C24NFG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C32_SPARSE)) == TUI_DETAIL_G8_C32_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C32NBG_SPARSE)) == TUI_DETAIL_G8_C32NBG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G8_C32NFG_SPARSE)) == TUI_DETAIL_G8_C32NFG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C0_SPARSE)) == TUI_DETAIL_G16_C0_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C4_SPARSE)) == TUI_DETAIL_G16_C4_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C8_SPARSE)) == TUI_DETAIL_G16_C8_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C8NBG_SPARSE)) == TUI_DETAIL_G16_C8NBG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C8NFG_SPARSE)) == TUI_DETAIL_G16_C8NFG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C24_SPARSE)) == TUI_DETAIL_G16_C24_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C24NBG_SPARSE)) == TUI_DETAIL_G16_C24NBG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C24NFG_SPARSE)) == TUI_DETAIL_G16_C24NFG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C32_SPARSE)) == TUI_DETAIL_G16_C32_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C32NBG_SPARSE)) == TUI_DETAIL_G16_C32NBG_SPARSE);
    REQUIRE(tuiStringToDetailMode(TO_STRING(TUI_DETAIL_G16_C32NFG_SPARSE)) == TUI_DETAIL_G16_C32NFG_SPARSE);
}

TEST_CASE("tuiDetailGetGlyphFlag") {
    REQUIRE(tuiDetailGetGlyphFlag(TUI_DETAIL_G8_C0_FULL) == TUI_GLYPH_FLAG_G8);
    REQUIRE(tuiDetailGetGlyphFlag(TUI_DETAIL_G16_C0_FULL) == TUI_GLYPH_FLAG_G16);
}

TEST_CASE("tuiDetailGetColorFlag") {
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C0_FULL) == TUI_COLOR_FLAG_C0);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C4_FULL) == TUI_COLOR_FLAG_C4);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C8_FULL) == TUI_COLOR_FLAG_C8);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C8NBG_FULL) == TUI_COLOR_FLAG_C8NBG);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C8NFG_FULL) == TUI_COLOR_FLAG_C8NFG);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C24_FULL) == TUI_COLOR_FLAG_C24);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C24NBG_FULL) == TUI_COLOR_FLAG_C24NBG);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C24NFG_FULL) == TUI_COLOR_FLAG_C24NFG);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C32_FULL) == TUI_COLOR_FLAG_C32);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C32NBG_FULL) == TUI_COLOR_FLAG_C32NBG);
    REQUIRE(tuiDetailGetColorFlag(TUI_DETAIL_G8_C32NFG_FULL) == TUI_COLOR_FLAG_C32NFG);
}

TEST_CASE("tuiDetailGetLayoutFlag") {
    REQUIRE(tuiDetailGetLayoutFlag(TUI_DETAIL_G8_C0_FULL) == TUI_LAYOUT_FLAG_FULL);
    REQUIRE(tuiDetailGetLayoutFlag(TUI_DETAIL_G8_C0_SPARSE) == TUI_LAYOUT_FLAG_SPARSE);
}

TEST_CASE("tuiDetailModeIsValid") {
    SECTION("Detail modes should all return true") {
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C0_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C4_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C8_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C8NBG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C8NFG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C24_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C24NBG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C24NFG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C32_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C32NBG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C32NFG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C0_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C4_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C8_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C8NBG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C8NFG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C24_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C24NBG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C24NFG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C32_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C32NBG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C32NFG_FULL) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C0_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C4_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C8_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C8NBG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C8NFG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C24_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C24NBG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C24NFG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C32_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C32NBG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G8_C32NFG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C0_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C4_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C8_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C8NBG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C8NFG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C24_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C24NBG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C24NFG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C32_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C32NBG_SPARSE) == TUI_TRUE);
        REQUIRE(tuiDetailIsValid(TUI_DETAIL_G16_C32NFG_SPARSE) == TUI_TRUE);
    }
    SECTION("Solo flags should return false.") {
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_GLYPH_FLAG_G8) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_GLYPH_FLAG_G16) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C0) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C4) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C8) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C8NBG) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C8NFG) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C24) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C24NBG) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C24NFG) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C32) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C32NBG) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_COLOR_FLAG_C32NFG) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_LAYOUT_FLAG_FULL) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)TUI_LAYOUT_FLAG_SPARSE) == TUI_FALSE);
    }
    SECTION("Too many flags of one type should return false.") {
        REQUIRE(tuiDetailIsValid((TuiDetailMode)(TUI_DETAIL_G16_C32NFG_SPARSE | TUI_LAYOUT_FLAG_FULL)) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)(TUI_DETAIL_G16_C32NFG_SPARSE | TUI_COLOR_FLAG_C0)) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)(TUI_DETAIL_G16_C32NFG_SPARSE | TUI_GLYPH_FLAG_G8)) == TUI_FALSE);
    }
    SECTION("Flags of only to kinds should return false.") {
        REQUIRE(tuiDetailIsValid((TuiDetailMode)(TUI_COLOR_FLAG_C0 | TUI_GLYPH_FLAG_G8)) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)(TUI_COLOR_FLAG_C0 | TUI_LAYOUT_FLAG_SPARSE)) == TUI_FALSE);
        REQUIRE(tuiDetailIsValid((TuiDetailMode)(TUI_LAYOUT_FLAG_SPARSE | TUI_GLYPH_FLAG_G8)) == TUI_FALSE);
    }
}