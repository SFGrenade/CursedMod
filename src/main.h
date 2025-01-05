#ifndef CURSEDMODNATIVE_MAIN_H_
#define CURSEDMODNATIVE_MAIN_H_

#include "common.h"

void _SignalCallback( const int sigNum );
int _RegisterSignalCallbacks();

#if defined( CM_Windows )
#include <dwmapi.h>
#include <windows.h>
extern HWND unityWindowHandle;
extern NOTIFYICONDATA notifyData;
#elif defined( CM_MacOS )
#include <unistd.h>
#elif defined( CM_Linux )
#include <gio/gio.h>
#include <unistd.h>
extern GApplication *application;
extern GNotification *notification;
extern GIcon *icon;
#endif

extern "C" EXPORT bool Init();
extern "C" EXPORT bool Deinit();
extern "C" EXPORT bool SetWindowDarkMode( const bool darkMode );
extern "C" EXPORT bool SendShellNotification( char const *title, char const *message );
extern "C" EXPORT bool RemoveShellNotification();
extern "C" EXPORT bool DoFunStuff();

#endif  // CURSEDMODNATIVE_MAIN_H_
