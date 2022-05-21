#include "main.h"

void DeleteTempFiles( )
{
	if( std::filesystem::exists( "C:/DeadCode/Libs/State/1.bool" ) )
		std::filesystem::remove( "C:/DeadCode/Libs/State/1.bool" );

	if( std::filesystem::exists( "C:/DeadCode/Libs/State/n1.bool" ) )
		std::filesystem::remove( "C:/DeadCode/Libs/State/n1.bool" );
}

void CheckFolders( )
{
	wprintf( L"Проверка папок..." );

	std::vector< std::string > folderpaths;
	folderpaths.push_back( "C:/DeadCode/" );
	folderpaths.push_back( "C:/DeadCode/Libs/" );
	folderpaths.push_back( "C:/DeadCode/Libs/State/" );
	folderpaths.push_back( "C:/DeadCode/Libs/Images/" );
	folderpaths.push_back( "C:/DeadCode/Libs/Images/Background/" );
	folderpaths.push_back( "C:/DeadCode/Libs/Images/Other" );
	folderpaths.push_back( "C:/DeadCode/Libs/Images/Selected" );
	folderpaths.push_back( "C:/DeadCode/Libs/Images/Unselected" );
	folderpaths.push_back( "C:/DeadCode/Libs/Shaders/" );

	bool fail = false;
	for( auto folder : folderpaths )
	{
		if( !util::CheckCreateFolder( folder ) )
			fail = true;
	}

	if( !fail )
		util::PrintOk( );
}

void CheckFiles( )
{
	wprintf( L"Проверка файлов..." );

	std::vector< std::string > resources =
	{
		"C:/DeadCode/Libs/Images/Background/Combat.image",
		"C:/DeadCode/Libs/Images/Background/Configs.image",
		"C:/DeadCode/Libs/Images/Background/Console.image",
		"C:/DeadCode/Libs/Images/Background/Exploit.image",
		"C:/DeadCode/Libs/Images/Background/Friends.image",
		"C:/DeadCode/Libs/Images/Background/Movement.image",
		"C:/DeadCode/Libs/Images/Background/Other.image",
		"C:/DeadCode/Libs/Images/Background/Player.image",
		"C:/DeadCode/Libs/Images/Background/Render.image",
		"C:/DeadCode/Libs/Images/Background/World.image",

		"C:/DeadCode/Libs/Images/Other/Add.image",
		"C:/DeadCode/Libs/Images/Other/Arrows.image",
		"C:/DeadCode/Libs/Images/Other/Arrows2.image",
		"C:/DeadCode/Libs/Images/Other/Arrows-Run.image",
		"C:/DeadCode/Libs/Images/Other/Avatar.image",
		"C:/DeadCode/Libs/Images/Other/Avatar-Circle.image",
		"C:/DeadCode/Libs/Images/Other/Close.image",
		"C:/DeadCode/Libs/Images/Other/ComboBox-Arrow1.image",
		"C:/DeadCode/Libs/Images/Other/ComboBox-Arrow2.image",
		"C:/DeadCode/Libs/Images/Other/Delete.image",
		"C:/DeadCode/Libs/Images/Other/Friend.image",
		"C:/DeadCode/Libs/Images/Other/Grid.image",
		"C:/DeadCode/Libs/Images/Other/Load.image",
		"C:/DeadCode/Libs/Images/Other/Off.image",
		"C:/DeadCode/Libs/Images/Other/On.image",
		"C:/DeadCode/Libs/Images/Other/Profile-Style.image",
		"C:/DeadCode/Libs/Images/Other/Save.image",
		"C:/DeadCode/Libs/Images/Other/Search.image",
		"C:/DeadCode/Libs/Images/Other/Setting-Disabled.image",
		"C:/DeadCode/Libs/Images/Other/Setting-Enabled.image",

		"C:/DeadCode/Libs/Images/Selected/Combat.image",
		"C:/DeadCode/Libs/Images/Selected/Configs.image",
		"C:/DeadCode/Libs/Images/Selected/Console.image",
		"C:/DeadCode/Libs/Images/Selected/Exploit.image",
		"C:/DeadCode/Libs/Images/Selected/Friends.image",
		"C:/DeadCode/Libs/Images/Selected/Movement.image",
		"C:/DeadCode/Libs/Images/Selected/Other.image",
		"C:/DeadCode/Libs/Images/Selected/Player.image",
		"C:/DeadCode/Libs/Images/Selected/Render.image",
		"C:/DeadCode/Libs/Images/Selected/World.image",

		"C:/DeadCode/Libs/Images/Unselected/Combat.image",
		"C:/DeadCode/Libs/Images/Unselected/Configs.image",
		"C:/DeadCode/Libs/Images/Unselected/Console.image",
		"C:/DeadCode/Libs/Images/Unselected/Exploit.image",
		"C:/DeadCode/Libs/Images/Unselected/Friends.image",
		"C:/DeadCode/Libs/Images/Unselected/Movement.image",
		"C:/DeadCode/Libs/Images/Unselected/Other.image",
		"C:/DeadCode/Libs/Images/Unselected/Player.image",
		"C:/DeadCode/Libs/Images/Unselected/Render.image",
		"C:/DeadCode/Libs/Images/Unselected/World.image",

		"C:/DeadCode/Libs/Shaders/antirgb.shader",
		"C:/DeadCode/Libs/Shaders/glitch.shader",
		"C:/DeadCode/Libs/Shaders/round-rect.shader",
		"C:/DeadCode/Libs/Shaders/shadow.shader",

		"C:/DeadCode/Libs/c64.dll",
		"C:/DeadCode/Libs/d64.dll",
		"C:/DeadCode/Libs/e64.dll",
		"C:/DeadCode/Libs/l64.dll",

		"C:/DeadCode/Libs/libcrypto-1_1-x64.dll",
		"C:/DeadCode/Libs/libssl-1_1-x64.dll"
	};

	int i = 100;
	bool fail = false;
	for( auto res : resources )
	{
		i++;
		if( !util::CheckWriteResource( i, res ) )
			fail = true;
	}

	// особый случай
	if( !std::filesystem::exists( "C:/DeadCode/Libs/hook.dll" ) )
	{
		if( !fail )
		{
			util::PrintError( );
			fail = true;
		}

		wprintf( L"Копирую hook.dll из текущей папки в C:/DeadCode/Libs/hook.dll..." );

		if( !std::filesystem::copy_file( "hook.dll", "C:/DeadCode/Libs/hook.dll" ) )
		{
			util::PrintError( );
			system( "pause" );
			exit( 1 );
		}
		else
			util::PrintOk( );
	}

	if( !fail )
		util::PrintOk( );
	else
	{
		wprintf( L"Необходимые файлы были скопированы в C:/DeadCode, перезапустите кряк\n" );
		system( "pause" );
		exit( 1 );
	}

	Sleep( 1500 );
}

void CheckPorts( )
{
	wprintf( L"Проверка портов..." );

	const bool p80 = util::IsPortInUse( 80 );
	const bool p443 = util::IsPortInUse( 443 );

	if( !p80 && !p443 )
		util::PrintOk( );
	else
	{
		util::PrintError( );

		if( p80 )
			wprintf( L"Порт 80 занят, сервер эмулятор не сможет запуститься\n" );

		if( p443 )
			wprintf( L"Порт 443 занят, сервер эмулятор не сможет запуститься\n" );

		system( "pause" );
		exit( 1 );
	}
}

int main( )
{
	SetConsoleOutputCP( CP_UTF8 );
	SetConsoleCP( CP_UTF8 );
	setlocale( LC_ALL, "russian" );

	SetConsoleTitleW( L"DeadCode 3.5 crack loader (t.me/plutosolutions)" );

	wprintf( L"полная хуйня aka deadcodehack.org aka очередной чит который работает максимум на 5 серверах\ncracked by mrnv/ayywareseller\n%hs - %hs\n", __DATE__, __TIME__ );
	wprintf( L"mrnv:\n\tTelegram: t.me/ayywareseller\n\tGitHub: github.com/mr-nv\n" );
	wprintf( L"PlutoSolutions:\n\tTelegram: t.me/plutosolutions\n\tGitHub: github.com/PlutoSolutions\n" );
	wprintf( L"---------------------------------\n" );

	if( !std::filesystem::exists( "hook.dll" ) )
	{
		MessageBoxW( 0, L"hook.dll не был найден в папке с кряком\nПерекачайте кряк с t.me/plutosolutions или github.com/PlutoSolutions", L"deadcodecrack - error", MB_OK );
		exit( 1 );
	}
	
	CheckFolders( );
	DeleteTempFiles( );
	CheckFiles( );
	CheckPorts( );

	wprintf( L"Поиск процесса..." );
	DWORD id = 0;

	while( true )
	{
		id = util::GetProcessID( L"Minecraft 1.12.2", L"javaw.exe" );
		if( id > 0 )
		{
			util::PrintOk( );
			break;
		}

		Sleep( 1000 );
	}

	wprintf( L"ID процесса: %i\n", id );

	wprintf( L"Инжектим OpenSSL DLL..." );

	// не спрашивайте меня об этом, так надо
	for( int i = 0; i < 2; i++ )
	{
		util::Inject( id, "C:/DeadCode/Libs/libcrypto-1_1-x64.dll" );
		Sleep( 250 );
		util::Inject( id, "C:/DeadCode/Libs/libssl-1_1-x64.dll" );
		Sleep( 250 );
	}

	util::PrintOk( );

	wprintf( L"Инжектим первую DLL..." );

	if( !util::Inject( id, "C:/DeadCode/Libs/hook.dll" ) )
	{
		system( "pause" );
		exit( 1 );
	}
	else
		util::PrintOk( );

	wprintf( L"Ждем ответа..." );

	while( true )
	{
		const auto yes = std::filesystem::exists( "C:/DeadCode/Libs/State/1.bool" );
		const auto no = std::filesystem::exists( "C:/DeadCode/Libs/State/n1.bool" );

		if( yes || no )
		{
			if( yes && no )
			{
				util::PrintError( );
				wprintf( L"бля че бля сук\n" );
				exit( 1 );
			}

			if( yes && !no )
			{
				util::PrintOk( );
				break;
			}
			else if( !yes && no )
			{
				util::PrintError( );
				wprintf( L"Ошибка, посмотрите в логи игры\n" );
				system( "pause" );
				exit( 1 );
			}
		}

		Sleep( 1000 );
	}

	wprintf( L"Инжектим вторую DLL..." );
	if( util::Inject( id, "C:/DeadCode/Libs/c64.dll" ) )
		util::PrintOk( );

	wprintf( L"Это окно закроется через 10 секунд\n" );
	Sleep( 10000 );
	return 0;
}
