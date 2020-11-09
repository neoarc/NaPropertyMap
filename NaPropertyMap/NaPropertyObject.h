//
// 2020.10.26 neoarc; 2nd gen PropertyMap
//
#pragma once

#include <variant>
#include <map>
#include <vector>
#include <wtypes.h>

enum class NaResult : int
{
	Fail = -1,
	Success = 0,
	RefreshSelf,
	RefreshAll,

	NotFound,
	NotImpl,
};

using NaPropertySetterResult = NaResult;

struct NaPropertyInfo;

using NaPropertyMap = std::map<std::wstring, NaPropertyInfo>;
using NaVariant = std::variant<bool, int, unsigned int, float, double, std::wstring>;

class NaPropertyObjectBase
{
public:
	NaVariant GetProperty(std::wstring name);
	NaPropertySetterResult SetProperty(std::wstring name, NaVariant value);

	virtual NaPropertyMap* GetPropertyMap() { return nullptr; }
};

using NaPropertyGetter = NaVariant(NaPropertyObjectBase::*)(void);
using NaPropertySetter = NaPropertySetterResult(NaPropertyObjectBase::*)(NaVariant);

struct NaPropertyInfo
{
	std::wstring name_;
	int vt_;
	NaVariant defaultValue_;
	std::vector<std::wstring> valueNameList_; // Pre-defined name list
	std::wstring group_;
	bool useExtraEditor_;
	int minValue_;
	int maxValue_;
	NaPropertyGetter getter_;
	NaPropertySetter setter_;
};

using NaPropertyMap = std::map<std::wstring, NaPropertyInfo>;

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
	NaVariant get_##_prop(); NaPropertySetterResult set_##_prop(NaVariant val)

#define BEGIN_IMPL_PROPERTY_MAP(_class) \
	using _this_class = _class; \
	NaPropertyMap _class::_class##PropertyMap_ = NaPropertyGroupBuilder{ 

#define PROP_GROUP(_prop, _displayName) \
	{ L"_group" L###_prop, VT_EMPTY, 0, std::vector<std::wstring>(), L##_displayName, false, 0, 0, nullptr, nullptr },

#define PROP_T(_prop, _vt, _defaultWithCast) \
	{ \
		L###_prop, \
		_vt, \
		_defaultWithCast, \
		std::vector<std::wstring>(), \
		L"", \
		false, \
		0, \
		0, \
		(static_cast<NaPropertyGetter>(&_this_class::get_##_prop)), \
		(static_cast<NaPropertySetter>(&_this_class::set_##_prop)), \
	},

#define PROP_T_ENUM(_prop, _vt, _defaultWithCast, _enum) \
	{ \
		L###_prop, \
		_vt, \
		_defaultWithCast, \
		_enum, \
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

#define PROP_STR_ENUM(_prop, _default, _enum) PROP_T_ENUM(_prop, VT_LPWSTR, (std::wstring)L##_default, _enum)
#define PROP_INT_ENUM(_prop, _default, _enum) PROP_T_ENUM(_prop, VT_I4, (int)_default, _enum)

#define END_IMPL_PROPERTY_MAP(_class) \
	}; 	

#define IMPL_PROPERTY_GETTER(_class, _prop) \
	NaVariant _class::get_##_prop()

#define IMPL_PROPERTY_SETTER(_class, _prop) \
	NaPropertySetterResult _class::set_##_prop(NaVariant value)

