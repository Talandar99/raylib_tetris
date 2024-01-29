#include <stdbool.h>
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
        case 5:
            main_color = WHITE;
            accent_color = WHITE;
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
} Tetromino;
void DrawTetromino(Tetromino* tetromino) {
    for (int i = 0; i < 4; i++) {
        Vector2 coordinates = tetromino->blocks[i];
        float x = coordinates.x + 1 + tetromino->location.x;
        float y = coordinates.y + 9 + tetromino->location.y;
        int color = tetromino->color;

        DrawSingleBlock(color, (Vector2){x, y});
    }
}
bool CanMoveTetrominoLeftSide(Tetromino* tetromino, int** board) {
    bool can_move = true;
    for (int i = 0; i < 4; i++) {
        int x = tetromino->blocks[i].x + tetromino->location.x;
        int y = tetromino->blocks[i].y + tetromino->location.y;
        if (x < 1 || board[x - 1][y] > -1) {
            can_move = false;
        }
    }
    return can_move;
}
bool CanMoveTetrominoRightSide(Tetromino* tetromino, int** board) {
    bool can_move = true;
    for (int i = 0; i < 4; i++) {
        int x = tetromino->blocks[i].x + tetromino->location.x;
        int y = tetromino->blocks[i].y + tetromino->location.y;
        if (x > 8 || board[x + 1][y] > -1) {
            can_move = false;
        }
    }
    return can_move;
}
bool CanMoveTetrominoDown(Tetromino* tetromino, int** board) {
    bool can_move = true;
    for (int i = 0; i < 4; i++) {
        int x = tetromino->blocks[i].x + tetromino->location.x;
        int y = tetromino->blocks[i].y + tetromino->location.y;
        if (y + 1 > 19 || board[x][y + 1] > -1) {
            can_move = false;
        }
    }
    return can_move;
}
bool CanRotateTetromino(Tetromino* tetromino, int** board) {
    bool can_rotate = true;
    for (int i = 0; i < 4; i++) {
        int temp = tetromino->blocks[i].x;
        int x = tetromino->blocks[i].y + tetromino->location.x;
        int y = 3 - temp + tetromino->location.y;
        if (x > 8) {
            can_rotate = false;
        }
        if (x < 1) {
            can_rotate = false;
        }
        if (y + 1 > 19 || board[x][y + 1] > -1) {
            can_rotate = false;
        }
    }
    return can_rotate;
}
void RotateTetromino(Tetromino* tetromino) {
    float location_x = tetromino->location.x;
    float location_y = tetromino->location.y;

    for (int i = 0; i < 4; i++) {
        int temp = tetromino->blocks[i].x;
        tetromino->blocks[i].x = tetromino->blocks[i].y;
        tetromino->blocks[i].y = 3 - temp;
    }
}
void MoveTetromino(Tetromino* tetromino, Vector2 offset) {
    Vector2* new_blocks_location = malloc(4 * sizeof(Vector2));
    bool can_move = true;
    for (int i = 0; i < 4; i++) {
        new_blocks_location[i].x = tetromino->blocks[i].x + offset.x;
        new_blocks_location[i].y = tetromino->blocks[i].y + offset.y;
        if (new_blocks_location[i].y > 19) {
            can_move = false;
        }
    }
    if (can_move) {
        tetromino->location.x = tetromino->location.x + offset.x;
        tetromino->location.y = tetromino->location.y + offset.y;
    }
    free(new_blocks_location);
}
Tetromino CreateTetrominoI(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){1, 0};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){1, 3};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color};
    return tetromino;
}
Tetromino CreateTetrominoL(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){1, 0};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){2, 2};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color};
    return tetromino;
}
Tetromino CreateTetrominoJ(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){2, 0};
    blocks[1] = (Vector2){2, 1};
    blocks[2] = (Vector2){2, 2};
    blocks[3] = (Vector2){1, 2};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color};
    return tetromino;
}
Tetromino CreateTetrominoO(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){1, 1};
    blocks[1] = (Vector2){2, 2};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){2, 1};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color};
    return tetromino;
}
Tetromino CreateTetrominoT(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){0, 1};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){2, 1};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color};
    return tetromino;
}
Tetromino CreateTetrominoS(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){3, 1};
    blocks[1] = (Vector2){2, 1};
    blocks[2] = (Vector2){2, 2};
    blocks[3] = (Vector2){1, 2};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color};
    return tetromino;
}
Tetromino CreateTetrominoZ(int color) {
    struct Tetromino tetromino;
    Vector2* blocks = malloc(4 * sizeof(Vector2));
    blocks[0] = (Vector2){0, 1};
    blocks[1] = (Vector2){1, 1};
    blocks[2] = (Vector2){1, 2};
    blocks[3] = (Vector2){2, 2};
    tetromino = (Tetromino){blocks, (Vector2){0, 0}, color};
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
    int score = 0;
    int frame = 0;
    int** board = (int**)malloc(board_width * sizeof(int*));
    for (int i = 0; i < board_width; i++) {
        board[i] = (int*)malloc(board_height * sizeof(int));
    }
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            board[x][y] = -1;
        }
    }

    InitWindow(screenWidth, screenHeight, "basic window");
    SetTargetFPS(15);  // Set our game to run at 60 frames-per-second
    GuiSetFont(GetFontDefault());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    int game_state = 0;
    Tetromino user_controlled_tetromino = CreateRandomTetromino();
    Tetromino next_tetromino = CreateRandomTetromino();
    printf("[debug]\n");
    bool clear_row = true;

    user_controlled_tetromino = CreateRandomTetromino();
    next_tetromino = CreateRandomTetromino();
    next_tetromino.location.x = 15;
    next_tetromino.location.y = 1;
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        if (frame >= 60) {
            frame = 0;
        }
        // Update
        //----------------------------------------------------------------------------------
        Vector2 block_move = (Vector2){0, 0};
        if (frame % 4 == 0) {
            block_move.y = block_move.y + 1;
        }
        if (IsKeyDown(KEY_A)) {
            if (CanMoveTetrominoLeftSide(&user_controlled_tetromino, board)) {
                block_move.x = block_move.x - 1;
            }
        }
        if (IsKeyDown(KEY_D)) {
            if (CanMoveTetrominoRightSide(&user_controlled_tetromino, board)) {
                block_move.x = block_move.x + 1;
            }
        }
        if (IsKeyPressed(KEY_W)) {
            if (CanRotateTetromino(&user_controlled_tetromino, board)) {
                RotateTetromino(&user_controlled_tetromino);
            }
        }
        if (CanMoveTetrominoDown(&user_controlled_tetromino, board)) {
            MoveTetromino(&user_controlled_tetromino, block_move);
        } else {
            for (int i = 0; i < 4; i++) {
                int block_x = user_controlled_tetromino.blocks[i].x + user_controlled_tetromino.location.x;
                int block_y = user_controlled_tetromino.blocks[i].y + user_controlled_tetromino.location.y;
                int color = user_controlled_tetromino.color;
                board[block_x][block_y] = color;
            }
            next_tetromino.location.x = 3;
            next_tetromino.location.y = 0;
            user_controlled_tetromino = next_tetromino;
            next_tetromino = CreateRandomTetromino();
            next_tetromino.location.x = 15;
            next_tetromino.location.y = 1;
        }
        // Change row color if it's full
        for (int y = 0; y < 20; y++) {
            bool row_is_full = true;
            for (int x = 0; x < 10; x++) {
                if (board[x][y] == -1) {
                    row_is_full = false;
                }
            }
            if (row_is_full) {
                score = score + 100;
                for (int x = 0; x < 10; x++) {
                    board[x][y] = -1;
                }
                for (int y2 = y; y2 > 1; y2--) {
                    for (int x = 0; x < 10; x++) {
                        board[x][y2] = board[x][y2 - 1];
                    }
                }
            }
        }

        frame++;
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
                    DrawSingleBlock(-1, (Vector2){x, y});
                }
                if (y == 8 || y == 9 + board_height) {
                    DrawSingleBlock(-1, (Vector2){x, y});
                }
            }
        }
        for (int x = 0; x < board_width; x++) {
            for (int y = 0; y < board_height; y++) {
                if (board[x][y] > -1) {
                    DrawSingleBlock(board[x][y], (Vector2){x + 1, y + 9});
                }
            }
        }
        DrawText("NEXT:", 13 * 20, 12 * 20, 20, LIGHTGRAY);
        DrawText("SCORE:", 13 * 20, 17 * 20, 20, LIGHTGRAY);
        DrawText(TextFormat("%i", score), 13 * 20, 18 * 20, 20, LIGHTGRAY);
        DrawTetromino(&user_controlled_tetromino);
        DrawTetromino(&next_tetromino);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
