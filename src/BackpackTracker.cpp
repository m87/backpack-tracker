#include "Session.h"


/**
 * @mainpage
 * Ref parameter - common parameter which represents reference image. For dimension, type and other common attributes.
 *
 * VERBOSE_O macro is defined for all informations that are very frequent
 *
 *
 */

int main(int argc, char *argv[])
{
    INFO("Hit Ctrl+c to end session!");
    ConfigManager::getConfigManager().initConfigManager(argv[1]);
    Session session;
    session.run();

    return 0;
}
