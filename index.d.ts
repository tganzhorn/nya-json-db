declare module "*nyatdb.node" {
    declare class NyaJSONDB {
        constructor(path: string, options?: Options);
        set(key: string, value: Record<any, any>): void;
        get(key: string): Record<any, any>;
        clear(): void;
    }
    interface Options {
        autoSave: boolean | true;
    }
}

