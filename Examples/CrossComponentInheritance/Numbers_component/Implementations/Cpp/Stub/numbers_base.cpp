/*++

Copyright (C) 2019 Numbers developers

All rights reserved.

Abstract: This is a stub class definition of CBase

*/

#include "numbers_base.hpp"
#include "numbers_interfaceexception.hpp"

// Include custom headers here.


using namespace Numbers::Impl;

/*************************************************************************************************************************
 Class definition of CBase 
**************************************************************************************************************************/

void CBase::ClearErrorMessages()
{
	m_pErrors.reset();
}

void CBase::RegisterErrorMessage(const std::string & sErrorMessage)
{
	if (!m_pErrors) {
		m_pErrors.reset(new std::list<std::string>());
	}
	m_pErrors->clear();
	m_pErrors->push_back(sErrorMessage);
}

Numbers_pvoid CBase::GetSymbolLookupMethod()
{
	return m_ExtendedHandle.m_pfnSymbolLookupMethod;
}

void CBase::ReleaseInstance()
{
	m_nReferenceCount--;
	if (!m_nReferenceCount) {
		delete this;
	}
}

void CBase::AcquireInstance()
{
	++m_nReferenceCount;
}

void CBase::GetVersion(Numbers_uint32 & nMajor, Numbers_uint32 & nMinor, Numbers_uint32 & nMicro)
{
	nMajor = NUMBERS_VERSION_MAJOR;
	nMinor = NUMBERS_VERSION_MINOR;
	nMicro = NUMBERS_VERSION_MICRO;
}

bool CBase::GetLastError(std::string & sErrorMessage)
{
	if (m_pErrors && !m_pErrors->empty()) {
		sErrorMessage = m_pErrors->back();
		return true;
	} else {
		sErrorMessage = "";
		return false;
	}
}

