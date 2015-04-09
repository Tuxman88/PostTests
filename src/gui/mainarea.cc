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
   
   mLabelsLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mLabelsLayout );
   
   mButtonsLayout = new QHBoxLayout ();
   mMainLayout->addLayout ( mButtonsLayout );
   
   mWebUrlLabel = new QLabel ( "Web URL:" );
   mLabelsLayout->addWidget ( mWebUrlLabel );
   
   mWebUrlLine = new QLineEdit ();
   mLabelsLayout->addWidget ( mWebUrlLine );
   
   mConnectButton = new QPushButton ( "Conectar" );
   mButtonsLayout->addStretch ();
   mButtonsLayout->addWidget ( mConnectButton );
   mButtonsLayout->addStretch ();
   
   mWebUrlLine->setEnabled ( false );
   mWebUrlLine->setText ( Base::Config::get ( "WebUrl" ) );
   
   return;
}

void Gui::MainArea::connectAll ( void )
{
   connect ( mConnectButton , SIGNAL ( clicked ( bool ) ) ,
             this           , SLOT ( sendMessage () ) );
   
   return;
}

void Gui::MainArea::sendMessage(void)
{
   Core::Control::tryToConnect ();
   
   return;
}
