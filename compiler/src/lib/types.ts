export interface Component {
    id: string;
    type: string;
    map: {
        port: string;
        signal: string;
    }[];
}
