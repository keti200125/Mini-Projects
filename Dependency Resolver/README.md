# 🔗 Dependency Resolver

A small application for calculating **transitive dependencies** between items.  
Given a set of items with their direct dependencies, the program computes the **full list of dependencies** for each item.  
Optionally, it can also calculate **inverse dependencies** (i.e., determine the items that depend on a given one).  

---

## 🚀 Features

- 📌 Parse dependency rules from text input  
- 🔄 Compute **direct + transitive dependencies**  
- 📊 Output sorted, unique dependency lists  
- ↩️ Optional **inverse dependency resolution**  
- 🛑 Prevent cycles (no infinite loops)  

---


##  Example Input and Output

```text
📦 Example Input:

A B C
B C E
C G
D A F
E F
F H

📊 Example Output:

A B C E F G H
B C E F G H
C G
D A B C E F G H
E F H
F H

📊 Example Output
(Inverse Dependencies):

G C B A D
F E B A D
H F E B A D
```