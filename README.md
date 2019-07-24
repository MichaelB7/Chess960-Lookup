# Chess960-Lookup
Generate or lookup Chess960 positions sequentially or randomly.
#### 
To build: gcc -O3 960v09.c -o 960Lookup

#### Usage:
  Enter the non-zero based 960 position number 1 through 960 for that position in PGN format.

  Enter zero to dislay all Chess960 starting positions in PGN format.

  Enter a negative number less than -1 for Chess960 positions chosen at random.

  Any mumber greater than 960 will return all Chess 960 positions in raw FEN format.

  Enter -1 (minus one) to exit. Output can be redirected to a file.

  Example: Chess960-LookUp > c960.txt - but learn the commands first. ;>)

#### Formula basis: 
```
White's Chess960 starting array can be derived from its number N (0 ... 959) as follows:
 a) Divide N by 4, yielding quotient N2 and remainder B1. Place a B​ishop upon the bright square corresponding to B1 (0=b, 1=d, 2=f, 3=h).
 
 b) Divide N2 by 4 again, yielding quotient N3 and remainder B2. Place a second B​ishop upon the dark square corresponding to B2 (0=a, 1=c, 2=e, 3=g).
 
 c) Divide N3 by 6, yielding quotient N4 and remainder Q. Place the Q​ueen according to Q, where 0 is the first free square starting from a, 1 is the second, etc.
 
 d) N4 will be a single digit, 0 ... 9. Place the K​n​ights according to its value by consulting the following table:
 
 Digit     Knight positioning
 0         N   N   -   -   -
 1         N   -   N   -   -
 2         N   -   -   N   -
 3         N   -   -   -   N
 4         -   N   N   -   -
 5         -   N   -   N   -
 6         -   N   -   -   N
 7         -   -   N   N   -
 8         -   -   N   -   N
 9         -   -   -   N   N
 ``` 
 
#### Attributions:
Generator: https://codegolf.stackexchange.com/users/3544/ugoren  
Random array shuffle: https://www.sanfoundry.com/c-program-implement-fisher-yates-algorithm-array-shuffling
Chess960 numbering scheme: https://en.wikipedia.org/wiki/Chess960_numbering_scheme 
