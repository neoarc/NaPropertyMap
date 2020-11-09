#include "DemoObject.h"

// Implement part
BEGIN_IMPL_PROPERTY_MAP(DemoObject)
	PROP_GROUP(personality, "Personality")
		PROP_STR(name, "")
		PROP_INT(age, 0)
		PROP_FLOAT(weight, 60.0f)
	PROP_GROUP(clothColor, "Cloth Color")
		PROP_STR(shirtsColor, "black")
		PROP_STR(pantsColor, "blue")
END_IMPL_PROPERTY_MAP(DemoObject)

// name
IMPL_PROPERTY_GETTER(DemoObject, name)
{
	NaVariant var = name_;
	return std::move(var);
}

IMPL_PROPERTY_SETTER(DemoObject, name)
{
	name_ = std::get<std::wstring>(value);
	return NaResult::Success;
}

// age
IMPL_PROPERTY_GETTER(DemoObject, age)
{
	NaVariant var = age_;
	return std::move(var);
}

IMPL_PROPERTY_SETTER(DemoObject, age)
{
	age_ = std::get<int>(value);
	return NaResult::Success;
}

// weight
IMPL_PROPERTY_GETTER(DemoObject, weight)
{
	NaVariant var = weight_;
	return std::move(var);
}

IMPL_PROPERTY_SETTER(DemoObject, weight)
{
	weight_ = std::get<float>(value);
	return NaResult::Success;
}

// shirtsColor
IMPL_PROPERTY_GETTER(DemoObject, shirtsColor)
{
	NaVariant var = shirtsColor_;
	return std::move(var);
}

IMPL_PROPERTY_SETTER(DemoObject, shirtsColor)
{
	shirtsColor_ = std::get<std::wstring>(value);
	return NaResult::Success;
}

// pantsColor
IMPL_PROPERTY_GETTER(DemoObject, pantsColor)
{
	NaVariant var = pantsColor_;
	return std::move(var);
}

IMPL_PROPERTY_SETTER(DemoObject, pantsColor)
{
	pantsColor_ = std::get<std::wstring>(value);
	return NaResult::Success;
}

