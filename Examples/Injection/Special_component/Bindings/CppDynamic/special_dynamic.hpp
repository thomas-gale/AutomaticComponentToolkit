/*++

Copyright (C) 2019 Special Numbers developers

All rights reserved.

This file has been generated by the Automatic Component Toolkit (ACT) version 1.7.0-develop.

Abstract: This is an autogenerated C++-Header file in order to allow an easy
 use of Special Numbers library

Interface version: 1.0.0

*/

#ifndef __SPECIAL_CPPHEADER_DYNAMIC_CPP
#define __SPECIAL_CPPHEADER_DYNAMIC_CPP

#include "special_types.hpp"
#include "special_dynamic.h"

#include "numbers_dynamic.hpp"

#ifdef _WIN32
#include <windows.h>
#else // _WIN32
#include <dlfcn.h>
#endif // _WIN32
#include <string>
#include <memory>
#include <vector>
#include <exception>

namespace Special {

/*************************************************************************************************************************
 Forward Declaration of all classes
**************************************************************************************************************************/
class CWrapper;
class CBase;
class CSpecialVariable;

/*************************************************************************************************************************
 Declaration of deprecated class types
**************************************************************************************************************************/
typedef CWrapper CSpecialWrapper;
typedef CBase CSpecialBase;
typedef CSpecialVariable CSpecialSpecialVariable;

/*************************************************************************************************************************
 Declaration of shared pointer types
**************************************************************************************************************************/
typedef std::shared_ptr<CWrapper> PWrapper;
typedef std::shared_ptr<CBase> PBase;
typedef std::shared_ptr<CSpecialVariable> PSpecialVariable;

/*************************************************************************************************************************
 Declaration of deprecated shared pointer types
**************************************************************************************************************************/
typedef PWrapper PSpecialWrapper;
typedef PBase PSpecialBase;
typedef PSpecialVariable PSpecialSpecialVariable;


/*************************************************************************************************************************
 Class ESpecialException 
**************************************************************************************************************************/
class ESpecialException : public std::exception {
protected:
	/**
	* Error code for the Exception.
	*/
	SpecialResult m_errorCode;
	/**
	* Error message for the Exception.
	*/
	std::string m_errorMessage;

public:
	/**
	* Exception Constructor.
	*/
	ESpecialException(SpecialResult errorCode, const std::string & sErrorMessage)
		: m_errorMessage("Special Error " + std::to_string(errorCode) + " (" + sErrorMessage + ")")
	{
		m_errorCode = errorCode;
	}

	/**
	* Returns error code
	*/
	SpecialResult getErrorCode() const noexcept
	{
		return m_errorCode;
	}

	/**
	* Returns error message
	*/
	const char* what() const noexcept
	{
		return m_errorMessage.c_str();
	}

};

/*************************************************************************************************************************
 Class CInputVector
**************************************************************************************************************************/
template <typename T>
class CInputVector {
private:
	
	const T* m_data;
	size_t m_size;
	
public:
	
	CInputVector( const std::vector<T>& vec)
		: m_data( vec.data() ), m_size( vec.size() )
	{
	}
	
	CInputVector( const T* in_data, size_t in_size)
		: m_data( in_data ), m_size(in_size )
	{
	}
	
	const T* data() const
	{
		return m_data;
	}
	
	size_t size() const
	{
		return m_size;
	}
	
};

// declare deprecated class name
template<typename T>
using CSpecialInputVector = CInputVector<T>;

/*************************************************************************************************************************
 Class CWrapper 
**************************************************************************************************************************/
class CWrapper {
public:
	
	CWrapper(void* pSymbolLookupMethod)
	{
		CheckError(nullptr, initWrapperTable(&m_WrapperTable));
		CheckError(nullptr, loadWrapperTableFromSymbolLookupMethod(&m_WrapperTable, pSymbolLookupMethod));
		
		CheckError(nullptr, checkBinaryVersion());
	}
	
	CWrapper(const std::string &sFileName)
	{
		CheckError(nullptr, initWrapperTable(&m_WrapperTable));
		CheckError(nullptr, loadWrapperTable(&m_WrapperTable, sFileName.c_str()));
		
		CheckError(nullptr, checkBinaryVersion());
	}
	
	static PWrapper loadLibrary(const std::string &sFileName)
	{
		return std::make_shared<CWrapper>(sFileName);
	}
	
	static PWrapper loadLibraryFromSymbolLookupMethod(void* pSymbolLookupMethod)
	{
		return std::make_shared<CWrapper>(pSymbolLookupMethod);
	}
	
	~CWrapper()
	{
		releaseWrapperTable(&m_WrapperTable);
	}
	
	inline void CheckError(CBase * pBaseClass, SpecialResult nResult);

	inline PSpecialVariable CreateSpecialVariable(const Special_double dInitialValue);
	inline void GetVersion(Special_uint32 & nMajor, Special_uint32 & nMinor, Special_uint32 & nMicro);
	inline bool GetLastError(CBase * pInstance, std::string & sErrorMessage);
	inline void ReleaseInstance(CBase * pInstance);
	inline void AcquireInstance(CBase * pInstance);
	inline Special_pvoid GetSymbolLookupMethod();

private:
	sSpecialDynamicWrapperTable m_WrapperTable;
	// Injected Components
	Numbers::PWrapper m_pNumbersWrapper;

	
	SpecialResult checkBinaryVersion()
	{
		Special_uint32 nMajor, nMinor, nMicro;
		GetVersion(nMajor, nMinor, nMicro);
		if ( (nMajor != SPECIAL_VERSION_MAJOR) || (nMinor < SPECIAL_VERSION_MINOR) ) {
			return SPECIAL_ERROR_INCOMPATIBLEBINARYVERSION;
		}
		return SPECIAL_SUCCESS;
	}
	SpecialResult initWrapperTable(sSpecialDynamicWrapperTable * pWrapperTable);
	SpecialResult releaseWrapperTable(sSpecialDynamicWrapperTable * pWrapperTable);
	SpecialResult loadWrapperTable(sSpecialDynamicWrapperTable * pWrapperTable, const char * pLibraryFileName);
	SpecialResult loadWrapperTableFromSymbolLookupMethod(sSpecialDynamicWrapperTable * pWrapperTable, void* pSymbolLookupMethod);

	friend class CBase;
	friend class CSpecialVariable;

};

	
/*************************************************************************************************************************
 Class CBase 
**************************************************************************************************************************/
class CBase {
private:
	Special_FunctionTableBase m_sFunctionTableBase;
public:
	
protected:
	/* Wrapper Object that created the class. */
	CWrapper * m_pWrapper;
	/* Handle to Instance in library*/
	SpecialExtendedHandle m_pHandle;

	/* Checks for an Error code and raises Exceptions */
	void CheckError(SpecialResult nResult)
	{
		if (m_pWrapper != nullptr)
			m_pWrapper->CheckError(this, nResult);
	}
public:
	/**
	* CBase::CBase - Constructor for Base class.
	*/
	CBase(CWrapper * pWrapper, SpecialExtendedHandle pHandle)
		: m_pWrapper(pWrapper), m_pHandle(pHandle)
	{
	}

	/**
	* CBase::~CBase - Destructor for Base class.
	*/
	virtual ~CBase()
	{
		if (m_pWrapper != nullptr)
			m_pWrapper->ReleaseInstance(this);
		m_pWrapper = nullptr;
	}

	/**
	* CBase::GetHandle - Returns handle to instance.
	*/
	SpecialExtendedHandle GetHandle()
	{
		return m_pHandle;
	}
	
	friend class CWrapper;
};
	
/*************************************************************************************************************************
 Class CSpecialVariable 
**************************************************************************************************************************/
class CSpecialVariable : public CBase {
private:
	sSpecialFunctionTableSpecialVariable m_sFunctionTableSpecialVariable;
	// this is not nice yet, as the base class has its own WrapperTable
public:
	
	/**
	* CSpecialVariable::CSpecialVariable - Constructor for SpecialVariable class.
	*/
	CSpecialVariable(CWrapper* pWrapper, SpecialExtendedHandle pHandle)
		: CBase(pWrapper, pHandle)
	{
		Special_FunctionTableSpecialVariable* pVariableWrapperTable = (Special_FunctionTableSpecialVariable*)pHandle.m_pFunctionTable;
		m_sFunctionTableSpecialVariable.m_AcquireInstance = (PSpecialAcquireInstancePtr)pVariableWrapperTable->m_pfnAcquireOwnership;
		m_sFunctionTableSpecialVariable.m_ReleaseInstance = (PSpecialReleaseInstancePtr)pVariableWrapperTable->m_pfnReleaseOwnership;
		m_sFunctionTableSpecialVariable.m_GetLastError = (PSpecialGetLastErrorPtr)pVariableWrapperTable->m_pfnAcquireOwnership;

		m_sFunctionTableSpecialVariable.m_Variable_GetValue = (PSpecialSpecialVariable_GetValuePtr)pVariableWrapperTable->m_pfnGetValue;
		m_sFunctionTableSpecialVariable.m_Variable_SetValue = (PSpecialSpecialVariable_SetValuePtr)pVariableWrapperTable->m_pfnSetValue;
		m_sFunctionTableSpecialVariable.m_SpecialVariable_GetSpecialValue = (PSpecialSpecialVariable_GetSpecialValuePtr)pVariableWrapperTable->m_pfnGetSpecialValue;
	}
	
	inline Numbers_double GetValue();
	inline void SetValue(const Numbers_double dValue);
	inline Special_int64 GetSpecialValue();
};
	
	/**
	* CWrapper::CreateSpecialVariable - Creates a new Variable instance
	* @param[in] dInitialValue - Initial value of the new SpecialVariable
	* @return New SpecialVariable instance
	*/
	inline PSpecialVariable CWrapper::CreateSpecialVariable(const Special_double dInitialValue)
	{
		SpecialExtendedHandle hInstance;
		CheckError(nullptr,m_WrapperTable.m_CreateSpecialVariable(dInitialValue, &hInstance));
		
		if (!hInstance.m_hHandle) {
			CheckError(nullptr,SPECIAL_ERROR_INVALIDPARAM);
		}
		return std::make_shared<CSpecialVariable>(this, hInstance);
	}
	
	/**
	* CWrapper::GetVersion - retrieves the binary version of this library.
	* @param[out] nMajor - returns the major version of this library
	* @param[out] nMinor - returns the minor version of this library
	* @param[out] nMicro - returns the micro version of this library
	*/
	inline void CWrapper::GetVersion(Special_uint32 & nMajor, Special_uint32 & nMinor, Special_uint32 & nMicro)
	{
		CheckError(nullptr,m_WrapperTable.m_GetVersion(&nMajor, &nMinor, &nMicro));
	}
	
	/**
	* CWrapper::GetLastError - Returns the last error recorded on this object
	* @param[in] pInstance - Instance Handle
	* @param[out] sErrorMessage - Message of the last error
	* @return Is there a last error to query
	*/
	inline bool CWrapper::GetLastError(CBase * pInstance, std::string & sErrorMessage)
	{
		SpecialExtendedHandle hInstance;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		Special_uint32 bytesNeededErrorMessage = 0;
		Special_uint32 bytesWrittenErrorMessage = 0;
		bool resultHasError = 0;
		CheckError(nullptr,m_WrapperTable.m_GetLastError(hInstance, 0, &bytesNeededErrorMessage, nullptr, &resultHasError));
		std::vector<char> bufferErrorMessage(bytesNeededErrorMessage);
		CheckError(nullptr,m_WrapperTable.m_GetLastError(hInstance, bytesNeededErrorMessage, &bytesWrittenErrorMessage, &bufferErrorMessage[0], &resultHasError));
		sErrorMessage = std::string(&bufferErrorMessage[0]);
		
		return resultHasError;
	}
	
	/**
	* CWrapper::ReleaseInstance - Releases shared ownership of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	inline void CWrapper::ReleaseInstance(CBase * pInstance)
	{
		SpecialExtendedHandle hInstance;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		CheckError(nullptr,m_WrapperTable.m_ReleaseInstance(hInstance));
	}
	
	/**
	* CWrapper::AcquireInstance - Acquires shared ownership of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	inline void CWrapper::AcquireInstance(CBase * pInstance)
	{
		SpecialExtendedHandle hInstance;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		CheckError(nullptr,m_WrapperTable.m_AcquireInstance(hInstance));
	}
	
	/**
	* CWrapper::GetSymbolLookupMethod - Returns the address of the SymbolLookupMethod
	* @return Address of the SymbolAddressMethod
	*/
	inline Special_pvoid CWrapper::GetSymbolLookupMethod()
	{
		Special_pvoid resultSymbolLookupMethod = 0;
		CheckError(nullptr,m_WrapperTable.m_GetSymbolLookupMethod(&resultSymbolLookupMethod));
		
		return resultSymbolLookupMethod;
	}
	
	inline void CWrapper::CheckError(CBase * pBaseClass, SpecialResult nResult)
	{
		if (nResult != 0) {
			std::string sErrorMessage;
			if (pBaseClass != nullptr) {
				GetLastError(pBaseClass, sErrorMessage);
			}
			throw ESpecialException(nResult, sErrorMessage);
		}
	}
	

	inline SpecialResult CWrapper::initWrapperTable(sSpecialDynamicWrapperTable * pWrapperTable)
	{
		if (pWrapperTable == nullptr)
			return SPECIAL_ERROR_INVALIDPARAM;
		
		pWrapperTable->m_LibraryHandle = nullptr;
		pWrapperTable->m_SpecialVariable_GetSpecialValue = nullptr;
		pWrapperTable->m_CreateSpecialVariable = nullptr;
		pWrapperTable->m_GetVersion = nullptr;
		pWrapperTable->m_GetLastError = nullptr;
		pWrapperTable->m_ReleaseInstance = nullptr;
		pWrapperTable->m_AcquireInstance = nullptr;
		pWrapperTable->m_GetSymbolLookupMethod = nullptr;
		
		return SPECIAL_SUCCESS;
	}

	inline SpecialResult CWrapper::releaseWrapperTable(sSpecialDynamicWrapperTable * pWrapperTable)
	{
		if (pWrapperTable == nullptr)
			return SPECIAL_ERROR_INVALIDPARAM;
		
		if (pWrapperTable->m_LibraryHandle != nullptr) {
		#ifdef _WIN32
			HMODULE hModule = (HMODULE) pWrapperTable->m_LibraryHandle;
			FreeLibrary(hModule);
		#else // _WIN32
			dlclose(pWrapperTable->m_LibraryHandle);
		#endif // _WIN32
			return initWrapperTable(pWrapperTable);
		}
		
		return SPECIAL_SUCCESS;
	}

	inline SpecialResult CWrapper::loadWrapperTable(sSpecialDynamicWrapperTable * pWrapperTable, const char * pLibraryFileName)
	{
		if (pWrapperTable == nullptr)
			return SPECIAL_ERROR_INVALIDPARAM;
		if (pLibraryFileName == nullptr)
			return SPECIAL_ERROR_INVALIDPARAM;
		
		#ifdef _WIN32
		// Convert filename to UTF16-string
		int nLength = (int)strlen(pLibraryFileName);
		int nBufferSize = nLength * 2 + 2;
		std::vector<wchar_t> wsLibraryFileName(nBufferSize);
		int nResult = MultiByteToWideChar(CP_UTF8, 0, pLibraryFileName, nLength, &wsLibraryFileName[0], nBufferSize);
		if (nResult == 0)
			return SPECIAL_ERROR_COULDNOTLOADLIBRARY;
		
		HMODULE hLibrary = LoadLibraryW(wsLibraryFileName.data());
		if (hLibrary == 0) 
			return SPECIAL_ERROR_COULDNOTLOADLIBRARY;
		#else // _WIN32
		void* hLibrary = dlopen(pLibraryFileName, RTLD_LAZY);
		if (hLibrary == 0) 
			return SPECIAL_ERROR_COULDNOTLOADLIBRARY;
		dlerror();
		#endif // _WIN32
		
		#ifdef _WIN32
		pWrapperTable->m_SpecialVariable_GetSpecialValue = (PSpecialSpecialVariable_GetSpecialValuePtr) GetProcAddress(hLibrary, "special_specialvariable_getspecialvalue");
		#else // _WIN32
		pWrapperTable->m_SpecialVariable_GetSpecialValue = (PSpecialSpecialVariable_GetSpecialValuePtr) dlsym(hLibrary, "special_specialvariable_getspecialvalue");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_SpecialVariable_GetSpecialValue == nullptr)
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_CreateSpecialVariable = (PSpecialCreateSpecialVariablePtr) GetProcAddress(hLibrary, "special_createspecialvariable");
		#else // _WIN32
		pWrapperTable->m_CreateSpecialVariable = (PSpecialCreateSpecialVariablePtr) dlsym(hLibrary, "special_createspecialvariable");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_CreateSpecialVariable == nullptr)
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetVersion = (PSpecialGetVersionPtr) GetProcAddress(hLibrary, "special_getversion");
		#else // _WIN32
		pWrapperTable->m_GetVersion = (PSpecialGetVersionPtr) dlsym(hLibrary, "special_getversion");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetVersion == nullptr)
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetLastError = (PSpecialGetLastErrorPtr) GetProcAddress(hLibrary, "special_getlasterror");
		#else // _WIN32
		pWrapperTable->m_GetLastError = (PSpecialGetLastErrorPtr) dlsym(hLibrary, "special_getlasterror");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetLastError == nullptr)
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_ReleaseInstance = (PSpecialReleaseInstancePtr) GetProcAddress(hLibrary, "special_releaseinstance");
		#else // _WIN32
		pWrapperTable->m_ReleaseInstance = (PSpecialReleaseInstancePtr) dlsym(hLibrary, "special_releaseinstance");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_ReleaseInstance == nullptr)
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_AcquireInstance = (PSpecialAcquireInstancePtr) GetProcAddress(hLibrary, "special_acquireinstance");
		#else // _WIN32
		pWrapperTable->m_AcquireInstance = (PSpecialAcquireInstancePtr) dlsym(hLibrary, "special_acquireinstance");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_AcquireInstance == nullptr)
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetSymbolLookupMethod = (PSpecialGetSymbolLookupMethodPtr) GetProcAddress(hLibrary, "special_getsymbollookupmethod");
		#else // _WIN32
		pWrapperTable->m_GetSymbolLookupMethod = (PSpecialGetSymbolLookupMethodPtr) dlsym(hLibrary, "special_getsymbollookupmethod");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetSymbolLookupMethod == nullptr)
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		pWrapperTable->m_LibraryHandle = hLibrary;
		return SPECIAL_SUCCESS;
	}

	inline SpecialResult CWrapper::loadWrapperTableFromSymbolLookupMethod(sSpecialDynamicWrapperTable * pWrapperTable, void* pSymbolLookupMethod)
{
		if (pWrapperTable == nullptr)
			return SPECIAL_ERROR_INVALIDPARAM;
		if (pSymbolLookupMethod == nullptr)
			return SPECIAL_ERROR_INVALIDPARAM;
		
		typedef SpecialResult(*SymbolLookupType)(const char*, void**);
		
		SymbolLookupType pLookup = (SymbolLookupType)pSymbolLookupMethod;
		
		SpecialResult eLookupError = SPECIAL_SUCCESS;
		eLookupError = (*pLookup)("special_specialvariable_getspecialvalue", (void**)&(pWrapperTable->m_SpecialVariable_GetSpecialValue));
		if ( (eLookupError != 0) || (pWrapperTable->m_SpecialVariable_GetSpecialValue == nullptr) )
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("special_createspecialvariable", (void**)&(pWrapperTable->m_CreateSpecialVariable));
		if ( (eLookupError != 0) || (pWrapperTable->m_CreateSpecialVariable == nullptr) )
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("special_getversion", (void**)&(pWrapperTable->m_GetVersion));
		if ( (eLookupError != 0) || (pWrapperTable->m_GetVersion == nullptr) )
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("special_getlasterror", (void**)&(pWrapperTable->m_GetLastError));
		if ( (eLookupError != 0) || (pWrapperTable->m_GetLastError == nullptr) )
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("special_releaseinstance", (void**)&(pWrapperTable->m_ReleaseInstance));
		if ( (eLookupError != 0) || (pWrapperTable->m_ReleaseInstance == nullptr) )
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("special_acquireinstance", (void**)&(pWrapperTable->m_AcquireInstance));
		if ( (eLookupError != 0) || (pWrapperTable->m_AcquireInstance == nullptr) )
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		eLookupError = (*pLookup)("special_getsymbollookupmethod", (void**)&(pWrapperTable->m_GetSymbolLookupMethod));
		if ( (eLookupError != 0) || (pWrapperTable->m_GetSymbolLookupMethod == nullptr) )
			return SPECIAL_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		return SPECIAL_SUCCESS;
}

	
	
	/**
	 * Method definitions for class CBase
	 */
	
	/**
	 * Method definitions for class CSpecialVariable
	 */
	
	Numbers_double CSpecialVariable::GetValue()
	{
		Numbers_double resultValue = 0;

		// CheckError(m_pWrapper->m_WrapperTable.m_Variable_GetValue(m_pHandle, &resultValue));
		CheckError(m_sFunctionTableSpecialVariable.m_Variable_GetValue(m_pHandle, &resultValue));

		return resultValue;
	}

	/**
	* CVariable::SetValue - Set the numerical value of this Variable
	* @param[in] dValue - The new value of this Variable
	*/
	void CSpecialVariable::SetValue(const Numbers_double dValue)
	{
		// CheckError(m_pWrapper->m_WrapperTable.m_Variable_SetValue(m_pHandle, dValue));
		CheckError(m_sFunctionTableSpecialVariable.m_Variable_SetValue(m_pHandle, dValue));
	}

	/**
	* CSpecialVariable::GetSpecialValue - Returns the current value of this Variable as integer. i.e. it rounds
	* @return The current value of this Variable
	*/
	Special_int64 CSpecialVariable::GetSpecialValue()
	{
		Special_int64 resultValue = 0;
		CheckError(m_pWrapper->m_WrapperTable.m_SpecialVariable_GetSpecialValue(m_pHandle, &resultValue));
		
		return resultValue;
	}

} // namespace Special

#endif // __SPECIAL_CPPHEADER_DYNAMIC_CPP
