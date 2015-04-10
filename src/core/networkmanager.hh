# ifndef NETWORKMANAGER_HH_
# define NETWORKMANAGER_HH_

# include <QtCore/QByteArray>
# include <QtCore/QObject>
# include <QtCore/QQueue>
# include <QtCore/QUrl>
# include <QtCore/QUrlQuery>
# include <QtNetwork/QNetworkAccessManager>
# include <QtNetwork/QNetworkReply>
# include <QtNetwork/QNetworkRequest>

# include "../base/config.hh"

namespace Core
{
   class NetworkManager : public QObject
   {
      Q_OBJECT
      
      public:
         explicit NetworkManager ( void );
         virtual ~NetworkManager ( void );
         
         void sendToServer ( QByteArray& data_to_send );
         QByteArray getNextResponse ( void );
         QNetworkReply::NetworkError getErrorFound ( void );
         
      signals:
         void responseReady ( void );
         
      private slots:
         void readResponse ( QNetworkReply* response );
         
      private:
         QNetworkAccessManager* mAccessManager;
         QUrl* mWebUrl;
         QQueue< QByteArray > mResponsesQueue;
         QQueue< QNetworkReply::NetworkError > mErrorFoundQueue;
   };
}

# endif
