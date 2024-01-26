#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "deps/raygui/src/raygui.h"

void DrawSingleBlock(int color, Vector2 coordinates) {
    Color main_color = BLACK;
    Color accent_color = BLACK;
    Rectangle rectangle = (Rectangle){coordinates.x * 20, coordinates.y * 20, 20, 20};

    switch (color) {
        case 0:
            main_color = RED;
            accent_color = MAROON;
            break;
        case 1:
            main_color = GOLD;
            accent_color = ORANGE;
            break;
        case 2:
            main_color = LIME;
            accent_color = DARKGREEN;
            break;
        case 3:
            main_color = BLUE;
            accent_color = DARKBLUE;
            break;
        case 4:
            main_color = PURPLE;
            accent_color = VIOLET;
            break;
        default:
            main_color = GRAY;
            accent_color = DARKGRAY;
    }
    DrawRectangleRec(rectangle, main_color);
    DrawRectangleLinesEx(rectangle, 4, accent_color);
}
void DrawTetrisText() {
    DrawSingleBlock(0, (Vector2){1, 1});
    DrawSingleBlock(0, (Vector2){2, 1});
    DrawSingleBlock(0, (Vector2){2, 2});
    DrawSingleBlock(0, (Vector2){2, 3});
    DrawSingleBlock(0, (Vector2){2, 4});
    DrawSingleBlock(0, (Vector2){2, 5});
    DrawSingleBlock(0, (Vector2){2, 4});
    DrawSingleBlock(0, (Vector2){3, 1});

    DrawSingleBlock(1, (Vector2){5, 1});
    DrawSingleBlock(1, (Vector2){5, 2});
    DrawSingleBlock(1, (Vector2){5, 3});
    DrawSingleBlock(1, (Vector2){6, 3});
    DrawSingleBlock(1, (Vector2){5, 4});
    DrawSingleBlock(1, (Vector2){5, 5});
    DrawSingleBlock(1, (Vector2){6, 5});
    DrawSingleBlock(1, (Vector2){7, 5});
    DrawSingleBlock(1, (Vector2){6, 1});
    DrawSingleBlock(1, (Vector2){7, 1});

    DrawSingleBlock(0, (Vector2){9, 1});
    DrawSingleBlock(0, (Vector2){10, 1});
    DrawSingleBlock(0, (Vector2){10, 2});
    DrawSingleBlock(0, (Vector2){10, 3});
    DrawSingleBlock(0, (Vector2){10, 4});
    DrawSingleBlock(0, (Vector2){10, 5});
    DrawSingleBlock(0, (Vector2){10, 4});
    DrawSingleBlock(0, (Vector2){11, 1});

    DrawSingleBlock(2, (Vector2){13, 1});
    DrawSingleBlock(2, (Vector2){13, 2});
    DrawSingleBlock(2, (Vector2){13, 3});
    DrawSingleBlock(2, (Vector2){13, 4});
    DrawSingleBlock(2, (Vector2){13, 5});
    DrawSingleBlock(2, (Vector2){14, 1});
    DrawSingleBlock(2, (Vector2){14, 3});
    DrawSingleBlock(2, (Vector2){15, 1});
    DrawSingleBlock(2, (Vector2){15, 2});
    DrawSingleBlock(2, (Vector2){15, 4});
    DrawSingleBlock(2, (Vector2){15, 5});

    DrawSingleBlock(3, (Vector2){17, 1});
    DrawSingleBlock(3, (Vector2){17, 2});
    DrawSingleBlock(3, (Vector2){17, 3});
    DrawSingleBlock(3, (Vector2){17, 4});
    DrawSingleBlock(3, (Vector2){17, 5});

    DrawSingleBlock(4, (Vector2){19, 1});
    DrawSingleBlock(4, (Vector2){20, 1});
    DrawSingleBlock(4, (Vector2){21, 1});
    DrawSingleBlock(4, (Vector2){19, 2});
    DrawSingleBlock(4, (Vector2){19, 3});
    DrawSingleBlock(4, (Vector2){20, 3});
    DrawSingleBlock(4, (Vector2){21, 3});
    DrawSingleBlock(4, (Vector2){21, 4});
    DrawSingleBlock(4, (Vector2){19, 5});
    DrawSingleBlock(4, (Vector2){20, 5});
    DrawSingleBlock(4, (Vector2){21, 5});
}
typedef struct Tetromino {
    Vector2* blocks;
    Vector2 location;
    int color;
    bool isVisible;
} Tetromino;
void DrawTetromino(Tetromino* tetromino, Vector2 board_zero_coordinates) {
    for (int i = 0; i < 4; i++) {
        Vector2 coordinates = tetromino->blocks[i];
        float x = coordinates.x + board_zero_coordinates.x;
        float y = coordinates.y + board_zero_coordinates.y;
        int color = tetromino->color;

        DrawSingleBlock(color, (Vector2){x, y});
    }
}
Tetromino CreateTetrominoI(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){1, 0};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){1, 3};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color, true};
    return tetromino;
}
Tetromino CreateTetrominoL(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){1, 0};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){2, 2};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color, true};
    return tetromino;
}
Tetromino CreateTetrominoJ(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){2, 0};
    blocks[1] = (Vector2){2, 1};
    blocks[2] = (Vector2){2, 2};
    blocks[3] = (Vector2){1, 2};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color, true};
    return tetromino;
}
Tetromino CreateTetrominoO(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){1, 1};
    blocks[1] = (Vector2){2, 2};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){2, 1};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color, true};
    return tetromino;
}
Tetromino CreateTetrominoT(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){0, 1};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){2, 1};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color, true};
    return tetromino;
}
Tetromino CreateTetrominoS(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){2, 1};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){0, 2};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color, true};
    return tetromino;
}
Tetromino CreateTetrominoZ(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){0, 1};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){2, 2};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color, true};
    return tetromino;
}
Tetromino CreateRandomTetromino() {
    int random_color = rand();
    int random_tetromino = rand();
    Tetromino tetromino;
    random_color = random_color % 5;
    random_tetromino = random_tetromino % 7;

    switch (random_tetromino) {
        case 0:
            tetromino = CreateTetrominoI(random_color);
            break;
        case 1:
            tetromino = CreateTetrominoL(random_color);
            break;
        case 2:
            tetromino = CreateTetrominoJ(random_color);
            break;
        case 3:
            tetromino = CreateTetrominoO(random_color);
            break;
        case 4:
            tetromino = CreateTetrominoT(random_color);
            break;
        case 5:
            tetromino = CreateTetrominoS(random_color);
            break;
        default:
            tetromino = CreateTetrominoZ(random_color);
    }
    return tetromino;
}
int main(void) {
    // Initialization
    const int screenWidth = 460;
    const int screenHeight = 600;
    const int board_height = 20;
    const int board_width = 10;

    int board[board_width][board_height];
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            board[x][y] = -1;
        }
    }

    InitWindow(screenWidth, screenHeight, "basic window");
    SetTargetFPS(5);  // Set our game to run at 60 frames-per-second
    GuiSetFont(GetFontDefault());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    int game_state = 0;
    Tetromino user_controlled_tetromino = CreateRandomTetromino();

    printf("[debug]\n");
    bool clear_row = true;
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        user_controlled_tetromino = CreateRandomTetromino();
        // Update
        //----------------------------------------------------------------------------------
        //        for (int y = 0; y < 20; y++) {
        //            clear_row = true;
        //            for (int x = 0; x < 10; x++) {
        //                int c = board[x][19];
        //                printf("x=%i|color=%i\n", x, c);
        //                if (board[x][19] == -1) {
        //                    clear_row = false;
        //                }
        //            }
        //            if (clear_row == true) {
        //                for (int x = 0; x < 10; x++) {
        //                    board[x][19] = -1;
        //                }
        //                printf("clear_row=true\n");
        //            } else {
        //                printf("clear_row=false\n");
        //            }
        //        }
        //        for (int y = 20 - 2; y >= 0; y--) {
        //            for (int x = 0; x < 10; x++) {
        //                int y_plus_one_color = board[x][y + 1];
        //                int current_y_color = board[x][y];
        //                if (current_y_color > -1) {
        //                    printf("%i\n", current_y_color);
        //                    printf("x=%i|y=%i\n", x, y);
        //                    if (y_plus_one_color == -1) {
        //                        board[x][y + 1] = current_y_color;
        //                        board[x][y] = -1;
        //                    }
        //                }
        //            }
        //        }
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        //
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTetrisText();
        for (int y = 0; y < 30; y++) {
            for (int x = 0; x < 23; x++) {
                int x_offseted = x + board_height;
                int y_offseted = y + board_height;
                if (x >= 1 && x < 1 + board_width) {
                    if (y >= 9 && y < 9 + board_height) {
                        DrawRectangleLines(x * 20, y * 20, 20, 20, DARKGRAY);
                    }
                }
                if ((y >= 9 && y < 9 + board_height) && (x == 0 || x == board_width + 1 || x == 22)) {
                    DrawSingleBlock(5, (Vector2){x, y});
                }
                if (y == 8 || y == 9 + board_height) {
                    DrawSingleBlock(5, (Vector2){x, y});
                }
            }
        }

        // for (int y = 0; y < 20; y++) {
        //     for (int x = 0; x < 10; x++) {
        //         int color = board[x][y];
        //         if (color > -1) {
        //             DrawSingleBlock(color, (Vector2){x + 1, y + 9});
        //         }
        //     }
        // }
        DrawText("NEXT:", 13 * 20, 12 * 20, 20, LIGHTGRAY);
        DrawText("SCORE:", 13 * 20, 17 * 20, 20, LIGHTGRAY);
        DrawText("2137", 13 * 20, 18 * 20, 20, LIGHTGRAY);
        DrawTetromino(&user_controlled_tetromino, (Vector2){18, 10});
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
