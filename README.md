# ft_minirt

Our own **ray tracing**, 42 project with [Chanmachan](https://github.com/Chanmachan)

<img width="399" alt="image" src="https://user-images.githubusercontent.com/101627898/225529552-9447cbf7-9fec-49e2-ae7f-f9b752ebb7c2.png">

### How to use

```
make && ./miniRT <scene.rt>
```

Sample ``.rt`` files are in ``rt_files`` directory.

Or in short,

```
./test.sh
```

### Format of .rt File

.rt files need at least one Camera, Ambient Light and Light. The geometric shapes available are planes, cylinders and spheres.

| **Objects**   | **Input**                                            | **Example**                      |
| ------------- | ---------------------------------------------------- | ---------------------------------|
| Camera        | C  [coordinate] [vector] [field of view]             | C  -10,0,0 -1,0,0 90             |
| Ambient Light | A  [brightness] [rgb color]                          | A  0.3 0,255,0                   |
| Light         | L  [coordinate] [brightness] [rgb color]             | L 0,-10,10 0.13 255,255,255      |
| Plane         | pl [coordinate] [vector] [rgb color] [checker_width] | pl 0,0,0 0,1,0 255,0,255 1.0     |
| Sphere        | sp [coordinate] [diameter] [rgb color]               | sp 0,0,0 3 0,0,255               |
| Cylinder      | cy [coordinate] [vector] [diameter] [height] [color] | cy 0,0,0 0,0,1 3 5 145,39,79     |
| Cone          | co [coordinate] [vector] [diameter] [height] [color] | co 0,0,0 0,1,0 10 10 255,255,255 |
