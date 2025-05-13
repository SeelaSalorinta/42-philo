# 🍝 Philo – My First Concurrency Project!

For my ninth project at Hive Helsinki, I stepped into the world of multithreading and built a simulation of the classic **Dining Philosophers Problem** using `pthreads` and `mutexes`! 🧠🔧

In this simulation, a group of philosophers sit around a table, alternating between thinking, eating, and sleeping — but there’s a catch...

---

## 🪑 Each Philosopher:

- Is a **separate thread** 🧵
- Needs **two forks to eat** 🍴🍝
- Shares forks (protected by **mutexes**) with their neighbors
- **Dies** if they don’t eat in time 😵‍💫

---

## 🧾 Program Rules

The program takes the following arguments:

  ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

---

### 📌 Arguments explained:

- `number_of_philosophers`: How many hungry thinkers at the table
- `time_to_die`: Max time (in ms) a philosopher can go without eating 💀
- `time_to_eat`: Time (in ms) spent eating 🍽️
- `time_to_sleep`: Time (in ms) spent sleeping 😴
- `number_of_times_each_philosopher_must_eat` (optional): If provided, the sim ends when all philosophers have eaten enough 🍛

---

## 🧠 Philosopher Behavior

Each philosopher alternates between:

- Thinking 🧠
- Taking forks 🍴
- Eating 🍝
- Sleeping 🛌

---

## 🧷 Safety and Precision

- **Forks** are protected with **mutexes** 🛡️
- A dedicated **monitoring thread** checks all philosophers constantly to detect any death within **10ms** ⚠️
- All logs follow this format:
  timestamp_in_ms X is eating/thinking/sleeping/has taken a fork/died


---

## 🧠 Challenges

- ❌ No global variables
- 📄 No overlapping logs (clean and readable output)
- 🔒 Must avoid data races (thread safety is crucial!)
- 🧵 Real-time monitoring with proper synchronization

---

## 📝 What I Learned

This project taught me a lot about:

- Multithreading
- Synchronization and mutexes
- Detecting and preventing race conditions
- The challenge of starvation and deadlock prevention
