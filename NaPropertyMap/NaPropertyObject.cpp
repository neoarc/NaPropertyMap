#include "NaPropertyObject.h"

NaPropertyGroupBuilder::NaPropertyGroupBuilder(std::initializer_list<NaPropertyInfo> data)
{
	operator=(data);
}

NaPropertyGroupBuilder& NaPropertyGroupBuilder::operator=(std::initializer_list<NaPropertyInfo> data)
{
	map_.clear();
	
	std::wstring lastGroup = L"";
	for (auto &it : data)
	{
		auto &name = it.name_;
		auto &info = it;

		// #TODO improve group handling
		std::wstring groupName = lastGroup;
		if (groupName.empty() || !info.group_.empty() || info.vt_ == VT_EMPTY)
			lastGroup = groupName = info.group_;
		if (info.vt_ == VT_EMPTY)
			continue;

		NaPropertyInfo infoClone = info;
		infoClone.group_ = groupName;
		map_.insert(std::make_pair(name, std::move(infoClone)));
	}
	return *this;
}

NaPropertyGroupBuilder::operator NaPropertyMap() const
{
	return std::move(map_);
}

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

NaResult NaPropertyObjectBase::SetProperty(std::wstring name, NaVariant value)
{
	auto propMap = GetPropertyMap();
	auto it = propMap->find(name);
	if (it != propMap->end())
	{
		auto &setter = it->second.setter_;
		if (setter == nullptr)
			return NaResult::ReadOnly;
		auto result = (this->*setter)(value);
		return result;
	}
	return NaResult::Success;
}

