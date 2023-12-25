#ifndef __APP_VERSION_H__
#define __APP_VERSION_H__

#define _APP_VERSION     0
#define _APP_PATCHLEVEL  4	
#define _APP_SUBLEVEL    0
#define _APP_EXTRAVERSION    "debug"	

#define APP_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define APP_VERSION_CODE APP_VERSION(_APP_VERSION, _APP_PATCHLEVEL, _APP_SUBLEVEL)

char *app_get_version_string(void);
char *get_compile_time(void);

#endif /*__APP_VERSION_H__*/