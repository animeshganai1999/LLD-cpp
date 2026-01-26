# Creational Design Patterns

Creational design patterns provide various object creation mechanisms, which increase flexibility and reuse of existing code.

## Table of Contents
1. [Singleton Pattern](#singleton-pattern)
2. [Factory Pattern](#factory-pattern)
3. [Abstract Factory Pattern](#abstract-factory-pattern)
4. [Builder Pattern](#builder-pattern)
5. [Prototype Pattern](#prototype-pattern)

---

## Singleton Pattern

### Description
Ensures that a class has only **one instance** and provides a global point of access to it.

### Key Features
- Only one instance exists throughout the application
- Global access point
- Lazy or eager initialization
- Thread-safe implementation (in modern C++)

### Advantages
✅ Controlled access to single instance  
✅ Reduces global variables and namespace pollution  
✅ Lazy initialization (created only when needed)  
✅ Can be extended by subclassing  
✅ Memory efficient (only one instance)

### Disadvantages
❌ Difficult to unit test (tight coupling)  
❌ Violates Single Responsibility Principle  
❌ Can hide dependencies (implicit coupling)  
❌ Requires special handling in multi-threaded environments  
❌ Can become a global state anti-pattern

### When to Use
- Database connections
- Logger classes
- Configuration managers
- Cache/Registry objects
- Thread pools

### Special Syntax Used

**Mutex (`std::mutex`)**
- Thread synchronization primitive
- Prevents multiple threads from accessing critical section simultaneously
- Used with `lock_guard` for automatic lock management

**Lock Guard (`std::lock_guard`)**
- RAII wrapper for mutex
- Automatically locks mutex on construction
- Automatically unlocks on destruction (exception-safe)

**Delete Keyword (`= delete`)**
- C++11 feature to explicitly delete functions
- Prevents copying and assignment of singleton

**Static Members**
- Shared across all instances of a class
- Must be initialized outside class definition

**Double-Checked Locking**
- Performance optimization technique
- First check without locking (fast path)
- Second check with locking (thread-safe)

---

## Factory Pattern

### Description
Provides an interface for creating objects without specifying their exact classes. Delegates the instantiation logic to a factory class.

### Key Features
- Encapsulates object creation
- Client doesn't need to know concrete classes
- Uses a method to create objects
- Returns objects through a common interface

### Advantages
✅ Loose coupling - Client code independent of concrete classes  
✅ Single Responsibility Principle - Creation logic in one place  
✅ Open/Closed Principle - Easy to add new product types  
✅ Code reusability across application  
✅ Simplifies code maintenance

### Disadvantages
❌ Can become complex with many product types  
❌ Requires creating new subclass for each product  
❌ May increase overall code complexity  
❌ Extra layer of abstraction

### When to Use
- Object creation is complex or requires significant logic
- Don't know exact types at compile time
- Need to centralize object creation logic
- Want to decouple client from concrete classes
- System should be independent of how objects are created

### Real-World Examples
- Database connection factories (MySQL, PostgreSQL, MongoDB)
- Document creators (PDF, Word, Excel)
- Vehicle factories (Car, Bike, Truck)
- UI component factories

### Special Syntax Used

**Pure Virtual Function (`= 0`)**
- Makes a function pure virtual
- Class becomes abstract (cannot instantiate)
- Must be overridden in derived classes

**Override Keyword**
- Explicitly indicates function overrides base class
- Compile-time error checking
- Improves code readability

**Enum Class**
- Strongly-typed enumerations (C++11)
- Type-safe compared to traditional enums
- Prevents implicit conversions

---

## Abstract Factory Pattern

### Description
Provides an interface for creating **families of related or dependent objects** without specifying their concrete classes. It's a factory of factories.

### Key Features
- Creates families of related objects
- Ensures product consistency
- Multiple factory methods in one interface
- Higher level of abstraction than Factory Pattern

### Advantages
✅ Ensures product consistency within families  
✅ Isolates concrete classes from client code  
✅ Easy to swap entire product families  
✅ Single Responsibility Principle for product creation  
✅ Open/Closed Principle for adding new families  
✅ Promotes consistency among products

### Disadvantages
❌ Complexity increases significantly  
❌ Adding new products requires changing all factories  
❌ More classes and interfaces to manage  
❌ Can be overkill for simple scenarios  
❌ Steep learning curve

### When to Use
- System needs to work with multiple families of related objects
- Want to ensure objects from same family are used together
- Need to provide library of products without revealing implementations
- System should be independent of product creation and composition

### Real-World Examples
- UI Frameworks (Windows/Mac/Linux themes)
- Database drivers with related components
- Document format exporters (PDF/Word with charts, tables)
- Cross-platform GUI toolkits
- Theme systems (Light/Dark mode components)

### Factory vs Abstract Factory

| Factory Pattern | Abstract Factory Pattern |
|----------------|-------------------------|
| Creates single products | Creates families of products |
| One factory method | Multiple factory methods |
| Simpler structure | More complex structure |
| Example: createShape() | Example: createButton(), createCheckbox() |

---

## Builder Pattern

### Description
Separates the construction of a complex object from its representation, allowing the same construction process to create different representations.

### Key Features
- Step-by-step object construction
- Same construction process, different representations
- Fluent interface (method chaining)
- Optional Director class for construction control

### Advantages
✅ Step-by-step construction of complex objects  
✅ Reusable construction code  
✅ Highly readable with fluent interface  
✅ Can create immutable objects  
✅ Handles many optional parameters elegantly  
✅ Different representations using same construction code  
✅ Single Responsibility Principle for construction logic

### Disadvantages
❌ Increases overall code complexity  
❌ More classes to maintain  
❌ Overkill for simple objects  
❌ Client must know about builder  
❌ Can lead to partially constructed objects if not careful

### When to Use
- Object has many parameters (especially optional ones)
- Construction process is complex and multi-step
- Want to create immutable objects
- Need different representations of same object
- Avoid telescoping constructors
- Want readable, maintainable construction code

### Real-World Examples
- StringBuilder/StringBuffer
- HTTP Request Builders (Retrofit, OkHttp)
- Query Builders (SQL, MongoDB queries)
- Configuration/Settings objects
- UI Dialog builders
- Email/Message builders

### Special Syntax Used

**Method Chaining (Fluent Interface)**
- Each method returns `this` pointer
- Allows chaining multiple method calls
- Improves code readability

**Initializer List**
- Constructor syntax for member initialization
- More efficient than assignment
- Required for const members and references

**Protected Members**
- Accessible to derived classes
- Not accessible from outside
- Used for shared state in builders

---

## Prototype Pattern

### Description
Creates new objects by copying existing objects (prototypes) instead of creating them from scratch.

### Key Features
- Cloning mechanism for object creation
- Avoids expensive initialization
- Runtime flexibility for object types
- Creates copies without knowing exact class

### Advantages
✅ Avoids expensive object creation operations  
✅ Reduces need for subclassing  
✅ Hides complexity of creating new instances  
✅ Runtime flexibility (add/remove objects dynamically)  
✅ More flexible than factory patterns in some cases  
✅ Can clone complex object graphs efficiently

### Disadvantages
❌ Cloning complex objects with circular references is difficult  
❌ Deep copy implementation can be tricky  
❌ Each subclass must implement clone method  
❌ Hard to clone objects with private fields  
❌ Can violate encapsulation

### When to Use
- Object creation is expensive (database queries, network calls)
- Want to avoid subclasses of object creator
- System should be independent of how objects are created
- Number of object types determined at runtime
- Need to hide complexity of creating instances

### Real-World Examples
- Game objects (characters, items)
- Document templates
- Database connection prototypes
- Configuration presets
- GUI components with default settings

### Special Syntax Used

**Copy Constructor**
- Special constructor that creates copy of object
- Takes const reference to same class
- Deep copy vs shallow copy considerations

**Virtual Functions**
- Runtime polymorphism
- Allows derived class method calls through base pointer
- Clone method typically virtual

**this Pointer**
- Pointer to current object
- Used with dereference (`*this`) to pass current object
- Essential for clone implementation

**Virtual Destructor**
- Ensures proper cleanup in inheritance hierarchy
- Called when deleting through base pointer
- Prevents memory leaks

**Const Reference (`const Type&`)**
- Prevents modification of referenced object
- Avoids copying overhead
- Commonly used in copy constructors

---

## Comparison of Creational Patterns

| Pattern | Purpose | Complexity | Use Case |
|---------|---------|------------|----------|
| **Singleton** | One instance only | Low | Logger, Config |
| **Factory** | Create single objects | Low-Medium | Shape creator |
| **Abstract Factory** | Create object families | High | UI themes |
| **Builder** | Complex construction | Medium | Computer builder |
| **Prototype** | Clone objects | Medium | Document templates |

---

## Thread Safety Considerations

### Thread-Safe Implementations

**Meyers' Singleton (Recommended)**
- Local static variable initialization (C++11+)
- Thread-safe by language guarantee
- No explicit locking needed

**Double-Checked Locking**
- First check without locking (performance)
- Lock acquisition only when needed
- Second check with locking (safety)

**Eager Initialization**
- Object created at program startup
- Thread-safe by definition
- May waste resources if never used

### Thread Safety Syntax

**std::mutex**
- Mutual exclusion primitive
- Protects shared data from concurrent access

**std::lock_guard<std::mutex>**
- RAII-style mutex wrapper
- Automatically releases lock
- Exception-safe

**std::thread**
- C++11 threading support
- Platform-independent threading
- Used for concurrent execution

---

## Best Practices

1. **Choose the right pattern** - Don't force-fit patterns
2. **Keep it simple** - Don't over-engineer
3. **Thread safety** - Consider multi-threading implications
4. **Memory management** - Use smart pointers when possible
5. **Documentation** - Explain why pattern was chosen
6. **Testing** - Ensure patterns don't hinder testability
7. **Consistency** - Use similar patterns across codebase

---

## Key C++ Syntax Summary

| Syntax | Purpose | Example |
|--------|---------|---------|
| `virtual func() = 0` | Pure virtual function | Abstract class |
| `override` | Override base function | Type safety |
| `= delete` | Delete function | Prevent copying |
| `static` | Class-level member | Shared state |
| `const Type&` | Const reference | Prevent copying |
| `this` | Current object pointer | Method chaining |
| `std::mutex` | Thread synchronization | Thread safety |
| `lock_guard` | RAII lock wrapper | Exception safety |
| `enum class` | Strongly-typed enum | Type safety |

---

## Conclusion

Creational patterns are essential for flexible and maintainable object creation. Choose the pattern that best fits your specific requirements:

- **Singleton**: When you need exactly one instance
- **Factory**: When you need to create similar objects
- **Abstract Factory**: When you need families of related objects
- **Builder**: When object construction is complex
- **Prototype**: When cloning is cheaper than creation

Understanding these patterns and their trade-offs will help you write better, more maintainable C++ code.
