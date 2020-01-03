# house_of_pepsipu
heap exploit by taking advantage of malloc(0) and topchunk size

malloc(0), as stated here: https://stackoverflow.com/questions/2022335/whats-the-point-in-malloc0, returns a perfectly valid pointer that is safe to be freed. Although it's not a chunk that has a size of 0, it returns a pointer that is very close to the top chunk size (libc 2.28). If a program allows you to write to a pointer returned by malloc(0), you are able to overwrite the top chunk's size, effectively allowing malloc to return a near arbitrary pointer using the House Of Force.

this is an example challenge showcasing such a bug
