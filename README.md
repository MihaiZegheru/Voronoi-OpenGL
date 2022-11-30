# Voronoi-OpenGL

OpenGL project that generates a Voronoi diagram with moving seeds 


## Installing

Download the [latest release](https://github.com/MihaiZegheru/Voronoi-OpenGL/releases/latest).


## Building

Make sure you are in `/`
```bash
mkdir build
cd build
cmake ..
```

## Usage

Compile and run the project.
#

### Distances
You can change the way the Voronoi diagram is rendered by manipulating the distances 
```cpp
float EuclideanDistance(vec2 a, vec2 b);
float ManhattanDistance(vec2 a, vec2 b);
float ChebyshevDistance(vec2 a, vec2 b);
float MinkowskiDistance(vec2 a, vec2 b, float p);
```

Change the function on this line in `defaultfragmentshader.glsl`.

```cpp
gl_FragDepth =  MinkowskiDistance(seedPos, gl_FragCoord.xy, MINKOWSKI_VALUE) / length(screenRes);
```
#

### Seeds
You can also change the number of seeds(voronoi generators) by changing this field in `main.cpp`
```cpp
#define SEEDS_COUNT 10
```
**Note**
Please note that the seeds are generated randomly and there is no current implementation of a special noise function.
#

### Window Size
You can set the initial window size by changing these fields in `main.cpp`
```cpp
#define WINDOW_WIDTH  1000;
#define WINDOW_HEIGHT 1000;
```

## License

[MIT](https://github.com/MihaiZegheru/Voronoi-OpenGL/blob/main/LICENSE)
