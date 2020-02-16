#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <chrono>

using std::string;
using namespace std::chrono;

class Sudoku {
    private:

    class Cell {
        public:
        
        Cell() : val(0), row(-1), col(-1) {}
        Cell(int n, int r, int c) : val(n), row(r), col(c) {}
        bool empty() const { return val == 0; }
        void set(int n) { val = n; }
        int get() { return val; }
        void set_row(int r) { row = r; }
        void set_col(int c) { col = c; }
        const int get_row() { return row; }
        const int get_col() { return col; }


        private:

        int val;
        int row;
        int col;
        friend class Sudoku;
    };

    int size;
    Cell*** grid;
    std::vector<Cell*> empty_cells;
    std::vector<Cell*> ans;

    public:

    Sudoku(std::istream& is)
    {
        is >> size;
        grid = new Cell**[size];
        for (int i = 0; i < size; ++i)
        {
            Cell** row = new Cell*[size];
            for (int j = 0; j < size; ++j)
            {
                int n;
                is >> n;
                row[j] = new Cell(n, i, j);
                if (n == 0)
                    empty_cells.push_back(row[j]);
            }
            grid[i] = row;
        }
    }

    ~Sudoku()
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                delete grid[i][j];
            }
            delete[] grid[i];
        }
        delete[] grid;
    }

    bool isValid(Cell* c)
    {
        const int row = c->get_row();
        const int col = c->get_col();
        const int val = c->get();
        if (val == 0) { return false; }
        // check row
        for (int i = 0; i < size; ++i)
        {
            if (i != col && grid[row][i]->get() == val)
                return false;
        }

        // check col
        for (int i = 0; i < size; ++i)
        {
            if (i != row && grid[i][col]->get() == val)
                return false;
        }

        // check box
        int box_len = int(std::pow(size, 0.5));
        int box_tl_row = row - (row % box_len);
        int box_tl_col = col - (col % box_len);
        for (int i = box_tl_row; i < box_tl_row + box_len; ++i)
        {
            for (int j = box_tl_col; j < box_tl_col + box_len; ++j)
            {
                Cell* cur = grid[i][j];
                if (cur != c && cur->get() == val)
                    return false;
            }
        }
        return true;
    }


    void solve()
    {
        solve_helper(0, empty_cells);
    }


    void solve_helper(int n, std::vector<Cell*> cells)
    {
        if (isValid(cells[cells.size() - 1]))
        {
            ans = cells;
            //print_ans();
        }
        else
        {
            for (int i = 1; i <= size; ++i)
            {
                Cell* cur_cell = cells[n];
                cur_cell->set(i);
                if (isValid(cur_cell))
                {
                    solve_helper(n + 1, cells);/* 
                    if (isValid(cur_cell))
                        break; */
                    if (isValid(cells[cells.size() - 1]))
                        break;
                }
                //cur_cell->set(i - 1);
                cells[n]->set(0);
            }
        }
    }

    void print() const
    {
        int box_len = int(std::pow(size, 0.5));

        std::cout << " ";
        for (int k = 0; k < size * 2 - 1; ++k)
            std::cout << "-";
        std::cout << "\n";

        for (int i = 0; i < size; ++i)
        {
            std::cout << "|";
            for (int j = 0; j < size; ++j)
            {
                std::cout << grid[i][j]->get();
                if (j % box_len == box_len - 1)
                    std::cout << "|";
                else
                    std::cout << " ";
            }
            std::cout << "\n";
            if (i % box_len == box_len - 1)
            {
                std::cout << " ";
                for (int k = 0; k < size * 2 - 1; ++k)
                    std::cout << "-";
                std::cout << "\n";
            }
        }
        std::cout << '\n';
    }
    

    void print_ans() const
    {
        for (size_t i = 0; i < ans.size(); ++i)
        {
            empty_cells[i]->set(ans[i]->get());
        }
        print();
    }
};


int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        std::ifstream fin(argv[1]);
        if (!fin.is_open())
            std::cout << "File not open\n";
        Sudoku s(fin);
        auto start = high_resolution_clock::now();
        s.solve();
        auto end = high_resolution_clock::now();
        std::cout << duration_cast<milliseconds>((end - start)).count() << " milliseconds" << std::endl;
	s.print_ans();
    }
    else
    {
        std::cerr << "Usage: a.out FILE.IN\n";
    }
    
    return 0;
}
