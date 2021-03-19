# 3DOVE: 3D Object Viewer

## Team members
Ari Webb, Tejas Narayanan

## Project description
A 3D object viewer that reads a .obj file and displays the 3D model.
Users can rotate the camera around the model, as well as zoom in/out.

## Member contribution
**Ari**
* Triangle drawing
* Z-buffering
* Lighting calculations

**Tejas**
* Math and linear algebra libraries
* .obj file parsing
* Linear transformation library
* GPU library (unused)

## References

### Rendering concepts/math
* Pat Hanrahan's wonderful advice!
* Perspective projection: https://www.scratchapixel.com/lessons/3d-basic-rendering/rendering-3d-scene-overview/perspective-projection
* Camera/view matrices: https://www.3dgep.com/understanding-the-view-matrix/#Look_At_Camera

### Math library
* Square root calculation method: https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method

### 3D Models
* Monkey: Blender default shape (https://www.blender.org/)
* Wolf: https://free3d.com/3d-model/low-poly-wolf-71850.html
* Goat: https://free3d.com/3d-model/low-poly-goat-35241.html
* Cat: https://free3d.com/3d-model/low-poly-cat-46138.html
* Deer: https://free3d.com/3d-model/low-poly-deer-87801.html

### GPU Library
* VideoCore IV assembler/example programs: https://github.com/hermanhermitage/videocoreiv
  * The `tinyasm` module (GPU assembler) is from this repository. No additional changes were made.
* Mailbox properties documentation: https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
* Example of bare metal program that uses mailbox to get Raspberry Pi's serial number: https://github.com/bztsrc/raspi3-tutorial/tree/master/04_mailboxes
  * Used this code to understand how to use the mailbox to communicate with the GPU. No code was taken from this repository.
* Example program to peek/poke a memory address using the GPU: https://github.com/ali1234/vcpoke
  * Used this code to understand the process of executing a program on the GPU. No code was taken from this repository.

## Self-evaluation

We were able to meet all of our main goals for the project! The final renderer is
both faster and more accurate than we expected it to be. We learned a lot about
how different rendering techniques, such as z-buffering and perspective projection,
are implemented.

Seeing the cube and monkey render correctly for the first time was a wonderful moment!

We unfortunately didn't have enough time to translate the rendering to GPU assembly
to improve rendering speed, but we were able to make the viewer interactive. Users can use
the arrow keys to move the camera around the model.

## Photos

Video demo: https://drive.google.com/file/d/1jsQI91-H1OuIeEY4wmy1Li1u-xQmRkDC/view?usp=sharing

Suzanne, the default Blender monkey:
![Monkey](images/monkey.jpg)

An orange-colored wolf:
![Orange wolf](images/wolf_colored.jpg)

A z-buffer demonstration on the wolf model. Lighter colors are closer to the
camera than darker colors.
![Z-buffer of wolf](images/wolf_z_buffer.jpg)

A deer:
![Deer](images/deer.jpg)
