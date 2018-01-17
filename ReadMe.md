# Einführung in die Programmierung für Physiker WiSe 2017/18 - Final Project

```
##   ## # #    # ######  ####  #    # ###### ###### #####  ###### ##### 
# # # # # ##   # #      #      #    # #      #      #    # #      #    #
#  #  # # # #  # #####   ####  #    # #####  #####  #    # #####  #    #
#     # # #  # # #           # # ## # #      #      #####  #      ##### 
#     # # #   ## #      #    # ##  ## #      #      #      #      #   # 
#     # # #    # ######  ####  #    # ###### ###### #      ###### #    # 
```

## 1 Introduction
---
This project contains a console implementation of the well-known game 'Minesweeper'.
It is written in C and tested in a linux terminal
...
(... exit() und clear function für verschiedene Betriebssysteme erwähnen)
...
Please note that especially colors are dependant of the operating system and color scheme of your terminal. Therefore they might not appear the way they should.

## 2 How to use the program
---
To start the program, run the executable "Minesweeper". You have the option of adding arguments for the number of rows, columns and mines as well as the additional option of playing an extended version of the game with periodic boundary conditions.
...
(erklären was genau man wie eingeben muss)
...
If you don't provide any command line arguments, the default game with 8 rows, 8 columns and 7 mines and no periodic boundary conditions will start.

## 3 Rules and functionalities of the game
---
The basic rules of the game are simple. Hidden somewhere underneath the tiles is a certain amount of mines. Your task is to open all safe tiles without opening a mine tile. If you do open a mine tile, you lose instantly.
Every safe tile has a number on it that indicates how many of the adjacent tiles have mines on them. 
If you think you know which of the hidden tiles has a mine underneath, you can mark that tile as armed. Of course you can also disarm a tile if you change your mind. However you cannot mark an already revealed tile as armed, because that doesn't make any sense.
If you reveal a tile that doesn't have any mines surrounding it (an empty tile), all surrounding tiles will automatically be revealed as well. This will set off a chain reaction if one of the surrounding tiles is empty as well.
You also have the option of "digging" underneath an already revealed tile, meaning you can re-reveal an open tile and thereby reveal all adjacent tiles. This option is only available if the number of marked-as-armed tiles adjacent to the chosen tile is at least as high as the number on the tile. The marked tiles are safe, which means that you are safe as long as you've marked the right tiles. If you've made a mistake, you'll lose.
The second you open the last safe tile on the board, you win the game.

If you've lost, the board will be printed another time in the state it was when the game ended but with all mines highlighted in one shade of red, and the mine that made you lose in another.

If you've won, the board will be printed with mines highlighted in green color.

### 3.1 Periodic boundary conditions

Having periodic boundary conditions in this game means that all tiles have the same number of adjacent tiles. Therefore borders don't actually exist, a border tile connects to another border tile on the other side of the board.
Instead of a board like this:

```
|2|x|2| | | | | |
|2|x|3|1| | | | |
|1|2|x|1| | | | |
| |1|1|2|1|2|1|1|
| | | |1|x|2|x|1|
| |1|1|2|1|2|1|1|
|1|2|x|1| | | | |
|1|x|2|1| | | | |
```
You actually have a board like this:
```
|2|x|2| | | | | |2|x|2| | | | | |2|x|2| | | | | |2|x|2| | | | | |
|2|x|3|1| | | | |2|x|3|1| | | | |2|x|3|1| | | | |2|x|3|1| | | | |  
|1|2|x|1| | | | |1|2|x|1| | | | |1|2|x|1| | | | |1|2|x|1| | | | |    
| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| 
| | | |1|x|2|x|1| | | |1|x|2|x|1| | | |1|x|2|x|1| | | |1|x|2|x|1| 
| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| 
|1|2|x|1| | | | |1|2|x|1| | | | |1|2|x|1| | | | |1|2|x|1| | | | |   
|1|x|2|1| | | | |1|x|2|1| | | | |1|x|2|1| | | | |1|x|2|1| | | | |  
|2|x|2| | | | | |2|x|2| | | | | |2|x|2| | | | | |2|x|2| | | | | |  
|2|x|3|1| | | | |2|x|3|1| | | | |2|x|3|1| | | | |2|x|3|1| | | | |  
|1|2|x|1| | | | |1|2|x|1| | | | |1|2|x|1| | | | |1|2|x|1| | | | | 
| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| 
| | | |1|x|2|x|1| | | |1|x|2|x|1| | | |1|x|2|x|1| | | |1|x|2|x|1| 
| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| |1|1|2|1|2|1|1| 
|1|2|x|1| | | | |1|2|x|1| | | | |1|2|x|1| | | | |1|2|x|1| | | | | 
|1|x|2|1| | | | |1|x|2|1| | | | |1|x|2|1| | | | |1|x|2|1| | | | |
```
...and so on. Therefore you should be careful and take the mines on the other side if the field into account.
Revealing adjacent tiles, the chain reaction for empty tiles and the digging option all cross the borders. 
                    