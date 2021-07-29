#include <TUIC/tuic.h>
#include "objects.h"
#include <GLFW/glfw3.h>
#include "opengl33.h"
#include "glfw_error_check.h"
#include "image_inline.h"

static int mini(int x, int y)
{
	return x < y ? x : y;
}

static int maxi(int x, int y)
{
	return x > y ? x : y;
}

//taken from https://stackoverflow.com/a/31526753
static inline TuiMonitor _GetCurrentMonitor(GLFWwindow* window)
{
	GLFWmonitor* monitor = glfwGetWindowMonitor(window);
	if (monitor != NULL)
	{
		return (TuiMonitor)monitor;
	}

	int nmonitors, i;
	int wx, wy, ww, wh;
	int mx, my, mw, mh;
	int overlap, bestoverlap;

	GLFWmonitor** monitors;
	const GLFWvidmode* mode;

	bestoverlap = 0;

	glfwGetWindowPos(window, &wx, &wy);
	glfwGetWindowSize(window, &ww, &wh);
	monitors = glfwGetMonitors(&nmonitors);

	for (i = 0; i < nmonitors; i++) {
		mode = glfwGetVideoMode(monitors[i]);
		glfwGetMonitorPos(monitors[i], &mx, &my);
		mw = mode->width;
		mh = mode->height;

		overlap =
			maxi(0, mini(wx + ww, mx + mw) - maxi(wx, mx)) *
			maxi(0, mini(wy + wh, my + mh) - maxi(wy, my));

		if (bestoverlap < overlap) {
			bestoverlap = overlap;
			monitor = monitors[i];
		}
	}
	return (TuiMonitor)monitor;
}

static inline int _GCF(int n, int m) //returns the greatest common factor of the two values
{
	int gcf, remainder;

	while (n != 0)
	{
		remainder = m % n;
		m = n;
		n = remainder;
	}

	gcf = m;

	return gcf;
}

static inline TuiBoolean _WindowHasSizeLimits(TuiWindow window)
{
	return window->MinWidth != 0 && window->MinHeight != 0 && window->MaxWidth != 0 && window->MaxHeight != 0;
}

static inline void _WindowUpdateSizeLimits(TuiWindow window)
{
	glfwSetWindowSizeLimits(window->GlfwWindow, window->MinWidth, window->MinHeight, (window->MaxWidth == 0) ? GLFW_DONT_CARE : window->MaxWidth, (window->MaxHeight == 0) ? GLFW_DONT_CARE : window->MaxHeight);
}

static void glfwWindowPosCallback(GLFWwindow* glfw_window, int xpos, int ypos)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowMoveCallback(window, xpos, ypos);
}

static void glfwWindowCloseCallback(GLFWwindow* glfw_window)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowCloseCallback(window);
}

static void glfwWindowFocusCallback(GLFWwindow* glfw_window, int focused)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowFocusCallback(window, (TuiBoolean)focused);
}

static void glfwWindowIconifyCallback(GLFWwindow* glfw_window, int iconified)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowIconifyCallback(window, (TuiBoolean)iconified);
}

static void glfwWindowMaximizeCallback(GLFWwindow* glfw_window, int maximized)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowMaximizeCallback(window, (TuiBoolean)maximized);
}

static void glfwWindowFramebufferSizeCallback(GLFWwindow* glfw_window, int pixel_width, int pixel_height)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	if (
		(window->IsFullscreen == TUI_FALSE && glfwGetWindowAttrib(glfw_window, GLFW_RESIZABLE) == GLFW_TRUE) ||
		(window->ViewportPixelWidth == pixel_width && window->ViewportPixelHeight == pixel_height)
		) //this condition is to fix a weird GLFW issue where invalid sizes sometimes get passed into this callback. seems to happen especially when transitioning between windowed and fullscreen.
	{
		if (window->FramebufferMatchViewportSize == TUI_TRUE)
		{
			tuiWindowSetSize_Opengl33(window, pixel_width, pixel_height);
		}
		window->ViewportPixelWidth = pixel_width;
		window->ViewportPixelHeight = pixel_height;
		if (window->WindowResizeCallback != NULL)
		{
			window->WindowResizeCallback(window, pixel_width, pixel_height);
		}
	}
}

static void glfwWindowContentScaleCallback(GLFWwindow* glfw_window, float scale_wide, float scale_tall)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->WindowContentScaleCallback(window, scale_wide, scale_tall);
}

static void glfwKeyCallback(GLFWwindow* glfw_window, int key, int scancode, int button_state, int mod)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->KeyboardKeyCallback(window, (TuiKeyboardKey)key, scancode, (TuiButtonState)button_state, (TuiKeyboardMod)mod);
}

static void glfwCharCallback(GLFWwindow* glfw_window, unsigned int charcode)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->CharCallback(window, charcode);
}

static void glfwMouseButtonCallback(GLFWwindow* glfw_window, int mouse_button, int button_state, int mod)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->MouseButtonCallback(window, (TuiMouseButton)mouse_button, (TuiButtonState)button_state, (TuiKeyboardMod)mod);
}

static void glfwCursorMoveCallback(GLFWwindow* glfw_window, double xpos, double ypos)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->CursorMoveCallback(window, xpos, ypos);
}

static void glfwCursorEnterCallback(GLFWwindow* glfw_window, int entered)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->CursorEnterCallback(window, (TuiBoolean)entered);
}

static void glfwScrollCallback(GLFWwindow* glfw_window, double xscroll, double yscroll)
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->MouseScrollCallback(window, xscroll, yscroll);
}

static void glfwDropCallback(GLFWwindow* glfw_window, int path_count, const char* paths[])
{
	TuiWindow window = (TuiWindow)glfwGetWindowUserPointer(glfw_window);
	window->FileDropCallback(window, path_count, paths);
}

static size_t sWindowCount = 0;

TuiWindow tuiWindowCreate(int framebuffer_pixel_width, int framebuffer_pixel_height, const char* title, TuiWindowCreateInfo* create_info)
{
	TuiSystem system = tui_get_system();
	if (system == NULL)
	{
		tuiDebugError(TUI_ERROR_NOT_INITIALIZED, __func__);
		return NULL;
	}
	if (framebuffer_pixel_width <= 0 || framebuffer_pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS, __func__);
		return NULL;
	}
	if (create_info != NULL && create_info->framebuffer_match_viewport_size == TUI_FALSE && (create_info->unmatching_viewport_pixel_width <= 0 || create_info->umnatching_viewport_pixel_height <= 0))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS, __func__);
		return NULL;
	}

	if (title == NULL)
	{
		title = "";
	}

	TuiBoolean is_fullscreen = TUI_FALSE;
	TuiBoolean framebuffer_matches_viewport_size = TUI_TRUE;
	int window_width = framebuffer_pixel_width;
	int window_height = framebuffer_pixel_height;

	GLFWwindow* glfw_window = NULL;

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	int glfw_error = _GlfwErrorCheck(); //catch api version or api unavailable errors
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}

	if (create_info != NULL)
	{
		glfwWindowHint(GLFW_RESIZABLE, create_info->resizable);
		glfwWindowHint(GLFW_VISIBLE, create_info->visible);
		glfwWindowHint(GLFW_DECORATED, create_info->decorated);
		glfwWindowHint(GLFW_FOCUSED, create_info->focused);
		glfwWindowHint(GLFW_AUTO_ICONIFY, create_info->auto_iconify);
		glfwWindowHint(GLFW_FLOATING, create_info->topmost);
		glfwWindowHint(GLFW_MAXIMIZED, create_info->maximized);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, create_info->focus_on_show);

		TuiMonitor window_monitor = NULL;
		if (create_info->fullscreen == TUI_TRUE)
		{
			is_fullscreen = TUI_TRUE;
			if (create_info->monitor == NULL)
			{
				window_monitor = glfwGetPrimaryMonitor();
			}
			else
			{
				window_monitor = create_info->monitor;
			}
		}

		if (create_info->framebuffer_match_viewport_size == TUI_FALSE)
		{
			framebuffer_matches_viewport_size = create_info->framebuffer_match_viewport_size;
			window_width = create_info->unmatching_viewport_pixel_width;
			window_height = create_info->umnatching_viewport_pixel_height;
		}
		if (create_info->fullscreen == TUI_TRUE)
		{
			const GLFWvidmode* vid_mode = glfwGetVideoMode(window_monitor);
			window_width = vid_mode->width;
			window_height = vid_mode->height;
		}
	}
	else
	{
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
		glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
		glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
	}

	glfw_error = _GlfwErrorCheck(); //window hint errors
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
	}

	glfw_window = glfwCreateWindow(window_width, window_height, title, NULL, system->BaseWindow);

	if (glfw_window == NULL) //catch window creation errors
	{
		glfw_error = _GlfwErrorCheck();
		if (glfw_error != TUI_ERROR_NONE)
		{
			tuiDebugError(glfw_error, __func__);
		}
		else
		{
			tuiDebugError(TUI_ERROR_UNKNOWN, __func__);
		}
		return NULL;
	}

	if (create_info != NULL && create_info->fullscreen == TUI_FALSE && create_info->custom_window_position == TUI_TRUE)
	{
		glfwSetWindowPos(glfw_window, create_info->windowed_x_position, create_info->windowed_y_position);
	}

	glfwSetFramebufferSizeCallback(glfw_window, glfwWindowFramebufferSizeCallback);

	glfw_error = _GlfwErrorCheck(); //final error check before allocating TuiWindow
	if (glfw_error != TUI_ERROR_NONE)
	{
		glfwDestroyWindow(glfw_window); //it was created, so now destroy it
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}

	TuiWindow window = (TuiWindow_s*)tuiAllocate(sizeof(TuiWindow_s));
	window->FramebufferPixelWidth = framebuffer_pixel_width;
	window->FramebufferPixelHeight = framebuffer_pixel_height;
	window->ViewportPixelWidth = window_width;
	window->ViewportPixelHeight = window_height;
	window->GlfwWindow = glfw_window;
	window->IsFullscreen = TUI_FALSE;
	window->FramebufferMatchViewportSize = framebuffer_matches_viewport_size;
	TuiMonitor cur_monitor = _GetCurrentMonitor(glfw_window);
	glfwGetWindowPos(glfw_window, &window->FullscreenLastWindowedPositionX, &window->FullscreenLastWindowedPositionY);
	window->IsFixedAspectRatio = TUI_FALSE;
	window->UserPointer = NULL;
	window->WindowMoveCallback = NULL;
	window->WindowFocusCallback = NULL;
	window->WindowIconifyCallback = NULL;
	window->WindowMaximizeCallback = NULL;
	window->WindowResizeCallback = NULL;
	window->WindowContentScaleCallback = NULL;
	window->MouseButtonCallback = NULL;
	window->CursorMoveCallback = NULL;
	window->CursorEnterCallback = NULL;
	window->MouseScrollCallback = NULL;
	window->KeyboardKeyCallback = NULL;
	window->CharCallback = NULL;
	window->FileDropCallback = NULL;
	window->Title = tuiAllocate((strlen(title) + 1) * sizeof(char));
	strcpy(window->Title, title);
	glfwSetWindowUserPointer(glfw_window, window);
	glfwMakeContextCurrent(glfw_window);
	glfw_error = _GlfwErrorCheck(); // last error check after allocation of TuiWindow
	if (glfw_error != TUI_ERROR_NONE)
	{
		glfwDestroyWindow(glfw_window); //it was created, so now destroy it
		tuiFree(window);
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	tuiWindowCreate_Opengl33(window);
	sWindowCount++;
	
	return window;
}

TuiWindowCreateInfo tuiWindowCreateInfo()
{
	TuiWindowCreateInfo info;
	info.resizable = TUI_FALSE;
	info.visible = TUI_TRUE;
	info.decorated = TUI_TRUE;
	info.focused = TUI_TRUE;
	info.auto_iconify = TUI_TRUE;
	info.topmost = TUI_FALSE;
	info.maximized = TUI_FALSE;
	info.center_cursor = TUI_FALSE;
	info.focus_on_show = TUI_TRUE;
	info.fullscreen = TUI_FALSE;
	info.monitor = NULL;
	info.custom_window_position = TUI_FALSE;
	info.windowed_x_position = 0;
	info.windowed_y_position = 0;
	info.framebuffer_match_viewport_size = TUI_TRUE;
	info.unmatching_viewport_pixel_width = 0;
	info.unmatching_viewport_pixel_width = 0;
	return info;
}

void tuiWindowDestroy(TuiWindow window)
{
	TuiSystem system = tui_get_system();
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	tuiWindowDestroy_Opengl33(window);
	glfwDestroyWindow(window->GlfwWindow);
	_GlfwClearErrors();
	tuiFree(window->Title);
	tuiFree(window);
	sWindowCount--;
}

int tuiGetWindowCount()
{
	return sWindowCount;
}

void tuiWindowClearColor(TuiWindow window, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	tuiWindowClearColor_Opengl33(window, r, g, b, a);
}

void tuiWindowSetFramebufferPixelDimensions(TuiWindow window, int pixel_width, int pixel_height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (pixel_width <= 0 || pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_FRAMEBUFFER_DIMENSIONS, __func__);
		return;
	}

	if (window->FramebufferMatchViewportSize == TUI_TRUE)
	{
		window->ViewportPixelWidth = pixel_width;
		window->ViewportPixelHeight = pixel_height;
		glfwSetWindowSize(window->GlfwWindow, pixel_width, pixel_height);
	}	
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	tuiWindowSetSize_Opengl33(window, pixel_width, pixel_height);
}

int tuiWindowGetFramebufferPixelWidth(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return (int)window->FramebufferPixelWidth;
}

int tuiWindowGetFramebufferPixelHeight(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return (int)window->FramebufferPixelHeight;
}

void tuiWindowGetFramebufferPixelDimensons(TuiWindow window, int* width, int* height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	if (width != NULL)
	{
		*width = (int)window->FramebufferPixelWidth;
	}
	if (height != NULL)
	{
		*height = (int)window->FramebufferPixelHeight;
	}
}

TuiImage tuiWindowGetImage(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	size_t p_width = 0;
	size_t p_height = 0;
	uint8_t* pixel_data = tuiWindowGetPixels_Opengl33(window, &p_width, &p_height, NULL);
	TuiImage image = _CreateImage(p_width, p_height, 4, pixel_data, TUI_FALSE, __func__);
	return image;
}

void tuiWindowWriteImage(TuiWindow window, TuiImage image)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (image == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_IMAGE, __func__);
		return;
	}

	image->PixelData = tuiWindowGetPixels_Opengl33(window, &image->PixelWidth, &image->PixelHeight, image->PixelData);
}

uint8_t* tuiWindowGetPixels(TuiWindow window, int* pixel_width, int* pixel_height, uint8_t* fill_pixels)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	size_t o_width, o_height;
	fill_pixels = tuiWindowGetPixels_Opengl33(window, &o_width, &o_height, fill_pixels);
	*pixel_width = (int)o_width;
	*pixel_height = (int)o_height;
	return fill_pixels;
}

void tuiWindowDrawBatch(TuiWindow window, TuiAtlas atlas, TuiPalette palette, TuiBatch batch)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (atlas == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_ATLAS, __func__);
		return;
	}
	if (batch == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (tuiDetailHasPalette(batch->DetailMode) == TUI_TRUE && palette == NULL)
	{
		tuiDebugError(TUI_ERROR_PALETTE_REQUIRED, __func__);
		return;
	}
	if (tuiDetailHasFlag(batch->DetailMode, TUI_LAYOUT_FLAG_SPARSE) == TUI_TRUE && batch->TileCount == 0)
	{
		return;
	}

	tuiWindowDrawBatchData_Opengl33(window, atlas, palette, batch->DetailMode, batch->TilesWide, batch->TilesTall, batch->TileCount, batch->Data, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
}

void tuiWindowDrawBatchData(TuiWindow window, TuiAtlas atlas, TuiPalette palette, TuiDetailMode detail_mode, int tiles_wide, int tiles_tall, size_t sparse_index, uint8_t* batch_data)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (batch_data == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH_DATA, __func__);
		return;
	}
	if (tiles_wide <= 0 || tiles_tall <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_DATA_DIMENSIONS, __func__);
		return;
	}
	if (tuiDetailIsValid(detail_mode) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_DETAIL_MODE, __func__);
		return;
	}
	if (tuiDetailHasPalette(detail_mode) == TUI_TRUE && palette == NULL)
	{
		tuiDebugError(TUI_ERROR_PALETTE_REQUIRED, __func__);
		return;
	}
	if (tuiDetailHasFlag(detail_mode, TUI_LAYOUT_FLAG_SPARSE) == TUI_TRUE && sparse_index == 0)
	{
		return;
	}

	tuiWindowDrawBatchData_Opengl33(window, atlas, palette, (size_t)detail_mode, (size_t)tiles_wide, (size_t)tiles_tall, (size_t)sparse_index, batch_data, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);

}

void tuiWindowDrawBatchTransformed(TuiWindow window, TuiAtlas atlas, TuiPalette palette, TuiBatch batch, int left_x, int right_x, int top_y, int bottom_y)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (atlas == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_ATLAS, __func__);
		return;
	}
	if (batch == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH, __func__);
		return;
	}
	if (tuiDetailHasPalette(batch->DetailMode) == TUI_TRUE && palette == NULL)
	{
		tuiDebugError(TUI_ERROR_PALETTE_REQUIRED, __func__);
		return;
	}
	if (tuiDetailHasFlag(batch->DetailMode, TUI_LAYOUT_FLAG_SPARSE) == TUI_TRUE && batch->TileCount == 0)
	{
		return;
	}

	tuiWindowDrawBatchData_Opengl33(window, atlas, palette, batch->DetailMode, batch->TilesWide, batch->TilesTall, batch->TileCount, batch->Data, left_x, right_x, top_y, bottom_y);
}

void tuiWindowDrawBatchDataTransformed(TuiWindow window, TuiAtlas atlas, TuiPalette palette, TuiDetailMode detail_mode, int tiles_wide, int tiles_tall, size_t sparse_index, uint8_t* batch_data, int left_x, int right_x, int top_y, int bottom_y)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (batch_data == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_BATCH_DATA, __func__);
		return;
	}
	if (tiles_wide <= 0 || tiles_tall <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_BATCH_DATA_DIMENSIONS, __func__);
		return;
	}
	if (tuiDetailIsValid(detail_mode) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_DETAIL_MODE, __func__);
		return;
	}
	if (tuiDetailHasFlag(detail_mode, TUI_LAYOUT_FLAG_SPARSE) == TUI_TRUE && sparse_index == 0)
	{
		return;
	}

	tuiWindowDrawBatchData_Opengl33(window, atlas, palette, (size_t)detail_mode, (size_t)tiles_wide, (size_t)tiles_tall, sparse_index, batch_data, left_x, right_x, top_y, bottom_y);
}

void tuiWindowDrawPanel(TuiWindow window, TuiPanel panel)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (panel == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}

	tuiWindowDrawPanel_Opengl33(window, panel, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
}

void tuiWindowDrawPanelTransformed(TuiWindow window, TuiPanel panel, int left_x, int right_x, int top_y, int bottom_y)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (panel == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_PANEL, __func__);
		return;
	}

	tuiWindowDrawPanel_Opengl33(window, panel, left_x, right_x, top_y, bottom_y);
}

void tuiWindowDrawTexture(TuiWindow window, TuiTexture texture)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (texture == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	tuiWindowDrawTexture_Opengl33(window, texture, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
}

void tuiWindowDrawTextureTransformed(TuiWindow window, TuiTexture texture, int left_x, int right_x, int top_y, int bottom_y)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (texture == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	tuiWindowDrawTexture_Opengl33(window, texture, left_x, right_x, top_y, bottom_y);
}

void tuiWindowDrawAtlas(TuiWindow window, TuiAtlas atlas)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (atlas == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	tuiWindowDrawAtlas_Opengl33(window, atlas, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
}

void tuiWindowDrawAtlasTransformed(TuiWindow window, TuiAtlas atlas, int left_x, int right_x, int top_y, int bottom_y)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (atlas == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_TEXTURE, __func__);
		return;
	}

	tuiWindowDrawAtlas_Opengl33(window, atlas, left_x, right_x, top_y, bottom_y);
}

void tuiWindowDrawWindow(TuiWindow window, TuiWindow subject_window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (subject_window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_SUBJECT_WINDOW, __func__);
		return;
	}

	tuiWindowDrawWindow_Opengl33(window, subject_window, 0, window->FramebufferPixelWidth, 0, window->FramebufferPixelHeight);
}

void tuiWindowDrawWindowTransformed(TuiWindow window, TuiWindow subject_window, int left_x, int right_x, int top_y, int bottom_y)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (subject_window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_SUBJECT_WINDOW, __func__);
		return;
	}

	tuiWindowDrawWindow_Opengl33(window, subject_window, left_x, right_x, top_y, bottom_y);
}

void tuiWindowFrame(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	tuiWindowRender_Opengl33(window);
	glfwSwapBuffers(window->GlfwWindow);
	
}

void tuiWindowFrameInterval(TuiWindow window, int interval)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwMakeContextCurrent(window->GlfwWindow);
	glfwSwapInterval(interval);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

const char* tuiWindowGetClipboardString(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	const char* str = glfwGetClipboardString(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return str;
}

void tuiWindowSetClipboardString(TuiWindow window, const char* string)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (string == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_STRING, __func__);
		return;
	}

	glfwSetClipboardString(window->GlfwWindow, string);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiCursorMode tuiWindowGetCursorMode(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_CURSOR_MODE_INVALID;
	}

	TuiCursorMode cursor_mode = (TuiCursorMode)glfwGetInputMode(window->GlfwWindow, GLFW_CURSOR);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_CURSOR_MODE_INVALID;
	}
	return cursor_mode;
}

void tuiWindowSetCursorMode(TuiWindow window, TuiCursorMode cursor_mode)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (tuiCursorModeIsValid(cursor_mode) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_CURSOR_MODE, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_CURSOR, (int)cursor_mode);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetStickyKeys(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int sticky_keys = glfwGetInputMode(window->GlfwWindow, GLFW_STICKY_KEYS);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (sticky_keys == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetStickyKeys(TuiWindow window, TuiBoolean sticky_keys_mode)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_STICKY_KEYS, (int)sticky_keys_mode);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetStickyMouseButtons(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int sticky_mouse_buttons = glfwGetInputMode(window->GlfwWindow, GLFW_STICKY_MOUSE_BUTTONS);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (sticky_mouse_buttons == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetStickyMouseButtons(TuiWindow window, TuiBoolean sticky_mouse_buttons)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_STICKY_MOUSE_BUTTONS, (int)sticky_mouse_buttons);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetLockKeyMods(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int lock_mods = glfwGetInputMode(window->GlfwWindow, GLFW_LOCK_KEY_MODS);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (lock_mods == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetLockKeyMods(TuiWindow window, TuiBoolean lock_mods)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_LOCK_KEY_MODS, (int)lock_mods);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetRawMouseMotion(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int raw_mouse_motion = glfwGetInputMode(window->GlfwWindow, GLFW_RAW_MOUSE_MOTION);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (raw_mouse_motion == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetRawMouseMotion(TuiWindow window, TuiBoolean raw_mouse_motion)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (glfwRawMouseMotionSupported() == GLFW_FALSE)
	{
		tuiDebugError(TUI_ERROR_UNSUPPORTED_RAW_MOUSE_MOTION, __func__);
		return;
	}

	glfwSetInputMode(window->GlfwWindow, GLFW_RAW_MOUSE_MOTION, (int)raw_mouse_motion);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiButtonState tuiWindowGetKeyboardKey(TuiWindow window, TuiKeyboardKey key)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_BUTTON_INVALID;
	}
	if (tuiKeyboardKeyIsValid(key) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_KEYBOARD_KEY, __func__);
		return TUI_BUTTON_INVALID;
	}
	
	TuiButtonState button_state = (TuiButtonState)glfwGetKey(window->GlfwWindow, key);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_BUTTON_INVALID;
	}
	return button_state;
}

TuiButtonState tuiWindowGetMouseButton(TuiWindow window, TuiMouseButton mouse_button)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_BUTTON_INVALID;
	}
	if (tuiMouseButtonIsValid(mouse_button) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_MOUSE_BUTTON, __func__);
		return TUI_BUTTON_INVALID;
	}

	TuiButtonState button_state = (TuiButtonState)glfwGetMouseButton(window->GlfwWindow, mouse_button);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_BUTTON_INVALID;
	}
	return button_state;
}

void tuiWindowGetCursorPosition(TuiWindow window, double* x_position, double* y_position)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwGetCursorPos(window->GlfwWindow, x_position, y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

double tuiWindowGetCursorXPosition(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0;
	}

	double x_position = 0.0;
	glfwGetCursorPos(window->GlfwWindow, &x_position, NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0;
	}
	return x_position;
}

double tuiWindowGetCursorYPosition(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0;
	}

	double y_position = 0.0;
	glfwGetCursorPos(window->GlfwWindow, NULL, &y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0;
	}
	return y_position;
}

void tuiWindowSetCursorPosition(TuiWindow window, double x_position, double y_position)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetCursorPos(window->GlfwWindow, x_position, y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetTitle(TuiWindow window, const char* title)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (title == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_STRING, __func__);
		return;
	}

	if (title == NULL)
	{
		title = "";
	}

	tuiFree(window->Title);
	window->Title = tuiAllocate(strlen(title) * sizeof(char));
	strcpy(window->Title, title);
	glfwSetWindowTitle(window->GlfwWindow, title);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

const char* tuiWindowGetTitle(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	return window->Title;
}

void tuiWindowSetDefaultIcon(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowIcon(window->GlfwWindow, 0, NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetIcon(TuiWindow window, TuiImage image)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (image == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_IMAGE, __func__);
		return;
	}
	TuiSystem system = tui_get_system();
	if (system == NULL)
	{
		tuiDebugError(TUI_ERROR_GLFW_NOT_INITIALIZED, __func__);
		return;
	}
	if (system->WindowIconsSupported == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_UNSUPPORTED_WINDOW_ICONS, __func__);
		return;
	}

	GLFWimage icon_images[3];

	unsigned char level1pixels[16 * 16 * 4];
	icon_images[0].width = 16;
	icon_images[0].height = 16;
	icon_images[0].pixels = _ResizeImageData(image->PixelData, image->PixelWidth, image->PixelHeight, image->ChannelCount, 16, 16, level1pixels, __func__);

	unsigned char level2pixels[32 * 32 * 4];
	icon_images[1].width = 32;
	icon_images[1].height = 32;
	icon_images[1].pixels = _ResizeImageData(image->PixelData, image->PixelWidth, image->PixelHeight, image->ChannelCount, 32, 32, level2pixels, __func__);

	unsigned char level3pixels[48 * 48 * 4];
	icon_images[2].width = 48;
	icon_images[2].height = 48;
	icon_images[2].pixels = _ResizeImageData(image->PixelData, image->PixelWidth, image->PixelHeight, image->ChannelCount, 48, 48, level3pixels, __func__);

	glfwSetWindowIcon(window->GlfwWindow, 3, icon_images);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowIconsSupported()
{
	TuiSystem system = tui_get_system();
	if (system == NULL)
	{
		tuiDebugError(TUI_ERROR_GLFW_NOT_INITIALIZED, __func__);
		return TUI_FALSE;
	}
	return system->WindowIconsSupported;
}

void tuiWindowGetPosition(TuiWindow window, int* x_position, int* y_position)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwGetWindowPos(window->GlfwWindow, x_position, y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

int tuiWindowGetXPosition(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	int x_position = 0;
	glfwGetWindowPos(window->GlfwWindow, &x_position, NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0;
	}
	return x_position;
}

int tuiWindowGetYPosition(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	int y_position = 0;
	glfwGetWindowPos(window->GlfwWindow, NULL, &y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0;
	}
	return y_position;
}

void tuiWindowSetPosition(TuiWindow window, int x_position, int y_position)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowPos(window->GlfwWindow, x_position, y_position);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetSizeLimits(TuiWindow window, int min_width, int min_height, int max_width, int max_height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (min_width < 0 ||
		min_height < 0 ||
		max_width < 0 ||
		max_height < 0 ||
		((max_width != 0) && (max_width < min_width)) ||
		((max_height != 0) && max_height < min_height)
		)
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MinWidth = min_width;
	window->MinHeight = min_height;
	window->MaxWidth = max_width;
	window->MaxHeight = max_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMinSizeLimits(TuiWindow window, int min_width, int min_height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (min_width < 0 || min_height < 0 || ((window->MaxWidth != 0) && min_width > window->MaxWidth) || ((window->MaxHeight != 0) && min_height > window->MaxHeight))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MinWidth = min_width;
	window->MinHeight = min_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMaxSizeLimits(TuiWindow window, int max_width, int max_height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (max_width < 0 || max_height < 0 || ((max_width != 0) && (max_width < window->MinWidth)) ||	((max_height != 0) && max_height < window->MinHeight))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MaxWidth = max_width;
	window->MaxHeight = max_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMinWidth(TuiWindow window, int min_width)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (min_width < 0 || ((window->MaxWidth != 0) && (window->MaxWidth < window->MinWidth)))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MinWidth = min_width;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMinHeight(TuiWindow window, int min_height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (min_height < 0 || ((window->MaxHeight != 0) && (window->MaxHeight < min_height)))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MinHeight = min_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMaxWidth(TuiWindow window, int max_width)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (max_width < 0 || ((max_width != 0) && (max_width < window->MinWidth)))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MaxWidth = max_width;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetMaxHeight(TuiWindow window, int max_height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (max_height < 0 || ((max_height != 0) && (max_height < window->MinHeight)))
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_SIZE_LIMITS, __func__);
		return;
	}

	window->MaxHeight = max_height;
	_WindowUpdateSizeLimits(window);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowGetSizeLimits(TuiWindow window, int* min_width, int* min_height, int* max_width, int* max_height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	if (min_width != NULL)
	{
		*min_width = window->MinWidth;
	}
	if (min_height != NULL)
	{
		*min_height = window->MinHeight;
	}
	if (max_width != NULL)
	{
		*max_width = window->MaxWidth;
	}
	if (max_height != NULL)
	{
		*max_height = window->MaxHeight;
	}
}

int tuiWindowGetMinWidth(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->MinWidth;
}

int tuiWindowGetMinHeight(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->MinHeight;
}

int tuiWindowGetMaxWidth(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->MaxWidth;
}

int tuiWindowGetMaxHeight(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->MaxHeight;
}

TuiBoolean tuiWindowHasSizeLimits(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	return _WindowHasSizeLimits(window);
}

TuiBoolean tuiWindowHasMinSizeLimits(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	if (window->MinWidth != 0 || window->MinHeight != 0)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowHasMaxSizeLimits(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	if (window->MaxWidth != 0 || window->MaxHeight != 0)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetFixedAspectRatio(TuiWindow window, int numerator, int denominator)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (numerator <= 0 || denominator <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_ASPECT_RATIO, __func__);
		return;
	}

	window->IsFixedAspectRatio = TUI_TRUE;
	glfwSetWindowAspectRatio(window->GlfwWindow, numerator, denominator);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowFixCurrentAspectRatio(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	window->IsFixedAspectRatio = TUI_TRUE;
	int greatest_common_factor = _GCF(window->ViewportPixelWidth, window->ViewportPixelHeight);
	glfwSetWindowAspectRatio(window->GlfwWindow, window->ViewportPixelWidth / greatest_common_factor, window->ViewportPixelHeight / greatest_common_factor);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowUnfixAspectRatio(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	
	window->IsFixedAspectRatio = TUI_FALSE;
	glfwSetWindowAspectRatio(window->GlfwWindow, GLFW_DONT_CARE, GLFW_DONT_CARE);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetAspectRatioIsFixed(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	return window->IsFixedAspectRatio;
}

void tuiWindowGetAspectRatio(TuiWindow window, int* numerator, int* denominator)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	int greatest_common_factor = _GCF(window->ViewportPixelWidth, window->ViewportPixelHeight);
	if (numerator != NULL)
	{
		*numerator = window->ViewportPixelWidth / greatest_common_factor;
	}
	if (denominator != NULL)
	{
		*denominator = window->ViewportPixelHeight / greatest_common_factor;
	}
}

void tuiWindowGetContentScale(TuiWindow window, float* scale_wide, float* scale_tall)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwGetWindowContentScale(window->GlfwWindow, scale_wide, scale_tall);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

float tuiWindowGetContentScaleWide(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0f;
	}

	float scale_wide = 0.0f;
	glfwGetWindowContentScale(window->GlfwWindow, &scale_wide, NULL);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0f;
	}
	return scale_wide;
}

float tuiWindowGetContentScaleTall(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0f;
	}

	float scale_tall = 0.0f;
	glfwGetWindowContentScale(window->GlfwWindow, NULL, &scale_tall);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0f;
	}
	return scale_tall;
}

float tuiWindowGetOpacity(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0.0f;
	}

	float opacity = glfwGetWindowOpacity(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return 0.0f;
	}
	return opacity;
}

void tuiWindowSetOpacity(TuiWindow window, float opacity)
{
	opacity = (opacity > 1.0f) ? 1.0f : (opacity < 0.0f) ? 0.0f : opacity;

	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	glfwSetWindowOpacity(window->GlfwWindow, opacity);
	glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowIconify(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwIconifyWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowRestore(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwRestoreWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}


TuiBoolean tuiWindowShouldClose(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int should_close = glfwWindowShouldClose(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (should_close == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetShouldClose(TuiWindow window, TuiBoolean should_close)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowShouldClose(window->GlfwWindow, should_close);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowMaximize(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwMaximizeWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowShow(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwShowWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowHide(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwHideWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowFocus(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwFocusWindow(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowRequestAttention(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwRequestWindowAttention(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiMonitor tuiWindowGetMonitor(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	TuiMonitor monitor = _GetCurrentMonitor(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return monitor;
}

void tuiWindowSetFullscreenCurrentMonitor(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	TuiMonitor monitor = _GetCurrentMonitor(window->GlfwWindow);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	glfwGetWindowPos(window->GlfwWindow, &window->FullscreenLastWindowedPositionX, &window->FullscreenLastWindowedPositionY);
	const GLFWvidmode* vid_mode = glfwGetVideoMode(monitor);
	window->IsFullscreen = TUI_TRUE;
	glfwSetWindowMonitor(window->GlfwWindow, monitor, 0, 0, vid_mode->width, vid_mode->height, vid_mode->refreshRate);
	glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	window->ViewportPixelWidth = vid_mode->width;
	window->ViewportPixelHeight = vid_mode->height;
	if (window->FramebufferMatchViewportSize == TUI_TRUE)
	{
		tuiWindowSetSize_Opengl33(window, (size_t)vid_mode->width, (size_t)vid_mode->height);
	}
}

void tuiWindowSetFullscreen(TuiWindow window, TuiMonitor monitor)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (monitor == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_MONITOR, __func__);
		return;
	}

	glfwGetWindowPos(window->GlfwWindow, &window->FullscreenLastWindowedPositionX, &window->FullscreenLastWindowedPositionY);
	const GLFWvidmode* vid_mode = glfwGetVideoMode(monitor);
	window->IsFullscreen = TUI_TRUE;
	glfwSetWindowMonitor(window->GlfwWindow, monitor, 0, 0, vid_mode->width, vid_mode->height, vid_mode->refreshRate);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
	window->ViewportPixelWidth = vid_mode->width;
	window->ViewportPixelHeight = vid_mode->height;
	if (window->FramebufferMatchViewportSize == TUI_TRUE)
	{
		tuiWindowSetSize_Opengl33(window, (size_t)vid_mode->width, (size_t)vid_mode->height);
	}
}

void tuiWindowSetWindowed(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	if (window->IsFullscreen == TUI_TRUE)
	{
		glfwSetWindowMonitor(window->GlfwWindow, NULL, window->FullscreenLastWindowedPositionX, window->FullscreenLastWindowedPositionY, window->FramebufferPixelWidth, window->FramebufferPixelHeight, GLFW_DONT_CARE);
		TuiErrorCode glfw_error = _GlfwErrorCheck();
		if (glfw_error != TUI_ERROR_NONE)
		{
			tuiDebugError(glfw_error, __func__);
			return;
		}
		window->IsFullscreen = TUI_FALSE;
		window->ViewportPixelWidth = window->FramebufferPixelWidth;
		window->ViewportPixelHeight = window->FramebufferPixelHeight;
	}
}

void tuiWindowSetWindowedViewportSize(TuiWindow window, int viewport_pixel_width, int viewport_pixel_height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}
	if (viewport_pixel_width <= 0 || viewport_pixel_height <= 0)
	{
		tuiDebugError(TUI_ERROR_INVALID_WINDOW_VIEWPORT_DIMENSIONS, __func__);
		return;
	}

	if (window->IsFullscreen == TUI_TRUE)
	{
		window->IsFullscreen = TUI_FALSE;
		window->ViewportPixelWidth = viewport_pixel_width;
		window->ViewportPixelHeight = viewport_pixel_height;
		glfwSetWindowMonitor(window->GlfwWindow, NULL, window->FullscreenLastWindowedPositionX, window->FullscreenLastWindowedPositionY, viewport_pixel_width, viewport_pixel_height, GLFW_DONT_CARE);
		TuiErrorCode glfw_error = _GlfwErrorCheck();
		if (glfw_error != TUI_ERROR_NONE)
		{
			tuiDebugError(glfw_error, __func__);
			return;
		}
		if (window->FramebufferMatchViewportSize == TUI_TRUE)
		{
			tuiWindowSetSize_Opengl33(window, (size_t)viewport_pixel_width, (size_t)viewport_pixel_height);
		}
	}
	else //(window->IsFullscreen == TUI_FALSE)
	{
		window->ViewportPixelWidth = viewport_pixel_width;
		window->ViewportPixelHeight = viewport_pixel_height;
		glfwSetWindowSize(window->GlfwWindow, viewport_pixel_width, viewport_pixel_height);
		TuiErrorCode glfw_error = _GlfwErrorCheck();
		if (glfw_error != TUI_ERROR_NONE)
		{
			tuiDebugError(glfw_error, __func__);
			return;
		}
		if (window->FramebufferMatchViewportSize == TUI_TRUE)
		{
			tuiWindowSetSize_Opengl33(window, (size_t)viewport_pixel_width, (size_t)viewport_pixel_height);
		}
	}
}

int tuiWindowGetViewportPixelWidth(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->ViewportPixelWidth;
}

int tuiWindowGetViewportPixelHeight(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return 0;
	}

	return window->ViewportPixelHeight;
}

void tuiWindowGetViewportPixelDimensons(TuiWindow window, int* width, int* height)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	if (width != NULL)
	{
		*width = (int)window->ViewportPixelWidth;
	}
	if (height != NULL)
	{
		*height = (int)window->ViewportPixelHeight;
	}
}

void tuiWindowSetFramebufferMatchesViewportSize(TuiWindow window, TuiBoolean framebuffer_matches_viewport_size)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	window->FramebufferMatchViewportSize = framebuffer_matches_viewport_size;
	if (window->FramebufferMatchViewportSize == TUI_TRUE)
	{
		tuiWindowSetSize_Opengl33(window, window->ViewportPixelWidth, window->ViewportPixelHeight);
	}
}

TuiBoolean tuiWindowGetFramebufferMatchesViewportSize(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	return window->FramebufferMatchViewportSize;
}

TuiBoolean tuiWindowGetIsFullscreen(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	return window->IsFullscreen;
}

TuiBoolean tuiWindowGetFocused(TuiWindow window)
{ 
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int focused = glfwGetWindowAttrib(window->GlfwWindow, GLFW_FOCUSED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (focused == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetIconified(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int iconified = glfwGetWindowAttrib(window->GlfwWindow, GLFW_ICONIFIED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (iconified == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetMaximized(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int maximized = glfwGetWindowAttrib(window->GlfwWindow, GLFW_MAXIMIZED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (maximized == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetMouseEntered(TuiWindow window)
{ 
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int mouse_entered = glfwGetWindowAttrib(window->GlfwWindow, GLFW_HOVERED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (mouse_entered == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetVisible(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int visible = glfwGetWindowAttrib(window->GlfwWindow, GLFW_VISIBLE);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (visible == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

TuiBoolean tuiWindowGetResizable(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int resizable = glfwGetWindowAttrib(window->GlfwWindow, GLFW_RESIZABLE);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (resizable == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetResizable(TuiWindow window, TuiBoolean resizable)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_RESIZABLE, (int)resizable);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetDecorated(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int decorated = glfwGetWindowAttrib(window->GlfwWindow, GLFW_DECORATED);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (decorated == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetDecorated(TuiWindow window, TuiBoolean decorated)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_DECORATED, (int)decorated);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetAutoIconify(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int auto_iconify = glfwGetWindowAttrib(window->GlfwWindow, GLFW_AUTO_ICONIFY);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (auto_iconify == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetAutoIconify(TuiWindow window, TuiBoolean auto_iconify)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_AUTO_ICONIFY, (int)auto_iconify);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetTopmost(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int topmost =glfwGetWindowAttrib(window->GlfwWindow, GLFW_FLOATING); //"topmost" is easier to understand than "floating"
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (topmost == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetTopmost(TuiWindow window, TuiBoolean topmost)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_FLOATING, (int)topmost);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

TuiBoolean tuiWindowGetFocusOnShow(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return TUI_FALSE;
	}

	int focus_on_show = glfwGetWindowAttrib(window->GlfwWindow, GLFW_FOCUS_ON_SHOW);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return TUI_FALSE;
	}
	if (focus_on_show == GLFW_TRUE)
	{
		return TUI_TRUE;
	}
	return TUI_FALSE;
}

void tuiWindowSetFocusOnShow(TuiWindow window, TuiBoolean focus_on_show)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetWindowAttrib(window->GlfwWindow, GLFW_FOCUS_ON_SHOW, (int)focus_on_show);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

void tuiWindowSetUserPointer(TuiWindow window, void* ptr)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	window->UserPointer = ptr; //use a member variable instead of the GLFWwindow user pointer, because that pointer contains a pointer to this TuiWindow for internal uses.
}

void* tuiWindowGetUserPointer(TuiWindow window)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	return window->UserPointer;
}

void tuiWindowSetCursor(TuiWindow window, TuiCursor cursor)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return;
	}

	glfwSetCursor(window->GlfwWindow, cursor);
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return;
	}
}

tuiWindowMoveFunction tuiWindowSetMoveCallback(TuiWindow window, tuiWindowMoveFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiWindowMoveFunction old_callback = window->WindowMoveCallback;
	window->WindowMoveCallback = callback;
	if (callback == NULL)
	{
		glfwSetWindowPosCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetWindowPosCallback(window->GlfwWindow, glfwWindowPosCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiWindowCloseFunction tuiWindowSetCloseCallback(TuiWindow window, tuiWindowCloseFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiWindowCloseFunction old_callback = window->WindowCloseCallback;
	window->WindowCloseCallback = callback;
	if (callback == NULL)
	{
		glfwSetWindowCloseCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetWindowCloseCallback(window->GlfwWindow, glfwWindowCloseCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiWindowFocusFunction tuiWindowSetFocusCallback(TuiWindow window, tuiWindowFocusFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiWindowFocusFunction old_callback = window->WindowFocusCallback;
	window->WindowFocusCallback = callback;
	if (callback == NULL)
	{
		glfwSetWindowFocusCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetWindowFocusCallback(window->GlfwWindow, glfwWindowFocusCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiWindowIconifyFunction tuiWindowSetIconifyCallback(TuiWindow window, tuiWindowIconifyFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiWindowIconifyFunction old_callback = window->WindowIconifyCallback;
	window->WindowIconifyCallback = callback;
	if (callback == NULL)
	{
		glfwSetWindowIconifyCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetWindowIconifyCallback(window->GlfwWindow, glfwWindowIconifyCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiWindowMaximizeFunction tuiWindowSetMaximizeCallback(TuiWindow window, tuiWindowMaximizeFunction callback)
{ 
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiWindowMaximizeFunction old_callback = window->WindowMaximizeCallback;
	window->WindowMaximizeCallback = callback;
	if (callback == NULL)
	{
		glfwSetWindowMaximizeCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetWindowMaximizeCallback(window->GlfwWindow, glfwWindowMaximizeCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiWindowResizeFunction tuiWindowSetResizeCallback(TuiWindow window, tuiWindowResizeFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiWindowResizeFunction old_callback = window->WindowResizeCallback;
	window->WindowResizeCallback = callback;
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiWindowContentScaleFunction tuiWindowSetContentScaleCallback(TuiWindow window, tuiWindowContentScaleFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiWindowContentScaleFunction old_callback = window->WindowContentScaleCallback;
	window->WindowContentScaleCallback = callback;
	if (callback == NULL)
	{
		glfwSetWindowContentScaleCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetWindowContentScaleCallback(window->GlfwWindow, glfwWindowContentScaleCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiKeyboardKeyboardKeyFunction tuiWindowSetKeyboardKeyCallback(TuiWindow window, tuiKeyboardKeyboardKeyFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiKeyboardKeyboardKeyFunction old_callback = window->KeyboardKeyCallback;
	window->KeyboardKeyCallback = callback;
	if (callback == NULL)
	{
		glfwSetKeyCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetKeyCallback(window->GlfwWindow, glfwKeyCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiCharFunction tuiWindowSetCharCallback(TuiWindow window, tuiCharFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiCharFunction old_callback = window->CharCallback;
	window->CharCallback = callback;
	if (callback == NULL)
	{
		glfwSetCharCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetCharCallback(window->GlfwWindow, glfwCharCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiMouseButtonFunction tuiWindowSetMouseButtonCallback(TuiWindow window, tuiMouseButtonFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiMouseButtonFunction old_callback = window->MouseButtonCallback;
	window->MouseButtonCallback = callback;
	if (callback == NULL)
	{
		glfwSetMouseButtonCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetMouseButtonCallback(window->GlfwWindow, glfwMouseButtonCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiCursorMoveFunction tuiWindowSetCursorMoveCallback(TuiWindow window, tuiCursorMoveFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiCursorMoveFunction old_callback = window->CursorMoveCallback;
	window->CursorMoveCallback = callback;
	if (callback == NULL)
	{
		glfwSetCursorPosCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetCursorPosCallback(window->GlfwWindow, glfwCursorMoveCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiCursorEnterFunction tuiWindowSetCursorEnterCallback(TuiWindow window, tuiCursorEnterFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiCursorEnterFunction old_callback = window->CursorEnterCallback;
	window->CursorEnterCallback = callback;
	if (callback == NULL)
	{
		glfwSetCursorEnterCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetCursorEnterCallback(window->GlfwWindow, glfwCursorEnterCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiMouseScrollFunction tuiWindowSetMouseScrollCallback(TuiWindow window, tuiMouseScrollFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiMouseScrollFunction old_callback = window->MouseScrollCallback;
	window->MouseScrollCallback = callback;
	if (callback == NULL)
	{
		glfwSetScrollCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetScrollCallback(window->GlfwWindow, glfwScrollCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}

tuiFileDropFunction tuiWindowSetFileDropCallback(TuiWindow window, tuiFileDropFunction callback)
{
	if (window == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_WINDOW, __func__);
		return NULL;
	}

	tuiFileDropFunction old_callback = window->FileDropCallback;
	window->FileDropCallback = callback;
	if (callback == NULL)
	{
		glfwSetDropCallback(window->GlfwWindow, NULL);
	}
	else
	{
		glfwSetDropCallback(window->GlfwWindow, glfwDropCallback);
	}
	TuiErrorCode glfw_error = _GlfwErrorCheck();
	if (glfw_error != TUI_ERROR_NONE)
	{
		tuiDebugError(glfw_error, __func__);
		return NULL;
	}
	return old_callback;
}
