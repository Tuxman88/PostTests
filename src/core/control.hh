# ifndef CONTROL_HH_
# define CONTROL_HH_

# include <QtCore/QByteArray>
# include <QtCore/QObject>
# include <QtCore/QUrl>
# include <QtCore/QUrlQuery>
# include <QtNetwork/QNetworkAccessManager>
# include <QtNetwork/QNetworkReply>
# include <QtNetwork/QNetworkRequest>

# include "../base/config.hh"

namespace Core
{
   class Control : public QObject
   {
      Q_OBJECT
      
      public:
         explicit Control ( void );
         virtual ~Control ( void );
         
         static Core::Control* instance ( void );
         
         static void tryToConnect ( void );
         
         static QByteArray& getLatestResponse ( void );
         
      signals:
         void responseReady ( void );
         
      private slots:
         void readResponse ( QNetworkReply* response );
         
      private:
         QByteArray mLatestResponse;
         QUrl* mWebUrl;
         QNetworkAccessManager* mNetworkManager;
         QNetworkReply* mNetworkReply;
   };
}

# endif
