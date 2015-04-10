# include "mainarea.hh"

Gui::MainArea::MainArea ( void )
   : QWidget ()
{
   buildGui ();
   connectAll ();
}

Gui::MainArea::~MainArea ( void )
{
}

void Gui::MainArea::buildGui ( void )
{
   mMainLayout = new QVBoxLayout ( this );
   setLayout ( mMainLayout );
   
   /*
    * Componentes de la fila de la URL del servicio
    */
   mWebUrlLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mWebUrlLayout );
   
   mWebUrlLabel = new QLabel ( "Web URL:" );
   mWebUrlLayout->addWidget ( mWebUrlLabel );
   
   mWebUrlLine = new QLineEdit ();
   mWebUrlLayout->addWidget ( mWebUrlLine );
   
   /*
    * Boton para el servicio de envío de información de datos de usuario.
    */
   
   mSendUserInfoLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mSendUserInfoLayout );
   
   mSendUserInfoButton = new QPushButton ( "Enviar info de usuario" );
   mSendUserInfoLayout->addStretch ();
   mSendUserInfoLayout->addWidget ( mSendUserInfoButton );
   mSendUserInfoLayout->addStretch ();
   
   /*
    * Configuración de componentes
    */
   
   mWebUrlLine->setEnabled ( false );
   mWebUrlLine->setText ( Base::Config::get ( "WebUrl" ) );
   
   return;
}

void Gui::MainArea::connectAll ( void )
{
   connect ( mSendUserInfoButton , SIGNAL ( clicked ( bool ) ) ,
             this                , SIGNAL ( sendUserInfo () ) );
   
   return;
}
