# Programming-2-structures-Hitori
Tampere University, Projects made in the course Programming 2: structures. Game Hitori

Game rules

The aim is achieve a game board that fulfills the following requirements:

- No row or column can have more than one occurrence of any given number.
- Empty squares cannot be adjacent, although they can be diagonal to one another.
- No remaining square containing a number can be isolated from the other ones, i.e. the square must have a common side with another remaining square (common corner point is not enough).
- The last requirement differs from that in the original Hitori game. The above one is easier to implement.

Moreover, the original Hitori game accepts game grids of different sizes, but in the project we use the fixed size 5 x 5.

Your task is to implement a Hitori game that follows the rules described above.

The program starst by asking how to fill the game board:

Select start (R for random, I for input): x

Select start (R for random, I for input): yy

Select start (R for random, I for input): r

Enter seed value: 1

=================

|   | 1 2 3 4 5 |

-----------------
| 1 | 1 1 4 3 3 |

| 2 | 2 1 4 4 5 |

| 3 | 2 3 5 1 1 |

| 4 | 3 4 1 2 1 |

| 5 | 3 4 3 5 5 |

=================

Enter removable element (x, y):
The question is repeated until the user gives either string R or I. Note that both upper-case and lower-case letters are accepted equally.

Since the user selected a way, where the gameboard is filled with randomly drawn numbers, the program asks next a seed value for the random number generator. After that the program prints the gameboard filled with random numbers generated based on the seed value.

If the user had chosen a non-random way to fill the board, the program would have proceeded as follows:

Select start (R for random, I for input): i

Input: 2 5 5 3 2 3 4 2 5 3 1 2 2 1 4 2 1 5 2 3 1 2 4 2 4

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5 2 3 |

| 5 | 1 2 4 2 4 |

=================

Enter removable element (x, y):
After that the user can give a square to be removed (x and y coordinates). If one of the coordinates does not belong in the interval [1..5], the program prints:

Out of board
and asks for coordinates again.

If the user gives coordinates of a square that has already been removed, the program prints:

Already removed
and asks for coordinates again.

These cases can be seen in the following execution:

Enter removable element (x, y): 1 6

Out of board

Enter removable element (x, y): xx yy

Out of board

Enter removable element (x, y): 4 4

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5 X 3 |

| 5 | 1 2 4 2 4 |

=================

Enter removable element (x, y): 4 4
Already removed
Enter removable element (x, y):
Note that if the given coordinates are not numeric, the program also now prints Out of board. Here the given function stoi_with_check is useful: It returns zero, if the given parameter string is not numeric, and zero is outside of the game board.

Note also that the game board is printed at start and after that only when there are changes in it.

We can continue from the above situation and play the game successfully, for example, as follows:

Enter removable element (x, y): 5 5

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5  X 3 |

| 5 | 1 2 4 2 X  |

=================

Enter removable element (x, y): 2 5

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5 X  3 |

| 5 | 1 X 4 2  X |

=================

Enter removable element (x, y): 1 3

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | X  2 2 1 4 |

| 4 | 2 1 5 X  3 |

| 5 | 1  X 4 2  X |

=================

Enter removable element (x, y): 3 3

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | X  2  X 1 4 |

| 4 | 2 1 5 X  3 |

| 5 | 1  X 4 2 X  |

=================

Enter removable element (x, y): 1 1

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | X  5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | X  2  X 1 4 |

| 4 | 2 1 5  X 3 |

| 5 | 1 X  4 2 X  |

=================

Enter removable element (x, y): 3 1

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | X  5 X  3 2 |

| 2 | 3 4 2 5 3 |

| 3 |  X 2  X 1 4 |

| 4 | 2 1 5 X  3 |

| 5 | 1 X  4 2  X |

=================

Enter removable element (x, y): 5 2

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | X  5  X 3 2 |

| 2 | 3 4 2 5 X  |

| 3 | X  2 X  1 4 |

| 4 | 2 1 5  X 3 |

| 5 | 1 X  4 2  X |

=================

You won
In the latest situation, the requirements described earlier were fulfilled, which means that the player won, and the program printed You won.

Suppose the same starting point as above. If the player made a mistake, the game would end, for example, as follows:

Enter removable element (x, y): 4 4

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5  X 3 |

| 5 | 1 2 4 2 4 |

=================

Enter removable element (x, y): 1 1

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | X  5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5   3 |

| 5 | 1 2 4 2 4 |

=================

Enter removable element (x, y): 2 1

=================

|   | 1 2 3 4 5 |

-----------------

| 1 |   X  5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5 X  3 |

| 5 | 1 2 4 2 4 |

=================

You lost
Now the player removed two adjacent numbers (from coordinates (1, 1) and (2, 1)), and thus, they lost and the program printed You lost.

A loss would have happened also as follows:

Enter removable element (x, y): 4 4

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 3 2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5  X 3 |

| 5 | 1 2 4 2 4 |

=================

Enter removable element (x, y): 4 1

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5 X  2 |

| 2 | 3 4 2 5 3 |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5 X  3 |

| 5 | 1 2 4 2 4 |

=================

Enter removable element (x, y): 5 2

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 2 5 5  X 2 |

| 2 | 3 4 2 5  X |

| 3 | 1 2 2 1 4 |

| 4 | 2 1 5  X 3 |

| 5 | 1 2 4 2 4 |

=================

You lost
Now the number 2 in coordinates (5, 1) is isolated from the other numbers, and thus, the player lost. A square in the middle of the game board would be isolated, if all four squares around it were removed. A square in the border (but not in the corner) of the game board would be isolated, if all three squares around it were removed.

Although the both loss conditions were fulfilled at the same time (with the removal of a single element), the text You lost will be printed only once.

It is also possible to quit the game with the command Q (or q). You can give this command at the point where the program asks for coordinates:

Select start (R for random, I for input): r

Enter seed value: 1

=================

|   | 1 2 3 4 5 |

-----------------

| 1 | 1 1 4 3 3 |

| 2 | 2 1 4 4 5 |

| 3 | 2 3 5 1 1 |

| 4 | 3 4 1 2 1 |

| 5 | 3 4 3 5 5 |

=================

Enter removable element (x, y): 1 1

=================

|   | 1 2 3 4 5 |

-----------------

| 1 |  X 1 4 3 3 |

| 2 | 2 1 4 4 5 |

| 3 | 2 3 5 1 1 |

| 4 | 3 4 1 2 1 |

| 5 | 3 4 3 5 5 |

=================

Enter removable element (x, y): q
Quitting
Now the program prints Quitting and terminates its execution.

