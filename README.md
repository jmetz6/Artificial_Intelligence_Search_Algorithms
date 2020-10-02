# Artificial_Intelligence_Search_Algorithms
Solved a puzzle (C++) using breadth-first search, depth-first search, iterative  deepening depth-first search, and A-Star search. <br>

The puzzle solved was the "chickens and wolves" puzzle. <br>
Here is a link to the puzzle description: https://www.ign.com/wikis/professor-layton-and-the-curious-village/Puzzle_007 <br>

NOTE: This program is meant to be run on linux system. <br>

In order to run the program please... <br>
1) Compile using the compile script by running <br>
    "./COMPILE" <br>
2) Run the program by running <br>
    "./Game.exe" {Start State File} {Goal State File} {Mode String} {Output File} <br>
   with the proper arguments <br>
   
   Start state files and goal state files all correspond based on number <br>
   i.e start1.txt corresponds with goal1.txt NOT goal2.txt <br>
   These starts and goals differ by having larger numbers of chickens and wolves to start with. <br>
   
   Modes: <br>
      argument: name <br>
      bfs: bread-first search <br>
      dfs: depth-first search <br>
      iddfs: Iterative deepening depth first search <br>
      astar: A-Star Search <br>
      
   Output file can be given as arbitrary file "Output". It is more useful as the size of the problem increases as there will be many more steps especially for a less efficient search. <br>
   
   See the "Programming Assignment 1.pdf" for an analysis of the algorithms on this puzzle. <br>
   
