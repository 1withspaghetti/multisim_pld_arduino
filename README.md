# multisim_pld_arduino
Compile Multisim 14 VHDL files (.vhd) to custom bytecode that can emulate a PLD on arduino hardware using the emulator firmware

## [Compiler](./compiler/)
Simple website built on Vite + Svelte + Typescript + Tailwindcss

For the compiling, it uses 4 main files: 
- [processVHDL.ts](./compiler/src/lib/processVHDL.ts) - Main compiling file, calls functions from the other files to parse and get component definitions. Assembles the virtual stack and builds the bytecode off the parsed data. 
- [parseVHDL.ts](./compiler/src/lib/parseVHDL.ts) - Takes a .VHD file exported from multisim and parses the VHDL code for all the ports, signals (aka wires), components/connections (port maps) into program objects 
- [getComponentDefinition.ts](./compiler/src/lib/getComponentDefinition.ts) - For each component, based on the type (AND2, NAND5, etc.) assigns a numeric id for the type as well as assigns parameters for it, such as pointers for where in the stack memory the wire state is for the inputs and outputs 
- [App.svelte](./compiler/src/App.svelte) - Contains the simple frontend code for the form and buttons to interact with the compiler

## [Emulator](./emulator_firmware/)
C++ Arduino Code using the PlatformIO framework, intended to run on a micro esp32 arduino. 

For emulating, it uses 4 main files: 
- [main.cpp](./emulator_firmware/src/main.cpp) - Main file, on startup it allocates memory for the stack and then loops through each component of the bytecode and executes it using definitions in another file 
- [components.cpp](./emulator_firmware/src/components.cpp)/[h](./emulator_firmware/src/components.h) - For each component, depending on the type, uses the parameters to get locations in memory and perform the functions of the component, such as AND or XOR 
- [util.cpp](./emulator_firmware/src/util.cpp)/[h](./emulator_firmware/src/util.h) - Utility functions for manipulating memory from pointers and reading bytes from the bytecode 
- [pld_bytecode.h](./emulator_firmware/src/pld_bytecode.h) - File where the exported bytecode from the compiler is pasted 