# COP-4520-Assignment-2
The minotaur has a birthday party, with threads he calls "guests".

He also has a labyrinth with cupcakes and a showroom with a crystal vase.

Note that this repo is based on the assignment outlined in the `assignment.pdf` file.
All below explanations require understanding of the assignment first.

## Part 1 - The Labyrinth
This is referring to code in `labyrinth.cpp`.

### Design Breakdown
To solve part 1, the idea is that everyone besides the first guest will do one of two things when exiting the labyrinth:
- Eat the cupcake if it is there **and** they haven't eaten one already
- Do nothing otherwise

The first guest will be chosen as the checker. When selected by the minotaur, it will check to see if there is an empty plate. If the plate is empty, it knows that there has been one new unique completition of the labyrinth. The checker holds a counter of the number of unique completitions. It adds one when the plate it empty. Then, it asks for a new cupcake and leaves *without* eating it.

The cycle then continues on and on as guests are selected randomely. Until it is the case that the total count stored by the checker reaches the same value as the number of guests (minus 1 as we do not have the checker eat the cupcake). When this happens, the checker tells the minotaur that all guests have completed the labyrinth!

Note that this solution heavily relies on the idea of the *mutex* represented by the entrance of the labyrinth. This allows for each guest (thread) to only access the labyrinth one at a time. Once a guest (thread) enters the labyrinth, they lock the entrance mutex, only unlocking once they exit. This makes it so that processsing can only occur for the single guest in the labyrinth.

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
For this first part, considering the randomness of the guest selection process, the theoretical best runtime would be O(n) however, this assumes perfect selection of guests randomly. It could very well be O(n!) at the worst case. So somewhere between a great O(n) and a horrendous O(n!) runtime.

Here are a range of runtimes for a given number of guests:
- 10 guests: 8-30ms
- 25 guests: 70-120ms
- 50 guests: 1000-2000ms
- 100 guests: 7000-18000ms

## Part 2 - The Crystal Vase
This is refering to code in `crystal_vase.cpp`

### Solution Selection
For this part, we had to choose between three main options for ensuring one guest enters the showroom at a time.

The first solution has some advantages as it is quite simple to do and really just involves effectively data racing for each of the threads. Basically, just make the threads constantly try to access to the showroom. This is basically not using any mutexes as at all and possibly just using a global variable. The issue with this is directly in the explanation of the solution, there is no gaurantee when a guest will be able to enter the showroom. It also would cause "crowding" at the door, which is overall just inefficient.

The third solution wouldn't be too bad as it involves using a queue and simply lining the guests up. The problem with this is that it doesn't allow guests to roam around the party. They constantly need to be queued up in line, the thread would constantly be active and running, ensuring that it is not yet at the front of the queue before trying to enter.

The second solution is clearly the best one as it still allows our guests to roam around the party and not crowd the door while the door says "NOT AVAILABLE", but at the same time, any guest that enters when it says "AVAILABLE" understands very clearly that no one is in there. This is a great example of precicely what a mutex is (similar to the labyrinth entrance). 


### Design Breakdown
To implement the second solution we use a similar structure to the labyrinth but actually a bit more simple. We select guests at random as "wanting" to enter the showroom, similar to the minotaur selecting guests to enter the labyrinth. However, all guests are doing the same thing in this case, no designated "checker". The idea is that we use a mutex that represents the entrance to the showroom. When a guest is interested in entering the showroom, they will try to see if the showroom is available by checking the mutex, if it is, they enter. Once they leave, the mutex / entrance gets unlocked and others may enter.

Once a guest enters the showroom and it is there first time entering it adds to a total count of unique views of the vase. The moment that value hits the same as the number of guests, all threads are joined up and the output is printed to the console.

### Compiling and Running
To compile the code, navigate to the location of this repo in your terminal and run the following:
```
g++ crystal_vase.cpp -o crystal_vase
```
Then, run the code by running the executable:
```
./crystal_vase
```
The code will output when a guest has seen the vase for the first time and when all guests have entered the showroom.

### Evaluation
The randomness involved in this one is even deeper compared to the labyrinth question. Now the guests are not just randomely interested in entering the showroom, but if the showroom is occupied, they walk around the party for some random amount of time. As a result, the times can be much longer than the previous one.

Here are a range of runtimes for a given number of guests (note these are in seconds because they take much longer!):
- 10 guests: 1-3s
- 25 guests: 6-9s
- 50 guests: 16-20s
- 100 guests: 31-40s