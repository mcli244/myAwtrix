#include "app_version.h"
#include <stdio.h>

char *app_get_version_string(void)
{
    static char app_verison[32];
    sprintf(app_verison, "%d.%d.%d-%s", _APP_VERSION, _APP_PATCHLEVEL, _APP_SUBLEVEL, _APP_EXTRAVERSION);
    return app_verison;
}

char *get_compile_time(void)
{
    static char compile_time[64] = {0};
    sprintf(compile_time, "%s %s", __DATE__, __TIME__);
    return compile_time;
}
