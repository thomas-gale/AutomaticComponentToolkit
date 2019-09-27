/*++

Copyright (C) 2019 Special Numbers developers

All rights reserved.

This file has been generated by the Automatic Component Toolkit (ACT) version 1.7.0-develop.

Abstract: This is an autogenerated C++ application that demonstrates the
 usage of the Dynamic C++ bindings of Special Numbers library

Interface version: 1.0.0

*/

#include <iostream>
#include "special_dynamic.hpp"


int main()
{
	try
	{
		// TODO: put the location of the Special-library file here.
		std::string libpath = ("D:/PUBLIC/AutomaticComponentToolkit/Examples/Injection/Special_component/Implementations/Cpp/build/Debug");
		auto wrapper = Special::CWrapper::loadLibrary(libpath + "/special.dll"); // TODO: add correct suffix of the library
		Special_uint32 nMajor, nMinor, nMicro;
		wrapper->GetVersion(nMajor, nMinor, nMicro);
		std::cout << "Special.Version = " << nMajor << "." << nMinor << "." << nMicro;
		std::cout << std::endl;

		auto pSpecialVariable = wrapper->CreateSpecialVariable(1.0);
		pSpecialVariable->SetValue(10.25);
		double val = pSpecialVariable->GetValue();
		Special_int64 iVal = pSpecialVariable->GetSpecialValue();

		// Upcast: (this should go in some function); note that this does not require the binary Numbers-Component but only the header.
		NumbersExtendedHandle sNumbersHandle;
		sNumbersHandle.m_hHandle = pSpecialVariable->GetHandle().m_hHandle;
		sNumbersHandle.m_pFunctionTable = (Numbers_FunctionTableBase*)pSpecialVariable->GetHandle().m_pFunctionTable;

		Numbers::CVariable* pVariable = new Numbers::CVariable(nullptr, sNumbersHandle);
		// For all client-purposes, pVariable is an instance of CVariable EXCEPT when one would pass CVariable as in-parameter to the Numbers component.
		// In particular we can pase pVariable into a third component (e.g. Calcuation) TODO

		double dBaseVal = pVariable->GetValue(); // this DOES NOT call a base class implementation but still the implementation of Special::SpecialVariable
		// one can get this behaviour by implementing a "has-a"-relationship inside the implementation of Special::SpecialVariable
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
