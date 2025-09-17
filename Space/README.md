# 🚀 SPACE 2025 — Cosmic Path Finder

A C# (.NET) console application that helps an astronaut navigate a hazardous asteroid field and return to the Space Station.  
Given a grid map with start (`S`), finish (`F`), open space (`O`) and asteroids (`X`), the program computes:

- total number of possible paths from `S` to `F` (moving up/down/left/right),
- the shortest path length,
- and prints the map with the shortest route numbered from `1` to `L`.

This repository contains a clear, testable implementation and optional helpers to export the shortest path as CSV and (optionally) send it by email.

---

## 🔎 Features

- Parse map sizes and grid from console or file input
- Count **all possible** paths (no revisiting the same cell in a single path)
- Find the **shortest path** and its length
- Print the map with the shortest path marked with sequential numbers
- Export shortest path as CSV report
- Send CSV report via SMTP
- Defensive programming and validation for map size and characters

---

## 📥 Input Format

1. An integer `M` — number of rows (2 ≤ M ≤ 100)  
2. An integer `N` — number of columns (2 ≤ N ≤ 100)  
3. `M` rows, each containing `N` space-separated characters (`S`, `F`, `O`, `X`)

You can provide input either interactively (console) or via a text file redirected to the program.

---

## 📦 Example Input

```text
Map rows: 5
Map columns: 7
Cosmic map:
S O X O O O O
X O O O O X O
X X O X O X O
O X X O O X O
O X X O O O F
```

## 📊 Example Output
```text
Number of possible paths: 6
Shortest path length: 10
Shortest path map:
S 1 X O O O O
X 2 3 4 5 X O
X X O X 6 X O
O X X O 7 X O
O X X O 8 9 10