declare module "*nyatdb.node" {
    declare class NyaJSONDB {
        constructor(path: string);
        set(key: string, value: Record<any, any>): void;
        get(key: string): Record<any, any>;
        clear(): void;
    }
}

