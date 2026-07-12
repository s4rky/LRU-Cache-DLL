# Welcome!
This is my second project on github. Although not as flashy as my previous, this was meant to be a 1 day challenge and a good practice of my fundamentals.

# LRUCache
<img width="932" height="716" alt="image" src="https://github.com/user-attachments/assets/c7f2c9aa-069e-4541-94cb-b3ab71f1a300" />

An O(1) Least Recently Used (LRU) cache built in C++ from first principles using a doubly linked list (DLL) plus a hash map. Inspired heavily by [LeetCode 146](https://leetcode.com/problems/lru-cache/).

## The problem

An LRU cache has to do three things, all in **O(1)**:

1. **Look up** a value by key.
2. **Promote** the key you just touched to "most recently used."
3. **Evict** the least recently used key when you're over capacity.

The whole design falls out of taking all three constraints seriously at once. A hash map alone gives you (1) but has no notion of ordering, so it can't do (2) or (3). An ordered list gives you recency but O(n) lookup. Neither structure is sufficient, but their intersection is.

## The derivation

If I lay every entry out in a sequence from most-recently-used at the front to least-recently-used at the back, then eviction is just "remove the last element" and promotion is "move this element to the front." A doubly linked list makes both endpoints O(1) and, more importantly, lets me *unlink a node from the middle* in O(1), because each node knows its own neighbours, I can splice it out and re-stitch the list without walking to find it.

**How do I get to the node I want in O(1)?** A linked list alone would force an O(n) scan to find the node for a given key. That's the gap the hash map fills. **The map doesn't store values. Rather, it stores pointers to the nodes themselves.** `key -> Node*`. So a `get` is one hash lookup to land directly on the node, then an O(1) splice to promote it.

## Architecture

Three components, each with a header in `include/` and an implementation in `source/`:

| Component | Responsibility |
|-----------|----------------|
| `Node` | A single `{key, val}` cell with `prev`/`next` links. The atom. |
| `DLL` | The doubly linked list. Owns the nodes' lifetimes. Exposes `push_front`, `pop_back`, `splice`, `begin`, `back`, `empty`. |
| `LRUCache` | The policy layer. Holds a `DLL` for ordering and an `unordered_map<int, Node*>` for addressing, and enforces the capacity invariant. |

The separation is deliberate: `DLL` knows nothing about caching or recency. It is a pure data structure that could be lifted out and reused. `LRUCache` knows nothing about pointer stitching. It delegates every structural mutation to the list. The `splice` operation is the seam between them, allowing for a structural re-org of the cache.

## Ownership model

This is the part that's easy to get wrong, so I made it explicit:

- **The `DLL` owns every `Node`.** It allocates them in `push_front` and frees them in `pop_back` and its destructor.
- **The map holds non-owning `Node*` pointers.** They're pure references. This is why eviction has to erase the map entry *before* `pop_back` deletes the node. The order matters, or you'd leave a dangling pointer in the map...ie a memory leak.

No node is ever freed twice, and no node outlives the list. The destructor walks the list once, freeing as it goes.

## Complexity

| Operation | Time | Why |
|-----------|------|-----|
| `get(key)` | O(1) | one hash lookup + one splice |
| `put(key, val)` | O(1) | hash lookup, then either splice or push-front + optional pop-back |
| space | O(capacity) | one node and one map entry per cached key |

## Build

Headers live in `include/`, sources in `source/`. Each `.cpp` includes its header via relative path (`#include "../include/DLL.h"`).

```bash
g++ -std=c++17 source/*.cpp main.cpp -o lrucache
./lrucache
```

Or open `LRUCache.xcodeproj` and hit run.

## Design notes / things I'd flag

- **Eviction is push-then-trim.** I always insert first, then check whether I've exceeded capacity and drop the tail if so. This keeps the "new key becomes MRU" and "old key gets evicted" cases from "edge-casing" each other.
- **The capacity-0 and capacity-1 edges are handled by the list, not the cache.** Because `begin()` and `back()` collapse to the same node when the list has one element, the trimming logic stays uniform.

## Example

A capacity-2 walkthrough. `printCache()` prints the list from **most-recently-used (left)** to **least-recently-used (right)**, so you can watch each access re-order the line:

```cpp
LRUCache cache(2);

cache.put(1, 1);
cache.put(2, 2);
cache.printCache();              // [2:2] <--> [1:1]

std::cout << cache.get(1) << "\n";  // 1        (1 is touched, jumps to front)
cache.printCache();              // [1:1] <--> [2:2]

cache.put(3, 3);                 // over capacity -> evict LRU (key 2)
cache.printCache();              // [3:3] <--> [1:1]

std::cout << cache.get(2) << "\n";  // -1       (2 was evicted)

cache.put(4, 4);                 // over capacity -> evict LRU (key 1)
cache.printCache();              // [4:4] <--> [3:3]

std::cout << cache.get(1) << "\n";  // -1
std::cout << cache.get(3) << "\n";  // 3        (3 promoted to front)
cache.printCache();              // [3:3] <--> [4:4]

std::cout << cache.get(4) << "\n";  // 4
cache.printCache();              // [4:4] <--> [3:3]
```

Console output:

```
[2:2] <--> [1:1]
1
[1:1] <--> [2:2]
[3:3] <--> [1:1]
-1
[4:4] <--> [3:3]
-1
3
[3:3] <--> [4:4]
4
[4:4] <--> [3:3]
```

The thing to watch is `get(1)` on line 5: reading a key isn't a passive lookup — it mutates recency, so `1` slides to the front and `2` becomes the next eviction target. That's the whole policy, visible in one line.

## Design notes / things I'd flag

- **Eviction is push-then-trim.** I always insert first, then check whether I've exceeded capacity and drop the tail if so. This keeps the "new key becomes MRU" and "old key gets evicted" cases from special-casing each other.
- **The capacity-0 and capacity-1 edges are handled by the list, not the cache.** Because `begin()` and `back()` collapse to the same node when the list has one element, the trimming logic stays uniform.

:)
