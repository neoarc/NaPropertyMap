#include <iostream>

#include "DemoObject.h"

using namespace std;

int main()
{
	DemoObject a;
	a.name_ = L"ObjA";

	auto propMap = a.GetPropertyMap();
	for (auto &propIt : *propMap)
	{
		auto &propInfo = propIt.second;
		wcout << L"[Prop] " << propInfo.name_.c_str() << L"\n";
	}
	
	// Getter
	{
		auto varNameA = a.GetProperty(L"name");
		auto nameA = std::get<std::wstring>(varNameA);
		wcout << L"[Getter] a.name: " << nameA.c_str() << L"\n";
	}

	// Setter
	{
		a.SetProperty(L"name", (std::wstring)L"ObjA-Modified");
		wcout << L"[Setter] a.name: " << a.name_.c_str() << L"\n";

		auto varNameA = a.GetProperty(L"name");
		auto nameA = std::get<std::wstring>(varNameA);
		wcout << L"[Getter] a.name: " << nameA.c_str() << L"\n";
	}

	// Fin.
	cout << "Enter any number to exit.\n";
	int dummy;
	cin >> dummy;

	return 0;
}
