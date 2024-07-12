# Philosophers Project

## Overview

The Philosophers project is a classic synchronization problem often used in concurrent algorithm design to illustrate synchronization issues and 
techniques for resolving them. This project is part of the curriculum at 42 Paris and involves simulating a scenario where philosophers alternately think, eat, and sleep.

## Project Structure

The project is organized into several source files and headers, each handling different aspects of the simulation:

### Source Files

-   `main.c`: Entry point of the program, initializes the simulation and starts the philosopher threads.
-   `exit.c`: Handles error messages and resource cleanup.
-   `init.c`: Initializes the philosopher and table structures, including mutexes.
-   `parsing.c`: Parses command-line arguments and sets up the simulation parameters.
-   `philosopher.c`: Contains the main logic for the philosopher's actions (thinking, eating, sleeping).
-   `supervisor.c`: Monitors the state of the philosophers and stops the simulation if necessary.
-   `time.c`: Provides time-related utility functions.

### Header Files

-   `philo.h`: Contains the definitions of structures, constants, and function prototypes used throughout the project.

### Makefile

The `Makefile` is used to compile the project. It defines the compilation rules and dependencies.

## Compilation

To compile the project, you can use the `make` command. This will produce an executable named `philo`.

## Usage

To run the simulation, use the following command:

`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\`

-   `number_of_philosophers`: The number of philosophers and forks.
-   `time_to_die`: Time in milliseconds a philosopher can go without eating before dying.
-   `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
-   `time_to_sleep`: Time in milliseconds a philosopher will sleep after eating.
-   `number_of_times_each_philosopher_must_eat` (optional): If all philosophers eat at least this many times, the simulation stops. If not specified, the simulation will run indefinitely.

## Example

To run the simulation with 5 philosophers, 800 milliseconds to die, 200 milliseconds to eat, 200 milliseconds to sleep, and 10 times each philosopher must eat, you can run the following command:

`./philo 5 800 200 200 10`

## Conclusion

The Philosophers project is an excellent exercise in understanding concurrency, synchronization, and the challenges of multi-threaded programming. By completing 
this project, students at 42 Paris gain valuable experience in managing resources and ensuring thread safety in a concurrent environment.
