import getComponentDefinition from "./getComponentDefinition";
import parseVHDL from "./parseVHDL";

// Key is the id of the entity port, value is the location in the gpio on the stack
const IO_ID_TO_GPIO: Record<string, number> = {
    "BTN0": 40,
    "BTN1": 41,
    "LED1": 11,
    "LED2": 12,
    "LED3": 13,
    "LED4": 14,
    "SEGA_PIO09": 4,
    "SEGB_PIO08": 5,
    "SEGC_PIO07": 6,
    "SEGD_PIO06": 7,
    "SEGE_PIO05": 8,
    "SEGF_PIO04": 9,
    "SEGG_PIO03": 10,
    "DIG0_PIO01": 15,
    "DIG1_PIO02": 16,
    "Ext_Clk_In_PIO16": 21,
}
export function getGPIOByPortName(portName: string) {
    const gpio = IO_ID_TO_GPIO[portName];
    if (gpio === undefined) {
        throw new Error(`Unknown port name ${portName} for GPIO lookup`);
    }
    return gpio;
}

export default function processVHDL(code: string) {

    // Parse the VHDL code and get all the components
    // and signals used in the code
    const {entity, signals, components} = parseVHDL(code);
    console.log("Parsed code", {entity, signals, components});

    // In bits!!
    let stackSize = 0;
    function alloc(size: number = 8) {
        const loc = stackSize;
        stackSize += size;
        return loc;
    }

    // Place in stack where all the current signal (wire) states are located
    const signalPointers = signals.map(signal => {
        const pointer = alloc(1); // 1 bit for each signal, high or low
        return {
            id: signal.id,
            type: signal.type,
            pointer: pointer
        }
    });

    const componentCode = components.map((component) => getComponentDefinition(component, alloc, signalPointers));

    console.log(componentCode.length, " components processed", componentCode);
    console.log(signalPointers.length, " signals processed", signalPointers);
    console.log(stackSize, " bits allocated");

    // Bytes
    const bufferSize = 
        2 + // 2 bytes for the size of the buffer (in bytes)
        2 + // 2 bytes for the stack length (in bits)
        2 + // 2 bytes for the number of GPIOs to init
        entity.ports.length * 2 + // 2 bytes for each GPIO (1 byte for the GPIO number, 1 byte for the type)
        componentCode.reduce((acc, code) => acc + ( // Bytes for each component
            1 + // 1 byte for the component type
            code.paramLength // bytes for the parameters
        ), 0)
    console.log("Buffer size", bufferSize);
    console.log("Stack size", stackSize);
    console.log("GPIO size", entity.ports.length * 2);
    

    const buffer = new ArrayBuffer(bufferSize);
    const view = new DataView(buffer);

    view.setUint16(0, bufferSize); // Set the size of the buffer
    view.setUint16(2, stackSize); // Set the size of the stack
    view.setUint16(4, entity.ports.length); // Set the number of GPIOs to init
    let offset = 6; // Start after the size of the buffer
    // Write the GPIOs to the buffer
    for (let i = 0; i < entity.ports.length; i++) {
        const port = entity.ports[i];
        view.setUint8(offset, getGPIOByPortName(port.name)); // Set the GPIO number
        offset += 1; // Move to the next byte
        view.setUint8(offset, port.direction.toLowerCase().includes("in") ? 0x01 : 0x03); // Set the input (1) or output (3) type
        offset += 1; // Move to the next bytes
        console.log("GPIO", port.name, "->", getGPIOByPortName(port.name), "direction", port.direction);
    }
    // Write the component code to the buffer
    for (const component of componentCode) {
        view.setUint8(offset, component.type); // Set the type of the component
        offset += 1; // Move to the next byte
        for (const param of component.params) {
            if (param.len === 1) view.setUint8(offset, param.val);
            else if (param.len === 2) view.setUint16(offset, param.val);
            else if (param.len === 4) view.setUint32(offset, param.val);
            else throw new Error("Invalid parameter length " + param.len);
            offset += param.len; // Move to the next byte
        }
    }

    if (offset !== bufferSize) throw new Error("Buffer size mismatch " + offset + " != " + bufferSize);
    console.log("Buffer", buffer);
    return buffer;
}
