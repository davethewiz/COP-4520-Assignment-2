# COP-4520-Assignment-2
A simulation of a Minotaur with an interest in concurrency.

The minotaur has a birthday party, with threads he calls "guests".
He also has a labyrinth with cupcakes and a showroom with a crystal vase.

Note that the explanations below refer to the `assignment.pdf` file greatly.

## Part 1 - The Labyrinth
This is referring to code in `labyrinth.cpp`.

### Design Breakdown
To solve part 1, the idea is that everyone besides the first guest will do one of two things when exiting the labyrinth:
- Eat the cupcake if it is there **and** they haven't eaten one already
- Do nothing otherwise

The first guest will be chosen as the checker. When selected by the minotaur, it will check to see if there is an empty plate. If the plate is empty, it knows that there has been one new unique completition of the labyrinth. The checker holds a counter of the number of unique completitions. It adds one when the plate it empty. Then, it asks for a new cupcake and leaves *without* eating it.

The cycle then continues on and on as guests are selected randomely. Until it is the case that the total count stored by the checker reaches the same value as the number of guests (minus 1 as we do not have the checker eat the cupcake). When this happens, the checker tells the minotaur that all guests have completed the labyrinth!

### Compiling and Running
To compile the code, navigate to the location of this repo in your terminal and run the following:
```
g++ labyrinth.cpp -o labyrinth
```
Then, run the code by running the executable:
```
./labyrinth
```
The code will output the current status of the first guest's counter and when all guests have completed the labyrinth.

### Evaluation
For this first part, considering the randomness of the guest selection process, the theoretical best runtime would be O(n) however, this assumes perfect selection of guests randomly. It could very well be O(n!) at the worst case. So somewhere between a great O(n) and a horrendous O(n!) runtime! Gotta love randomness!

Here are a range of runtimes for a given number of guests:
- 10 Guests => 8-30ms
- 25 Guests => 70-120ms
- 50 Guests => 1000-2000ms
- 100 Guests => 7000-18000ms

As you can so it grows quite quickly with more guests!

## Part 2 - The Crystal Vase
This is refering to code in `crystal_vase.cpp`

### Design Breakdown
`todo!()`

### Compiling and Running
To compile the code, navigate to the location of this repo in your terminal and run the following:
```
g++ crystal_vase.cpp -o crysal_vase
```
Then, run the code by running the executable:
```
./crystal_vase
```
The code will output the `todo!()`

### Evaluation
`todo!()`