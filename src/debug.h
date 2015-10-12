/* in production build, turn off APP_LOG */
// #undef APP_LOG

// when setting seconds per minute to 1, makes debugging easier cause time lapses faster

#define DEBUG_TO_SECONDS
#define DEBUG_CHECK_MORE
// #define DEBUG_SAVE_DEBUG_RECORDS
#define VERSION_INFO "Trudi"
#undef APP_LOG
#define APP_LOG(level,fmt,args...)

