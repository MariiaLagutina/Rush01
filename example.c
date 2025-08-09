#include <unistd.h>

int parse_input(char *str, int *clues);
void print_error(void);
int solve(int grid[4][4], int clues[16]);
int is_valid(int grid[4][4], int row, int col, int num, int clues[16]);
void print_grid(int grid[4][4]);

int main(int argc, char **argv)
{
    int clues[16];
    int grid[4][4] = {{0}};
    
    if (argc != 2)
    {
        print_error();
        return (1);
    }
    if (!parse_input(argv[1], clues))
    {
        print_error();
        return (1);
    }
    if (!solve(grid, clues))
    {
        print_error();
        return (1);
    }
    print_grid(grid);
    return (0);
}


/*********************** */

int ft_is_valid_char(char c)
{
    return (c >= '1' && c <= '4');
}

int parse_input(char *str, int *clues)
{
    int i = 0, j = 0;
    while (str[i] && j < 16)
    {
        if (str[i] == ' ')
        {
            i++;
            continue;
        }
        if (!ft_is_valid_char(str[i]))
            return (0);
        clues[j++] = str[i] - '0';
        i++;
    }
    if (j != 16)
        return (0);
    return (1);
}

void print_error(void)
{
    write(1, "Error\n", 6);
}

/*********************** */

int is_valid(int grid[4][4], int row, int col, int num, int clues[16])
{
    int i;
    // Проверяем строку и столбец на повтор числа
    for (i = 0; i < 4; i++)
    {
        if (grid[row][i] == num)
            return 0;
        if (grid[i][col] == num)
            return 0;
    }
    // Тут будет проверка подсказок по видимости (можно позже добавить)
    return 1;
}

int solve(int grid[4][4], int clues[16])
{
    int row, col, num;

    // Поиск пустой клетки
    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 4; col++)
        {
            if (grid[row][col] == 0)
            {
                // Перебор вариантов 1-4
                for (num = 1; num <= 4; num++)
                {
                    if (is_valid(grid, row, col, num, clues))
                    {
                        grid[row][col] = num;
                        if (solve(grid, clues))
                            return 1;
                        grid[row][col] = 0;
                    }
                }
                return 0; // Не подошло ни одно число
            }
        }
    }
    // Если дошли сюда — все заполнено
    return 1;
}


#include <unistd.h>

void print_grid(int grid[4][4])
{
    char c;
    int row, col;

    for (row = 0; row < 4; row++)
    {
        for (col = 0; col < 4; col++)
        {
            c = grid[row][col] + '0';
            write(1, &c, 1);
            if (col != 3)
                write(1, " ", 1);
        }
        write(1, "\n", 1);
    }
}


int check_row_left(int grid[4][4], int row, int expected)
{
    int count = 0;
    int max_height = 0;
    int i = 0;
    while (i < 4)
    {
        if (grid[row][i] > max_height)
        {
            max_height = grid[row][i];
            count++;
        }
        i++;
    }
    return (count == expected);
}

int check_row_right(int grid[4][4], int row, int expected)
{
    int count = 0;
    int max_height = 0;
    int i = 3;
    while (i >= 0)
    {
        if (grid[row][i] > max_height)
        {
            max_height = grid[row][i];
            count++;
        }
        i--;
    }
    return (count == expected);
}

int check_col_top(int grid[4][4], int col, int expected)
{
    int count = 0;
    int max_height = 0;
    int i = 0;
    while (i < 4)
    {
        if (grid[i][col] > max_height)
        {
            max_height = grid[i][col];
            count++;
        }
        i++;
    }
    return (count == expected);
}

int check_col_bottom(int grid[4][4], int col, int expected)
{
    int count = 0;
    int max_height = 0;
    int i = 3;
    while (i >= 0)
    {
        if (grid[i][col] > max_height)
        {
            max_height = grid[i][col];
            count++;
        }
        i--;
    }
    return (count == expected);
}

int check_visibility(int grid[4][4], int clues[16])
{
    int i = 0;
    while (i < 4)
    {
        if (!check_col_top(grid, i, clues[i]))
            return 0;
        if (!check_col_bottom(grid, i, clues[i + 4]))
            return 0;
        if (!check_row_left(grid, i, clues[i + 8]))
            return 0;
        if (!check_row_right(grid, i, clues[i + 12]))
            return 0;
        i++;
    }
    return 1;
}
