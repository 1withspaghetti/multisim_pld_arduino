import getComponentDefinition from "./getComponentDefinition";
import parseVHDL from "./parseVHDL";

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
        componentCode.reduce((acc, code) => acc + ( // Bytes for each component
            1 + // 1 byte for the component type
            code.paramLength // bytes for the parameters
        ), 0)
    console.log("Buffer size", bufferSize);
    

    const buffer = new ArrayBuffer(bufferSize);
    const view = new DataView(buffer);

    view.setUint16(0, bufferSize); // Set the size of the buffer
    view.setUint16(2, stackSize); // Set the size of the stack
    let offset = 4; // Start after the size of the buffer
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
