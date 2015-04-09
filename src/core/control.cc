# include "control.hh"

Core::Control::Control ( void )
   : QObject ()
{
   mNetworkManager = new QNetworkAccessManager ( this );
   connect ( mNetworkManager , SIGNAL ( finished ( QNetworkReply* ) ) ,
             this            , SLOT ( readResponse ( QNetworkReply* ) ) );
   mWebUrl = new QUrl ( Base::Config::get ( "WebUrl" ) );
}

Core::Control::~Control ( void )
{
   delete mNetworkManager;
   delete mWebUrl;
}

QByteArray& Core::Control::getLatestResponse ( void )
{   
   return ( Core::Control::instance ()->mLatestResponse );
}

Core::Control* Core::Control::instance ( void )
{
   static Core::Control myself;
   
   return ( &myself );
}

void Core::Control::readResponse ( QNetworkReply* response )
{
   qDebug () << "Control: Leyendo informacion llegada";
   
   qDebug () << "Info: " << response->readAll ();
   
   qDebug () << "Info2: " << mNetworkReply->readAll ();
   
   emit ( responseReady () );
   
   switch ( mNetworkReply->error () )
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

void Core::Control::tryToConnect ( void )
{
   qDebug () << "Intentando conectar y enviar datos";
   Core::Control* myself = Core::Control::instance ();
   
   QByteArray jsonString = "{\"empleado\":{\"nombre\":\"Moises Chavez\",\"edad\":27}}";
   QByteArray postDataSize = QByteArray::number(jsonString.size());

   QNetworkRequest request( *(myself->mWebUrl) );
   request.setRawHeader("User-Agent", "MoisesTest1");
   request.setRawHeader("X-Custom-User-Agent", "MoisesTest1");
   request.setRawHeader("Content-Type", "application/json");
   request.setRawHeader("Content-Length", postDataSize);

   myself->mNetworkReply = myself->mNetworkManager->post ( request , jsonString );
   
   /*QByteArray post_information;
   
   post_information = "{empleado:{nombre:'Moises Chavez',edad:27}}";
   //post_information = "test";
   
   myself->mNetworkReply = myself->mNetworkManager->post ( QNetworkRequest ( *(myself->mWebUrl) ) , post_information );
   
   QUrlQuery post_data;
   post_data.addQueryItem ( "parameter", "teststring");
   
   QNetworkRequest request ( *(myself->mWebUrl) );
   request.setHeader ( QNetworkRequest::ContentTypeHeader , 
                       "application/x-www-form-urlencoded" );

   myself->mNetworkReply = myself->mNetworkManager->post ( request , post_data.toString ( QUrl::FullyEncoded ).toUtf8 () );*/
   
   return;
}
