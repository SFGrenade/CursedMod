#include "../main.h"

#include <stdlib.h>
#include <string.h>

namespace MissingValues {
enum CUSTOM_DWMWINDOWATTRIBUTE : WORD {
  DWMWA_USE_HOSTBACKDROPBRUSH = 17,
  DWMA_USE_IMMERSIVE_DARKMODE_BEFORE20H1 = 19,
  DWMA_USE_IMMERSIVE_DARKMODE = 20,
  DWMWA_WINDOW_CORNER_PREFERENCE = 33,
  DWMWA_BORDER_COLOR,
  DWMWA_CAPTION_COLOR,
  DWMWA_TEXT_COLOR,
  DWMWA_VISIBLE_FRAME_BORDER_THICKNESS,
  DWMWA_SYSTEMBACKDROP_TYPE
};
}
HWND unityWindowHandle = 0;
NOTIFYICONDATAA notifyData;

bool Init() {
  openFile( true );
  printInFile( "Initializing library..." );

  unityWindowHandle = FindWindowA( "UnityWndClass", "Hollow Knight" );
  printInFile( "HWND: %d", unityWindowHandle );

  notifyData.cbSize = sizeof( notifyData );
  printInFile( "notifyData.cbSize: %d", notifyData.cbSize );
  notifyData.hWnd = unityWindowHandle;
  printInFile( "notifyData.hWnd: %d", notifyData.hWnd );
  notifyData.uID = 0;
  printInFile( "notifyData.uID: %d", notifyData.uID );
  notifyData.uTimeout = 30000;
  printInFile( "notifyData.uTimeout: %d", notifyData.uTimeout );
  notifyData.dwInfoFlags = NIIF_NONE;
  printInFile( "notifyData.dwInfoFlags: %d", notifyData.dwInfoFlags );
  notifyData.uFlags = NIF_INFO;
  printInFile( "notifyData.uFlags: %d", notifyData.uFlags );

  if( _RegisterSignalCallbacks() <= 0 ) {
    printInFile( "Error registering signal callbacks!" );
    return false;
  }

  printInFile( "Library initialized!" );
  return true;
}

bool Deinit() {
  printInFile( "Deinitializing library..." );

  closeFile();

  return true;
}

bool SetWindowDarkMode( const bool darkMode ) {
  printInFile( "SetWindowDarkMode(darkMode: %d) - Windows", darkMode );

  printInFile( "Set window theme..." );
  COLORREF themeColor = darkMode ? 0x00505050 : 0x00FFFFFF;
  BOOL useDarkMode = darkMode;
  bool immersiveDarkModeResult = S_OK
                                 == DwmSetWindowAttribute( unityWindowHandle,
                                                           MissingValues::CUSTOM_DWMWINDOWATTRIBUTE::DWMA_USE_IMMERSIVE_DARKMODE,
                                                           &useDarkMode,
                                                           sizeof( useDarkMode ) );
  bool immersiveDarkMode20h1Result = S_OK
                                     == DwmSetWindowAttribute( unityWindowHandle,
                                                               MissingValues::CUSTOM_DWMWINDOWATTRIBUTE::DWMA_USE_IMMERSIVE_DARKMODE_BEFORE20H1,
                                                               &useDarkMode,
                                                               sizeof( useDarkMode ) );
  bool borderColorResult
      = S_OK == DwmSetWindowAttribute( unityWindowHandle, MissingValues::CUSTOM_DWMWINDOWATTRIBUTE::DWMWA_BORDER_COLOR, &themeColor, sizeof( themeColor ) );
  bool captionColorResult
      = S_OK == DwmSetWindowAttribute( unityWindowHandle, MissingValues::CUSTOM_DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR, &themeColor, sizeof( themeColor ) );
  printInFile( "DwmSetWindowAttribute returned %d %d %d %d", immersiveDarkModeResult, immersiveDarkMode20h1Result, borderColorResult, captionColorResult );
  bool windowThemeResult = S_OK == SetWindowTheme( unityWindowHandle, L"Explorer", NULL );
  printInFile( "windowThemeResult returned %d", windowThemeResult );
  bool dwmColorChangedResult = S_OK != SendNotifyMessageA( unityWindowHandle, WM_DWMCOLORIZATIONCOLORCHANGED, themeColor, 0 );
  printInFile( "dwmColorChangedResult returned %d", dwmColorChangedResult );
  tagRECT windowRect;
  GetWindowRect( unityWindowHandle, static_cast< LPRECT >( &windowRect ) );
  printInFile( "Got window rect: (%d, %d, %d, %d)", windowRect.top, windowRect.left, windowRect.right, windowRect.bottom );
  tagRECT adjustedRect;
  adjustedRect.top = 0;
  adjustedRect.left = 0;
  adjustedRect.right = windowRect.right - windowRect.left;
  adjustedRect.bottom = windowRect.bottom - windowRect.top;
  BOOL setPosResult = SetWindowPos( unityWindowHandle,
                                    HWND_BOTTOM,
                                    adjustedRect.top,
                                    adjustedRect.left,
                                    adjustedRect.right - 1,
                                    adjustedRect.bottom,
                                    SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER );
  SetWindowPos( unityWindowHandle,
                HWND_TOPMOST,
                adjustedRect.top,
                adjustedRect.left,
                adjustedRect.right,
                adjustedRect.bottom,
                SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER );
  printInFile( "SetWindowPos returned %d", setPosResult );
  return immersiveDarkModeResult || immersiveDarkMode20h1Result || borderColorResult || captionColorResult || windowThemeResult || dwmColorChangedResult;
}

bool SendShellNotification( char const* title, char const* message ) {
  printInFile( "SendShellNotification(title: '%ls', message: '%ls') - Windows", title, message );

  memset( notifyData.szInfo, 0, sizeof( notifyData.szInfo ) );
  sprintf( notifyData.szInfo, "%s", message );
  printInFile( "notifyData.szInfo: '%s'", notifyData.szInfo );
  memset( notifyData.szInfoTitle, 0, sizeof( notifyData.szInfoTitle ) );
  sprintf( notifyData.szInfoTitle, "%s", title );
  printInFile( "notifyData.szInfoTitle: '%s'", notifyData.szInfoTitle );
  bool notifyAddResult = Shell_NotifyIconA( NIM_ADD, &notifyData );
  printInFile( "notifyAddResult: %d", notifyAddResult );
  if( !notifyAddResult ) {
    RemoveShellNotification();
    notifyAddResult = Shell_NotifyIconA( NIM_ADD, &notifyData );
    printInFile( "notifyAddResult: %d", notifyAddResult );
  }
  return notifyAddResult;
}

bool RemoveShellNotification() {
  printInFile( "RemoveShellNotification - Windows" );

  bool notifyDeleteResult = Shell_NotifyIconA( NIM_DELETE, &notifyData );
  printInFile( "notifyDeleteResult: %d", notifyDeleteResult );
  return notifyDeleteResult;
}

bool DoFunStuff() {
  printInFile( "DoFunStuff - Windows" );

  bool ret = true;

  char* currentDir = static_cast< char* >( calloc( MSG_SIZE, sizeof( char ) ) );
  if( GetCurrentDirectoryA( MSG_SIZE, currentDir ) != 0 ) {
    printInFile( "Current working dir: '%s'", currentDir );
    ret = true;
  } else {
    printInFile( "GetCurrentDirectory() error" );
    ret = false;
  }
  free( currentDir );

  return ret;
}
