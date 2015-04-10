# include "control.hh"

Core::Control::Control ( void )
   : QObject ()
{
   mUserInfoDialogsCounter = 0;
   
   connect ( &mCleanUnusedComponentsTimer , SIGNAL ( timeout () ) ,
             this                         , SLOT ( cleanUnusedComponents () ) );
   
   mCleanUnusedComponentsTimer.start ( 1000 );
   
   mNetworkManager = new Core::NetworkManager ();
   
   connect ( mNetworkManager , SIGNAL ( responseReady () ) , this , SLOT ( networkResponseReady () ) );
}

Core::Control::~Control ( void )
{
   delete mNetworkManager;
}

void Core::Control::validateNetworkError ( void )
{
   switch ( mNetworkManager->getErrorFound () )
   {
      case QNetworkReply::NoError:
         qDebug () << "NoError";
         break;
      case QNetworkReply::ConnectionRefusedError:
         qDebug () << "ConnectionRefusedError";
         break;
      case QNetworkReply::RemoteHostClosedError:
         qDebug () << "RemoteHostClosedError";
         break;
      case QNetworkReply::HostNotFoundError:
         qDebug () << "HostNotFoundError";
         break;
      case QNetworkReply::TimeoutError:
         qDebug () << "TimeoutError";
         break;
      case QNetworkReply::OperationCanceledError:
         qDebug () << "OperationCanceledError";
         break;
      case QNetworkReply::SslHandshakeFailedError:
         qDebug () << "SslHandshakeFailedError";
         break;
      case QNetworkReply::TemporaryNetworkFailureError:
         qDebug () << "TemporaryNetworkFailureError";
         break;
      case QNetworkReply::NetworkSessionFailedError:
         qDebug () << "NetworkSessionFailedError";
         break;
      case QNetworkReply::BackgroundRequestNotAllowedError:
         qDebug () << "BackgroundRequestNotAllowedError";
         break;
      case QNetworkReply::ProxyConnectionRefusedError:
         qDebug () << "ProxyConnectionRefusedError";
         break;
      case QNetworkReply::ProxyConnectionClosedError:
         qDebug () << "ProxyConnectionClosedError";
         break;
      case QNetworkReply::ProxyNotFoundError:
         qDebug () << "ProxyNotFoundError";
         break;
      case QNetworkReply::ProxyTimeoutError:
         qDebug () << "ProxyTimeoutError";
         break;
      case QNetworkReply::ProxyAuthenticationRequiredError:
         qDebug () << "ProxyAuthenticationRequiredError";
         break;
      case QNetworkReply::ContentAccessDenied:
         qDebug () << "ContentAccessDenied";
         break;
      case QNetworkReply::ContentOperationNotPermittedError:
         qDebug () << "ContentOperationNotPermittedError";
         break;
      case QNetworkReply::ContentNotFoundError:
         qDebug () << "ContentNotFoundError";
         break;
      case QNetworkReply::AuthenticationRequiredError:
         qDebug () << "AuthenticationRequiredError";
         break;
      case QNetworkReply::ContentReSendError:
         qDebug () << "ContentReSendError";
         break;
      case QNetworkReply::ContentConflictError:
         qDebug () << "ContentConflictError";
         break;
      case QNetworkReply::ContentGoneError:
         qDebug () << "ContentGoneError";
         break;
      case QNetworkReply::InternalServerError:
         qDebug () << "InternalServerError";
         break;
      case QNetworkReply::OperationNotImplementedError:
         qDebug () << "OperationNotImplementedError";
         break;
      case QNetworkReply::ServiceUnavailableError:
         qDebug () << "ServiceUnavailableError";
         break;
      case QNetworkReply::ProtocolUnknownError:
         qDebug () << "ProtocolUnknownError";
         break;
      case QNetworkReply::ProtocolInvalidOperationError:
         qDebug () << "ProtocolInvalidOperationError";
         break;
      case QNetworkReply::UnknownNetworkError:
         qDebug () << "UnknownNetworkError";
         break;
      case QNetworkReply::UnknownProxyError:
         qDebug () << "UnknownProxyError";
         break;
      case QNetworkReply::UnknownContentError:
         qDebug () << "UnknownContentError";
         break;
      case QNetworkReply::ProtocolFailure:
         qDebug () << "ProtocolFailure";
         break;
      case QNetworkReply::UnknownServerError:
         qDebug () << "UnknownServerError";
         break;
   }
   
   return;
}

void Core::Control::networkResponseReady ( void )
{
   QByteArray next_response = mNetworkManager->getNextResponse ();
   
   qDebug () << "Server response: " << next_response;
   
   QJsonDocument document;
   document = QJsonDocument::fromJson ( next_response );
   
   QJsonObject main_object;
   main_object = document.object ();
   
   QStringList main_keys;
   main_keys = main_object.keys ();
   
   if ( main_object.isEmpty () )
   {
      qDebug () << "Main object is empty";
      
      validateNetworkError ();
      
      return;
   }
   
   bool final_status = false;
   QByteArray data_bytes;
   
   for ( int i = 0; i < main_keys.size (); i++ )
   {
      if ( main_keys[ i ] == "status" )
      {
         QJsonValue status_value;
         status_value = main_object.value ( "status" );
         
         if ( status_value.isBool () )
         {
            final_status = status_value.toBool ();
         }
         else
            qDebug () << "Status value is not Bool";
      }
      else if ( main_keys[ i ] == "data" )
      {
         QJsonValue data_value;
         data_value = main_object.value ( "data" );
         
         if ( !data_value.isObject () )
         {
            qDebug () << "Data object is not an object";
            continue;
         }
         
         QJsonObject data_object;
         data_object = data_value.toObject ();
         
         QJsonDocument data_document ( data_object );
         data_bytes = data_document.toJson ( QJsonDocument::Compact );
      }
      else
         qDebug () << "UNknown key: " << main_keys[ i ];
   }
   
   qDebug () << "Status: " << final_status;
   qDebug () << "Data bytes: " << data_bytes;
   
   validateReceivedJson ( data_bytes );
   
   return;
}

void Core::Control::validateReceivedJson ( QByteArray& json_data )
{
   qDebug () << "Validating received info: " << json_data;
   
   return;
}

void Core::Control::sendUserInfo ( void )
{
   Gui::Dialogs::UserInfoInput* user_info_dialog;
   user_info_dialog = new Gui::Dialogs::UserInfoInput ( mUserInfoDialogsCounter );
   
   connect ( user_info_dialog , SIGNAL ( infoReady ( unsigned int ) ) , 
             this             , SLOT ( userInfoReady ( unsigned int ) ) );
   
   connect ( user_info_dialog , SIGNAL ( infoCanceled ( unsigned int ) ) , 
             this             , SLOT ( userInfoCanceled ( unsigned int ) ) );
   
   mUserInfoDialogsCounter++;
   
   user_info_dialog->show ();
   
   QMutexLocker locker ( &mUserInfoDialogsMutex );
   mUserInfoDialogs.append ( user_info_dialog );
   
   return;
}

void Core::Control::userInfoCanceled ( unsigned int user_id )
{
   QMutexLocker locker ( &mUnusedInfoDialogsMutex );
   mUnusedInfoDialogs.append ( user_id );
   
   return;
}

void Core::Control::userInfoReady ( unsigned int user_id )
{
   // Busco sobre la lista de dialogos de solicitud para extraer la información
   bool dialog_found = false;
   
   QMutexLocker locker ( &mUserInfoDialogsMutex );
   
   for ( int i = 0; i < mUserInfoDialogs.size () && !dialog_found; i++ )
   {
      if ( mUserInfoDialogs[ i ]->getUserId () == user_id )
      {
         QString user_name;
         unsigned int user_age;
         
         user_name = mUserInfoDialogs[ i ]->getUserName ();
         user_age = mUserInfoDialogs[ i ]->getUserAge ();
         
         prepareUserInfo ( user_name , user_age );
         
         dialog_found = true;
         
         QMutexLocker locker2 ( &mUnusedInfoDialogsMutex );
         mUnusedInfoDialogs.append ( user_id );
      }
   }
   
   if ( !dialog_found )
      qDebug () << "Logic error";
   
   return;
}

void Core::Control::cleanUnusedComponents ( void )
{   
   QMutexLocker active_locker ( &mUserInfoDialogsMutex );
   QMutexLocker unused_locker ( &mUnusedInfoDialogsMutex );
   
   for ( int i = 0; i < mUnusedInfoDialogs.size (); i++ )
   {
      bool dialog_found = false;
      
      for ( int j = 0; j < mUserInfoDialogs.size () && !dialog_found; j++ )
      {
         if ( mUserInfoDialogs[ j ]->getUserId () == mUnusedInfoDialogs[ i ] )
         {
            delete mUserInfoDialogs[ j ];
            mUserInfoDialogs[ j ] = 0;
            mUserInfoDialogs.removeAt ( j );
            
            dialog_found = true;
         }
      }
      
      if ( !dialog_found )
         qDebug () << "Dialog " << mUnusedInfoDialogs[ i ] << " not found";
      else
      {
         mUnusedInfoDialogs.removeAt ( i );
         i = 0;
      }
   }
   
   return;
}

void Core::Control::prepareUserInfo ( QString& user_name, unsigned int user_age )
{   
   QJsonObject main_object;
   QJsonObject employee_info;
   
   employee_info.insert ( "nombre" , QJsonValue::fromVariant ( user_name ) );
   employee_info.insert ( "edad" , QJsonValue::fromVariant ( user_age ) );
   
   main_object.insert ( "empleado" , employee_info );
   
   QJsonDocument document ( main_object );
   
   QByteArray json_data = document.toJson ( QJsonDocument::Compact );
   
   qDebug () << "Json created: " << json_data;
   mJsonsSent.append ( json_data );
   mNetworkManager->sendToServer ( json_data );
   
   return;
}
