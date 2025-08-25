# CS 300 Portfolio Submission

## Reflection

**What was the problem you were solving in the projects for this course?**  
I was solving the problem of creating a program to help academic advisors organize and retrieve course information. The system needed to sort courses in alphanumeric order and allow the user to search for a course and see its prerequisites. Another problem was analyzing which data structures (vector, hash table, or binary search tree) would be most efficient for this task.

**How did you approach the problem? Why are data structures important to understand?**  
I approached the problem by first designing pseudocode for each data structure, then analyzing runtime and memory efficiency. Data structures are important because they directly affect how efficiently a program runs and how scalable it can be. For example, a BST provides efficient lookups and sorted order, while a hash table provides faster average-case lookups but doesn’t maintain order.

**How did you overcome any roadblocks you encountered while going through the activities or project?**  
I faced challenges with implementing the BST insertion and traversal correctly, especially handling duplicates and maintaining sorted order. I overcame this by carefully debugging and testing small cases before scaling to full CSV files. I also made sure to write helper functions like `trim()` and `splitCSV()` to handle file input errors.

**How has your work on this project expanded your approach to designing software and developing programs?**  
This project taught me to carefully evaluate trade-offs between different data structures before coding. I now plan out efficiency and readability before implementing features, which makes my programs more reliable.

**How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?**  
I learned to keep functions modular, use helper methods, and write clear comments. This makes the program easier to maintain and adapt later if requirements change, such as switching from a BST to a hash table. Writing clean, reusable code has become a priority for me.
