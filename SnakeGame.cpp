#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Размеры игрового поля
const int WIDTH = 50;
const int HEIGHT = 25;

// Координаты змейки и еды
vector<pair<int, int>> snake;
pair<int, int> food;

// Направление движения змейки
char direction = 'd';

// Флаг окончания игры
bool gameOver = false;

// Инициализация игры
void initializeGame() {
    snake.clear();
    snake.push_back({ HEIGHT / 2, WIDTH / 2 });
    srand(time(0));
    food = { rand() % HEIGHT, rand() % WIDTH };
}

// Рисование игрового поля
void draw() {
    system("cls");

    // Верхняя граница
    for (int i = 0; i < WIDTH + 2; i++) 
        cout << "=";
    cout << endl;

    // Поле с змеёй и едой
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            if (j == 0 || j == WIDTH + 1)
                cout << "=";
            else {
                bool isSnakePart = false;
                for (auto& part : snake) {
                    if (part.first == i && part.second == j - 1) {
                        cout << "@";
                        isSnakePart = true;
                        break;
                    }
                }
                if (food.first == i && food.second == j - 1)
                    cout << "O";
                else if (!isSnakePart)
                    cout << " ";
            }
        }
        cout << endl;
    }

    // Нижняя граница
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "=";
    cout << endl;
}

// Логика движения змейки
void update() {
    if (_kbhit()) { // Даём ввести символ
        char newDirection = _getch(); // Определяем этот символ
        if ((newDirection == 'w' && direction != 's') ||
            (newDirection == 's' && direction != 'w') ||
            (newDirection == 'a' && direction != 'd') ||
            (newDirection == 'd' && direction != 'a')) {
            direction = newDirection;
        }
    }

    // Новая голова змейки
    pair<int, int> newHead = snake[0];
    if (direction == 'w')
        newHead.first--;
    else if (direction == 's')
        newHead.first++;
    else if (direction == 'a')
        newHead.second--;
    else if (direction == 'd')
        newHead.second++;

    // Проверка столкновения с границами или самой собой(+прикольчик)
    if (newHead.first < 0 || newHead.first >= HEIGHT || newHead.second < 0 || newHead.second >= WIDTH) {
        if (direction == 'w' || direction == 's') {
            if (snake[0].second > 0) direction = 'a' ;
            else direction = 'd';
        }
        else if (direction == 'a' || direction == 'd') {
            if (snake[0].first > 0) direction = 'w';
            else direction = 's';
        }
        /*gameOver = true;*/
        return;
    }

    for (auto& part : snake) {
        if (newHead == part) {
            gameOver = true;
            return;
        }
    }

    // Устанавливаем реалистичное передвижение змейки из за особенностей символов
    if (direction == 'w' || direction == 's')
        Sleep(45); 
    else
        Sleep(5);

    // Добавление головы в змейку
    snake.insert(snake.begin(), newHead);

    // Проверка, съела ли змейка еду
    if (newHead == food) {
        food = { rand() % HEIGHT, rand() % WIDTH };
    }
    else {
        snake.pop_back();
    }
}

int main() {
    initializeGame();

    while (!gameOver) {
        draw();
        update();
    }

    cout << "Game Over!" << endl;
    return 0;
}