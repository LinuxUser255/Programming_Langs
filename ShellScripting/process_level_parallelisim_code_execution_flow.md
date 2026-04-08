Here's how the execution flows — each function has a distinct role, and they nest cleanly:Here's the execution story top to bottom:

**`main()` is the dispatcher.** It runs a loop from 1 to 10, calling `run_pool` on each number. It has no idea what a task is or how many jobs are running — it just hands work to `run_pool` and moves on.

**`run_pool()` is the gatekeeper.** Every time it receives a number from `main`, it does two things: fires `task "$1" &` in the background and saves the resulting PID into `joblist`. Then it checks — if the pool is full (`joblist >= MAX_JOBS`), it blocks and waits for the *oldest* job to finish before returning control to `main`. That feedback loop on the left of the diagram is the semaphore — it's what keeps the pool from overflowing.

**`task()` is the worker.** Each instance runs independently in its own subprocess. It knows nothing about the pool, nothing about other tasks, nothing about `main`. It just does its job — makes a directory, writes 10 files — and exits. The `&` is what makes them all run in parallel.

**`wait` at the end of `main()` is the drain.** After the loop finishes dispatching all 10 items, there may still be jobs running in the background. The final `wait` holds the script open until every last background process finishes before printing "All done."

The key insight is that **each function has exactly one responsibility** and never reaches into another layer's concern. That's what makes the pattern clean and reusable.
