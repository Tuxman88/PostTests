# ifndef USERINFOINPUT_HH_
# define USERINFOINPUT_HH_

# include <QtCore/QDebug>
# include <QtWidgets/QHBoxLayout>
# include <QtWidgets/QLabel>
# include <QtWidgets/QLineEdit>
# include <QtWidgets/QPushButton>
# include <QtWidgets/QSpinBox>
# include <QtWidgets/QWidget>
# include <QtWidgets/QVBoxLayout>

namespace Gui
{
   namespace Dialogs
   {
      class UserInfoInput : public QWidget
      {
         Q_OBJECT
         
         public:
            explicit UserInfoInput ( unsigned int user_id );
            virtual ~UserInfoInput ( void );
            
            unsigned int getUserId ( void );
            
            QString getUserName ( void );
            unsigned int getUserAge ( void );
            
         signals:
            void infoReady ( unsigned int );
            void infoCanceled ( unsigned int );
            
         private:
            void buildGui ( void );
            void connectAll ( void );
            
         private slots:
            void validateInfo ( void );
            void cancelInfo ( void );
            
         private:
            unsigned int mUserId;
            
            QVBoxLayout* mMainLayout;
            QHBoxLayout* mUserNameLayout;
            QHBoxLayout* mUserAgeLayout;
            QHBoxLayout* mAcceptInfoLayout;
            
            QLabel* mUserNameLabel;
            QLabel* mUserAgeLabel;
            
            QLineEdit* mUserNameLine;
            QSpinBox* mUserAgeSpin;
            
            QPushButton* mCancelInfoButton;
            QPushButton* mAcceptInfoButton;
      };
   }
}

# endif
