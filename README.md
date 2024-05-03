# Welcome to My Mouse

---

## Task

Walk in a labyrinth :
◦ This project is about finding the shortest path between entering and leaving
a labyrinth while avoiding obstacles.
◦ A maze is given to you in a file to be passed as an argument to the program
(Maze generator in Appendix).
◦ The first line of the labyrinth contains the information to read the map:
∗ The number of labyrinth lines then the number of columns (LINExCOL);
∗ The "full" character
∗ The "empty" character
∗ The character "path"
∗ The character "entered labyrinth"
∗ The character "exit labyrinth".
◦ The maze is composed of "empty" characters, "full" characters, characters "entering the labyrinth" and characters "exiting the labyrinth".
◦ The purpose of the program is to replace "empty" characters with "path" characters to represent the shortest way to cross the labyrinth.
◦ Movements can only be horizontally or vertically, not diagonally.
◦ In the case where several solutions exist, one will choose to represent the shortest one. In case of equality, it will be the one whose exit where the solution is the most up then the leftmost. If there are 2 solutions for the same output, when crossing from the start we will choose the solutions in this order: up> left> right> down
So if you have a choice between going up or right, you have to take the solution
that goes up.

## Description

◦ Definition of a valid map :
∗ All lines must respect the sizes given in the first line (LINExCOL).
∗ There can only be one entrance.
∗ There must be only one exit.
∗ There must be a solution to the labyrinth.
∗ The labyrinth will not be more than a thousand square.
∗ At the end of each line, there is a new line.
∗ The characters present in the map must be only those shown on the first
line.
∗ If there is an invalid map, you will print MAP ERROR on STDERR followed by a new line. The program will then proceed to the next labyrinth
treatment.

Exit(s) will always be located on "outside walls"

## Installation

`make`

## Usage

```
./my_mouse ./tests/01.map |  ruby ./my_mouse_checker.rb
```

### The Core Team

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
