# The bare-mental demo for Thrust

## `vector_sort`

The `vector_sort.cu` is copied from offical readme [https://github.com/thrust/thrust](https://github.com/thrust/thrust), and we tested:

* customized thrust version (by giving `-DThrust_DIR`)
* three backends currently supported (CUDA, TBB, OpenMP)

And the results are:

``` vi
$./vector_cuda 
vec len: 536870912
time: 23308.4
t1-t0: 10386.2
t2-t1: 12680.8
t3-t2: 241.32

$./vector_tbb 
vec len: 536870912
time: 38487.9
t1-t0: 10554.6
t2-t1: 27732.7
t3-t2: 200.56

$./vector_omp 
vec len: 536870912
time: 72577
t1-t0: 10663.6
t2-t1: 61704.9
t3-t2: 208.532
```



