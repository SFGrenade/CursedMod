#include "../main.h"

#include <stdlib.h>
#include <string.h>

bool Init() {
  openFile( true );
  printInFile( "Initializing library..." );

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
  printInFile( "SetWindowDarkMode(darkMode: %d) - MacOS", darkMode );

  printInFile( "SetWindowDarkMode is unsupported on MacOS" );

  return false;
}

bool SendShellNotification( char const* title, char const* message ) {
  printInFile( "SendShellNotification(title: '%s', message: '%s') - MacOS", title, message );

  printInFile( "SendShellNotification is unsupported on MacOS" );

  return false;
}

bool RemoveShellNotification() {
  printInFile( "RemoveShellNotification - MacOS" );

  printInFile( "RemoveShellNotification is unsupported on MacOS" );

  return false;
}

bool DoFunStuff() {
  printInFile( "DoFunStuff - MacOS" );

  printInFile( "DoFunStuff is unsupported on MacOS" );

  return false;
}
