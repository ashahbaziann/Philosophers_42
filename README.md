# Philosophers

A multithreaded simulation of the classic **Dining Philosophers** problem, implemented in C using POSIX threads and mutexes.

## About

A number of philosophers sit around a table with a fork between each pair of them. Each philosopher alternates between three states — eating, thinking, and sleeping — but needs to pick up both the fork to their left and the fork to their right to eat. Since forks are shared between neighbors, philosophers must coordinate access without starving or deadlocking one another.

Each philosopher runs on its own thread, and forks are represented as mutexes shared between adjacent philosophers. The simulation ends either when a philosopher starves (doesn't eat in time) or when every philosopher has eaten the required number of meals (if specified).

## Rules of the Simulation

- A philosopher must pick up their left and right forks (in some order) before eating.
- A philosopher can only eat when holding both forks.
- After eating, a philosopher puts down both forks and goes to sleep.
- If a philosopher goes too long without eating (`time_to_die`), the simulation stops and that philosopher's death is logged.
- The simulation can also stop early if every philosopher has eaten at least `eating_limit` times (when provided).

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Time (ms) a philosopher can go without eating before dying |
| `time_to_eat` | Time (ms) it takes a philosopher to eat |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(optional)* Simulation stops once every philosopher has eaten this many times |

**Example:**

```bash
./philo 5 800 200 200
./philo 4 410 200 200 7
```

## Building

```bash
make        # builds the philo executable
make clean  # removes object files
make fclean # removes object files and the executable
make re     # rebuilds from scratch
```

## Project Structure

Key data structures:

- **`t_data`** — shared simulation state: timing parameters, fork mutexes, and control mutexes (start time, simulation status, meal count tracking).
- **`t_philo`** — per-philosopher state: id, meals eaten, last meal timestamp, and pointers to its left/right fork mutexes.

Core source areas (by function grouping in the header):

| Area | Responsibility |
|---|---|
| Validation | Parses and validates command-line arguments |
| Init | Sets up `t_data`, allocates philosophers and forks |
| Utils | Helpers: `ft_atoi`, `get_time`, `ft_sleep`, string checks |
| Simulation control | `simulation_on`, `display_state`, thread creation/joining, cleanup |
| Simulation | `start_simulation` — kicks off philosopher threads and the death-watcher |
| Routine | `routine` — the per-philosopher thread loop (eat/sleep/think) |
| Wrappers | `mutex_handler` and `thread_handler` — centralized init/lock/unlock/create/join/destroy for mutexes and threads, with error handling |

## Concurrency Notes

- Mutexes protect: individual forks, each philosopher's `last_meal_time`, the shared meal counter, simulation on/off state, and console output (to avoid interleaved logs).
- Fork pickup order is handled carefully to avoid deadlock (e.g. asymmetric ordering between even/odd-numbered philosophers is a common approach for this project).
- A dedicated monitoring loop periodically checks each philosopher's `last_meal_time` against `time_to_die` to detect starvation.

## Notes

- This is a learning project (42 School curriculum) focused on threads, mutexes, race conditions, and deadlock avoidance in C.
- No dynamic memory is leaked by design in the 42 spec, and no invalid access to shared data should occur between threads.

## License

No license specified.
