# include "config.hh"

Base::Config::Config ( void )
{
   mConfigValues[ "WebUrl" ] = "http://www.4code.mx/gp/index.php/api/test_api/empleado";
   
   loadValues ();
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

void Base::Config::loadValues ( void )
{
   QFile config_file ( "settings.cfg" );
   
   if ( !config_file.exists () )
   {
      saveValues ();
      
      return;
   }
   
   if ( !config_file.open ( QIODevice::ReadOnly ) )
      return;
   
   QTextStream input_stream ( &config_file );
   
   while ( !input_stream.atEnd () )
   {
      QString input_line = input_stream.readLine ();
      
      parseInputLine ( input_line );
   }
   
   return;
}

void Base::Config::saveValues ( void )
{
   QFile output_file ( "settings.cfg" );

   if ( !output_file.open ( QIODevice::ReadWrite ) )
      return;

   QTextStream output_stream ( &output_file );

   QList< QString > config_keys;
   config_keys = mConfigValues.keys ();

   for ( int i = 0; i < config_keys.size (); i++ )
      output_stream << config_keys[ i ] << "=" << mConfigValues[ config_keys[ i ] ] << "\n";

   output_file.close ();
   
   return;
}

void Base::Config::parseInputLine ( QString& input_line )
{
   QStringList line_components = input_line.split ( "=" );
   
   if ( line_components.size () != 2 )
      return;
   
   mConfigValues[ line_components[ 0 ] ] = line_components[ 1 ];
   
   return;
}
