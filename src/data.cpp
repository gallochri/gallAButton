#include <data.h>

String formatBytes ( size_t bytes )
{
    if ( bytes < 1024 ){
        return String ( bytes ) + " B";
    }
    else if ( bytes < ( 1024 * 1024 ) ){
        return String ( bytes / 1024.0 ) + " KB";
    }
    else if ( bytes < ( 1024 * 1024 * 1024 ) ){
        return String ( bytes / 1024.0 / 1024.0 ) + " MB";
    }
    else{
        return String ( bytes / 1024.0 / 1024.0 / 1024.0 ) + " GB";
    }
}

void setupSPIFFS(){

    FSInfo  fs_info;
    Dir     dir;
    File    f;
    String  filename;
    SPIFFS.begin();
    uint16_t cnt = 0;
    dir = SPIFFS.openDir("/");
    Serial.println();
    Serial.println("|--------------------------------------------------------|");
    Serial.println("|Name                           -                    Size|");
    while ( dir.next() )
    {
        f = dir.openFile ( "r" ) ;
        filename = dir.fileName() ;
        Serial.printf( "|%-30s - %9d|\n",
                       filename.c_str(),
                       formatBytes ( f.size() ).c_str()
                       );
        cnt++;
    }

}
