#include "DemoObject.h"

// Implement part
BEGIN_IMPL_PROPERTY_MAP(DemoObject)
	PROP_STR(name)
END_IMPL_PROPERTY_MAP(DemoObject)

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

