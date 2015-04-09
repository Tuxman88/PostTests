# ifndef CONFIG_HH_
# define CONFIG_HH_

# include <QtCore/QMap>
# include <QtCore/QString>

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
         QMap< QString , QString > mConfigValues;
   };
}

# endif
