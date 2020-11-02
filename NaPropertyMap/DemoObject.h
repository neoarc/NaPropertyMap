#pragma once

#include "NaPropertyObject.h"

class DemoObject : public NaPropertyObjectBase
{
public:
	std::wstring name_;
	int age_;
	float weight_;

	DECL_PROPERTY_MAP(DemoObject);
	DECL_PROP(name);
	DECL_PROP(age);
	DECL_PROP(weight);
};

