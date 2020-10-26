#pragma once

#include "NaPropertyObject.h"

class DemoObject : public NaPropertyObjectBase
{
public:
	std::wstring name_;

	DECL_PROPERTY_MAP(DemoObject);
	DECL_PROP(name);
};

