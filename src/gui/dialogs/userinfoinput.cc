# include "userinfoinput.hh"

Gui::Dialogs::UserInfoInput::UserInfoInput ( unsigned int user_id )
   : QWidget ()
{
   mUserId = user_id;
   
   buildGui ();
   connectAll ();
}

Gui::Dialogs::UserInfoInput::~UserInfoInput ( void )
{
}

void Gui::Dialogs::UserInfoInput::buildGui ( void )
{
   mMainLayout = new QVBoxLayout ( this );
   setLayout ( mMainLayout );
   
   mUserNameLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mUserNameLayout );
   
   mUserAgeLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mUserAgeLayout );
   
   mAcceptInfoLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mAcceptInfoLayout );
   
   mUserNameLabel = new QLabel ( "Nombre:" );
   mUserNameLayout->addWidget ( mUserNameLabel );
   
   mUserNameLine = new QLineEdit ();
   mUserNameLayout->addWidget ( mUserNameLine );
   
   mUserAgeLabel = new QLabel ( "Edad:" );
   mUserAgeLayout->addWidget ( mUserAgeLabel );
   
   mUserAgeSpin = new QSpinBox ();
   mUserAgeLayout->addWidget ( mUserAgeSpin );
   
   mCancelInfoButton = new QPushButton ( "Cancelar" );
   mAcceptInfoLayout->addWidget ( mCancelInfoButton );
   
   mAcceptInfoLayout->addStretch ();
   
   mAcceptInfoButton = new QPushButton ( "Aceptar" );
   mAcceptInfoLayout->addWidget ( mAcceptInfoButton );
   
   mUserAgeSpin->setMinimum ( 0 );
   mUserAgeSpin->setMaximum ( 200 );
   
   return;
}

void Gui::Dialogs::UserInfoInput::connectAll ( void )
{
   connect ( mAcceptInfoButton , SIGNAL ( clicked ( bool ) ) ,
             this              , SLOT ( validateInfo () ) );
   
   connect ( mCancelInfoButton , SIGNAL ( clicked ( bool ) ) ,
             this              , SLOT ( cancelInfo () ) );
   
   return;
}

unsigned int Gui::Dialogs::UserInfoInput::getUserId ( void )
{
   return ( mUserId );
}

void Gui::Dialogs::UserInfoInput::cancelInfo ( void )
{
   setVisible ( false );
   
   emit ( infoCanceled ( mUserId ) );
   
   return;
}

void Gui::Dialogs::UserInfoInput::validateInfo ( void )
{
   if ( mUserNameLine->text ().isEmpty () )
   {
      qDebug () << "No valido";
      
      return;
   }
   
   setVisible ( false );
   
   emit ( infoReady ( mUserId ) );
   
   return;
}

unsigned int Gui::Dialogs::UserInfoInput::getUserAge ( void )
{
   return ( mUserAgeSpin->value () );
}

QString Gui::Dialogs::UserInfoInput::getUserName ( void )
{
   return ( mUserNameLine->text () );
}
