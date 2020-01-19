# Sudoku class
The driver class that handles input and searches for solutions.

## Member variables
- integer representing size of array
- 2D dynamic array with dimensions n × n

## Member functions
Private functions to be added as needed
```
- Sudoku(istream& is)
- Sudoku(const Sudoku& other)
- ~Sudoku()
- Sudoku& operator=(const Sudoku& rhs)

- void solve()
```
---

## Cell class
Information about a certain cell<br>
friend class of sudoku class

### Member variables
- integer contained in cell<br>
    - 0 if empty
    - has to be between 0 and n inclusive

### Member functions
```
- Cell()
- Cell(int n)
- bool empty() const
- const int val() const
- void set(int x)

```