# Tools for Discovering New Sator Squares
![Sator Square](https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sator_Square_at_Opp%C3%A8de.jpg/330px-Sator_Square_at_Opp%C3%A8de.jpg)
## What is the Sator Square?
The [Sator Square](https://en.wikipedia.org/wiki/Sator_Square) is a famous "2D Palindrome" in Latin that was widespread through the ancient world.  

Its 5 Latin words in a grid read the same in any direction.  Try it!
```
SATOR
AREPO
TENET
OPERA
ROTAS
```
Left-to-right then top-to-bottom (normal English order): Sator Arepo tenet opera rotas.

Top-to-bottom then left-to-right: Sator Arepo tenet opera rotas.

Right-to-left then bottom-to-top: Sator Arepo tenet opera rotas.

Bottom-to-top then right-to-left: Sator Arepo tenet opera rotas.

If written out as a 1D sentence, it is also a palindrome.

For the careful reader who realizes that there are four more possibilities (e.g., left-to-right then bottom-to-top), the reverse word order ("Rotas opera tenet Arepo Sator") means the same thing in Latin because the word order doesn't really matter in this regard.

The Sator Square was reproduced all over Europe for hundreds of years and its cryptic meaning was embued with mystical significance because of the sheer awesomeness of its palindromic properties, which led many to believe that the phrase must mean something deep.
![Sator Square](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/Grenoble_-_Sator_02.jpg/330px-Grenoble_-_Sator_02.jpg)

As for how nicely to translate it, you can read various opinions online, but I'm going with "Arepo the Sower holds the Wheel Work."  In both pagan and Christian milieux this sort of translation tended to see the phrase as indicating that God (or Christ as "the Sower", or the *logos spermatikos* of Stoic philosophy) governed the world (by having hold of its "wheels" = inner workings).

Word mysticism aside, it's been a long time since we've had another Sator-like square, and they are not easy to make up with pencil and paper and sheer cleverness.  

**Given the enormous popularity of the first Sator Square, wouldn't it be nice to find more?**

## Tools Required: An algorithm and a dictionary
### Algorithm
The algorithm is not too hard to discover.  To make the Sator Square work, the 5x5 matrix has the same characters reflected across *both* diagonals.  This fundamental property generalizes to Sator Squares of any size.  

For odd sizes (5x5, 7x7) we require a palindromic word in the center row, and then pairs of words such that one is the reverse of the other for all the other rows.  For even sizes, we only require pairs of words such that one is the reverse of the other.  We shall call such pairs **palindromic pairs.**

As my daughter observed, the requirement that all pairs be meaningful words is actually more rigorous than the original Sator Square since "Arepo" means nothing in Latin, and by sheer presumption was taken as a mysterious proper name for the sake of an intelligible reading.  (So I provide an optional way to soften this requirement likewise for one pair of words if you wish.)

The rest of the algorithm comes down to finding combinations of palindromes and palindromic pairs that satisfy our further requirement about how the characters are the same reflected across the diagonals.

For a 5x5 matrix, if we label the coordinates row-first then column like so:
```
(0,0)   (0,1)   (0,2)   (0,3)   (0,4)
(1,0)   (1,1)   (1,2)   (1,3)   (1,4)
(2,0)   (2,1)   (2,2)   (2,3)   (2,4)
(3,0)   (3,1)   (3,2)   (3,3)   (3,4)
(4,0)   (4,1)   (4,2)   (4,3)   (4,4)
```
We require that the character C(0,1) = C(1,0), C(0,2)=C(2,0), C(1,2)=C(2,1), etc. for one diagonal, and also that C(0,3)=(1,4), C(0,2)=C(2,4), C(1,2)=C(2,3), etc. for the other diagonal.  Closer consideration reveals that because of symmetry, we don't have to check all these conditions.

For the 5x5 matrix, we proceed as follows:
-Comb the dictionary for words 5 characters long, and put them in the `dictionary` vector
-Search the `dictionary` vector, and create a `palindromes` vector for all the palindromic words
-Search the `dictionary` vector, and create a `pairs` vector for words such that its reverse is a word (a palindromic pair).  This is an N-squared time complexity, but it doesn't take too long.
-







