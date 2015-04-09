# include "config.hh"

Base::Config::Config ( void )
{
   mConfigValues[ "WebUrl" ] = "http://www.4code.mx/gp/index.php/api/test_api/empleado";
}

Base::Config::~Config ( void )
{
}

QString& Base::Config::get ( QString key )
{
   Base::Config* myself = Config::instance ();
   
   return ( myself->mConfigValues[ key ] );
}

Base::Config* Base::Config::instance ( void )
{
   static Base::Config myself;
   
   return ( &myself );
}