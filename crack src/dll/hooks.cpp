#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "main.h"
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment( lib, "Ws2_32.lib" )

template< typename T >
T HookAPI( const wchar_t* dll, const char* func, void* newfunc )
{
	if( !GetModuleHandleW( dll ) )
	{
		speak( "[hook] Loading %ws", dll );
		if( !LoadLibraryW( dll ) )
		{
			speak( "[hook] Failed to load %ws", dll );
			return nullptr;
		}
	}

	void* ret = nullptr;

	const auto result = MH_CreateHookApi( dll, func, newfunc, ( LPVOID* )&ret );
	if( result != MH_OK )
	{
		speak( "[hook] Failed to create hook on [%ws / %s] -> [%s]", dll, func, MH_StatusToString( result ) );
		return nullptr;
	}

	return ( T )ret;
}

typedef int( WSAAPI* getaddrinfoFn )( PCSTR, PCSTR, const ADDRINFOA*, PADDRINFOA* );
getaddrinfoFn original_getaddrinfo;

int WSAAPI hooked_getaddrinfo( PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA* pHints, PADDRINFOA* ppResult )
{
	if( !pNodeName ) goto original;

	/*speak( "getaddrinfo call" );
	speak( "pNodeName -> [%s]", pNodeName );*/

	if( !strcmp( pNodeName, "deadcodehack.org" ) )
		return original_getaddrinfo( "localhost", pServiceName, pHints, ppResult );

original:
	return original_getaddrinfo( pNodeName, pServiceName, pHints, ppResult );
}

typedef hostent*( WSAAPI* gethostbynameFn )( const char* );
gethostbynameFn original_gethostbyname;

hostent* WSAAPI hooked_gethostbyname( const char* name )
{
	if( !name ) return original_gethostbyname( name );

	//speak( "gethostbyname call" );
	//speak( "[%s]", name );

	if( !strcmp( name, "api.ipify.org" ) )
		return original_gethostbyname( "localhost" );

	return original_gethostbyname( name );
}

typedef int( WSAAPI* GetAddrInfoExWFn )( PCWSTR, PCWSTR, DWORD, LPGUID, const ADDRINFOEXW*, PADDRINFOEXW*, timeval*, LPOVERLAPPED, LPLOOKUPSERVICE_COMPLETION_ROUTINE, LPHANDLE );
GetAddrInfoExWFn original_GetAddrInfoExW;

int WSAAPI hooked_GetAddrInfoExW( PCWSTR pName, PCWSTR pServiceName, DWORD dwNameSpace, LPGUID lpNspId, const ADDRINFOEXW* hints,
								  PADDRINFOEXW* ppResult, timeval* timeout, LPOVERLAPPED lpOverlapped,
								  LPLOOKUPSERVICE_COMPLETION_ROUTINE lpCompletionRoutine, LPHANDLE lpNameHandle )
{
	if( !pName ) goto original;

	/*speak( "GetAddrInfoExW call" );
	speak( "[%ws]", pName );*/

	if( !wcscmp( pName, L"deadcodehack.org" ) )
		return original_GetAddrInfoExW( L"localhost", pServiceName, dwNameSpace, lpNspId, hints, ppResult, timeout, lpOverlapped, lpCompletionRoutine, lpNameHandle );

original:
	return original_GetAddrInfoExW( pName, pServiceName, dwNameSpace, lpNspId, hints, ppResult, timeout, lpOverlapped, lpCompletionRoutine, lpNameHandle );
}

// gamehooks.cpp
bool HookJVM( );

bool Hook( )
{
	const auto init = MH_Initialize( );
	if( init != MH_OK )
	{
		speak( "[hook] Failed to initialize MinHook [%s]", MH_StatusToString( init ) );
		return false;
	}

	original_getaddrinfo = HookAPI< getaddrinfoFn >( L"ws2_32.dll", "getaddrinfo", hooked_getaddrinfo );
	if( !original_getaddrinfo ) return false;

	original_gethostbyname = HookAPI< gethostbynameFn >( L"ws2_32.dll", "gethostbyname", hooked_gethostbyname );
	if( !original_gethostbyname ) return false;

	original_GetAddrInfoExW = HookAPI< GetAddrInfoExWFn >( L"ws2_32.dll", "GetAddrInfoExW", hooked_GetAddrInfoExW );
	if( !original_GetAddrInfoExW ) return false;

	if( !HookJVM( ) ) return false;

	const auto enable = MH_EnableHook( MH_ALL_HOOKS );
	if( enable != MH_OK )
	{
		speak( "[hook] Failed to enable all hooks [%s]", MH_StatusToString( init ) );
		return false;
	}

	return true;
}
