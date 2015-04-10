# include "networkmanager.hh"

Core::NetworkManager::NetworkManager ( void )
   : QObject ()
{
   mAccessManager = new QNetworkAccessManager ( this );
   
   connect ( mAccessManager , SIGNAL ( finished ( QNetworkReply* ) ) ,
             this           , SLOT ( readResponse ( QNetworkReply* ) ) );
   
   mWebUrl = new QUrl ( Base::Config::get ( "WebUrl" ) );
}

Core::NetworkManager::~NetworkManager ( void )
{
   delete mAccessManager;
   delete mWebUrl;
}

void Core::NetworkManager::sendToServer ( QByteArray& data_to_send )
{
   QByteArray post_data_size = QByteArray::number ( data_to_send.size () );

   QNetworkRequest request( *(mWebUrl) );
   
   request.setRawHeader ( "User-Agent"          , "MoisesTest1" );
   request.setRawHeader ( "X-Custom-User-Agent" , "MoisesTest1" );
   request.setRawHeader ( "Content-Type"        , "application/json" );
   request.setRawHeader ( "Content-Length"      , post_data_size );

   mAccessManager->post ( request , data_to_send );
   
   return;
}

QByteArray Core::NetworkManager::getNextResponse ( void )
{
   return ( mResponsesQueue.dequeue () );
}

void Core::NetworkManager::readResponse ( QNetworkReply* response )
{
   mErrorFoundQueue.enqueue ( response->error () );
   mResponsesQueue.enqueue ( response->readAll () );
   
   emit ( responseReady () );
   
   return;
}

QNetworkReply::NetworkError Core::NetworkManager::getErrorFound ( void )
{
   return ( mErrorFoundQueue.dequeue () );
}
