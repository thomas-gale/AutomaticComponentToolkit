(*++

Copyright (C) 2019 PrimeDevelopers

All rights reserved.

This file has been generated by the Automatic Component Toolkit (ACT) version 1.5.0.

Abstract: This is an autogenerated Pascal implementation file in order to allow easy
development of Prime Numbers Library. It needs to be generated only once.

Interface version: 1.2.0

*)

{$MODE DELPHI}
Unit libprimes_impl;

interface

uses
	libprimes_types,
	libprimes_exception,
	libprimes_interfaces,
	Classes,
	sysutils;

type
	TLibPrimesWrapper = class (TObject)
		public
			class procedure GetVersion(out AMajor: Cardinal; out AMinor: Cardinal; out AMicro: Cardinal);
			class function GetLastError(AInstance: TObject; out AErrorMessage: String): Boolean;
			class procedure ReleaseInstance(AInstance: TObject);
			class function CreateFactorizationCalculator(): TObject;
			class function CreateSieveCalculator(): TObject;
			class procedure SetJournal(const AFileName: String);
	end;


implementation

class procedure TLibPrimesWrapper.GetVersion(out AMajor: Cardinal; out AMinor: Cardinal; out AMicro: Cardinal);
begin
	raise ELibPrimesException.Create (LIBPRIMES_ERROR_NOTIMPLEMENTED);
end;

class function TLibPrimesWrapper.GetLastError(AInstance: TObject; out AErrorMessage: String): Boolean;
begin
	raise ELibPrimesException.Create (LIBPRIMES_ERROR_NOTIMPLEMENTED);
end;

class procedure TLibPrimesWrapper.ReleaseInstance(AInstance: TObject);
begin
	raise ELibPrimesException.Create (LIBPRIMES_ERROR_NOTIMPLEMENTED);
end;

class function TLibPrimesWrapper.CreateFactorizationCalculator(): TObject;
begin
	raise ELibPrimesException.Create (LIBPRIMES_ERROR_NOTIMPLEMENTED);
end;

class function TLibPrimesWrapper.CreateSieveCalculator(): TObject;
begin
	raise ELibPrimesException.Create (LIBPRIMES_ERROR_NOTIMPLEMENTED);
end;

class procedure TLibPrimesWrapper.SetJournal(const AFileName: String);
begin
	raise ELibPrimesException.Create (LIBPRIMES_ERROR_NOTIMPLEMENTED);
end;


end.
