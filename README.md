# Philosophers - Solving the dining philosophers dilemma with threads

For this project, the challenge was code a solution for the following classical hypothesis:

One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating
nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their
left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again.
The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

The program created will provide logs similar to the following (example obtained with ./philo 8 800 200 200 5):

```
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 3 is sleeping
200 4 has taken a fork
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
200 4 has taken a fork
200 4 is eating
400 3 is thinking
400 1 is thinking
400 4 is sleeping
400 2 is sleeping
400 1 has taken a fork
400 3 has taken a fork
400 3 has taken a fork
400 3 is eating
400 1 has taken a fork
400 1 is eating
etc.
```

## How to use it

After cloning the repository, cd into it and run **make**. After that, you can use the following arguments:

```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]
```

The time values must be given in milliseconds. Large numbers of philosophers might not work. Have fun!
