# include "mainwindow.hh"

Gui::MainWindow::MainWindow ( void )
   : QMainWindow ()
{
   buildGui ();
   connectAll ();
}

Gui::MainWindow::~MainWindow ( void )
{
}

void Gui::MainWindow::buildGui ( void )
{
   mMainArea = new Gui::MainArea ();
   
   setCentralWidget ( mMainArea );
   
   return;
}

void Gui::MainWindow::connectAll ( void )
{
   connect ( mMainArea , SIGNAL ( sendUserInfo () ) , 
             this      , SIGNAL ( sendUserInfo () ) );
   
   return;
}
