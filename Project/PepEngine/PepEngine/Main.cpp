#include "PepEnginePCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine.h"

int main(int, char* []) {
	pep::Engine pepEngine;
	pepEngine.Run();
	return 0;
}