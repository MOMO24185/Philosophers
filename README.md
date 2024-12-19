# Philosophers

## Overview
The "Philosophers" project is a practical implementation of the classic Dining Philosophers Problem. This problem explores the complexities of multi-threaded programming by simulating philosophers who alternately think and eat while sharing limited resources (forks). The project emphasizes advanced memory management techniques to prevent deadlocks and data races, offering a deep understanding of concurrent programming challenges.

## Features
- **Threading:** Implements threads to simulate philosophers' concurrent behavior.
- **Mutexes:** Ensures safe access to shared resources (forks).
- **Deadlock Avoidance:** Applies strategies to prevent circular waits and ensure system progress.
- **Data Race Prevention:** Ensures consistent and predictable behavior in a multi-threaded environment.
- **Real-Time Simulation:** Displays the philosophers' actions in real-time.

## How It Works
1. **Initialization:**
   - The program initializes philosophers, forks, and the required synchronization primitives (mutexes).

2. **Simulation:**
   - Each philosopher alternates between thinking, picking up forks to eat, and then returning to thinking.
   - Philosophers coordinate their actions to avoid deadlocks and minimize starvation.

3. **Termination:**
   - The program runs for a defined simulation duration or until all philosophers have completed their tasks.

## Usage
### Compilation
Compile the program using the `Makefile`:
```bash
make
```

### Running the Program
Execute the program with the following syntax:
```bash
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

#### Example:
```bash
./philosophers 5 800 200 200 2
```
This command simulates 5 philosophers with the following conditions:
- Each philosopher dies if they don't eat within 800ms.
- Each philosopher takes 200ms to eat.
- Each philosopher takes 200ms to sleep.
- (Optional) Number of times each philosopher must eat before terminating the program.

## Key Concepts
### Dining Philosophers Problem
This classic problem illustrates synchronization issues in concurrent programming. Philosophers seated at a round table need to pick up two forks (shared resources) to eat but must put them down after eating to allow others access.

### Deadlock Avoidance
The project uses techniques like:
- **Odd/Even Fork Ordering:** Philosophers pick up forks in a specific order to prevent circular waits.
- **State Checking:** Ensures forks are available before attempting to pick them up.

## Challenges Addressed
- **Deadlocks:** Ensures that no philosopher gets stuck waiting indefinitely for resources.
- **Starvation:** Guarantees fair access to forks for all philosophers.
- **Data Races:** Safeguards shared data integrity using mutexes.

## License
This project is released under the MIT License.

