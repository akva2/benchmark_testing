# benchmark_testing

Tests various microbenchmarking tools such as palanteer, tracy, easy-profiler, etc

To build, run

```bash
cmake <path to repo> -DPROGRAM_TIMER_BACKEND=<backend>
```

where ```<backend>``` is one of the following

 - `NONE`: No timing done
 - `PALANTEER`: palanteer timing
 - `TRACY` : tracy timing
 - `EASY_PROFILER`: easy_profiler
 - `MICROPROFILE`: microprofiler
 - `REMOTERY`: remotery
 
 Run the simulator by simply running
 
 ```bash
 ./simulator
 ```
 
 
