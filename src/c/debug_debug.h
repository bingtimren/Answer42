// when setting DEBUG_TO_SECONDS, set seconds per minute to 1, makes debugging easier cause time lapses faster
// #define DEBUG_TO_SECONDS

#define DEBUG_CHECK_MORE
// #define DEBUG_SAVE_DEBUG_RECORDS

/* Testings
 * 
 * 1. run Nothing and see if reminders triggered 5x2_5x10_30
 * 2. select Work and see if reminded 15x2_15 and repeats forever (see log repeating)
 * 3. commit and not-confirm, should return to work
 * 4. commit and confirm, without select, should return to nothing
 * 5. commit to show selection screen, select Hygine, shall commit as is after 30_10x5
 * 6. should show nothing after auto commit
 * 7. select what_domestic, should stay no-reminder after 30_10x5
 * 8. test abandon current session - confirm / no-confirm
 * 9. test communication - before each commit
 * 10 test reset 
 * 11 select something - exit - get back, see things still there and data still there
 * 12 exit - wait for reminder to kick out and return to screen
 * */
