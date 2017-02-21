# Flags
This file defines the flags that could be used to enable or disable
some feature of the library. Here's the name, the default value and
the consequence by setting them.

### `_CNG_NODEFAULT_GS_=false`
Setting this flag to `true` will prevent the default Graphics from 
being compiled. You will have to provide your own graphics
implementation this case. Please refer to `include/cng/graphics.h`
for detail.
