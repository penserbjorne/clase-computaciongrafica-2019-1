# clase-computaciongrafica-2019-1
Proyecto final para la clase de Computación Gráfica, FI, UNAM, 2019-1

## Requerimientos del proyecto

**Objetivo:** Crear un renderizador de una escena aplicando técnicas de graficación ray-tracing,

**Elementos a implementar**

- [ ] (5%) Leer de un archivo la configuración de su mundo, el formato que se debe manejar son archivos YAML (Obligatorio).
- [ ] Se podrá configurar los siguientes elementos.
  - [ ] (10%) Luces: Se pondrá configurar los diferentes tipos de luces.
    - [ ] Spot
    - [ ] Point
  - [ ] (10%) Modelos: Los modelos geométricos que se debe implementar son:
    - [x] Cubos
    - [x] Cilindros
    - [ ] Esferas
    - [ ] Prismas
    - [ ] Modelos en formato OBJ
    - [ ] Planos
  - [ ] (10%) Se podrá colocar una textura a cada modelo, si el objeto es reflectivo o refractivo.
  - [ ] (10%) Múltiples cámaras.
    - [ ] Manejar la cámara en primera persona y la cámara orbital (Arcball).
      - [ ] Para ambas cámaras los movimientos de pitch y yaw realizarlos con el mouse.
    - [ ] Al seleccionar un objeto en específico de la escena crear una nueva cámara Orbital que permite visualizar al objeto desde todos los ángulos.
    - [ ] Se podrá cambiar las múltiples cámaras con combinaciones de teclas.
 - [ ] (10%) Configuración del orden del ray-tracing.
 - [ ] (10%) Para los objetos sólidos manejar sombras.
 - [ ] (35%) Optimizar el ray tracing con CUDA:
   - [ ] Ray-Tracing en paralelo, el reto está en la recursividad y concurrencia de los núcleos de CUDA.
   - [ ] Realizar una partición del mundo en Octrees utilizando CUDA.

## Uso

En construcción.

Utilizar como ejemplo de parámetro el archivo [example-world.yaml](./example-world.yaml).

## Recursos consultados
- [Introduction to OpenGL for Game Programmers by Jeremiah van Oosten.](https://www.3dgep.com/introduction-opengl/)
- [Using OpenGL Vertex Buffer Objects by Jeremiah van Oosten.](https://www.3dgep.com/using-opengl-vertex-buffer-objects/)

## Posibles recursos para consultar

### OpenGL

- [Normal Mapping with Cg and OpenGL by Jeremiah van Oosten.](https://www.3dgep.com/normal-mapping-with-cg-and-opengl/)
- [Texturing and Lighting in OpenGL by Jeremiah van Oosten.](https://www.3dgep.com/texturing-and-lighting-in-opengl/)
- [Loading and Animating MD5 Models with OpenGL by Jeremiah van Oosten.](https://www.3dgep.com/loading-and-animating-md5-models-with-opengl/)

#### GLSL y otras cosas ;@

- [Introduction to OpenGL and GLSL by Jeremiah van Oosten.](https://www.3dgep.com/introduction-to-opengl-and-glsl/)
- [Texturing and Lighting with OpenGL and GLSL by Jeremiah van Oosten.](https://www.3dgep.com/texturing-and-lighting-with-opengl-and-glsl/)
- [Forward vs Deferred vs Forward+ Rendering with DirectX 11 by Jeremiah van Oosten.](https://www.3dgep.com/forward-plus/)

### CUDA

- [Introduction to CUDA using Visual Studio 2008 by Jeremiah van Oosten.](https://www.3dgep.com/introduction-to-cuda-using-visual-studio-2008/)
- [CUDA Thread Execution Model by Jeremiah van Oosten.](https://www.3dgep.com/cuda-thread-execution-model/)
- [CUDA Memory Model by Jeremiah van Oosten.](https://www.3dgep.com/cuda-memory-model/)
- [Introduction to CUDA 5.0 by Jeremiah van Oosten.](https://www.3dgep.com/introduction-to-cuda-5-0/)
- [OpenGL Interoperability with CUDA by Jeremiah van Oosten.](https://www.3dgep.com/opengl-interoperability-with-cuda/)
- [Optimizing CUDA Applications by Jeremiah van Oosten.](https://www.3dgep.com/optimizing-cuda-applications/)

### Ray Tracing
- [Ray Tracing in One Weekend by Peter Shirley.](https://github.com/petershirley/raytracinginoneweekend)
- [Ray Tracing The Next Week by Peter Shirley.](https://github.com/petershirley/raytracingthenextweek)
- [Ray Tracing The Rest of Your Life by Peter Shirley.](https://github.com/petershirley/raytracingtherestofyourlife)
