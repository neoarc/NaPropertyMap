//
// 2020.10.26 neoarc; 2nd gen PropertyMap
//
#pragma once

#include <iostream>
#include <variant>
#include <map>
#include <wtypes.h>

struct NaPropertyInfo;

using NaPropertyMap = std::map<std::wstring, NaPropertyInfo>;
using NaVariant = std::variant<std::wstring, double, float, int, bool>;

class NaPropertyObjectBase
{
public:
	NaVariant GetProperty(std::wstring name);
	int SetProperty(std::wstring name, NaVariant value);

	virtual NaPropertyMap* GetPropertyMap() { return nullptr; }
};

using NaPropertyGetter = NaVariant(NaPropertyObjectBase::*)(void);
using NaPropertySetter = int(NaPropertyObjectBase::*)(NaVariant);

struct NaPropertyInfo
{
	std::wstring name_;
	int vt_;
	NaVariant defaultValue_;
	wchar_t** typeNameList_;
	std::wstring group_;
	bool useExtraEditor_;
	int minValue_;
	int maxValue_;
	NaPropertyGetter getter_;
	NaPropertySetter setter_;
};

using NaPropertyMap = std::map<std::wstring, NaPropertyInfo>;

#define DECL_PROPERTY_MAP(_class) \
	static NaPropertyMap _class##PropertyMap_; \
	virtual NaPropertyMap* GetPropertyMap() { return &_class::_class##PropertyMap_; }

#define DECL_PROP(_prop) \
	NaVariant get_##_prop(); int set_##_prop(NaVariant val)

#define BEGIN_IMPL_PROPERTY_MAP(_class) \
	using _this_class = _class; \
	NaPropertyMap _class::_class##PropertyMap_{ 

#define PROP_GROUP(_prop) \
	{ L###_prop, { L###_prop, VT_EMPTY }},

#define PROP_STR(_prop, _default) \
	{ \
		L###_prop, \
		{ \
			L###_prop, \
			VT_LPWSTR, \
			(std::wstring)L##_default, \
			nullptr, \
			L"", \
			false, \
			0, \
			0, \
			(static_cast<NaPropertyGetter>(&_this_class::get_##_prop)), \
			(static_cast<NaPropertySetter>(&_this_class::set_##_prop)), \
		} \
	},

#define PROP_INT(_prop, _default) \
	{ \
		L###_prop, \
		{ \
			L###_prop, \
			VT_I4, \
			(int)_default, \
			nullptr, \
			L"", \
			false, \
			0, \
			0, \
			(static_cast<NaPropertyGetter>(&_this_class::get_##_prop)), \
			(static_cast<NaPropertySetter>(&_this_class::set_##_prop)), \
		} \
	},

#define PROP_FLOAT(_prop, _default) \
	{ \
		L###_prop, \
		{ \
			L###_prop, \
			VT_R4, \
			(float)_default, \
			nullptr, \
			L"", \
			false, \
			0, \
			0, \
			(static_cast<NaPropertyGetter>(&_this_class::get_##_prop)), \
			(static_cast<NaPropertySetter>(&_this_class::set_##_prop)), \
		} \
	},

#define END_IMPL_PROPERTY_MAP(_class) \
	}; 	
