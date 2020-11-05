//
// 2020.10.26 neoarc; 2nd gen PropertyMap
//
#pragma once

#include <iostream>
#include <variant>
#include <map>
#include <unordered_map>
#include <wtypes.h>

struct NaPropertyInfo;

using NaPropertyMap = std::unordered_map<std::wstring, NaPropertyInfo>;
using NaVariant = std::variant<bool, int, unsigned int, float, double, std::wstring>;

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

using NaPropertyMap = std::unordered_map<std::wstring, NaPropertyInfo>;

class NaPropertyGroupBuilder
{
public:
	NaPropertyGroupBuilder() = delete;
	NaPropertyGroupBuilder(std::initializer_list<NaPropertyInfo> data);

	NaPropertyGroupBuilder& operator=(std::initializer_list<NaPropertyInfo> data);
	operator NaPropertyMap() const;

	protected:
	NaPropertyMap map_;
};

#define DECL_PROPERTY_MAP(_class) \
	static NaPropertyMap _class##PropertyMap_; \
	virtual NaPropertyMap* GetPropertyMap() { return &_class::_class##PropertyMap_; }

#define DECL_PROP(_prop) \
	NaVariant get_##_prop(); int set_##_prop(NaVariant val)

#define BEGIN_IMPL_PROPERTY_MAP(_class) \
	using _this_class = _class; \
	NaPropertyMap _class::_class##PropertyMap_ = NaPropertyGroupBuilder{ 

#define PROP_GROUP(_prop, _displayName) \
	{ L"_group" L###_prop, VT_EMPTY, 0, nullptr, L##_displayName, false, 0, 0, nullptr, nullptr },

#define PROP_T(_prop, _vt, _defaultWithCast) \
	{ \
		L###_prop, \
		_vt, \
		_defaultWithCast, \
		nullptr, \
		L"", \
		false, \
		0, \
		0, \
		(static_cast<NaPropertyGetter>(&_this_class::get_##_prop)), \
		(static_cast<NaPropertySetter>(&_this_class::set_##_prop)), \
	},

#define PROP_STR(_prop, _default) PROP_T(_prop, VT_LPWSTR, (std::wstring)L##_default)
#define PROP_INT(_prop, _default) PROP_T(_prop, VT_I4, (int)_default)
#define PROP_UINT(_prop, _default) PROP_T(_prop, VT_UI4, (int)_default)
#define PROP_FLOAT(_prop, _default) PROP_T(_prop, VT_R4, (float)_default)
#define PROP_BOOL(_prop, _default) PROP_T(_prop, VT_BOOL, (bool)_default)

#define END_IMPL_PROPERTY_MAP(_class) \
	}; 	

#define IMPL_PROPERTY_GETTER(_class, _prop) \
	NaVariant _class::get_##_prop()

#define IMPL_PROPERTY_SETTER(_class, _prop) \
	int _class::set_##_prop(NaVariant value)








