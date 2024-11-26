import random
import threading
from time import time

class ThreadSafeCounter:
    def __init__(self):
        self.lock = threading.Lock()
        self.count = 0

    def increment(self, value):
        with self.lock:
            self.count += value


def calculate_pi_part(n_points, counter):
    local_count = 0
    for _ in range(n_points):
        x = random.uniform(-1, 1)
        y = random.uniform(-1, 1)
        if x**2 + y**2 <= 1:
            local_count += 1
    counter.increment(local_count)

if __name__ == "__main__":
    n = 10_000_000 
    num_threads = 8  
    points_per_thread = n // num_threads  

    counter = ThreadSafeCounter()
    threads = []

    start_time = time()

   
    for _ in range(num_threads):
        thread = threading.Thread(target=calculate_pi_part, args=(points_per_thread, counter))
        threads.append(thread)
        thread.start()

    
    for thread in threads:
        thread.join()

   
    pi = 4 * counter.count / n
    end_time = time()

    print(f"pi: {pi:.5f}, total points: {n}, inside circle: {counter.count}")
    print(f"Elapsed time: {end_time - start_time:.5f} seconds")
