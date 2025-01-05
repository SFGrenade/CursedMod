#ifndef CURSEDMODNATIVE_MAIN_H_
#define CURSEDMODNATIVE_MAIN_H_

#include "common.h"

void _SignalCallback( const int sigNum );
int _RegisterSignalCallbacks();

#if defined( CM_Windows )
#include <Windows.h>
#include <dwmapi.h>
extern HWND unityWindowHandle;
extern NOTIFYICONDATAA notifyData;
#elif defined( CM_MacOS )
#include <unistd.h>
#elif defined( CM_Linux )
#include <gio/gio.h>
#include <unistd.h>
extern GApplication *application;
extern GNotification *notification;
extern GIcon *icon;
#endif

extern "C" {
EXPORT bool Init();
EXPORT bool Deinit();
EXPORT bool SetWindowDarkMode( const bool darkMode );
EXPORT bool SendShellNotification( char const *title, char const *message );
EXPORT bool RemoveShellNotification();
EXPORT bool DoFunStuff();
}

#endif  // CURSEDMODNATIVE_MAIN_H_
