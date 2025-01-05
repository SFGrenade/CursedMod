#include "common.h"

FILE *logFile = nullptr;

void openFile( bool truncate ) {
  char const *openMode = "a";
  if( truncate ) {
    openMode = "w";
  }
  if( logFile == nullptr ) {
    logFile = fopen( "CursedMod-Native.log", openMode );
  }
}
void closeFile() {
  if( logFile != nullptr ) {
    fclose( logFile );
    logFile = nullptr;
  }
}
void printInFile( char const *msg ) {
  if( logFile != nullptr ) {
    fprintf( logFile, "%s", msg );
    fprintf( logFile, "\n" );
    fflush( logFile );
  }
}

#if defined( CM_Windows )
extern BOOL WINAPI DllMain( HINSTANCE const, DWORD const callReason, LPVOID const ) {
  switch( callReason ) {
    case DLL_PROCESS_ATTACH:
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
// extern BOOL WINAPI _DllMainCRTStartup( HINSTANCE const dllModHandle, DWORD const callReason, LPVOID const reserved ) {
//   return DllMain( dllModHandle, callReason, reserved );
// }
#endif
