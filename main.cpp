#include <raylib.h>
#include <raymath.h>

#define  SCREEN_WIDTH  600
#define  SCREEN_HEIGHT  600

#define  COLS 12
#define ROWS 12

const int TILE_WIDTH = SCREEN_WIDTH / COLS;
const int TILE_HEIGHT = SCREEN_HEIGHT / ROWS;

typedef struct 
{
    int x;
    int y;
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int nearbyMineCount;
} sTile;

sTile grid[COLS][ROWS];
int revealedTileCount;
int minesPresentCount;


void GameStartup();
void GameUpdate();
void GameShutdown();
void GameRender();
void GameReset();
void RenderTitles();
void RenderTile(sTile);
void ResetTiles();

void ResetTiles()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            grid[i][j] = (sTile)
            {
                .x = i, 
                .y = j,
                .isMine = false,
                .isRevealed = false,
                .isFlagged = false,
                .nearbyMineCount = -1
            };
        }
    }

    minesPresentCount = (int)(ROWS * COLS * 0.1f);
    int minesToPlace = minesPresentCount;
    while(minesToPlace > 0)
    {
        int col = GetRandomValue(0, COLS);
        int row = GetRandomValue(0, ROWS);

        if(!grid[col][row].isMine)
        {
            grid[col][row].isMine = true;
            minesToPlace--;
        }
    }

}

void RenderTile(sTile tile)
{
    if (tile.isMine)
    {
        DrawRectangle(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, RED);
    }
    DrawRectangleLines(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, WHITE);
}
void RenderTiles()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            RenderTile(grid[i][j]);
        }
    }
}

void GameStartup()
{
    InitAudioDevice();

    GameReset();
}

void GameUpdate()
{

}

void GameRender()
{
    RenderTiles();
}

void GameShutdown()
{
    CloseAudioDevice();
}

void GameReset()
{
    ResetTiles();
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MINESWEEPER");
    SetTargetFPS(60);
    GameStartup();

    while(!WindowShouldClose())
    {
        GameUpdate();

        BeginDrawing();
        ClearBackground(DARKBLUE);

        GameRender();


        EndDrawing();
    }
    GameShutdown();
    CloseWindow();

    return 0;
}