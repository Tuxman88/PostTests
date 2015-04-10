# include <QtWidgets/QApplication> 

# include "core/control.hh"
# include "gui/mainwindow.hh"

int main ( int argc , char** argv )
{
   QApplication application ( argc , argv );
   
   Core::Control* control;
   Gui::MainWindow* main_window;
   
   main_window = new Gui::MainWindow ();
   control = new Core::Control ();
   
   QObject::connect ( main_window , SIGNAL ( sendUserInfo () ) , 
                      control     , SLOT ( sendUserInfo () ) );
   
   main_window->show ();
   
   application.exec ();
   
   delete main_window;
   
   return ( 0 );
}