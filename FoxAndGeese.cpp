#include <iostream>
#include <cstdlib>   // Для функции rand()
#include <ctime>     // Для функции time()
#include <windows.h> // Для выделения цветом

constexpr auto MAX = 32767;
#define MIN -MAX

using namespace std;

// Класс, представляющий игровое поле
class TPlaying_Field {
public:
    char** board = new char* [13];
    int* poz_fox = new int[2];
    int number_geese = 17;
    int maxDepth = 5;

    bool geese = false;

    TPlaying_Field() {
        // Заполнение игрового поля
        for (int count = 0; count < 13; count++)
            board[count] = new char[13];

        for (int i = 0; i < 13; i++) {
            char* line = new char[13];
            if (i < 4 || i > 8) {
                if (i % 2 == 0) {
                    for (int j = 0; j < 13; j++) {
                        if (j < 4 || j > 8) {
                            line[j] = 'X';
                        }
                        else if (j % 2 == 0) {
                            line[j] = '·';
                        }
                        else {
                            line[j] = '-';
                        }
                    }
                }
                else {
                    for (int j = 0; j < 13; j++) {
                        if (j < 4 || j > 8) {
                            char value = 'X';
                            line[j] = value;
                        }
                        else if (j % 2 == 0) {
                            char value = '|';
                            line[j] = value;
                        }
                        else {
                            if ((i / 2) % 2 == 1) {
                                if ((j / 2) % 2 == 0) {
                                    line[j] = '/';
                                }
                                else {
                                    line[j] = '\\';
                                }
                            }
                            else {
                                if ((j / 2) % 2 == 0) {
                                    line[j] = '\\';
                                }
                                else {
                                    line[j] = '/';
                                }
                            }
                        }
                    }
                }
            }
            else {
                for (int j = 0; j < 13; j++) {
                    if (i % 2 == 0) {
                        if (j % 2 == 0) {
                            line[j] = '·';
                        }
                        else {
                            line[j] = '-';
                        }
                    }
                    else {
                        if (j % 2 == 0) {
                            line[j] = '|';
                        }
                        else {
                            if ((i / 2) % 2 == 0) {
                                if ((j / 2) % 2 == 0) {
                                    line[j] = '\\';
                                }
                                else {
                                    line[j] = '/';
                                }
                            }
                            else {
                                if ((j / 2) % 2 == 0) {
                                    line[j] = '/';
                                }
                                else {
                                    line[j] = '\\';
                                }
                            }
                        }
                    }
                }
            }

            for (int k = 0; k < 13; k++) {
                board[i][k] = line[k];
            }

            delete[] line;
        }

        // Начальное положение лисы
        board[6][6] = 'V';
        poz_fox[0] = 6;
        poz_fox[1] = 6;

        // Расстановка гусей
        for (int i = 4; i < 13; i += 2) {
            if (i < 8) {
                if (i != 4) {
                    board[i][0] = 'G';
                    board[i][12] = 'G';
                    board[i][2] = 'G';
                    board[i][10] = 'G';
                }
            }
            else {
                for (int j = 0; j < 13; j += 2) {
                    if (board[i][j] == '·') {
                        board[i][j] = 'G';
                    }
                }
            }
        }
    }

    ~TPlaying_Field() {
        for (int count = 0; count < 13; count++) {
            delete[] board[count];
        }
        delete[] board;
        delete[] poz_fox;
    }


    // Функция, которая увеличивает размер двумерного массива
    int** increase_array_size(int**& arr, int old_rows) {
        int new_rows = old_rows / 2;

        int** new_arr = new int* [new_rows + 1];
        for (int i = 0; i < new_rows + 1; ++i) {
            new_arr[i] = new int[2];
        }

        for (int i = 0; i < new_rows; ++i) {
            for (int j = 0; j < 2; ++j) {
                new_arr[i][j] = arr[i][j];
            }
        }

        for (int i = 0; i < old_rows / 2; ++i) {
            delete[] arr[i];
        }
        delete[] arr;

        return new_arr;
    }

    void display() {
        system("cls");
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Функция для отображения игрового поля в консоли.
    void display2(int ig, int jg) {
        system("cls");
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                if ((i == ig) && (j == jg)) {
                    // Получаем дескриптор консольного окна
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                    // Задаем цвет текста (например, зеленый на черном фоне)
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                    cout << board[i][j] << " ";

                    // Возвращаем обратно стандартный цвет
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    // Функция для отображения игрового поля в консоли.
    void display3(int ig, int jg, int im, int jm) {
        system("cls");
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                if ((i == ig) && (j == jg)) {
                    // Получаем дескриптор консольного окна
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                    // Задаем цвет текста (например, зеленый на черном фоне)
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                    cout << board[i][j] << " ";

                    // Возвращаем обратно стандартный цвет
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                else if ((i == im) && (j == jm)) {
                    // Получаем дескриптор консольного окна
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                    // Задаем цвет текста (например, зеленый на черном фоне)
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

                    cout << board[i][j] << " ";

                    // Возвращаем обратно стандартный цвет
                    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
                else {
                    cout << board[i][j] << " ";
                }
            }
            cout << endl;
        }
    }


    // Функция проверяет возможные ходы лисы для захвата гусей.
    int** check_capture(int i, int j) {
        int** moves = new int* [1];
        for (int count = 0; count < 1; count++)
            moves[count] = new int[2];

        int length = static_cast<int>(_msize(moves) / sizeof(int));

        // Слева вверху
        if (i >= 4 && j >= 4) {
            if (board[i - 1][j - 1] == '\\') {
                if (board[i - 2][j - 2] == 'G') {
                    if (board[i - 4][j - 4] == '·') {
                        moves[(length / 2) - 1][0] = i - 4;
                        moves[(length / 2) - 1][1] = j - 4;

                        // Увеличение массива и определение его новой длины
                        length = static_cast<int>(_msize(moves) / sizeof(int));
                        moves = increase_array_size(moves, length);
                        length = static_cast<int>(_msize(moves) / sizeof(int));
                    }
                }
            }
        }

        // Вверху справа
        if (i >= 4 && j <= 8) {
            if (board[i - 1][j + 1] == '/') {
                if (board[i - 2][j + 2] == 'G') {
                    if (board[i - 4][j + 4] == '·') {
                        moves[(length / 2) - 1][0] = i - 4;
                        moves[(length / 2) - 1][1] = j + 4;

                        length = static_cast<int>(_msize(moves) / sizeof(int));
                        moves = increase_array_size(moves, length);
                        length = static_cast<int>(_msize(moves) / sizeof(int));
                    }
                }
            }
        }

        // Слева внизу
        if (i <= 8 && j >= 4) {
            if (board[i + 1][j - 1] == '/') {
                if (board[i + 2][j - 2] == 'G') {
                    if (board[i + 4][j - 4] == '·') {
                        moves[(length / 2) - 1][0] = i + 4;
                        moves[(length / 2) - 1][1] = j - 4;

                        length = static_cast<int>(_msize(moves) / sizeof(int));
                        moves = increase_array_size(moves, length);
                        length = static_cast<int>(_msize(moves) / sizeof(int));
                    }
                }
            }
        }

        // Внизу справа
        if (i <= 8 && j <= 8) {
            if (board[i + 1][j + 1] == '\\') {
                if (board[i + 2][j + 2] == 'G') {
                    if (board[i + 4][j + 4] == '·') {
                        moves[(length / 2) - 1][0] = i + 4;
                        moves[(length / 2) - 1][1] = j + 4;

                        length = static_cast<int>(_msize(moves) / sizeof(int));
                        moves = increase_array_size(moves, length);
                        length = static_cast<int>(_msize(moves) / sizeof(int));
                    }
                }
            }
        }

        // Выше
        if (i >= 4) {
            if (board[i - 2][j] == 'G') {
                if (board[i - 4][j] == '·') {
                    moves[(length / 2) - 1][0] = i - 4;
                    moves[(length / 2) - 1][1] = j;

                    length = static_cast<int>(_msize(moves) / sizeof(int));
                    moves = increase_array_size(moves, length);
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                }
            }
        }

        // Под
        if (i <= 8) {
            if (board[i + 2][j] == 'G') {
                if (board[i + 4][j] == '·') {
                    moves[(length / 2) - 1][0] = i + 4;
                    moves[(length / 2) - 1][1] = j;

                    length = static_cast<int>(_msize(moves) / sizeof(int));
                    moves = increase_array_size(moves, length);
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                }
            }
        }

        // Слева
        if (j >= 4) {
            if (board[i][j - 2] == 'G') {
                if (board[i][j - 4] == '·') {
                    moves[(length / 2) - 1][0] = i;
                    moves[(length / 2) - 1][1] = j - 4;

                    length = static_cast<int>(_msize(moves) / sizeof(int));
                    moves = increase_array_size(moves, length);
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                }
            }
        }

        // Справа
        if (j <= 8) {
            if (board[i][j + 2] == 'G') {
                if (board[i][j + 4] == '·') {
                    moves[(length / 2) - 1][0] = i;
                    moves[(length / 2) - 1][1] = j + 4;

                    length = static_cast<int>(_msize(moves) / sizeof(int));
                    moves = increase_array_size(moves, length);
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                }
            }
        }

        return moves;
    }


    // Функция проверяет возможные ходы лисы без захвата гусей
    int** check_move(int i, int j) {
        int** moves = new int* [1];
        for (int count = 0; count < 1; count++)
            moves[count] = new int[2];

        int length = static_cast<int>(_msize(moves) / sizeof(int));

        // Слева вверху
        if (i >= 2 && j >= 2) {
            if (board[i - 1][j - 1] == '\\') {
                if (board[i - 2][j - 2] == '·') {
                    moves[(length / 2) - 1][0] = i - 2;
                    moves[(length / 2) - 1][1] = j - 2;

                    // Увеличение массива и определение его новой длины
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                    moves = increase_array_size(moves, length);
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                }
            }
        }

        // Вверху справа
        if (i >= 2 && j <= 10) {
            if (board[i - 1][j + 1] == '/') {
                if (board[i - 2][j + 2] == '·') {
                    moves[(length / 2) - 1][0] = i - 2;
                    moves[(length / 2) - 1][1] = j + 2;

                    length = static_cast<int>(_msize(moves) / sizeof(int));
                    moves = increase_array_size(moves, length);
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                }
            }
        }

        // Слева внизу
        if (i <= 10 && j >= 2) {
            if (board[i + 1][j - 1] == '/') {
                if (board[i + 2][j - 2] == '·') {
                    moves[(length / 2) - 1][0] = i + 2;
                    moves[(length / 2) - 1][1] = j - 2;

                    length = static_cast<int>(_msize(moves) / sizeof(int));
                    moves = increase_array_size(moves, length);
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                }
            }
        }

        // внизу справа
        if (i <= 10 && j < 10) {
            if (board[i + 1][j + 1] == '\\') {
                if (board[i + 2][j + 2] == '·') {
                    moves[(length / 2) - 1][0] = i + 2;
                    moves[(length / 2) - 1][1] = j + 2;

                    length = static_cast<int>(_msize(moves) / sizeof(int));
                    moves = increase_array_size(moves, length);
                    length = static_cast<int>(_msize(moves) / sizeof(int));
                }
            }
        }


        // Выше
        if (i >= 2) {
            if (board[i - 2][j] == '·') {
                moves[(length / 2) - 1][0] = i - 2;
                moves[(length / 2) - 1][1] = j;

                length = static_cast<int>(_msize(moves) / sizeof(int));
                moves = increase_array_size(moves, length);
                length = static_cast<int>(_msize(moves) / sizeof(int));
            }
        }

        // Под
        if (i <= 10) {
            if (board[i + 2][j] == '·') {
                moves[(length / 2) - 1][0] = i + 2;
                moves[(length / 2) - 1][1] = j;

                length = static_cast<int>(_msize(moves) / sizeof(int));
                moves = increase_array_size(moves, length);
                length = static_cast<int>(_msize(moves) / sizeof(int));
            }
        }

        // Слева
        if (j >= 2) {
            if (board[i][j - 2] == '·') {
                moves[(length / 2) - 1][0] = i;
                moves[(length / 2) - 1][1] = j - 2;

                length = static_cast<int>(_msize(moves) / sizeof(int));
                moves = increase_array_size(moves, length);
                length = static_cast<int>(_msize(moves) / sizeof(int));

            }
        }

        // справа
        if (j <= 10) {
            if (board[i][j + 2] == '·') {
                moves[(length / 2) - 1][0] = i;
                moves[(length / 2) - 1][1] = j + 2;

                length = static_cast<int>(_msize(moves) / sizeof(int));
                moves = increase_array_size(moves, length);
                length = static_cast<int>(_msize(moves) / sizeof(int));
            }
        }

        return moves;
    }
};


// Функция, которая проверяет, есть ли определенное значение в двумерном массиве
static bool is_not_value_in_array(int* poz, int** mv, int length_m) {
    for (int i = 0; i < (length_m / 2) - 1; ++i) {
        if (poz[0] == mv[i][0] && poz[1] == mv[i][1])
            return false;
    }
    return true;
}


// Оценочная функция
static int Evaluation(TPlaying_Field* Playing_Field) {
    int i = Playing_Field->poz_fox[0];
    int j = Playing_Field->poz_fox[1];

    int** mv = Playing_Field->check_move(i, j);
    int length_m = static_cast<int>(_msize(mv) / sizeof(int));

    int** capt = Playing_Field->check_capture(i, j);
    int length_c = static_cast<int>(_msize(capt) / sizeof(int));

    // Удаление capt, так как нам нужно количество захватов
    for (int i = 0; i < length_c / 2; ++i) {
        delete[] capt[i];
    }
    delete[] capt;

    for (int i = 0; i < (length_m / 2) - 1; i++) {

        int** temp = Playing_Field->check_move(mv[i][0], mv[i][1]);
        int length_t = static_cast<int>(_msize(temp) / sizeof(int));

        for (int i = 0; i < (length_t / 2) - 1; i++) {
            int* poz = new int[2];
            poz[0] = temp[i][0];
            poz[1] = temp[i][1];


            if (is_not_value_in_array(poz, mv, length_m)) {
                mv[(length_m / 2) - 1][0] = poz[0];
                mv[(length_m / 2) - 1][1] = poz[1];

                length_m = static_cast<int>(_msize(mv) / sizeof(int));
                mv = Playing_Field->increase_array_size(mv, length_m);
                length_m = static_cast<int>(_msize(mv) / sizeof(int));
            }

            delete[] poz;
        }

        length_t = static_cast<int>(_msize(temp) / sizeof(int));
        for (int i = 0; i < length_t / 2; ++i) {
            delete[] temp[i];
        }
        delete[] temp;

    }

    for (int i = 0; i < length_m / 2; ++i) {
        delete[] mv[i];
    }
    delete[] mv;

    int score = (Playing_Field->number_geese) * 100 - (length_m / 2 - 1) - (length_c / 2 - 1);
    return score;
}


static bool is_end_game(TPlaying_Field* Playing_Field) {
    if (Playing_Field->number_geese < 7) {
        return true;
    }

    int i = Playing_Field->poz_fox[0];
    int j = Playing_Field->poz_fox[1];

    int** mv = Playing_Field->check_move(i, j);
    int length_m = static_cast<int>(_msize(mv) / sizeof(int));

    int** capt = Playing_Field->check_capture(i, j);
    int length_c = static_cast<int>(_msize(capt) / sizeof(int));

    for (int i = 0; i < length_m / 2; ++i) {
        delete[] mv[i];
    }
    delete[] mv;


    for (int i = 0; i < length_c / 2; ++i) {
        delete[] capt[i];
    }
    delete[] capt;

    if ((((length_m / 2) - 1) == 0) && (((length_c / 2) - 1) == 0)) {
        return true;
    }

    return false;
}


static int AlphaBeta(TPlaying_Field* Playing_Field, int depth, int alpha, int beta, bool is_maximizing_player, bool captured = false) {

    if ((depth == (Playing_Field->maxDepth - 1)) || (is_end_game(Playing_Field))) {
        return Evaluation(Playing_Field);
    }

    if (is_maximizing_player) {

        int score = MIN;
        for (int lineIdx = 0; lineIdx < 13; lineIdx++) {
            auto line = Playing_Field->board[lineIdx];
            for (int colIdx = 0; colIdx < 13; colIdx++) {
                auto elem = line[colIdx];

                if (elem == 'G') {

                    Playing_Field->board[lineIdx][colIdx] = '·';
                    int** moves = Playing_Field->check_move(lineIdx, colIdx);
                    int length_m = static_cast<int>(_msize(moves) / sizeof(int));

                    for (int i = 0; i < (length_m / 2) - 1; i++) {
                        Playing_Field->board[moves[i][0]][moves[i][1]] = 'G';
                        int val = AlphaBeta(Playing_Field, depth + 1, alpha, beta, !is_maximizing_player);
                        score = max(score, val);
                        alpha = max(alpha, score);
                        Playing_Field->board[moves[i][0]][moves[i][1]] = '·';

                        if (beta <= alpha)
                            break;
                    }

                    for (int i = 0; i < length_m / 2; ++i) {
                        delete[] moves[i];
                    }
                    delete[] moves;

                    Playing_Field->board[lineIdx][colIdx] = 'G';
                }
            }
        }
        return score;
    }
    else {

        int score = MAX;

        int line_idx = Playing_Field->poz_fox[0];
        int col_idx = Playing_Field->poz_fox[1];

        Playing_Field->board[line_idx][col_idx] = '·';

        if (!(captured)) {
            int** moves = Playing_Field->check_move(line_idx, col_idx);
            int length_m = static_cast<int>(_msize(moves) / sizeof(int));

            for (int i = 0; i < (length_m / 2) - 1; i++) {

                Playing_Field->board[moves[i][0]][moves[i][1]] = 'V';
                Playing_Field->poz_fox[0] = moves[i][0];
                Playing_Field->poz_fox[1] = moves[i][1];

                int val = AlphaBeta(Playing_Field, depth + 1, alpha, beta, !is_maximizing_player);
                score = min(val, score);
                beta = min(beta, score);
                Playing_Field->board[moves[i][0]][moves[i][1]] = '·';
                Playing_Field->poz_fox[0] = line_idx;
                Playing_Field->poz_fox[1] = col_idx;

                if (beta <= alpha)
                    break;
            }
            for (int i = 0; i < length_m / 2; ++i) {
                delete[] moves[i];
            }
            delete[] moves;
        }

        int** captures = Playing_Field->check_capture(line_idx, col_idx);
        int length_c = static_cast<int>(_msize(captures) / sizeof(int));

        for (int i = 0; i < (length_c / 2) - 1; i++) {

            Playing_Field->board[captures[i][0]][captures[i][1]] = 'V';

            Playing_Field->poz_fox[0] = captures[i][0];
            Playing_Field->poz_fox[1] = captures[i][1];

            Playing_Field->board[(captures[i][0] + line_idx) / 2][(captures[i][1] + col_idx) / 2] = '·';

            Playing_Field->number_geese -= 1;

            int val = AlphaBeta(Playing_Field, depth + 1, alpha, beta, is_maximizing_player, true);
            score = min(val, score);
            beta = min(beta, score);

            Playing_Field->number_geese += 1;
            Playing_Field->board[captures[i][0]][captures[i][1]] = '·';
            Playing_Field->poz_fox[0] = line_idx;
            Playing_Field->poz_fox[1] = col_idx;
            Playing_Field->board[(captures[i][0] + line_idx) / 2][(captures[i][1] + col_idx) / 2] = 'G';

            if (beta <= alpha)
                break;
        }

        for (int i = 0; i < length_c / 2; ++i) {
            delete[] captures[i];
        }
        delete[] captures;

        if (captured && ((length_c / 2 - 1) == 0)) {
            Playing_Field->board[line_idx][col_idx] = 'V';
            score = AlphaBeta(Playing_Field, depth + 1, alpha, beta, !is_maximizing_player);
        }

        Playing_Field->board[line_idx][col_idx] = 'V';
        return score;
    }
}


static int** increase_array_size4(int**& arr, int old_rows) {


    int new_rows = old_rows / 2;

    int** new_arr = new int* [new_rows + 1];
    for (int i = 0; i < new_rows + 1; ++i) {
        new_arr[i] = new int[4];
    }

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < 4; ++j) {
            new_arr[i][j] = arr[i][j];
        }
    }



    for (int i = 0; i < old_rows / 4; ++i) {
        delete[] arr[i];
    }
    delete[] arr;



    return new_arr;
}

static int* findGmove(TPlaying_Field* Playing_Field, int score) {
    int** movelist = new int* [1];
    for (int count = 0; count < 1; count++)
        movelist[count] = new int[4];

    int length = static_cast<int>(_msize(movelist) / sizeof(int));

    for (int lineIdx = 0; lineIdx < 13; lineIdx++) {
        auto line = Playing_Field->board[lineIdx];
        for (int colIdx = 0; colIdx < 13; colIdx++) {
            auto elem = line[colIdx];

            if (elem == 'G') {
                Playing_Field->board[lineIdx][colIdx] = '·';
                int** moves = Playing_Field->check_move(lineIdx, colIdx);
                int length_m = static_cast<int>(_msize(moves) / sizeof(int));

                int val = 0;
                for (int i = 0; i < (length_m / 2) - 1; i++) {
                    Playing_Field->board[moves[i][0]][moves[i][1]] = 'G';

                    val = AlphaBeta(Playing_Field, 1, MIN, MAX, false);

                    if (val == score) {
                        movelist[(length / 2) - 1][0] = lineIdx;
                        movelist[(length / 2) - 1][1] = colIdx;
                        movelist[(length / 2) - 1][2] = moves[i][0];
                        movelist[(length / 2) - 1][3] = moves[i][1];

                        length = static_cast<int>(_msize(movelist) / sizeof(int));
                        movelist = increase_array_size4(movelist, length);
                        length = static_cast<int>(_msize(movelist) / sizeof(int));
                    }
                    Playing_Field->board[moves[i][0]][moves[i][1]] = '·';
                }

                Playing_Field->board[lineIdx][colIdx] = 'G';


                for (int i = 0; i < length_m / 2; ++i) {
                    delete[] moves[i];
                }
                delete[] moves;
            }
        }
    }

    if ((length / 2) - 1 == 1) {
        return movelist[0];
    }

    int randomIndex = abs(rand() % (length / 2) - 1);
    return movelist[randomIndex];
}


static int* findVmove(TPlaying_Field* Playing_Field, int score, bool captured) {
    int line_idx = Playing_Field->poz_fox[0];
    int col_idx = Playing_Field->poz_fox[1];

    Playing_Field->board[line_idx][col_idx] = '·';

    if (!(captured)) {
        int** moves = Playing_Field->check_move(line_idx, col_idx);
        int length_m = static_cast<int>(_msize(moves) / sizeof(int));

        for (int i = 0; i < (length_m / 2) - 1; i++) {

            Playing_Field->board[moves[i][0]][moves[i][1]] = 'V';
            Playing_Field->poz_fox[0] = moves[i][0];
            Playing_Field->poz_fox[1] = moves[i][1];

            int val = AlphaBeta(Playing_Field, 1, MIN, MAX, true);

            if (val == score) {
                Playing_Field->board[moves[i][0]][moves[i][1]] = '·';
                Playing_Field->poz_fox[0] = line_idx;
                Playing_Field->poz_fox[1] = col_idx;
                Playing_Field->board[line_idx][col_idx] = 'V';

                int* move = new int[4];
                move[0] = line_idx;
                move[1] = col_idx;
                move[2] = moves[i][0];
                move[3] = moves[i][1];

                return move;
            }
            Playing_Field->board[moves[i][0]][moves[i][1]] = '·';
            Playing_Field->poz_fox[0] = line_idx;
            Playing_Field->poz_fox[1] = col_idx;
        }
        for (int i = 0; i < length_m / 2; ++i) {
            delete[] moves[i];
        }
        delete[] moves;
    }

    int** captures = Playing_Field->check_capture(line_idx, col_idx);
    int length_c = static_cast<int>(_msize(captures) / sizeof(int));

    for (int i = 0; i < (length_c / 2) - 1; i++) {

        Playing_Field->board[captures[i][0]][captures[i][1]] = 'V';

        Playing_Field->poz_fox[0] = captures[i][0];
        Playing_Field->poz_fox[1] = captures[i][1];

        Playing_Field->board[(captures[i][0] + line_idx) / 2][(captures[i][1] + col_idx) / 2] = '·';

        Playing_Field->number_geese -= 1;

        int val = AlphaBeta(Playing_Field, 1, MIN, MAX, false, true);

        if (val >= score) {
            Playing_Field->number_geese += 1;
            Playing_Field->board[captures[i][0]][captures[i][1]] = '·';
            Playing_Field->poz_fox[0] = line_idx;
            Playing_Field->poz_fox[1] = col_idx;
            Playing_Field->board[(captures[i][0] + line_idx) / 2][(captures[i][1] + col_idx) / 2] = 'G';
            Playing_Field->board[line_idx][col_idx] = 'V';

            int* move = new int[4];
            move[0] = line_idx;
            move[1] = col_idx;
            move[2] = captures[i][0];
            move[3] = captures[i][1];

            return move;
        }

        Playing_Field->number_geese += 1;
        Playing_Field->board[captures[i][0]][captures[i][1]] = '·';
        Playing_Field->poz_fox[0] = line_idx;
        Playing_Field->poz_fox[1] = col_idx;
        Playing_Field->board[(captures[i][0] + line_idx) / 2][(captures[i][1] + col_idx) / 2] = 'G';
    }

    for (int i = 0; i < length_c / 2; ++i) {
        delete[] captures[i];
    }
    delete[] captures;

    Playing_Field->board[line_idx][col_idx] = 'V';

    int* move = new int[4];
    move[0] = line_idx;
    move[1] = col_idx;
    move[2] = line_idx;
    move[3] = col_idx;

    return move;
}

// Функция, которая проверяет, есть ли определенное значение в двумерном массиве
static bool is_value_in_array2(int linFin, int colFin, int** mv, int length_m) {
    for (int i = 0; i < (length_m / 2) - 1; ++i) {
        if (linFin == mv[i][0] && colFin == mv[i][1])
            return true;
    }
    return false;
}


int main() {
    setlocale(LC_ALL, "Rus");
    std::srand(static_cast<unsigned int>(std::time(0)));
    TPlaying_Field Game;

    int mode = 0;
    bool capture;
    bool player;

    cout << "Введите режим игры (1 - за лису; 2 - за гусей): ";
    cin >> mode;
    if (mode == 1) {
        Game.board[6][6] = '·';
        Game.display();

        cout << "Введите начальное положение лисы" << endl;

        cout << "По вертикали: ";
        cin >> Game.poz_fox[0];
        Game.poz_fox[0] = Game.poz_fox[0] * 2;


        cout << "По горизонтали: ";
        cin >> Game.poz_fox[1];
        Game.poz_fox[1] = Game.poz_fox[1] * 2;

        Game.board[Game.poz_fox[0]][Game.poz_fox[1]] = 'V';


        player = true;
        capture = false;
        Game.geese = true;
    }
    else {
        player = false;
        capture = false;
        Game.geese = false;
    }

    int score = 0;


    int linFin{};
    int colFin{};

    while (!is_end_game(&Game)) {
        if (player) {
            if (Game.geese) {
                score = AlphaBeta(&Game, 0, MIN, MAX, Game.geese);
                int* move = findGmove(&Game, score);
                Game.board[move[0]][move[1]] = '·';
                Game.board[move[2]][move[3]] = 'G';

                player = !player;

                Game.display();
                cout << endl;

                cout << endl;

                delete[] move;

            }
            else {
                score = AlphaBeta(&Game, 0, MIN, MAX, Game.geese, capture);
                int* move = findVmove(&Game, score, capture);

                if ((move[0] == move[2]) && (move[1] == move[3])) {
                    capture = false;
                    player = !player;
                }
                else {
                    Game.board[move[0]][move[1]] = '·';
                    Game.board[move[2]][move[3]] = 'V';

                    Game.poz_fox[0] = move[2];
                    Game.poz_fox[1] = move[3];

                    if ((abs(move[0] - move[2]) == 4) || (abs(move[1] - move[3]) == 4)) {
                        capture = true;

                        Game.board[abs(move[0] + move[2]) / 2][abs(move[1] + move[3]) / 2] = '·';
                        Game.number_geese -= 1;
                    }
                    else {
                        player = !player;
                    }
                }

                delete[] move;

                Game.display();
                cout << endl;
            }
        }
        else {
            Game.display();
            cout << endl;

            if (Game.geese) {
                int linInit = Game.poz_fox[0];
                int colInit = Game.poz_fox[1];

                int** ls = Game.check_capture(linInit, colInit);
                int length_ls = static_cast<int>(_msize(ls) / sizeof(int));

                if ((!capture) || ((length_ls / 2 - 1) != 0)) {
                    while (true) {
                        cout << "Evaluation: " << Evaluation(&Game);
                        cout << endl;
                        cout << "Введите ход лисы (на клавиши wasdqezc): ";
                        string k;
                        cin >> k;

                        if (k == "w") {
                            if (Game.board[Game.poz_fox[0] - 2][Game.poz_fox[1]] == 'G') {
                                linFin = Game.poz_fox[0] - 4;
                                colFin = Game.poz_fox[1];
                            }
                            else {
                                linFin = Game.poz_fox[0] - 2;
                                colFin = Game.poz_fox[1];
                            }
                        }
                        if (k == "d") {
                            if (Game.board[Game.poz_fox[0]][Game.poz_fox[1] + 2] == 'G') {
                                linFin = Game.poz_fox[0];
                                colFin = Game.poz_fox[1] + 4;
                            }
                            else {
                                linFin = Game.poz_fox[0];
                                colFin = Game.poz_fox[1] + 2;
                            }

                        }
                        if (k == "a") {
                            if (Game.board[Game.poz_fox[0]][Game.poz_fox[1] - 2] == 'G') {
                                linFin = Game.poz_fox[0];
                                colFin = Game.poz_fox[1] - 4;
                            }
                            else {
                                linFin = Game.poz_fox[0];
                                colFin = Game.poz_fox[1] - 2;
                            }

                        }
                        if (k == "s") {
                            if (Game.board[Game.poz_fox[0] + 2][Game.poz_fox[1]] == 'G') {
                                linFin = Game.poz_fox[0] + 4;
                                colFin = Game.poz_fox[1];
                            }
                            else {
                                linFin = Game.poz_fox[0] + 2;
                                colFin = Game.poz_fox[1];
                            }
                        }

                        if (k == "q") {
                            if (Game.board[Game.poz_fox[0] - 2][Game.poz_fox[1] - 2] == 'G') {
                                linFin = Game.poz_fox[0] - 4;
                                colFin = Game.poz_fox[1] - 4;
                            }
                            else {
                                linFin = Game.poz_fox[0] - 2;
                                colFin = Game.poz_fox[1] - 2;
                            }
                        }
                        if (k == "e") {
                            if (Game.board[Game.poz_fox[0] - 2][Game.poz_fox[1] + 2] == 'G') {
                                linFin = Game.poz_fox[0] - 4;
                                colFin = Game.poz_fox[1] + 4;
                            }
                            else {
                                linFin = Game.poz_fox[0] - 2;
                                colFin = Game.poz_fox[1] + 2;
                            }
                        }
                        if (k == "z") {
                            if (Game.board[Game.poz_fox[0] + 2][Game.poz_fox[1] - 2] == 'G') {
                                linFin = Game.poz_fox[0] + 4;
                                colFin = Game.poz_fox[1] - 4;
                            }
                            else {
                                linFin = Game.poz_fox[0] + 2;
                                colFin = Game.poz_fox[1] - 2;
                            }
                        }
                        if (k == "c") {
                            if (Game.board[Game.poz_fox[0] + 2][Game.poz_fox[1] + 2] == 'G') {
                                linFin = Game.poz_fox[0] + 4;
                                colFin = Game.poz_fox[1] + 4;
                            }
                            else {
                                linFin = Game.poz_fox[0] + 2;
                                colFin = Game.poz_fox[1] + 2;
                            }
                        }

                        break;
                    }
                }

                if (capture) {
                    if (((length_ls / 2) - 1) == 0) {
                        capture = false;
                        player = !player;
                    }
                    else if (is_value_in_array2(linFin, colFin, ls, length_ls)) {
                        Game.board[linInit][colInit] = '·';
                        Game.board[linFin][colFin] = 'V';

                        Game.poz_fox[0] = linFin;
                        Game.poz_fox[1] = colFin;

                        Game.number_geese -= 1;

                        Game.board[abs(linInit + linFin) / 2][abs(colInit + colFin) / 2] = '·';

                        Game.display();
                        cout << endl;
                    }
                }
                else {
                    int** move = Game.check_move(linInit, colInit);
                    int length_m = static_cast<int>(_msize(move) / sizeof(int));
                    if (is_value_in_array2(linFin, colFin, move, length_m)) {
                        Game.board[linInit][colInit] = '·';
                        Game.board[linFin][colFin] = 'V';

                        Game.poz_fox[0] = linFin;
                        Game.poz_fox[1] = colFin;

                        player = !player;

                        Game.display();
                        cout << endl;
                    }
                    else if (is_value_in_array2(linFin, colFin, ls, length_ls)) {
                        Game.board[linInit][colInit] = '·';
                        Game.board[linFin][colFin] = 'V';
                        Game.display();
                        cout << endl;

                        Game.poz_fox[0] = linFin;
                        Game.poz_fox[1] = colFin;
                        Game.number_geese -= 1;

                        Game.board[abs(linInit + linFin) / 2][abs(colInit + colFin) / 2] = '·';

                        capture = true;

                        Game.display();
                        cout << endl;
                    }

                    for (int i = 0; i < length_m / 2; ++i) {
                        delete[] move[i];
                    }
                    delete[] move;
                }

                for (int i = 0; i < length_ls / 2; ++i) {
                    delete[] ls[i];
                }
                delete[] ls;

            }
            else {
                Game.display();
                cout << endl;

                int linInit = 20;
                int colInit = 20;
                int linFin = 20;
                int colFin = 20;

                while (true) {


                    if (!Game.geese) {
                        cout << "Введите координаты гуся которого хотите подвинуть: " << endl;
                        cin >> linInit;
                        linInit = linInit * 2;
                        cout << endl;
                        cin >> colInit;
                        colInit = colInit * 2;
                        cout << endl;

                    }

                    if (Game.board[linInit][colInit] != 'G') {
                        Game.display2(linInit, colInit);
                        cout << endl;
                        cout << "Некорректный выбор" << endl;
                        continue;
                    }

                    Game.display2(linInit, colInit);
                    cout << endl;

                    cout << "Вы уверены в выборе(y/n): " << endl;
                    char z;
                    cin >> z;
                    if (z == 'y') {
                        break;
                    }

                }

                while (true) {

                    cout << "Введите координаты куда вы хотите подвинуть гуся: " << endl;
                    if (!Game.geese) {
                        cin >> linFin;
                        linFin = linFin * 2;
                        cout << endl;
                        cin >> colFin;
                        colFin = colFin * 2;
                        cout << endl;
                    }

                    if ((abs(linInit - linFin) + (abs(colInit - colFin)) >= 3) || (Game.board[linFin][colFin] == 'G')) {
                        Game.display3(linInit, colInit, linFin, colFin);
                        cout << endl;
                        cout << "Некорректный ход" << endl;
                        continue;
                    }

                    Game.display3(linInit, colInit, linFin, colFin);
                    cout << endl;

                    cout << "Вы уверены в выборе(y/n): " << endl;
                    char z;
                    cin >> z;
                    if (z == 'y') {
                        break;
                    }
                }



                if (linFin != linInit or colFin != colInit) {
                    player = !player;

                    Game.board[linInit][colInit] = '·';
                    Game.board[linFin][colFin] = 'G';
                }

                Game.display();
                cout << endl;
            }
        }
    }
    Game.display();

    if ((Game.number_geese < 7) && (player = true)) {
        cout << "\nВы выиграли" << endl;
    }
    else {
        cout << "\nВы проиграли" << endl;
    }


    return 0;
}