#include "Session.h"
int main(int argc, char *argv[])
{
    INFO("Hit 'q' to end session!");
    ConfigManager::getConfigManager().initConfigManager(argv[1]);
    Session session;
    session.run();

    return 0;
}
