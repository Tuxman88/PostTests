# ifndef CONTROL_HH_
# define CONTROL_HH_

# include <QtCore/QByteArray>
# include <QtCore/QJsonDocument>
# include <QtCore/QJsonObject>
# include <QtCore/QList>
# include <QtCore/QMutex>
# include <QtCore/QMutexLocker>
# include <QtCore/QObject>
# include <QtCore/QTimer>

# include "../base/config.hh"
# include "../gui/dialogs/userinfoinput.hh"
# include "networkmanager.hh"

namespace Core
{
   class Control : public QObject
   {
      Q_OBJECT
      
      public:
         explicit Control ( void );
         virtual ~Control ( void );
         
      public slots:
         void sendUserInfo ( void );
         
      private:
         void prepareUserInfo ( QString& user_name , unsigned int user_age );
         void validateNetworkError ( void );
         void validateReceivedJson ( QByteArray& json_data );
                  
      private slots:
         void cleanUnusedComponents ( void );
         void networkResponseReady ( void );
         void userInfoReady ( unsigned int user_id );
         void userInfoCanceled ( unsigned int user_id );
         
      private:
         Core::NetworkManager* mNetworkManager;
         QList< Gui::Dialogs::UserInfoInput* > mUserInfoDialogs;
         QList< unsigned int > mUnusedInfoDialogs;
         QList< QByteArray > mJsonsSent;
         unsigned int mUserInfoDialogsCounter;
         QMutex mUserInfoDialogsMutex;
         QMutex mUnusedInfoDialogsMutex;
         QTimer mCleanUnusedComponentsTimer;
   };
}

# endif
