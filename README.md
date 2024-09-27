# NaPropertyMap

`NaPropertyMap`은 C++로 작성된 Property Map 구현체로, 다양한 속성을 그룹화하여 관리할 수 있는 유연한 라이브러리입니다. 
이 라이브러리는 객체의 속성을 손쉽게 정의하고, 값을 가져오거나 설정할 수 있는 기능을 제공합니다.

# 주요 기능

- 속성을 그룹화하여 관리할 수 있는 Property Map
- 문자열, 정수, 실수 등 다양한 타입의 속성 지원
- 직관적인 Getter와 Setter 매크로를 통해 코드 간소화

# 활용 방안

- 클래스 객체의 속성 목록을 얻어 Property Grid와 같은에 표시하고 편집
- 클래스의 속성값들을 공통 인터페이스를 통해 파일로 저장하거나 파일에서 복원

# 사용 방법

사용 방법은 프로젝트 내의 `DemoObject.cpp`와 `DemoObject.h`, `NaPropertyMap.cpp`를 확인하면 어렵지 않게 파악할 수 있습니다.

## 클래스 정의/구현

```cpp
// DemoObject.h

#pragma once

#include "NaPropertyObject.h"

class DemoObject : public NaPropertyObjectBase
{
public:
    std::wstring name_;

private:
    int age_;
    float weight_;
    std::wstring shirtsColor_;
    std::wstring pantsColor_;
    
public:
    DECL_PROPERTY_MAP(DemoObject);
    DECL_PROP(name);
    DECL_PROP(age);
    DECL_PROP(weight);
    DECL_PROP(shirtsColor);
    DECL_PROP(pantsColor);
};
```

```cpp
// DemoObject.cpp

#include "DemoObject.h"

// Property Map 구현 부분
BEGIN_IMPL_PROPERTY_MAP(DemoObject)
    PROP_GROUP(personality, "Personality")
        PROP_STR(name, "")
        PROP_INT(age, 0)
        PROP_FLOAT(weight, 60.0f)
    PROP_GROUP(clothColor, "Cloth Color")
        PROP_STR(shirtsColor, "black")
        PROP_STR(pantsColor, "blue")
END_IMPL_PROPERTY_MAP(DemoObject)

// 각 속성의 Getter 및 Setter 구현

// name
IMPL_PROPERTY_GETTER(DemoObject, name) {
    NaVariant var = name_;
    return std::move(var);
}

IMPL_PROPERTY_SETTER(DemoObject, name) {
    name_ = std::get<std::wstring>(value);
    return NaResult::Success;
}

// age
IMPL_PROPERTY_GETTER(DemoObject, age) {
    NaVariant var = age_;
    return std::move(var);
}

IMPL_PROPERTY_SETTER(DemoObject, age) {
    age_ = std::get<int>(value);
    return NaResult::Success;
}

// 나머지 속성에 대해서도 비슷한 방식으로 Getter/Setter를 정의합니다.
```

## PropertyMap을 가진 클래스의 활용

```cpp
#include <iostream>

#include "DemoObject.h"

using namespace std;

int main()
{
	DemoObject a;
	a.name_ = L"ObjA";

  // a instance의 속성맵에 접근하여 갖고 있는 속성들을 나열합니다.
	auto propMap = a.GetPropertyMap();
	for (auto &[propName, propInfo] : *propMap)
	{
		wcout << L"[Prop] " << propInfo.name_.c_str() << L"\n";
	}
	
	// a instance의 속성중 "name"의 값을 읽습니다.
	{
		auto varNameA = a.GetProperty(L"name");
		auto nameA = std::get<std::wstring>(varNameA);
		wcout << L"[Getter] a.name: " << nameA.c_str() << L"\n";
	}

	// a instance의 속성중 "name"의 값을 변경합니다.
	{
		a.SetProperty(L"name", (std::wstring)L"ObjA-Modified");
		wcout << L"[Setter] a.name: " << a.name_.c_str() << L"\n";

		auto varNameA = a.GetProperty(L"name");
		auto nameA = std::get<std::wstring>(varNameA);
		wcout << L"[Getter] a.name: " << nameA.c_str() << L"\n";
	}

	return 0;
}
```

# 그 외

PropertyMap을 가진 객체를 PropertyGrid에 출력하는 코드도 이미 구현되었으나 이 프로젝트에는 포함되지 않았습니다.
요청이 있을 경우 데모와 함께 포함하도록 하겠습니다.

# 라이선스

이 프로젝트는 MIT 라이선스 하에 배포됩니다. 
- 자유롭게 사용 가능 (개인적, 상업적)
- 변경 및 배포 가능 (단, 배포시 원출처 정보를 포함해야함)
- 이 코드에 대한 보증이 없고 사용에 따른 책임은 사용자에게 있음
