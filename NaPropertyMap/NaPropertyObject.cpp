#include "NaPropertyObject.h"

NaVariant NaPropertyObjectBase::GetProperty(std::wstring name)
{
	auto propMap = GetPropertyMap();
	auto it = propMap->find(name);
	if (it != propMap->end())
	{
		auto &getter = it->second.getter_;
		auto result = (this->*getter)();
		return result;
	}
	return nullptr;
}

int NaPropertyObjectBase::SetProperty(std::wstring name, NaVariant value)
{
	auto propMap = GetPropertyMap();
	auto it = propMap->find(name);
	if (it != propMap->end())
	{
		auto &setter = it->second.setter_;
		auto result = (this->*setter)(value);
		return result;
	}
	return 0;
}