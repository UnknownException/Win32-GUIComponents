#ifndef _GUICOMPONENTS_HEADER
#define _GUICOMPONENTS_HEADER

#ifdef _GUICOMPONNENTS_HANDLELIBANDHEADERS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

	#include <CommCtrl.h>
	#pragma comment(lib, "Comctl32.lib")
	#pragma comment(linker,"\"/manifestdependency:type                  = 'win32' \
												  name                  = 'Microsoft.Windows.Common-Controls' \
												  version               = '6.0.0.0' \
												  processorArchitecture = '*' \
												  publicKeyToken        = '6595b64144ccf1df' \
												  language              = '*'\"")

	#include <vector>
#endif

#ifndef _INC_WINDOWS
	#error Windows.h must be included before including the GUIComponents header.
#endif
#ifndef _INC_COMMCTRL
	#error CommCtrl.h must be included before including the GUIComponents header.
#endif

namespace GUIComponents {
	#include "Vector2.h"
	#include "Font.h"

	#include "Item.h" //  Vector2.h, Font.h

	#include "Button.h" // Item.h
	#include "Checkbox.h" // Item.h
	#include "ComboBox.h" // Item.h
	#include "TextBox.h" // Item.h
	#include "TextLabel.h" // Item.h
	#include "Window.h" // Item.h

	#include "NumericBox.h" // TextBox.h
}

#endif