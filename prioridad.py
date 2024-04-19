class Process:
    def __init__(self, id, burst_time, priority, time_slice=0, waiting_time=0):
        self.id = id
        self.burst_time = burst_time
        self.priority = priority
        self.time_slice = time_slice
        self.waiting_time = waiting_time

class Queue:
    def __init__(self):
        self.queue = []
        self.front = -1
        self.rear = -1

    def is_empty(self):
        return len(self.queue) == 0

    def is_full(self):
        return len(self.queue) == 10

    def enqueue(self, process):
        if self.is_full():
            return False
        self.queue.append(process)
        if self.front == -1:
            self.front = 0
        self.rear += 1
        return True

    def dequeue(self):
        if self.is_empty():
            return None
        process = self.queue.pop(0)
        if len(self.queue) == 0:
            self.front = -1
            self.rear = -1
        return process

def process_execution(queues, waiting_list):
    for q in queues:
        if not q.is_empty():
            process = q.dequeue()
            print(f"Proceso {process.id} en ejecución con tiempo de burst {process.burst_time}, prioridad {process.priority}, y tiempo de espera {process.waiting_time}")
            process.time_slice += 1
            process.burst_time -= 1

            if process.time_slice >= 3:
                process.priority = max(0, process.priority - 1)
                process.time_slice = 0

            if process.burst_time > 0:
                queues[process.priority].enqueue(process)
            break

    i = 0
    while i < len(waiting_list):
        process = waiting_list[i]
        process.waiting_time += 1
        if queues[process.priority].enqueue(process):
            waiting_list.pop(i)
        else:
            i += 1

# Setup queues
high_priority = Queue()
medium_priority = Queue()
low_priority = Queue()
queues = [high_priority, medium_priority, low_priority]
waiting_list = []

# Create processes and manage queueing
for i in range(90):
    process = Process(id=i + 1, burst_time=10 - (i % 3), priority=2 - (i % 3))
    if not queues[process.priority].enqueue(process):
        waiting_list.append(process)

# Process execution until all queues and waiting list are empty
while any(not q.is_empty() for q in queues) or waiting_list:
    process_execution(queues, waiting_list)
