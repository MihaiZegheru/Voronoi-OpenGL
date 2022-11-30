# Voronoi-OpenGL

OpenGL project that generates a Voronoi diagram with moving seeds 


<img
  src="https://user-images.githubusercontent.com/45045543/204884686-16e7083c-eff8-4ace-b5ad-de005d8ee0b6.png"
  alt="Euclidean Distances"
  title="Euclidean Distances"
  style="display: inline-block; margin: auto; padding: auto; width: auto">

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

### Controls
You can pause and unpause the animation by pressing `Q`

The key is defined in `inputmanager.cpp`
```cpp
if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    m_Q = true;
}
else {
    m_Q = false;
}
```
#

### Distances
You can change the way the Voronoi diagram is rendered by manipulating the distances.
```cpp
float EuclideanDistance(vec2 a, vec2 b);
float ManhattanDistance(vec2 a, vec2 b);
float ChebyshevDistance(vec2 a, vec2 b);
float MinkowskiDistance(vec2 a, vec2 b, float p);
```

Change the function on this line in `defaultfragmentshader.glsl`

```cpp
gl_FragDepth =  MinkowskiDistance(seedPos, gl_FragCoord.xy, MINKOWSKI_VALUE) / length(screenRes);
```

<img
  src="https://user-images.githubusercontent.com/45045543/204848704-8e901701-cb38-4fb9-9c85-9e1a6c1dcd2e.PNG"
  alt="Euclidean Distances"
  title="Euclidean Distances"
  style="display: inline-block; padding: auto; width: 32%;
  padding: auto">
<img
  src="https://user-images.githubusercontent.com/45045543/204849744-62c0fee6-e63a-414c-8a74-243da4cdd743.PNG"
  alt="MinkowskiDistance"
  title="MinkowskiDistance"
  style="display: inline-block; padding: auto; width: 32%; padding: auto">
<img
  src="https://user-images.githubusercontent.com/45045543/204849749-24c458f6-07e4-40ca-a67b-0ab9df4b91d3.PNG"
  alt="Manhattan Distances"
  title="Manhattan Distances"
  style="display: inline-block; padding: auto; width: 32%; padding: auto">

#

### Seeds
You can also change the number of seeds(voronoi generators) by changing this field in `main.cpp`
```cpp
#define SEEDS_COUNT 10
```
>**Note**
The seeds are generated randomly and there is no current implementation of a special noise function. This is the same for the colors.
#

### Window Size
You can set the initial window size by changing these fields in `main.cpp`
```cpp
#define WINDOW_WIDTH  1000;
#define WINDOW_HEIGHT 1000;
```

## Credits
* [How I got the idea](https://www.youtube.com/watch?v=kT-Mz87-HcQ)

* [About distances](https://towardsdatascience.com/9-distance-measures-in-data-science-918109d069fa)


## License

Voronoi-OpenGL is released under [MIT License](https://github.com/MihaiZegheru/Voronoi-OpenGL/blob/main/LICENSE).
