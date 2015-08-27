# Answer42

Answer to THE question, 
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
* int ID
* A name (such as "work", "rest"...)
* Target length in minutes
* Running reminder interval in minutes (0 no reminder)
* Extension stage 1 length (0 to skip)
* Extension stage 1 reminder interval in minutes (0 no reminder)
* Extension stage 2 length (0 to skip)
* Extension stage 2 reminder interval in minutes (0 no reminder)
* Manual extension length in minutes
* Final reminder interval (0 to terminate immediately)


---
## Windows & Interaction

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

### Initialize
* Check storage if current what is available
* If not, current what is NIL and start right now
* Bring on window running



### Window Running

This is the first window

Display:
* Date / time / weekday / battery level
* Name of currently running "what"
* How long has it been running (or not started)
* Percentage indicator
* Target length, remaining, ends at
Interactions:
* Alarm (time out): 
   * Vibe to reminder
   * Determine state, and change to next state if time out
   * If current what finished, commit current record? set current what to NIL, start it, and return loop
   * State change:
      * Running reminder during target length
      * Extension reminder 1 during extension 1
      * Extension reminder 2 during extension 2
      * Reminder in final reminder mode or finish
* Button up
   * start / increase time by manual extension length
   * return state to running
* Button down - finish immediately, or choose again if not started
   * brings up Window Finish Running (that means not stop counting)
* Button middle - bring up Window Summary

### Window Finish Running
Display
* Just finished what and its running time
* An indicator, can indicate how much to switch to
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
   * Button middle - toggle to split mode 
   * Button up / down - toggle 1-8/8
* Button back - confirm & enter
   * add up to today/what total
   * create entry to buffer
   * if all entered (no split left), set current "what" to NIL and return to Window Running & then bring up Window Selection
   * if still slots left for split, return to split mode
* Time-out - do nothing & return to Window Running

### Window Selection

This is pushed into window stack after a "what" is finished
Display:  a list of "whats" for selection
Interactions:
* Up/Down for browsing
* Middle for select
   * immediately commit current NIL
 
