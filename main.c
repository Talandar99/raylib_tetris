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
void DrawTetris() {
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
    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
    GuiSetFont(GetFontDefault());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    int game_state = 0;
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTetris();
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

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 10; x++) {
                int color = board[x][y];
                if (color > -1) {
                    DrawSingleBlock(color, (Vector2){x + 1, y + 9});
                }
            }
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
