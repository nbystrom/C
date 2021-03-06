#include <iostream>
#include <cstdlib>
#include <ctime>

int width = 20;
int height = 20;

const short N = 1;
const short S = 2;
const short E = 4;
const short W = 8;

int DX[9];
int DY[9];
int opposite[9];

void shuffle(int array[], int length);
void CarveMaze(int x, int y);
void PrintMaze();
bool isOut(int cx, int cy);
void Create2DArray(int height, int width, int** arr, int value=0);

int** grid = NULL;

int main ()
{
    int seed = std::time(0);
    std::srand(seed);
    
    DX[N] = 0;
    DX[S] = 0;
    DX[E] = 1;
    DX[W] = -1;
    
    DY[N] = -1;
    DY[S] = 1;
    DY[E] = 0;
    DY[W] = 0;
    
    opposite[N] = S;
    opposite[S] = N;
    opposite[E] = W;
    opposite[W] = E;
    
    grid = new int*[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new int[width];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = 0;
        }
    }
    
    CarveMaze(0, 0);
    PrintMaze();
    
    std::cout << "seed was: " << seed << std::endl;
    
    for (int i = 0; i < height; i++) {
        delete [] grid[i];
    }
    delete [] grid;
}

void CarveMaze (int cx, int cy)
{
    int directions[4] = { N, S, E, W };
    shuffle(directions, 4);
    for (int i = 0; i < 4; i++) {
        int nx = cx + DX[directions[i]];
        int ny = cy + DY[directions[i]];
        
        if (isOut(nx, ny)) continue;
        
        if (grid[ny][nx] == 0) {
            grid[cy][cx] |= directions[i];
            grid[ny][nx] |= opposite[directions[i]];
            CarveMaze(nx, ny);
        }
    }
}

bool isOut (int x, int y)
{
    if (x < 0 || x >= width) return true;
    if (y < 0 || y >= height) return true;
    return false;
}

void PrintMaze ()
{
    using namespace std;
    
    cout << " ";
    for (int x = 0; x < width*2-1; x++) {
        cout << "_";
    }
    cout << endl;
    
    for (int y = 0; y < height; y++) {
        cout << "|";
        for (int x = 0; x < width; x++) {
            if ((grid[y][x] & S) != 0) {
                cout << " ";
            } else {
                cout << "_";
            }
            
            if ((grid[y][x] & E) != 0) {
                if (((grid[y][x] | grid[y][x+1]) & S) != 0) {
                    cout << " ";
                } else {
                    cout << "_";
                }
            } else {
                cout << "|";
            }
        }
        cout << endl;
    }
}


void shuffle (int array[], int length)
{    
    for (int i = length-1; i > 0; i--) {
        int j = std::rand() % i;
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
}
