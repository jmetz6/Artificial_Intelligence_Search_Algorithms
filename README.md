# Artificial_Intelligence_Search_Algorithms
Solved a puzzle (C++) using breadth-first search, depth-first search, iterative  deepening depth-first search, and A-Star search.

The puzzle solved was the "chickens and wolves" puzzle.
Here is a link to the puzzle description: https://www.ign.com/wikis/professor-layton-and-the-curious-village/Puzzle_007

NOTE: This program is meant to be run on linux system.

In order to run the program please...
1) Compile using the compile script by running
    "./COMPILE"
2) Run the program by running
    "./Game.exe" {Start State File} {Goal State File} {Mode String} {Output File}
   with the proper arguments
   
   Start state files and goal state files all correspond based on number
   i.e start1.txt corresponds with goal1.txt NOT goal2.txt
   These starts and goals differ by having larger numbers of chickens and wolves to start with.
   
   Modes: 
      argument: name
      bfs: bread-first search
      dfs: depth-first search
      iddfs: Iterative deepening depth first search
      astar: A-Star Search
      
   Output file can be given as arbitrary file "Output". It is more useful as the size of the problem increases as there will be many more steps especially for a less efficient      search.
   
   See the "Programming Assignment 1.pdf" for an analysis of the algorithms on this puzzle.
   
