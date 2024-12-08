# semiprime-factorization
Semiprime factorization using various algorithms, including the Quadratic Sieve.

    For numbers with aprox. 20 to 40 digits, the best value for B
    in order to find B-smooth numbers is about 30 to 50. So the 
    numbers we can try for B are: {29, 31, 37, 41, 43, 47, 53}.
    B-smooth numbers must only have factors that are less than or equal to
    the primes preceding B (meaning they are one of the following numbers:
    {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53}). In the beginning, we 
    could select B = 51 and slowly drop its value while checking if there 
    is a significant difference in the algorithm's accuracy every time we do so.


    STEPS OF THE QUADRATIC SIEVE ALGORITHM
    
    Supposing N is the number we want to factorize:
    1. Select B (for the first time we try to run the algorithm, B shall be 53)

    2. Find all primes less than or equal to B and put them in a list (because 
       we're not allowed to have a pre-generated list of primes). B-smooth 
       numbers must only have factors that are less than or equal to this 
       list of numbers.

    3. Calculate the square of every item on the list and store the modulo when
       dividing by N in another list.

    4. For each number on the list created in step 3, check if it is B-smooth 
       (this procedure requires factorization, but, as the numbers on the list 
       are quite small, trial division is enough - but, for every number where 
       a factor is found two times or more - e.g. 12 = 2^2 * 3, each factor only
       counts once and will be checked once). If it is B-smooth, it is added in a
       list.

    5. Linear algebra fancy stuff

    6. The solution vectors show the factors.
