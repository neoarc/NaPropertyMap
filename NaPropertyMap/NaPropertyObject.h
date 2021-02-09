//
// PropertyMap interfaces
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
	ReadOnly,
};

using NaPropertySetterResult = NaResult;

struct NaPropertyInfo;

using NaPropertyMap = std::map<std::wstring, NaPropertyInfo>;
using NaVariant = std::variant<bool, int, unsigned int, float, double, std::wstring>;

class NaPropertyObjectBase
{
public:
	virtual std::wstring NaGetClassName() { return L""; }
	
	NaVariant GetProperty(std::wstring name);
	NaPropertySetterResult SetProperty(std::wstring name, NaVariant value);

	virtual NaPropertyMap* GetPropertyMap() { return nullptr; }
};

using NaPropertyGetter = NaVariant(NaPropertyObjectBase::*)(void);
using NaPropertySetter = NaPropertySetterResult(NaPropertyObjectBase::*)(NaVariant);

struct NaPropertyInfo
{
	std::wstring name_;
	std::wstring displayName_;
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
	static std::wstring _className_; \
	static NaPropertyMap _class##PropertyMap_; \
	virtual std::wstring NaGetClassName() { return _className_; }; \
	virtual NaPropertyMap* GetPropertyMap() { return &_class::_class##PropertyMap_; }

#define DECL_PROP(_prop) \
	NaVariant get_##_prop(); NaPropertySetterResult set_##_prop(NaVariant val)

#define DECL_PROP_RO(_prop) \
	NaVariant get_##_prop(); 

#define BEGIN_IMPL_PROPERTY_MAP(_class) \
	std::wstring _class::_className_ = L###_class; \
	using _this_class = _class; \
	NaPropertyMap _class::_class##PropertyMap_ = NaPropertyGroupBuilder{ 

#define PROP_GROUP(_prop, _displayName) \
	{ L"_group" L###_prop, L###_prop, VT_EMPTY, 0, std::vector<std::wstring>(), L##_displayName, false, 0, 0, nullptr, nullptr },

#define PROP_EMPTY_ENUM	std::vector<std::wstring>()

#define PROP_T(_prop, _displayName, _vt, _defaultWithCast, _enum) \
	{ \
		L###_prop, \
		_displayName, \
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

#define PROP_T_RO(_prop, _displayName, _vt, _defaultWithCast, _enum) \
	{ \
		L###_prop, \
		_displayName, \
		_vt, \
		_defaultWithCast, \
		_enum, \
		L"", \
		false, \
		0, \
		0, \
		(static_cast<NaPropertyGetter>(&_this_class::get_##_prop)), \
		nullptr, \
	},

// Default macros
#define PROP_STR(_prop, _default)	PROP_T(_prop, L"", VT_LPWSTR, (std::wstring)L##_default, PROP_EMPTY_ENUM)
#define PROP_INT(_prop, _default)	PROP_T(_prop, L"",  VT_I4, (int)_default, PROP_EMPTY_ENUM)
#define PROP_UINT(_prop, _default)	PROP_T(_prop, L"", VT_UI4, (int)_default, PROP_EMPTY_ENUM)
#define PROP_FLOAT(_prop, _default) PROP_T(_prop, L"", VT_R4, (float)_default, PROP_EMPTY_ENUM)
#define PROP_BOOL(_prop, _default)	PROP_T(_prop, L"", VT_BOOL, (bool)_default, PROP_EMPTY_ENUM)

#define PROP_RO_STR(_prop, _default)	PROP_T_RO(_prop, L"", VT_LPWSTR, (std::wstring)L##_default, PROP_EMPTY_ENUM)
#define PROP_RO_INT(_prop, _default)	PROP_T_RO(_prop, L"",  VT_I4, (int)_default, PROP_EMPTY_ENUM)
#define PROP_RO_UINT(_prop, _default)	PROP_T_RO(_prop, L"", VT_UI4, (int)_default, PROP_EMPTY_ENUM)
#define PROP_RO_FLOAT(_prop, _default)	PROP_T_RO(_prop, L"", VT_R4, (float)_default, PROP_EMPTY_ENUM)
#define PROP_RO_BOOL(_prop, _default)	PROP_T_RO(_prop, L"", VT_BOOL, (bool)_default, PROP_EMPTY_ENUM)

// Default + DisplayName
#define PROP_D_STR(_prop, _displayName, _default)	PROP_T(_prop, L##_displayName, VT_LPWSTR, (std::wstring)L##_default, PROP_EMPTY_ENUM)
#define PROP_D_INT(_prop, _displayName, _default)	PROP_T(_prop, L##_displayName,  VT_I4, (int)_default, PROP_EMPTY_ENUM)
#define PROP_D_UINT(_prop, _displayName, _default)	PROP_T(_prop, L##_displayName, VT_UI4, (int)_default, PROP_EMPTY_ENUM)
#define PROP_D_FLOAT(_prop, _displayName, _default) PROP_T(_prop, L##_displayName, VT_R4, (float)_default, PROP_EMPTY_ENUM)
#define PROP_D_BOOL(_prop, _displayName, _default)	PROP_T(_prop, L##_displayName, VT_BOOL, (bool)_default, PROP_EMPTY_ENUM)

#define PROP_RO_D_STR(_prop, _displayName, _default)	PROP_T_RO(_prop, L##_displayName, VT_LPWSTR, (std::wstring)L##_default, PROP_EMPTY_ENUM)
#define PROP_RO_D_INT(_prop, _displayName, _default)	PROP_T_RO(_prop, L##_displayName,  VT_I4, (int)_default, PROP_EMPTY_ENUM)
#define PROP_RO_D_UINT(_prop, _displayName, _default)	PROP_T_RO(_prop, L##_displayName, VT_UI4, (int)_default, PROP_EMPTY_ENUM)
#define PROP_RO_D_FLOAT(_prop, _displayName, _default)	PROP_T_RO(_prop, L##_displayName, VT_R4, (float)_default, PROP_EMPTY_ENUM)
#define PROP_RO_D_BOOL(_prop, _displayName, _default)	PROP_T_RO(_prop, L##_displayName, VT_BOOL, (bool)_default, PROP_EMPTY_ENUM)

// Enumeration types
#define PROP_STR_ENUM(_prop, _default, _enum) PROP_T(_prop, L"", VT_LPWSTR, (std::wstring)L##_default, _enum)
#define PROP_INT_ENUM(_prop, _default, _enum) PROP_T(_prop, L"", VT_I4, (int)_default, _enum)

#define PROP_RO_STR_ENUM(_prop, _default, _enum) PROP_T_RO(_prop, L"", VT_LPWSTR, (std::wstring)L##_default, _enum)
#define PROP_RO_INT_ENUM(_prop, _default, _enum) PROP_T_RO(_prop, L"", VT_I4, (int)_default, _enum)

#define PROP_D_STR_ENUM(_prop, _displayName, _default, _enum) PROP_T(_prop, L##_displayName, VT_LPWSTR, (std::wstring)L##_default, _enum)
#define PROP_D_INT_ENUM(_prop, _displayName, _default, _enum) PROP_T(_prop, L##_displayName, VT_I4, (int)_default, _enum)

#define PROP_RO_D_STR_ENUM(_prop, _displayName, _default, _enum) PROP_T_RO(_prop, L##_displayName, VT_LPWSTR, (std::wstring)L##_default, _enum)
#define PROP_RO_D_INT_ENUM(_prop, _displayName, _default, _enum) PROP_T_RO(_prop, L##_displayName, VT_I4, (int)_default, _enum)

#define END_IMPL_PROPERTY_MAP(_class) \
	}; 	

#define IMPL_PROPERTY_GETTER(_class, _prop) \
	NaVariant _class::get_##_prop()

#define IMPL_PROPERTY_SETTER(_class, _prop) \
	NaPropertySetterResult _class::set_##_prop(NaVariant value)

