# ifndef CONFIG_HH_
# define CONFIG_HH_

# include <QtCore/QFile>
# include <QtCore/QMap>
# include <QtCore/QString>
# include <QtCore/QTextStream>

namespace Base
{
   class Config
   {
      public:
         explicit Config ( void );
         virtual ~Config ( void );
         
         static QString& get ( QString key );
         static Config* instance ( void );
         
      private:
         void saveValues ( void );
         void loadValues ( void );
         void parseInputLine ( QString& input_line );
         
      private:
         QMap< QString , QString > mConfigValues;
   };
}

# endif
