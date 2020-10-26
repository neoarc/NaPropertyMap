#include <iostream>

#include "DemoObject.h"

using namespace std;

int main()
{
	DemoObject a;
	a.name_ = L"ObjA";

	// Getter
	{
		auto varNameA = a.GetProperty("name");
		auto nameA = std::get<std::wstring>(varNameA);
		wcout << L"[Getter] a.name: " << nameA.c_str() << L"\n";
	}

	// Setter
	{
		a.SetProperty("name", (std::wstring)L"ObjA-Modified");
		wcout << L"[Setter] a.name: " << a.name_.c_str() << L"\n";

		auto varNameA = a.GetProperty("name");
		auto nameA = std::get<std::wstring>(varNameA);
		wcout << L"[Getter] a.name: " << nameA.c_str() << L"\n";
	}

	// Fin.
	cout << "Enter any number to exit.\n";
	int dummy;
	cin >> dummy;

	return 0;
}
