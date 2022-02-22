# Fillit (Hive / 42 School Project)
Program will take a file as parameter, which contains a list of Tetriminos, and arrange them in order to create the smallest square possible.

* The program takes only one parameter, a file which contains a list of Tetriminos to assemble. This file has a very specific format : every Tetrimino must exactly fit in a
4 by 4 chars square and all Tetrimino are separated by an newline each.
* If the number of parameters sent to executable is not 1, program must display its usage and exit properly. File should contain between 1 and 26 Tetriminos.
* The description of a Tetriminos must respect the following rules :
  * Precisely 4 lines of 4 characters, each followed by a new line (well... a 4x4 square).
  * A Tetrimino is a classic piece of Tetris composed of 4 blocks.
  * Each character must be either a block character(’#’ ) or an empty character (’.’).
  * Each block of a Tetrimino must touch at least one other block on any of his 4 sides (up, down, left and right).

**The goal of this project** is to arrange every Tetriminos with each others in order to make the smallest possible square. But in some cases, this square should contains holes when
some given pieces won’t fit in perfectly with others.
Even if they are embedded in a 4x4 square, each Tetrimino is defined by its minimal boundaries (their ’#’). The 12 remaining empty characters will be ignored for the
Tetriminos assemble process.
Tetriminos are ordered by they apparition order in the file. Among all the possible candidates for the smallest square, we only accept the one where Tetriminos is placed on
their most upper-left position.

![Solution](/images/example.png)
### How to use
* git clone https://github.com/AntonKilk/fillit.git
* cd ~/fillit/
* make
* ./fillit file

### Enjoy!
