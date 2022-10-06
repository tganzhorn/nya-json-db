const NyaJSONDB = require("../index");

describe("NyaJSONDB", () => {
    test("Should throw an error while instantiating class", () => {
        expect(() => new NyaJSONDB()).toThrow();
    });
    test("Should instantiate class", () => {
        expect(() => new NyaJSONDB("test")).not.toThrow();
    });
    test("Should throw an error if set gets called with wrong argument types", () => {
        const nyaJSONDB = new NyaJSONDB("test");
        expect(() => nyaJSONDB.set("a", false)).toThrow();
        expect(() => nyaJSONDB.set("a", "false")).toThrow();
        expect(() => nyaJSONDB.set("a", 0)).toThrow();

        expect(() => nyaJSONDB.set(0, {})).toThrow();
        expect(() => nyaJSONDB.set(false, {})).toThrow();
        expect(() => nyaJSONDB.set({}, {})).toThrow();

        expect(() => nyaJSONDB.set("a", [])).not.toThrow();
        expect(() => nyaJSONDB.set("0", {})).not.toThrow();

        expect(() => nyaJSONDB.clear()).not.toThrow();
    });
    test("Should save and remove database", () => {
        let nyaJSONDB = new NyaJSONDB("test.db");
        expect(() => nyaJSONDB.set("a", {})).not.toThrow();
        expect(() => nyaJSONDB = new NyaJSONDB("test.db")).not.toThrow();
        expect(nyaJSONDB.get("a")).toBeTruthy();
        expect(() => nyaJSONDB.clear()).not.toThrow();
        expect(nyaJSONDB.get("a")).toBeUndefined();
        expect(() => nyaJSONDB = new NyaJSONDB("test.db")).not.toThrow();
        expect(nyaJSONDB.get("a")).toBeUndefined();
        expect(() => nyaJSONDB.clear()).not.toThrow();
    });
    test("Should set and get items", () => {
        const testObject = { a: "b" };
        let nyaJSONDB = new NyaJSONDB("test.db");
        expect(() => nyaJSONDB.set("a", testObject)).not.toThrow();
        expect(JSON.stringify(nyaJSONDB.get("a"))).toBe(JSON.stringify(testObject));
        expect(() => nyaJSONDB.clear()).not.toThrow();
    });
    test("Should overwrite item", () => {
        const testObjectA = { a: "b" };
        const testObjectB = { c: "d" };
        let nyaJSONDB = new NyaJSONDB("test.db");
        expect(() => nyaJSONDB.set("a", testObjectA)).not.toThrow();
        expect(JSON.stringify(nyaJSONDB.get("a"))).toBe(JSON.stringify(testObjectA));
        expect(() => nyaJSONDB.set("a", testObjectB)).not.toThrow();
        expect(JSON.stringify(nyaJSONDB.get("a"))).toBe(JSON.stringify(testObjectB));
        expect(() => nyaJSONDB.clear()).not.toThrow();
    })
});