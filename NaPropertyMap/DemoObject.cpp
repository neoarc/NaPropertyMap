#include "DemoObject.h"

// Implement part
BEGIN_IMPL_PROPERTY_MAP(DemoObject)
	PROP_STR(name, "")
	PROP_INT(age, 0)
	PROP_FLOAT(weight, 60.0f)
END_IMPL_PROPERTY_MAP(DemoObject)

// name
NaVariant DemoObject::get_name()
{
	NaVariant var = name_;
	return std::move(var);
}

int DemoObject::set_name(NaVariant val)
{
	name_ = std::get<std::wstring>(val);
	return 0;
}

// age
NaVariant DemoObject::get_age()
{
	NaVariant var = age_;
	return std::move(var);
}

int DemoObject::set_age(NaVariant val)
{
	age_ = std::get<int>(val);
	return 0;
}

// weight
NaVariant DemoObject::get_weight()
{
	NaVariant var = weight_;
	return std::move(var);
}

int DemoObject::set_weight(NaVariant val)
{
	weight_ = std::get<float>(val);
	return 0;
}


