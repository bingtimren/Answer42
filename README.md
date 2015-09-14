# Answer42

Answer to THE question (of life, universe and everything :p), 
* where my time goes?
* how concentrated I am?
* how I feel?

----
## Features

* record What I'm doing for all the time
* record in watch a summary of how much time in what for the day & last 
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
   * on Committed -> Window Selection (current NIL)
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
   * Multiple stage reminder & repeats according to setup (see code)
   * If current what finished (expire of last stage), commit current record or NoFin, set current what to NIL, start it, and return loop
* Button up
   * increase time by manual extension length
   * return state to running
* Button down
   * brings up Window Finish Running (that means not stop counting)
* Button middle - bring up Window Summary

### Window Finish Running
Display
* Just finished what and its running time
* Tagging - switch on/off between several taggings to further mark the time

Interactions:
* Up / Down - scroll the tags list
* Button middle - toggle tag on/off
* Button back - confirm & enter
   * add up to today/what total
   * create entry to buffer
   * set current "what" to NIL and return to Window Running & then bring up Window Selection
* Time-out - do nothing & return to Window Running

### Window Selection

Display:  a list of "whats" for selection, or the (3X3 selection) 
Interactions:
* After selection
   * immediately commit current NIL
   * change current what to selected
   * exit window & return to running
 
