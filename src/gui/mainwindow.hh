# ifndef MAINWINDOW_HH_
# define MAINWINDOW_HH_

# include <QtWidgets/QMainWindow>

# include "mainarea.hh"

namespace Gui
{
   class MainWindow : public QMainWindow
   {
      Q_OBJECT
      
      public:
         explicit MainWindow ( void );
         virtual ~MainWindow ( void );
         
      signals:
         void sendUserInfo ( void );
         
      private:
         void buildGui ( void );
         void connectAll ( void );
         
      private:
         Gui::MainArea* mMainArea;
   };
}

# endif
