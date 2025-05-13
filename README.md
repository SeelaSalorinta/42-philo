# 🍝 Philo – My First Concurrency Project!

### For my ninth project at Hive Helsinki, I stepped into the world of multithreading and 
### built a simulation of the classic Dining Philosophers Problem using pthreads and mutexes! 🧠🔧

In this simulation, a group of philosophers sit around a table, alternating between thinking, eating, 
and sleeping — but there’s a catch...

#### 🪑 Each philosopher:

Is a separate thread 🧵

Needs two forks to eat 🍴🍝

Shares forks (protected by mutexes) with their neighbors

Dies if they don’t eat in time 😵‍💫

#### 🧾 Program Rules:
The program takes the following arguments:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

#### 📌 Arguments explained:

number_of_philosophers: How many hungry thinkers at the table

time_to_die: Max time (in ms) a philosopher can go without eating 💀

time_to_eat: Time (in ms) spent eating 🍽️

time_to_sleep: Time (in ms) spent sleeping 😴

number_of_times_each_philosopher_must_eat (optional): If provided, the sim ends when all philosophers have eaten enough 🍛

#### 🧠 Philosopher Behavior:

Each philosopher alternates between:

Thinking 🧠

Taking forks 🍴

Eating 🍝

Sleeping 🛌

#### 🧷 Safety and Precision:

Forks are protected with mutexes 🛡️

A dedicated monitoring thread constantly checks for dead philosophers and ensures that all deaths are detected within 10ms ⚠️

All logs follow a clean and consistent format:

timestamp_in_ms X is eating/thinking/sleeping/has taken a fork/died

#### 🧠 Challenges:

No global variables! ❌🌍

No overlapping logs (clean output) 📄

Must avoid data races (thread safety is key!) 🧵🔒

Keeping monitoring and philosopher threads in sync without delays

## This project taught me a ton about concurrency, synchronization, and the subtle art of starvation prevention. 
