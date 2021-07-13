#include <TUIC/cursor.h>
#include "image_inline.h"
#include <GLFW/glfw3.h>
#include "glfw_error_check.h"
#include <TUIC/debug.h>
#include <TUIC/system.h>
#include <TUIC/boolean.h>

static int sCursorCount;

TuiCursor tuiCursorCreate(TuiImage image, int xhot, int yhot)
{
	if (image == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_IMAGE, __func__);
		return NULL;
	}

	GLFWimage glfw_image = _TuiImageToGlfwImage(image, __func__);
	if (glfw_image.width == 0)
	{
		return NULL;
	}
	TuiCursor cursor = glfwCreateCursor(&glfw_image, xhot, yhot);
	GLFW_CHECK_ERROR_RETURN(NULL)
	sCursorCount++;
	return cursor;
}

TuiCursor tuiCursorCreateStandard(TuiCursorShape shape)
{
	if (tuiCursorShapeIsValid(shape) == TUI_FALSE)
	{
		tuiDebugError(TUI_ERROR_INVALID_CURSOR_SHAPE, __func__);
		return NULL;
	}
	sCursorCount++;
	TuiCursor cursor = glfwCreateStandardCursor(shape);
	GLFW_CHECK_ERROR_RETURN(NULL)
	sCursorCount++;
	return cursor;
}

void tuiCursorDestroy(TuiCursor cursor)
{
	if (cursor == NULL)
	{
		tuiDebugError(TUI_ERROR_NULL_CURSOR, __func__);
		return;
	}
	glfwDestroyCursor(cursor);
	GLFW_CHECK_ERROR()
	sCursorCount--;
	
}

int tuiGetCursorCount()
{
	return sCursorCount;
}
