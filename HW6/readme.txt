In this assignment, we were made to patch the ray tracer code so that it would
support multithreading. Due to the relative simplicity of the code itself and it
being embarrassingly parallel, this was easily done without too much knowledge
of how the ray tracer code actually functioned.

This was done by seperating the pieces of code that managed the actual pixels
into a seperate function. This function would then be called by the threads
through the function pthread_create. We would also pass a void point to this
function as a parameter, which would later be turned into an int that would
be used to specify which columns it would be in charge of.

We parallelize the function by seperating each column of pixels, telling
each thread to work on certain columns. For example, in the case of two
threads, in an image with eight columns, the following is the column assignments
(where the second row describes whether the first thread or the second
thread was in charge of the pixels in that column)

1 2 3 4 5 6 7 8
1 2 1 2 1 2 1 2

Additionally, to make sure that internal race conditions is not an issue,
instead of directly outputting the pixels, we instead put them into an
organized array, which would then be read from at the end of the program.

Personally, one issue that I ran into was the parameter that was passed in
had to be of the type void*. This was an issue because as opposed to regular
ints, the value that the pointer points to can change. In order to circumvent
this issue, I was forced to put the IDs in an array, instead of pointing
directly at the i variable.

This seemed to be extremely successful, as shown in the results below:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m41.060s
user    0m41.053s
sys     0m0.002s

time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m20.745s
user    0m41.246s
sys     0m0.002s

time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m10.782s
user    0m42.810s
sys     0m0.002s

time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m5.769s
user    0m44.642s
sys     0m0.004s

As we can see, the amount of time taken approximately halved every time
we doubled the amount of threads being used. As such, this implementation
greatly improves the performance of this program.
