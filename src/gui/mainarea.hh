# ifndef MAINAREA_HH_
# define MAINAREA_HH_

# include <QtCore/QDebug>
# include <QtWidgets/QHBoxLayout>
# include <QtWidgets/QLabel>
# include <QtWidgets/QLineEdit>
# include <QtWidgets/QPushButton>
# include <QtWidgets/QWidget>
# include <QtWidgets/QVBoxLayout>

# include "../base/config.hh"
# include "../core/control.hh"

namespace Gui
{
   class MainArea : public QWidget
   {
      Q_OBJECT
      
      public:
         explicit MainArea ( void );
         virtual ~MainArea ( void );
         
      private slots:
         void sendMessage ( void );
         
      private:
         void buildGui ( void );
         void connectAll ( void );
         
      private:
         QVBoxLayout* mMainLayout;
         QLabel* mWebUrlLabel;
         QLineEdit* mWebUrlLine;
         QHBoxLayout* mLabelsLayout;
         QHBoxLayout* mButtonsLayout;
         QPushButton* mConnectButton;
   };
}

# endif
