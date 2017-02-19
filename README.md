# CNG - CNG not GUI | Console Non-GUI
A wrap up library for GNU NCurses

### Box
Box is the most commonly used component in CNG.
A box consists of three parts:
- Content Pane: the reactive part of the component.
- Border: the bounding box of the box component.
- Margin: the outter paddings of the box.

The user will draw their content to the Content Pane, and input
will be dispatched into the pane if any.

The parent component locate their subcomponents by border. The user 
can resize the box by manipulating the border.

The margin is decorative portion and can receive input or manipulate.

Generally speaking, the content pane belongs to the box itself, the
border and margin belongs to its parent, though it is consider part
of the component while rendering.

### Layout & Dimension
The term layout usually depicts how components inside a container
is ordered and sized. While the term dimension is usually used to 
describe the size of a window or a component. 

The layout is usually assigned to a container. A component can assign 
a preferred dimension for itself, while its parent will allocate the 
actual dimension and position for the component.

### Main Loop
A main loop is common for GUI system. In the main loop, we usually
parses messages and dispatch to suitable components.
