# simple-bar-chart
Testbed for a basic bar chart rendering framework and to use for tech interview

Basic version is in place : <200 lines - maybe TOO basic, but I feel like they can read over the code the first time and get a feel for what's going on.  Not a 20 minute silent study session before we can ask them something.

Output:
```
 Value
  35 |       ####            
  31 |       ####        ####
  28 |       ####        ####
  24 | ####  ####        ####
  21 | ####  ####        ####
  17 | ####  ####        ####
  14 | ####  ####  ####  ####
  10 | ####  ####  ####  ####
   7 | ####  ####  ####  ####
   3 | ####  ####  ####  ####
     +---------------------->
       App   Ban   Che   Dat 
        Category
```
Ideas for interview tweaks:
- x axis always zero and at bottom, so negative data looks like 0.  Add a baseline, and unit test with negative data.
- Add a Rule class that associates a category (or maybe a response threshold) with a display character.  Allow for a prioritized list of Rules to be associated with a chart.  I did a simple fixed category rule with 2 lines of changes.  But maybe a Rule class with cat and resp subclasses and then multi-processing kicks it up a notch.  Still might be too basic for advanced career or all.
- Add one or more reference lines at specified response values.  Allow for front/back.  Unit test to make sure it works when outzide normal bar data range.  This might be trickier than needed becasue of the fillspan style graphics.
- We could rework to show grouped bars and then have them allow for stacked/clustered.  Might need to add a graphic library at that point.

Questions: 
 ? SHOULD we add a graphics library, just to draw rectangles in a frame buffer, instead of fillspans-style?
 ? Are any of these hard enough.  Maybe we could have them convert a function to a lambda if we can make it make sense.  
