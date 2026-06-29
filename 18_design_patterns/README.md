# Design Patterns in C++

> Based on: "Design Patterns: Elements of Reusable Object-Oriented Software" (Gang of Four)

---

## What Are Design Patterns?

Design patterns are **proven, reusable solutions** to commonly occurring problems in software design. They're not code you copy-paste — they're blueprints you adapt.

> 🔁 **Analogy:** Design patterns are like architectural blueprints for buildings. An architect doesn't invent a new way to build a door every time — they use known designs that work well. Same idea here.

---

## The Three Categories

```
┌─────────────────────────────────────────────────────────────────┐
│                     23 Gang of Four Patterns                    │
├─────────────────┬───────────────────┬───────────────────────────┤
│   CREATIONAL    │    STRUCTURAL     │      BEHAVIORAL           │
│                 │                   │                           │
│ HOW objects     │ HOW objects are   │ HOW objects communicate   │
│ are CREATED     │ COMPOSED          │ and assign responsibility │
│                 │                   │                           │
│ • Singleton     │ • Adapter         │ • Observer                │
│ • Factory       │ • Bridge          │ • Strategy                │
│ • Abstract      │ • Composite       │ • Command                 │
│   Factory       │ • Decorator       │ • Template Method         │
│ • Builder       │ • Facade          │ • State                   │
│ • Prototype     │ • Flyweight       │ • Chain of Responsibility │
│                 │ • Proxy           │ • Memento                 │
│                 │                   │ • Visitor                 │
│                 │                   │ • Mediator                │
│                 │                   │ • Iterator                │
└─────────────────┴───────────────────┴───────────────────────────┘
```

---

## When to Use Design Patterns?

```
Problem occurs frequently?
         │
    YES ─┘── NO → solve directly, no pattern needed
         │
         ▼
Does a pattern exactly match?
         │
    YES ─┘── NO → don't force-fit a pattern
         │
         ▼
Apply the pattern, adapting to your context
```

> ⚠️ **Don't over-pattern!** Using a pattern where it's not needed adds complexity without benefit. Patterns solve problems — if there's no problem, there's no pattern needed.

---

## Quick Pattern Reference

### Creational Patterns

| Pattern                                               | One-Line Summary                         | Use When                                    |
| ----------------------------------------------------- | ---------------------------------------- | ------------------------------------------- |
| [Singleton](creational/01_singleton.md)               | Only ONE instance ever exists            | Logger, config manager, DB connection       |
| [Factory Method](creational/02_factory.md)            | Subclasses decide which object to create | Creating objects without knowing exact type |
| [Abstract Factory](creational/03_abstract_factory.md) | Factory of factories                     | Creating families of related objects        |
| [Builder](creational/04_builder.md)                   | Build complex objects step by step       | Objects with many optional parameters       |
| [Prototype](creational/05_prototype.md)               | Clone an existing object                 | Creating objects by copying a template      |

### Structural Patterns

| Pattern                                 | One-Line Summary                                    | Use When                               |
| --------------------------------------- | --------------------------------------------------- | -------------------------------------- |
| [Adapter](structural/01_adapter.md)     | Make incompatible interfaces work together          | Integrating legacy or third-party code |
| [Decorator](structural/02_decorator.md) | Add behavior without changing the class             | Adding features at runtime             |
| [Facade](structural/03_facade.md)       | Simple interface to a complex subsystem             | Simplifying complex APIs               |
| [Proxy](structural/04_proxy.md)         | Stand-in that controls access to real object        | Lazy loading, access control, caching  |
| [Composite](structural/05_composite.md) | Tree structure — parts and wholes treated uniformly | File systems, UI trees                 |
| [Bridge](structural/06_bridge.md)       | Separate abstraction from implementation            | Multiple dimensions of variation       |
| [Flyweight](structural/07_flyweight.md) | Share many fine-grained objects                     | Large numbers of similar objects       |

### Behavioral Patterns

| Pattern                                                             | One-Line Summary                                   | Use When                                            |
| ------------------------------------------------------------------- | -------------------------------------------------- | --------------------------------------------------- |
| [Observer](behavioral/01_observer.md)                               | Notify many objects when one changes               | Event systems, UI updates                           |
| [Strategy](behavioral/02_strategy.md)                               | Swap algorithms at runtime                         | Multiple ways to do same thing                      |
| [Command](behavioral/03_command.md)                                 | Encapsulate a request as an object                 | Undo/redo, queuing, logging                         |
| [Template Method](behavioral/04_template_method.md)                 | Define skeleton, fill in steps in subclass         | Common workflow with variable steps                 |
| [State](behavioral/05_state.md)                                     | Change behavior based on internal state            | Objects that behave differently in different states |
| [Chain of Responsibility](behavioral/06_chain_of_responsibility.md) | Pass request along a chain                         | Request handled by one of many handlers             |
| [Memento](behavioral/07_memento.md)                                 | Capture and restore object state                   | Undo functionality                                  |
| [Visitor](behavioral/08_visitor.md)                                 | New operation on elements without changing classes | Operations on complex object structures             |
| [Mediator](behavioral/09_mediator.md)                               | Central hub coordinates communication              | Many objects interacting with each other            |

---

## Pattern Relationships Diagram

```
CREATIONAL                    STRUCTURAL                BEHAVIORAL
──────────                    ──────────                ──────────

Singleton ──────► often used with ──────► Facade
                                                │
Factory ────────► creates objects for ─────► Composite
                                                │
Builder ────────► assembles ────────────────► Decorator
                                                │
Prototype ──────► Memento (uses clone)          │
                                             Strategy/State
Abstract                                    (can use Factory
Factory ────────────────────────────────────► to create strategies)
```

---

## How to Read Each Pattern File

Each pattern file follows this structure:

1. **What is it?** — Plain English explanation + analogy
2. **When to use it?** — Real-world scenarios
3. **Structure diagram** — ASCII class/flow diagram
4. **C++ implementation** — Commented code
5. **Real-world example** — Practical use case
6. **Pros & Cons** — Tradeoffs

---

_Start with [Singleton](creational/01_singleton.md) — it's the simplest and most commonly seen pattern._
