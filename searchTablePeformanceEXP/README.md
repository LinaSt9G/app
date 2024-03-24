# [Experiment] What is the fastest way to search a table ?


## Table specification
|Index (`uint64_t`)|Value (`uint64_t`)|
|:--:|:--:|
|11850348733280213828ULL | 0ULL|
|11284608248952433500ULL | 1ULL|
| 4408355960716143467ULL | 2ULL|
|13471053399952226235ULL | 3ULL|
| 2692228457840470818ULL | 4ULL|
| 2501853370058879561ULL | 5ULL|
| 4971366770881955338ULL | 6ULL|
| 7362217287770153172ULL | 7ULL|
|... | ...|

- Here, `uint64_t` variable takes `0ULL` to `18446744073709551615ULL`.
- There are no duplicates in the table **Indexes**.
- The **index** is chosen from a subset of `uint64_t` integers. The index of the table does not contain all of the integers in `uint64_t`.
- This table **does not** add, delete, or change table data during program execution.


## What I want to do ?
If I receive an index number (say `2501853370058879561ULL`), I want to search the table and get the value (in this case `5ULL`) at that index number.  


## What I want research ?
What is the fastest way to implement a table to search a table?  
Usually programers think of `map` data stucture, which has a {`key`, `value`} combination. However if the tables has `n` datas, serach takes `O(n)` or `O(log(n))` time.  
Is there are way to serach by `O(1)` time ? Yes, there is. All you have to do is to calcurate the `value` from `key` directory, instead of searching.  

Now, I prepared the following ways of direct calcurate.
- array
- if
- switch
- calcurate value by compare operator

## Experiment 
1. unordered_map
2. array
3. if
4. switch
5. compare operator

Table has '10000' datas and search `10000` elements by random order.

## Result
Too big `array` can't comppile : `uint64_t array[18446744073709551615ULL];`.  
Others can do.

### Compile optimize option : `default`
```
== test start

[1] map
[1] map end. Time spent: 0.002289805 seconds

[2] if
[2] if end. Time spent: 0.392647530 seconds

[3] switch
[3] switch end. Time spent: 0.051384078 seconds

[4] compare
[4] compare end. Time spent: 0.408382896 seconds
```

In short, `map << switch << if < compare `.

### Compile optimize option : `-O3` (most optimized)

```
== test start

[1] map
[1] map end. Time spent: 0.000387068 seconds

[2] if
[2] if end. Time spent: 0.000002213 seconds

[3] switch
[3] switch end. Time spent: 0.000961915 seconds

[4] compare
[4] compare end. Time spent: 0.000002225 seconds
```

In short, `if = compare <<< map < switch `.

### Overall 
In short, `if(-O3) = compare(-O3) <<< map(-O3) < switch(-O3) << map(default) << switch(default) << if(default) < compare(default)`.