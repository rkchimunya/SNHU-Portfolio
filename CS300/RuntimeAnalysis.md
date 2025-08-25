# Runtime and Memory Analysis of Data Structures

For CS 300 Project One, I analyzed three different data structures — Vector, Hash Table, and Binary Search Tree (BST) — to determine their efficiency in solving the course advising problem.

---

## 1. Vector
**Advantages:**
- Simple to implement and use.
- Maintains order of insertion.
- Provides fast access by index (`O(1)`).

**Disadvantages:**
- Searching for a course by number requires linear search (`O(n)`).
- Inserting in sorted order can require shifting elements (`O(n)`).
- Memory is contiguous; resizing may be costly if the vector grows beyond capacity.

**Runtime Complexity:**
- Search: `O(n)`
- Insert (end): `O(1)` amortized
- Insert (sorted): `O(n)`
- Traverse all courses: `O(n)`

**Memory Usage:**  
Efficient in memory because it stores elements in a contiguous array. However, resizing may allocate extra unused space.

---

## 2. Hash Table
**Advantages:**
- Very fast lookups on average (`O(1)`).
- Efficient for direct access when searching by course number.
- Good for large datasets where fast retrieval is needed.

**Disadvantages:**
- Does not maintain sorted order (cannot directly print courses in alphanumeric order).
- Requires a good hash function to minimize collisions.
- Collisions (handled with chaining or probing) can degrade performance.

**Runtime Complexity:**
- Search: `O(1)` average, `O(n)` worst case with collisions
- Insert: `O(1)` average, `O(n)` worst case
- Traverse all courses: `O(n)` (but unsorted)

**Memory Usage:**  
Requires extra memory for hash buckets and possible linked lists (for collision resolution). More overhead than a vector.

---

## 3. Binary Search Tree (BST)
**Advantages:**
- Maintains elements in sorted order automatically (in-order traversal).
- Searching, inserting, and traversing can be efficient (`O(log n)` on average).
- Suitable for printing courses in alphanumeric order without extra sorting.

**Disadvantages:**
- Performance depends on tree balance; in the worst case (unbalanced), operations degrade to `O(n)`.
- Requires additional memory for node pointers (left, right).

**Runtime Complexity:**
- Search: `O(log n)` average, `O(n)` worst case
- Insert: `O(log n)` average, `O(n)` worst case
- Traverse all courses: `O(n)`

**Memory Usage:**  
Uses more memory than a vector due to node overhead (each node has pointers). Still reasonable for moderate datasets.

---

## Conclusion
- **Vector** is simple but inefficient for searching and maintaining sorted order.  
- **Hash Table** is best for fast lookup but cannot maintain sorted order, making it less useful for printing an ordered course list.  
- **BST** provides a balance: it supports efficient searching and also maintains sorted order, which matches the project requirements.  

👉 For the ABCU course advising program, the **BST was chosen** as the best data structure because it can both store courses and print them in alphanumeric order efficiently.

