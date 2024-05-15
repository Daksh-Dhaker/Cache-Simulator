# CacheSim

CacheSim is a cache simulator program that simulates a cache memory hierarchy with various configurations and policies.

## Introduction

CacheSim allows users to simulate cache behavior under different configurations such as the number of sets per cache, number of blocks per set, block size, and various cache policies including write allocation, write-back, and replacement policies like Least Recently Used (LRU).

## Requirements

- Linux or Unix-like operating system
- C compiler (e.g., GCC)

## Building CacheSim

1. Clone this repository to your local machine:

    ```bash
    https://github.com/Daksh-Dhaker/Cache-Simulator.git
    ```

2. Navigate to the project directory:

    ```bash
    cd cachesim
    ```

3. Build the cache simulator using the provided Makefile:

    ```bash
    make
    ```

## Usage

After building the cache simulator, you can run it with the desired parameters and cache configurations. Here's the basic command structure:

```bash
./cacheSim <sets> <blocks_per_set> <block_size> <write_policy> <replacement_policy> < <tracefile>
```

## Example

```bash
./cacheSim 256 4 16 write-allocate write-back lru < sometracefile
```
