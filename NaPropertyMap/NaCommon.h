#pragma once

#define USE_CHECKBOX_FOR_BOOL

enum VARENUM_ETC
{
	VT_ETC_COLOR = 0x10000,
	VT_ETC_NASTR,
	VT_ETC_NALIST,

	VT_ETC_MIXED,	// For multi selection
	
#if defined(USE_CHECKBOX_FOR_BOOL)
	VT_ETC_BOOL,	// Bool as checkbox
#endif
	VT_ETC_BUTTON,

	// Deprecated
	VT_ETC_NASTR_X,
};

#define DECL_PTR(class_) using class_##Ptr = std::shared_ptr<class_>