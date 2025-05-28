import { getGPIOByPortName } from "./processVHDL";
import type { Component } from "./types";

export default function getComponentDefinition(
    component: Component, 
    alloc: (size: number) => number,
    signalPointers: {id: string, type: string, pointer: number}[]
) {
    
    let id: number = 0; // 2 bytes
    let params = new ParamList(); // Data 


    // Helper functions
    function getPointerForSignal(id: string) {
        const signal = signalPointers.find(s => s.id === id);
        if (!signal) throw new Error("Could not find signal " + id);
        return signal.pointer;
    }
    function getPointersForSignals(ids: string[]) {
        return ids.map(id => getPointerForSignal(id));
    }

    function getSignalAtPort(portId: string) {
        const port = component.map.find(m => m.port === portId);
        if (!port) throw new Error("Could not find port " + port);
        return port.signal;
    }
    function getSignalsAtPorts(portIds: string[]) {
        return portIds.map(portId => getSignalAtPort(portId));
    }

    // Definitions for each component type
    
    let t = component.type;
    // id of 0 means no component, nothing happens
    if (t === "AUTO_IBUF") { // GPIO input
        id = 1;
        const [I, O] = getSignalsAtPorts(["I", "O"]);
        const GPIO = getGPIOByPortName(I);

        params.add(GPIO, 1); // 1 byte - GPIO
        params.addPointer(getPointerForSignal(O)); // pointer to signal
    } else if (t === "AUTO_OBUF") {
        id = 2;
        const [I, O] = getSignalsAtPorts(["I", "O"]);
        const GPIO = getGPIOByPortName(O);

        params.addPointer(getPointerForSignal(I)); // pointer to signal
        params.add(GPIO, 1); // 1 byte - GPIO
    } else if (t === "DIGITAL_HIGH_NI") {
        id = 3;
        params.addPointer(getPointerForSignal(getSignalAtPort("Y")));
    } else if (t === "DIGITAL_LOW_NI") {
        id = 4;
        params.addPointer(getPointerForSignal(getSignalAtPort("Y")));
    } else if (t === "INV_NI") {
        id = 5;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "Y"]
        )));
    } else if (t === "AND2_NI") {
        id = 10;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "Y"]
        )));
    } else if (t === "AND3_NI") {
        id = 11;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "Y"]
        )));
    } else if (t === "AND4_NI") {
        id = 12;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "Y"]
        )));
    } else if (t === "AND5_NI") {
        id = 13;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "Y"]
        )));
    } else if (t === "AND6_NI") {
        id = 14;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "Y"]
        )));
    } else if (t === "AND7_NI") {
        id = 15;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "Y"]
        )));
    } else if (t === "AND8_NI") {
        id = 16;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "H", "Y"]
        )));
    } else if (t === "NAND2_NI") {
        id = 20;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "Y"]
        )));
    } else if (t === "NAND3_NI") {
        id = 21;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "Y"]
        )));
    } else if (t === "NAND4_NI") {
        id = 22;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "Y"]
        )));
    } else if (t === "NAND5_NI") {
        id = 23;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "Y"]
        )));
    } else if (t === "NAND6_NI") {
        id = 24;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "Y"]
        )));
    } else if (t === "NAND7_NI") {
        id = 25;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "Y"]
        )));
    } else if (t === "NAND8_NI") {
        id = 26;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "H", "Y"]
        )));
    } else if (t === "NAND13") {
        id = 27;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "Y"]
        )));
    } else if (t === "OR2_NI") {
        id = 30;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "Y"]
        )));
    } else if (t === "OR3_NI") {
        id = 31;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "Y"]
        )));
    } else if (t === "OR4_NI") {
        id = 32;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "Y"]
        )));
    } else if (t === "OR5_NI") {
        id = 33;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "Y"]
        )));
    } else if (t === "OR6_NI") {
        id = 34;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "Y"]
        )));
    } else if (t === "OR7_NI") {
        id = 35;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "Y"]
        )));
    } else if (t === "OR8_NI") {
        id = 36;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "H", "Y"]
        )));
    } else if (t === "NOR2_NI") {
        id = 40;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "Y"]
        )));
    } else if (t === "NOR3_NI") {
        id = 41;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "Y"]
        )));
    } else if (t === "NOR4_NI") {
        id = 42;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "Y"]
        )));
    } else if (t === "NOR5_NI") {
        id = 43;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "Y"]
        )));
    } else if (t === "NOR6_NI") {
        id = 44;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "Y"]
        )));
    } else if (t === "NOR7_NI") {
        id = 45;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "Y"]
        )));
    } else if (t === "NOR8_NI") {
        id = 46;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "H", "Y"]
        )));
    } else if (t === "XOR2_NI") {
        id = 50;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "Y"]
        )));
    } else if (t === "XOR3_NI") {
        id = 51;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "Y"]
        )));
    } else if (t === "XOR4_NI") {
        id = 52;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "Y"]
        )));
    } else if (t === "XOR5_NI") {
        id = 53;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "Y"]
        )));
    } else if (t === "XOR6_NI") {
        id = 54;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "Y"]
        )));
    } else if (t === "XOR7_NI") {
        id = 55;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "Y"]
        )));
    } else if (t === "XOR8_NI") {
        id = 56;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "H", "Y"]
        )));
    } else if (t === "XNOR2_NI") {
        id = 60;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "Y"]
        )));
    } else if (t === "XNOR3_NI") {
        id = 61;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "Y"]
        )));
    } else if (t === "XNOR4_NI") {
        id = 62;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "Y"]
        )));
    } else if (t === "XNOR5_NI") {
        id = 63;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "Y"]
        )));
    } else if (t === "XNOR6_NI") {
        id = 64;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "Y"]
        )));
    } else if (t === "XNOR7_NI") {
        id = 65;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "Y"]
        )));
    } else if (t === "XNOR8_NI") {
        id = 66;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "E", "F", "G", "H", "Y"]
        )));
    } else if (t === "BUF_NI") {
        id = 70;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "Y"]
        )));
        params.addPointer(alloc(1)); // 1 bit for the buffer
    } else if (t === "BUF_INV_NI") {
        id = 71;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "Y"]
        )));
        params.addPointer(alloc(1)); // 1 bit for the buffer
    } else if (t === "FF_D_CO_NI") {
        id = 80;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["D", "CLK", "Q", "Qneg"]
        )));
        params.addPointer(alloc(1)); // 1 bit for the last clock value
        params.addPointer(alloc(1)); // 1 bit for the current state
    } else if (t === "DEC_BCD_7_NI") {
        id = 90;
        params.addPointers(getPointersForSignals(getSignalsAtPorts(
            ["A", "B", "C", "D", "LT", "RBI", "BI", "Y0", "Y1", "Y2", "Y3", "Y4", "Y5", "Y6"]
        )));
    } else {
        throw new Error("Unknown component type " + t);
    }

    return {
        type: id,
        params: params.params,
        paramLength : params.params.reduce((acc, param) => acc + param.len, 0),
    }
};


class ParamList {
    params: {val: number, len: number}[] = [];

    constructor() {
        this.params = [];
    }

    /**
     * @param val - The value of the parameter
     * @param len - Length in BYTES
     */
    add(val: number, len: number) {
        this.params.push({val, len});
    }

    /**
     * @param val - The pointer
     * Assumed to be 2 bytes
     */
    addPointer(val: number) {
        this.params.push({val, len: 2});
    }

    addPointers(val: number[]) {
        for (const v of val) {
            this.addPointer(v);
        }
    }
}