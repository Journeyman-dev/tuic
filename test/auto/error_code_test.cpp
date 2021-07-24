#include <TUIC/tuic.h>
#include <string>
#include <catch2/catch.hpp>
#define TO_STRING(value) #value

TEST_CASE("tuiErrorCodeToString") {
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_UNKNOWN)) == std::string(TO_STRING(TUI_ERROR_UNKNOWN)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NONE)) == std::string(TO_STRING(TUI_ERROR_NONE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_ALREADY_INITIALIZED)) == std::string(TO_STRING(TUI_ERROR_ALREADY_INITIALIZED)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC)) == std::string(TO_STRING(TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_DANGLING_ATLAS)) == std::string(TO_STRING(TUI_ERROR_DANGLING_ATLAS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_DANGLING_CURSOR)) == std::string(TO_STRING(TUI_ERROR_DANGLING_CURSOR)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_DANGLING_PALETTE)) == std::string(TO_STRING(TUI_ERROR_DANGLING_PALETTE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_DANGLING_PANEL)) == std::string(TO_STRING(TUI_ERROR_DANGLING_PANEL)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_DANGLING_TEXTURE)) == std::string(TO_STRING(TUI_ERROR_DANGLING_TEXTURE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_DANGLING_WINDOW)) == std::string(TO_STRING(TUI_ERROR_DANGLING_WINDOW)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_ENUM)) == std::string(TO_STRING(TUI_ERROR_GLFW_ENUM)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_FORMAT_UNAVAILABLE)) == std::string(TO_STRING(TUI_ERROR_GLFW_FORMAT_UNAVAILABLE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_INVALID_VERSION)) == std::string(TO_STRING(TUI_ERROR_GLFW_INVALID_VERSION)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_NO_GRAPHICS_CONTEXT)) == std::string(TO_STRING(TUI_ERROR_GLFW_NO_GRAPHICS_CONTEXT)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_NOT_INITIALIZED)) == std::string(TO_STRING(TUI_ERROR_GLFW_NOT_INITIALIZED)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_OUT_OF_MEMORY)) == std::string(TO_STRING(TUI_ERROR_GLFW_OUT_OF_MEMORY)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_PLATFORM)) == std::string(TO_STRING(TUI_ERROR_GLFW_PLATFORM)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_WINDOW_CREATION_FAILED)) == std::string(TO_STRING(TUI_ERROR_GLFW_WINDOW_CREATION_FAILED)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_GLFW_VALUE)) == std::string(TO_STRING(TUI_ERROR_GLFW_VALUE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INCOMPATIBLE_BLEND_MODE)) == std::string(TO_STRING(TUI_ERROR_INCOMPATIBLE_BLEND_MODE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INCOMPATIBLE_IMAGES)) == std::string(TO_STRING(TUI_ERROR_INCOMPATIBLE_IMAGES)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_ASPECT_RATIO)) == std::string(TO_STRING(TUI_ERROR_INVALID_ASPECT_RATIO)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_ATLAS_TYPE)) == std::string(TO_STRING(TUI_ERROR_INVALID_ATLAS_TYPE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_BATCH_DATA_DIMENSIONS)) == std::string(TO_STRING(TUI_ERROR_INVALID_BATCH_DATA_DIMENSIONS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_BATCH_DIMENSIONS)) == std::string(TO_STRING(TUI_ERROR_INVALID_BATCH_DIMENSIONS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_BATCH_SETTER)) == std::string(TO_STRING(TUI_ERROR_INVALID_BATCH_SETTER)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_BLEND_MODE)) == std::string(TO_STRING(TUI_ERROR_INVALID_BLEND_MODE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_BUTTON_STATE)) == std::string(TO_STRING(TUI_ERROR_INVALID_BUTTON_STATE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_CHANNEL_COUNT)) == std::string(TO_STRING(TUI_ERROR_INVALID_CHANNEL_COUNT)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS)) == std::string(TO_STRING(TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_CURSOR_MODE)) == std::string(TO_STRING(TUI_ERROR_INVALID_CURSOR_MODE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_CURSOR_SHAPE)) == std::string(TO_STRING(TUI_ERROR_INVALID_CURSOR_SHAPE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_DETAIL_FLAG)) == std::string(TO_STRING(TUI_ERROR_INVALID_DETAIL_FLAG)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_DETAIL_MODE)) == std::string(TO_STRING(TUI_ERROR_INVALID_DETAIL_MODE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_FILTER_MODE)) == std::string(TO_STRING(TUI_ERROR_INVALID_FILTER_MODE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_GLYPH_COUNT)) == std::string(TO_STRING(TUI_ERROR_INVALID_GLYPH_COUNT)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_GLYPH_DIMENSIONS)) == std::string(TO_STRING(TUI_ERROR_INVALID_GLYPH_DIMENSIONS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_IMAGE_DIMENSIONS)) == std::string(TO_STRING(TUI_ERROR_INVALID_IMAGE_DIMENSIONS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_KEYBOARD_KEY)) == std::string(TO_STRING(TUI_ERROR_INVALID_KEYBOARD_KEY)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_KEYBOARD_MOD)) == std::string(TO_STRING(TUI_ERROR_INVALID_KEYBOARD_MOD)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_MOUSE_BUTTON)) == std::string(TO_STRING(TUI_ERROR_INVALID_MOUSE_BUTTON)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_PALETTE_COLOR_COUNT)) == std::string(TO_STRING(TUI_ERROR_INVALID_PALETTE_COLOR_COUNT)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_PANEL_DIMENSIONS)) == std::string(TO_STRING(TUI_ERROR_INVALID_PANEL_DIMENSIONS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_PIXEL_DIMENSIONS)) == std::string(TO_STRING(TUI_ERROR_INVALID_PIXEL_DIMENSIONS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_TIME)) == std::string(TO_STRING(TUI_ERROR_INVALID_TIME)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_WINDOW_COUNT)) == std::string(TO_STRING(TUI_ERROR_INVALID_WINDOW_COUNT)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_WINDOW_DIMENSIONS)) == std::string(TO_STRING(TUI_ERROR_INVALID_WINDOW_DIMENSIONS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS)) == std::string(TO_STRING(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_LOAD_IMAGE_FAILURE)) == std::string(TO_STRING(TUI_ERROR_LOAD_IMAGE_FAILURE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NOT_INITIALIZED)) == std::string(TO_STRING(TUI_ERROR_NOT_INITIALIZED)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_ATLAS)) == std::string(TO_STRING(TUI_ERROR_NULL_ATLAS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_BATCH)) == std::string(TO_STRING(TUI_ERROR_NULL_BATCH)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_BATCH_DATA)) == std::string(TO_STRING(TUI_ERROR_NULL_BATCH_DATA)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_COLORS)) == std::string(TO_STRING(TUI_ERROR_NULL_COLORS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_CURSOR)) == std::string(TO_STRING(TUI_ERROR_NULL_CURSOR)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES)) == std::string(TO_STRING(TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_IMAGE)) == std::string(TO_STRING(TUI_ERROR_NULL_IMAGE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_MONITOR)) == std::string(TO_STRING(TUI_ERROR_NULL_MONITOR)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_PALETTE)) == std::string(TO_STRING(TUI_ERROR_NULL_PALETTE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_PANEL)) == std::string(TO_STRING(TUI_ERROR_NULL_PANEL)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_PATH)) == std::string(TO_STRING(TUI_ERROR_NULL_PATH)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_PIXELS)) == std::string(TO_STRING(TUI_ERROR_NULL_PIXELS)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_STRING)) == std::string(TO_STRING(TUI_ERROR_NULL_STRING)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_SUBJECT_PANEL)) == std::string(TO_STRING(TUI_ERROR_NULL_SUBJECT_PANEL)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_SUBJECT_WINDOW)) == std::string(TO_STRING(TUI_ERROR_NULL_SUBJECT_WINDOW)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_TARGET_IMAGE)) == std::string(TO_STRING(TUI_ERROR_NULL_TARGET_IMAGE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_TEXTURE)) == std::string(TO_STRING(TUI_ERROR_NULL_TEXTURE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_TEXTURE_COORDINATES)) == std::string(TO_STRING(TUI_ERROR_NULL_TEXTURE_COORDINATES)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_NULL_WINDOW)) == std::string(TO_STRING(TUI_ERROR_NULL_WINDOW)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_PALETTE_REQUIRED)) == std::string(TO_STRING(TUI_ERROR_PALETTE_REQUIRED)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_RESIZE_IMAGE_FAILURE)) == std::string(TO_STRING(TUI_ERROR_RESIZE_IMAGE_FAILURE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_UNAVAILABLE_GRAPHICS_API)) == std::string(TO_STRING(TUI_ERROR_UNAVAILABLE_GRAPHICS_API)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION)) == std::string(TO_STRING(TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE)) == std::string(TO_STRING(TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION)) == std::string(TO_STRING(TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION)));
    REQUIRE(std::string(tuiErrorCodeToString(TUI_ERROR_UNSUPPORTED_WINDOW_ICONS)) == std::string(TO_STRING(TUI_ERROR_UNSUPPORTED_WINDOW_ICONS)));
}

TEST_CASE("tuiStringToErrorCode") {
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_UNKNOWN)) == TUI_ERROR_UNKNOWN);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NONE)) == TUI_ERROR_NONE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_ALREADY_INITIALIZED)) == TUI_ERROR_ALREADY_INITIALIZED);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC)) == TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_DANGLING_ATLAS)) == TUI_ERROR_DANGLING_ATLAS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_DANGLING_CURSOR)) == TUI_ERROR_DANGLING_CURSOR);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_DANGLING_PALETTE)) == TUI_ERROR_DANGLING_PALETTE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_DANGLING_PANEL)) == TUI_ERROR_DANGLING_PANEL);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_DANGLING_TEXTURE)) == TUI_ERROR_DANGLING_TEXTURE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_DANGLING_WINDOW)) == TUI_ERROR_DANGLING_WINDOW);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_ENUM)) == TUI_ERROR_GLFW_ENUM);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_FORMAT_UNAVAILABLE)) == TUI_ERROR_GLFW_FORMAT_UNAVAILABLE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_INVALID_VERSION)) == TUI_ERROR_GLFW_INVALID_VERSION);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_NO_GRAPHICS_CONTEXT)) == TUI_ERROR_GLFW_NO_GRAPHICS_CONTEXT);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_NOT_INITIALIZED)) == TUI_ERROR_GLFW_NOT_INITIALIZED);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_OUT_OF_MEMORY)) == TUI_ERROR_GLFW_OUT_OF_MEMORY);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_PLATFORM)) == TUI_ERROR_GLFW_PLATFORM);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_WINDOW_CREATION_FAILED)) == TUI_ERROR_GLFW_WINDOW_CREATION_FAILED);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_GLFW_VALUE)) == TUI_ERROR_GLFW_VALUE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INCOMPATIBLE_BLEND_MODE)) == TUI_ERROR_INCOMPATIBLE_BLEND_MODE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INCOMPATIBLE_IMAGES)) == TUI_ERROR_INCOMPATIBLE_IMAGES);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_ASPECT_RATIO)) == TUI_ERROR_INVALID_ASPECT_RATIO);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_ATLAS_TYPE)) == TUI_ERROR_INVALID_ATLAS_TYPE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_BATCH_DATA_DIMENSIONS)) == TUI_ERROR_INVALID_BATCH_DATA_DIMENSIONS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_BATCH_DIMENSIONS)) == TUI_ERROR_INVALID_BATCH_DIMENSIONS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_BATCH_SETTER)) == TUI_ERROR_INVALID_BATCH_SETTER);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_BLEND_MODE)) == TUI_ERROR_INVALID_BLEND_MODE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_BUTTON_STATE)) == TUI_ERROR_INVALID_BUTTON_STATE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_CHANNEL_COUNT)) == TUI_ERROR_INVALID_CHANNEL_COUNT);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS)) == TUI_ERROR_INVALID_CODEPAGE_DIMENSIONS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_CURSOR_MODE)) == TUI_ERROR_INVALID_CURSOR_MODE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_CURSOR_SHAPE)) == TUI_ERROR_INVALID_CURSOR_SHAPE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_DETAIL_FLAG)) == TUI_ERROR_INVALID_DETAIL_FLAG);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_DETAIL_MODE)) == TUI_ERROR_INVALID_DETAIL_MODE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_FILTER_MODE)) == TUI_ERROR_INVALID_FILTER_MODE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_GLYPH_COUNT)) == TUI_ERROR_INVALID_GLYPH_COUNT);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_GLYPH_DIMENSIONS)) == TUI_ERROR_INVALID_GLYPH_DIMENSIONS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_IMAGE_DIMENSIONS)) == TUI_ERROR_INVALID_IMAGE_DIMENSIONS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_KEYBOARD_KEY)) == TUI_ERROR_INVALID_KEYBOARD_KEY);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_KEYBOARD_MOD)) == TUI_ERROR_INVALID_KEYBOARD_MOD);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_MOUSE_BUTTON)) == TUI_ERROR_INVALID_MOUSE_BUTTON);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_PALETTE_COLOR_COUNT)) == TUI_ERROR_INVALID_PALETTE_COLOR_COUNT);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_PANEL_DIMENSIONS)) == TUI_ERROR_INVALID_PANEL_DIMENSIONS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_PIXEL_DIMENSIONS)) == TUI_ERROR_INVALID_PIXEL_DIMENSIONS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_TIME)) == TUI_ERROR_INVALID_TIME);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_WINDOW_COUNT)) == TUI_ERROR_INVALID_WINDOW_COUNT);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_WINDOW_DIMENSIONS)) == TUI_ERROR_INVALID_WINDOW_DIMENSIONS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS)) == TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_LOAD_IMAGE_FAILURE)) == TUI_ERROR_LOAD_IMAGE_FAILURE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NOT_INITIALIZED)) == TUI_ERROR_NOT_INITIALIZED);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_ATLAS)) == TUI_ERROR_NULL_ATLAS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_BATCH)) == TUI_ERROR_NULL_BATCH);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_BATCH_DATA)) == TUI_ERROR_NULL_BATCH_DATA);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_COLORS)) == TUI_ERROR_NULL_COLORS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_CURSOR)) == TUI_ERROR_NULL_CURSOR);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES)) == TUI_ERROR_NULL_GLYPH_BOUNDING_BOXES);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_IMAGE)) == TUI_ERROR_NULL_IMAGE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_MONITOR)) == TUI_ERROR_NULL_MONITOR);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_PALETTE)) == TUI_ERROR_NULL_PALETTE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_PANEL)) == TUI_ERROR_NULL_PANEL);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_PATH)) == TUI_ERROR_NULL_PATH);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_PIXELS)) == TUI_ERROR_NULL_PIXELS);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_STRING)) == TUI_ERROR_NULL_STRING);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_SUBJECT_PANEL)) == TUI_ERROR_NULL_SUBJECT_PANEL);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_SUBJECT_WINDOW)) == TUI_ERROR_NULL_SUBJECT_WINDOW);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_TARGET_IMAGE)) == TUI_ERROR_NULL_TARGET_IMAGE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_TEXTURE)) == TUI_ERROR_NULL_TEXTURE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_TEXTURE_COORDINATES)) == TUI_ERROR_NULL_TEXTURE_COORDINATES);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_NULL_WINDOW)) == TUI_ERROR_NULL_WINDOW);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_PALETTE_REQUIRED)) == TUI_ERROR_PALETTE_REQUIRED);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_RESIZE_IMAGE_FAILURE)) == TUI_ERROR_RESIZE_IMAGE_FAILURE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_UNAVAILABLE_GRAPHICS_API)) == TUI_ERROR_UNAVAILABLE_GRAPHICS_API);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION)) == TUI_ERROR_UNAVAILABLE_GRAPHICS_API_VERSION);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE)) == TUI_ERROR_UNSUPPORTED_CURSOR_SHAPE);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION)) == TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION);
    REQUIRE(tuiStringToErrorCode(TO_STRING(TUI_ERROR_UNSUPPORTED_WINDOW_ICONS)) == TUI_ERROR_UNSUPPORTED_WINDOW_ICONS);
}
