#include "app_version.h"
#include <stdio.h>

char app_verison[32];

char *app_get_version_string(void)
{
    sprintf(app_verison, "%d.%d.%d-%s", _APP_VERSION, _APP_PATCHLEVEL, _APP_SUBLEVEL, _APP_EXTRAVERSION);
    return app_verison;
}

