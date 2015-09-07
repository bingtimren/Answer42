# Answer42

Answer to THE question (of life, universe and everything :p), 
* where my time goes?
* how concentrated I am?
* how I feel?

----
## Features

* record What I'm doing for all the time
* record in watch a summary of how much time in what for last 7 days
* locally store log up to xxx items
* automatically / manually upload log to watch & then to a datasource, and clean log

---
## Main Data Structure

### What's what?

see comments in "what.h"

---
## Windows & Interaction
### Initialize
* Check storage if current what is available
* If not, current what is NIL and start right now
* Bring on window running
### Window interaction
* Window Running
   * on Finish -> Window Finish Running
   * on View Summary -> view summary
* Window Finish Running
   * on All Committed -> Window Selection (current NIL)
   * on T-out -> return to Window Running
* Window Selection
   * on Select -> Window Running (set current Selected)
   * on T-out -> Window Running (remain NIL)

---
## Window Details 

### Window Running

This is the first window

Display:
* Date / time / weekday / battery level
* Name of currently running "what"
* How long has it been running
* Percentage indicator
* Target length, remaining, ends at
Interactions:
* Alarm (time out): 
   * Vibe to reminder
   * Determine state, and change to next state if time out
   * If current what finished (forced finish), commit current record or NoFin, set current what to NIL, start it, and return loop
   * State change:
      * Running reminder during target length
      * Extension reminder 1 during extension 1
      * Extension reminder 2 during extension 2
      * Reminder in final reminder mode or finish
* Button up
   * increase time by manual extension length
   * return state to running
* Button down
   * brings up Window Finish Running (that means not stop counting)
* Button middle - bring up Window Summary

### Window Finish Running
Display
* Just finished what and its running time
* An indicator, can indicate how much to split
* Concentration / feeling mode:
   * How concentrated I am (default very concentrated)
   * How good I feel (default very good)
* Split mode:
   * how much to split (1-8/remaining slices)
   * what to split (switch between whats)
Interactions:
* Concentration / feeling mode:
   * Button up - toggle concentration
   * Button down - toggle how good I feel
* Split mode:
   * Button middle - toggle to split mode / switch what
   * Button up / down - toggle 1-8/8
* Button back - confirm & enter
   * add up to today/what total
   * create entry to buffer
   * if all entered (no split left), set current "what" to NIL and return to Window Running & then bring up Window Selection
   * if still slots left for split, return to split mode
* Time-out - do nothing & return to Window Running

### Window Selection

Display:  a list of "whats" for selection
Interactions:
* Up/Down for browsing
* Middle for select
   * immediately commit current NIL
   * change current what to selected
   * exit window & return to running
 
