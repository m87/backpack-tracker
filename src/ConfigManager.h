#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class ConfigManager
{
    /* data */
    static const int CONFIG_NUM;
        
public:
    string _srcPath;
    int _MOGHistory;
    int _MOGNMixtures;
    bool _MOGShadows;
    float _opFrameX;
    float _opFrameY;
    int _firstStageDilatation;
    int _firstStageTreshold;
    int _detectionStep;    
    

    ConfigManager ();
    ConfigManager (string config);
    ConfigManager(int argc, char *argv[]);
    ~ConfigManager ();

};

#endif
