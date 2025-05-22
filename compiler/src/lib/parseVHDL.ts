const ENTITY_CODE_REGEX = /entity (?<name>\w+) is(?<code>.+)end \k<name>;/si;
const PORT_FUNCTION_CODE_REGEX = /port ?\((?<code>.+)\);/si;
const PORT_REGEX = /(?<name>\w+) ?: ?(?<direction>in|out) (?<type>.+)[;\n]/gi;

const ARCHITECTURE_CODE_REGEX = /architecture (?<name>\w+) of (?<entityName>\w+) is(?<definitions>.+)begin(?<code>.+)end \k<name>;/si;
const SIGNALS_REGEX = /signal +(?<id>.+) +: +(?<type>.+);/gi
const COMPONENTS_REGEX = /(?<id>\w+)\s+:\s+(?<type>\w+)\s+port\s+map\((?<mapCode>.+)\);/gi
const COMPONENTS_MAP_REGEX = /(?<port>\w+)\s*=>\s*(?<signal>[^\s,;()]+)/gi;

export default function parseVHDL(code: string) {

    // Find all the ports in/out of the main entity

    const entity = matchGetGroups<{name: string, code: string}>(code, ENTITY_CODE_REGEX);
    const entityPortsFunction = matchGetGroups<{code: string}>(entity.code, PORT_FUNCTION_CODE_REGEX);

    const entityPorts = matchAllGetGroups<{name: string, direction: string, type: string}>(entityPortsFunction.code, PORT_REGEX);

    // Find the definitions and code in the architecture

    const architecture = matchGetGroups<{name: string, entityName: string, definitions: string, code: string}>(code, ARCHITECTURE_CODE_REGEX);
    if (architecture.entityName !== entity.name) throw new Error("Architecture entity name does not match entity name (" + architecture.entityName + " != " + entity.name + ")");

    // Find the signals used (wires)

    const signals = matchAllGetGroups<{id: string, type: string}>(architecture.definitions, SIGNALS_REGEX);

    // Find the components used

    const componentsWithMapCode = matchAllGetGroups<{id: string, type: string, mapCode: string}>(architecture.code, COMPONENTS_REGEX);
    const components = componentsWithMapCode.map(component => {
        const map = matchAllGetGroups<{port: string, signal: string}>(component.mapCode, COMPONENTS_MAP_REGEX);
        return {
            id: component.id,
            type: component.type,
            map
        };
    });

    return {
        entity: {
            name: entity.name,
            ports: entityPorts,
        },
        signals,
        components
    }
}

function matchGetGroups<K extends object = Record<string, string>>(code: string, regex: RegExp): K {
    const match = code.match(regex);
    if (!match) throw new Error("No match found for regex " + regex);
    const groups = match.groups;
    if (!groups) throw new Error("No groups found for regex " + regex);
    return groups as K;
}

function matchAllGetGroups<K extends object = Record<string, string>>(code: string, regex: RegExp): K[] {
    const matches = code.matchAll(regex);
    if (!matches) throw new Error("No match found for regex " + regex);
    const groups = [];
    for (const match of matches) {
        const group = match.groups;
        if (!group) throw new Error("No groups found for regex " + regex);
        groups.push(group as K);
    }
    return groups;
}
