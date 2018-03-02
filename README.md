# Using SDL2 with bazel

## This repositories quirks

* Only works on windows x64
* Must copy SDL2.dll before running

### Building

```bat
bazel build //:bazel-sdl2-hello
```

### Copy SDL2.dll
Only have to do this once (unless you clean)

```bat
copy .\bazel-bazel-sdl2-hello\external\SDL2\lib\x64\SDL2.dll .\bazel-bin\
```

### Running

```bat
bazel run //:bazel-sdl2-hello
```
