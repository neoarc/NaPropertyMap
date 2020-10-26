//
// 2020.10.26 neoarc; 2nd gen PropertyMap
//
#pragma once

#include <iostream>
#include <variant>
#include <map>

struct NaPropertyInfo;

using NaPropertyMap = std::map<std::string, NaPropertyInfo>;
using NaVariant = std::variant<std::wstring, double, float, int, bool>;

class NaPropertyObjectBase
{
public:
	NaVariant GetProperty(std::string name);
	int SetProperty(std::string name, NaVariant value);

	virtual NaPropertyMap* GetPropertyMap() { return nullptr; }
};

using NaPropertyGetter = NaVariant(NaPropertyObjectBase::*)(void);
using NaPropertySetter = int(NaPropertyObjectBase::*)(NaVariant);

struct NaPropertyInfo
{
	std::string name_;
	NaPropertyGetter getter_;
	NaPropertySetter setter_;
};

using NaPropertyMap = std::map<std::string, NaPropertyInfo>;

#define DECL_PROPERTY_MAP(_class) \
	static NaPropertyMap _class##PropertyMap_; \
	virtual NaPropertyMap* GetPropertyMap() { return &_class::_class##PropertyMap_; }

#define DECL_PROP(_prop) \
	NaVariant get_##_prop(); int set_##_prop(NaVariant val)

#define BEGIN_IMPL_PROPERTY_MAP(_class) \
	using _this_class = _class; \
	NaPropertyMap _class::_class##PropertyMap_{ 

#define PROP_STR(_prop) \
	{ \
		#_prop, \
		{ \
			#_prop, \
			(static_cast<NaPropertyGetter>(&_this_class::get_##_prop)), \
			(static_cast<NaPropertySetter>(&_this_class::set_##_prop)), \
		} \
	}

#define END_IMPL_PROPERTY_MAP(_class) \
	}; 	
