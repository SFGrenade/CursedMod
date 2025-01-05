#include "../main.h"

#include <stdlib.h>
#include <string.h>

GApplication* application = nullptr;
GNotification* notification = nullptr;
GIcon* icon = nullptr;

bool Init() {
  openFile( true );
  printInFile( "Initializing library..." );

  application = g_application_new( "hollow.knight", G_APPLICATION_FLAGS_NONE );
  if( !g_application_register( application, NULL, NULL ) ) {
    printInFile( "Error registering GApplication!" );
    return false;
  }
  icon = g_themed_icon_new( "dialog-information" );

  if( _RegisterSignalCallbacks() <= 0 ) {
    printInFile( "Error registering signal callbacks!" );
    return false;
  }

  printInFile( "Library initialized!" );
  return true;
}

bool Deinit() {
  printInFile( "Deinitializing library..." );

  if( icon )
    g_object_unref( icon );
  if( notification )
    g_object_unref( notification );
  if( application )
    g_object_unref( application );

  closeFile();

  return true;
}

bool SetWindowDarkMode( const bool darkMode ) {
  printInFile( "SetWindowDarkMode(darkMode: %d) - Linux", darkMode );

  printInFile( "SetWindowDarkMode is unsupported on Linux" );

  return false;
}

bool SendShellNotification( char const* title, char const* message ) {
  printInFile( "SendShellNotification(title: '%s', message: '%s') - Linux", title, message );

  if( notification )
    g_object_unref( notification );
  notification = g_notification_new( title );
  g_notification_set_body( notification, message );
  g_notification_set_icon( notification, icon );
  g_application_send_notification( application, "message", notification );

  return true;
}

bool RemoveShellNotification() {
  printInFile( "RemoveShellNotification - Linux" );

  g_application_withdraw_notification( application, "message" );

  return true;
}

bool DoFunStuff() {
  printInFile( "DoFunStuff - Linux" );

  bool ret = true;

  char* currentDir = static_cast< char* >( calloc( MSG_SIZE * 2, sizeof( char ) ) );
  if( getcwd( currentDir, MSG_SIZE ) != nullptr ) {
    printInFile( "Current working dir: '%s'", currentDir );
    ret = true;
  } else {
    printInFile( "getcwd() error" );
    ret = false;
  }
  free( currentDir );

  return ret;
}
