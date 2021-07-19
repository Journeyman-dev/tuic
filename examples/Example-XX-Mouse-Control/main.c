
#include <TUIC/tuic.h>

#include <stdio.h>

void TuiMessageCallback(TuiErrorCode error_code, const char* msg)
{
    if (error_code == TUI_ERROR_GRAPHICS_BACKEND_SPECIFIC)
    {
        printf("%s : %s backend message: %s\n", tuiErrorCodeToString(error_code), tuiErrorCodeGetDescription(error_code), msg);
    }
    else
    {
        printf("%s : %s location: %s\n", tuiErrorCodeToString(error_code), tuiErrorCodeGetDescription(error_code), msg);
    }
}

const size_t kTilesWide = 50;
const size_t kTilesTall = 50;
const size_t kTilePixelWidth = 8;
const size_t kTilePixelHeight = 8;

static TuiImage custom_cursor_image = NULL;
static TuiCursorShape current_cursor_shape = TUI_CURSOR_SHAPE_FIRST;
static TuiCursor current_cursor = NULL;
static int foreground_color = 15;

TuiCursorShape increment_cursor_shape(TuiCursorShape current_shape)
{
    if (current_shape != 0 && current_shape < TUI_CURSOR_SHAPE_LAST)
    {
        current_shape = current_shape +  1;
    }
    else if (current_shape == TUI_CURSOR_SHAPE_LAST)
    {
        return 0;
    }
    else if (current_shape == 0)
    {
        current_shape = TUI_CURSOR_SHAPE_FIRST;
    }
    if (tuiCursorShapeIsSupported(current_shape) == TUI_FALSE)
    {
        return increment_cursor_shape(current_shape);
    }
    else
    {
        return current_shape;
    }
}

uint8_t increment_foreground_color(uint8_t foreground_color)
{
    foreground_color++;
    if (foreground_color == 16)
    {
        foreground_color = 0;
    }
    return foreground_color;
}

void key_callback(TuiWindow window, TuiKeyboardKey key, int scancode, TuiButtonState button_state, TuiKeyboardKeyMod key_mod)
{
    if (key == TUIK_C && button_state == TUI_BUTTON_PRESS)
    {
        current_cursor_shape = increment_cursor_shape(current_cursor_shape);
        if (current_cursor_shape == 0)
        {
            TuiCursor next_cursor = tuiCursorCreate(custom_cursor_image, 8, 8);
            tuiWindowSetCursor(window, next_cursor);
            tuiCursorDestroy(current_cursor);
            current_cursor = next_cursor;
        }
        else
        {
            TuiCursor next_cursor = tuiCursorCreateStandard(current_cursor_shape);
            tuiWindowSetCursor(window, next_cursor);
            tuiCursorDestroy(current_cursor);
            current_cursor = next_cursor;
        }
        printf("Cursor changed to %s.\n", (current_cursor_shape == 0) ? "custom" : tuiCursorShapeToString(current_cursor_shape));
    }
    if (key == TUIK_S && button_state == TUI_BUTTON_PRESS)
    {
        TuiImage screenshot = tuiWindowGetImage(window);
        const char* screenshot_file_name = "mouse_control_screenshot.png";
        tuiImageSave(screenshot, screenshot_file_name);
        printf("Screenshot saved to \"mouse_control_screenshot.png\".\n");
        tuiImageDestroy(screenshot);
        screenshot = NULL;
    }
}

void mouse_button_callback(TuiWindow window, TuiMouseButton mouse_button, TuiButtonState button_state, TuiKeyboardKeyMod key_mod)
{
    //checking the button state in a callback only gets checked when the state changes. This is different than the render loop (see bellow).
    if (mouse_button == TUI_MOUSE_BUTTON_RIGHT && button_state == TUI_BUTTON_PRESS)
    {
        foreground_color = increment_foreground_color(foreground_color);
        printf("Paint color changed to %d.\n", foreground_color);
    }
}


int main()
{
    int window_width = kTilesWide * kTilePixelWidth;
    int window_height = kTilesTall * kTilePixelHeight;

    /* Initialize TUIC. */
    TuiBoolean multi_window = TUI_FALSE;
    TuiBoolean initialization_successful = tuiInit(multi_window);
    if (initialization_successful == TUI_FALSE)
    {
        printf("Failed to initialize TUIC.");
        return -1;
    }

    /* Tell TUIC to send all debug messages to our message callback (the function we implemented above main). */
    tuiSetDebugErrorCallback(TuiMessageCallback);

    /* Load the custom cursor image. */
    int expected_channel_count = 4;
    custom_cursor_image  = tuiImageLoad("custom_cursor.png", expected_channel_count);

    /* Initialize the current cursor. */
    current_cursor = tuiCursorCreateStandard(current_cursor_shape);

    /* Load the atlas image */
    const char* atlas_image_name = "cp_8x8_rgb_fg_green.png";
    int atlas_image_expected_channel_count = 3;
    TuiImage atlas_image = tuiImageLoad(atlas_image_name, atlas_image_expected_channel_count);
    if (atlas_image == NULL)
    {
        printf("Issue loading image file. Make sure that it was moved from the content folder to a location the executable can read. You need to do this manually.\n");
        tuiTerminate();
        return -1;
    }

    /* Create the Glyph Atlas */
    TuiBlendMode blend_mode = TUI_BLEND_FG_GREEN;
    TuiAtlas atlas = tuiAtlasCreateCodepageGrid(atlas_image, blend_mode);
    tuiImageDestroy(atlas_image);
    atlas_image = NULL;

    /* Create the palette */
    int palette_color_count = 16;
    TuiPalette palette = tuiPaletteCreateXterm(palette_color_count);

    /* Create the batch */
    TuiDetailMode detail_mode = TUI_DETAIL_G8_C4_SPARSE;
    TuiBatch batch = tuiBatchCreate(detail_mode, kTilesTall, kTilesWide);

    /* Create the window. */
    const char* window_title = "Example XX";
    TuiWindow window = tuiWindowCreate(window_width, window_height, window_title, NULL);

    /* Render initial clear color to window. */
    tuiWindowClearColor(window, 0, 0, 0, 255); //black

    /* Set the window callbacks. */
    tuiWindowSetKeyboardKeyCallback(window, key_callback);
    tuiWindowSetMouseButtonCallback(window, mouse_button_callback);

    /* Print prompt to console. */
    printf("Press C to change mouse cursors. Left click and drag to paint tiles. Right click to change the paint color. Press S to save a screenshot.\n");

    //Render loop
    while (tuiWindowShouldClose(window) == TUI_FALSE)
    {
        tuiPollEvents(); //handle input events and call callback function.
       
        //checking state in the loop will get the state when the button is held down. This is different then mouse_button_callback (see above).
        TuiButtonState left_mouse_state = tuiWindowGetMouseButton(window, TUI_MOUSE_BUTTON_LEFT);

        if (left_mouse_state == TUI_BUTTON_PRESS)
        {
            double mouse_x = tuiWindowGetCursorXPosition(window);
            double mouse_y = tuiWindowGetCursorYPosition(window);
            int tile_x = (int)mouse_x / (kTilePixelWidth);
            int tile_y = (int)mouse_y / (kTilePixelHeight);
            uint8_t background_color = 0;
            uint8_t glyph = 255;
            uint8_t colors_byte = tuiClassicColorCombine(foreground_color, background_color);
            tuiBatchSetTile_G8_C4_SPARSE(batch, tile_x, tile_y, glyph, colors_byte);
            tuiWindowDrawBatch(window, atlas, palette, batch);
            
        }

        tuiWindowFrameBuffers(window); //swap the window buffers
        }


    /* Destroy all remaining TUIC objects */
    tuiWindowDestroy(window);
    window = NULL;
    tuiCursorDestroy(current_cursor);
    current_cursor = NULL;
    tuiPaletteDestroy(palette);
    palette = NULL;
    tuiAtlasDestroy(atlas);
    atlas = NULL;
    tuiBatchDestroy(batch);
    batch = NULL;

    tuiTerminate();
    return 0;
}
