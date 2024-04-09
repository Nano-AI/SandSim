#include <windows.h>
#include <wingdi.h>
#include <stdbool.h>
#include <windowsx.h>
#include <winuser.h>
#include <math.h>
#include <stdio.h>

int S_WIDTH = 1000;
int S_HEIGHT = 1000;
int C_WIDTH = 250;
int C_HEIGHT = 250;
int SPAWN_RADIUS = 5;
float COLOR_PERCENT = 0.001;
float TIMER = 1000.0 / 220;


//#define GRID false

//RGBTRIPLE COLOR_1 = { 242, 145, 135 };
//RGBTRIPLE COLOR_2 = { 139, 32, 211 };
//RGBTRIPLE COLOR_3 = { 0, 160, 253 };
//RGBTRIPLE COLOR_1 = { 135, 145, 242 };
//RGBTRIPLE COLOR_2 = { 211, 32, 139 };
//RGBTRIPLE COLOR_3 = { 253, 160, 0 };
RGBTRIPLE COLOR_1 = { 106, 86, 75 };
RGBTRIPLE COLOR_2 = { 142, 131, 87 };
RGBTRIPLE COLOR_3 = { 156, 196, 72 };


#define BACKGROUND_COLOR RGB(0, 0, 0)

int colorDirection = 1;
void DrawGrid(HDC hdc, RECT rect);
void UpdateGrid();
void interpolateColor();

typedef struct particle {
    COLORREF c;
    bool e;
} particle_t;

POINT mouseLocation;
bool leftMouseDown = false;

bool rightMouseToggle = true;

//particle_t grid[C_HEIGHT][C_WIDTH];
particle_t* grid;

COLORREF currentColor = RGB(0, 0, 0);

double colorPercent = 0.0;

particle_t EMPTY = (particle_t) { RGB(0, 0, 0), false };

const char g_szClassName[] = "sandWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    static HDC hdcBuffer = NULL;
    static HBITMAP hBitmap = NULL;
    static RECT clientRect;

    switch(msg) {
        case WM_RBUTTONDOWN:
            rightMouseToggle = !rightMouseToggle;
            break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            leftMouseDown = msg == WM_LBUTTONDOWN;
            if (leftMouseDown) {
                mouseLocation.x = GET_X_LPARAM(lParam);
                mouseLocation.y = GET_Y_LPARAM(lParam);
            }
            break;
        case WM_MOUSEMOVE: {
                if (leftMouseDown) {
                    mouseLocation.x = GET_X_LPARAM(lParam);
                    mouseLocation.y = GET_Y_LPARAM(lParam);
                }
            }
            break;
        case WM_CREATE:
//            printf("%llu\n", C_HEIGHT * C_WIDTH * sizeof(particle_t));
            grid = malloc((C_HEIGHT) * (C_WIDTH) * sizeof(particle_t));
            for (int i = 0; i < C_HEIGHT; i++) {
                for (int j = 0; j < C_WIDTH; j++) {
//                    grid[i][j] = EMPTY;
                    grid[i * C_HEIGHT + j] = EMPTY;
                }
            }
            printf("HEY");
            GetClientRect(hwnd, &clientRect);
            hdcBuffer = CreateCompatibleDC(NULL);
//            hBitmap = CreateCompatibleBitmap(GetDC(hwnd), clientRect.right, clientRect.bottom);
            hBitmap = CreateCompatibleBitmap(GetDC(hwnd), clientRect.right, clientRect.bottom);
            SelectObject(hdcBuffer, hBitmap);
            break;
        case WM_SIZE: {
                RECT newClientRect;
                GetClientRect(hwnd, &newClientRect);
                if (hBitmap != NULL) {
                    DeleteObject(hBitmap);
                }
                hBitmap = CreateCompatibleBitmap(hdcBuffer, newClientRect.right, newClientRect.bottom);
                SelectObject(hdcBuffer, hBitmap);
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            DeleteDC(hdcBuffer);
            DeleteObject(hBitmap);
            PostQuitMessage(0);
            break;
        case WM_PAINT: {
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(hwnd, &ps);
            DrawGrid(hdcBuffer, clientRect);
            BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcBuffer, 0, 0, SRCCOPY);

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_TIMER: {
            // UpdateGrid();
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    wc.hbrBackground = NULL;

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            g_szClassName,
            "Sand Simulation",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, S_WIDTH, S_HEIGHT,
            NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // 60 frame / s = 1 / 60 s / f = (1 / 60) * 1000 s / ms
    // 100 ms / frame
    SetTimer(hwnd, 1, TIMER, NULL);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

bool inRange(int y, int x) {
    return y >= 0 && y < C_HEIGHT && x >= 0 && x < C_WIDTH;
}

int displace(int y, int x, particle_t* temp) {
    if (y >= C_HEIGHT - 1) return 2;
//    if (inRange(y + 1, x) && !grid[y + 1][x].e && !temp[y + 1][x].e) {
    if (inRange(y + 1, x) && !grid[(y + 1) * C_HEIGHT + x].e && !temp[C_HEIGHT * (y + 1) + x].e) {
        return 0;
    }
//    if (inRange(y + 1, x - 1) && !grid[y + 1][x - 1].e && !temp[y + 1][x - 1].e) {
    if (inRange(y + 1, x + 1) && !grid[C_HEIGHT * (y + 1) + x + 1].e && !temp[C_HEIGHT * (y + 1) + x + 1].e) {
        return 1;
    }
    if (inRange(y + 1, x - 1) && !grid[C_HEIGHT * (y + 1 ) + x - 1].e && !temp[C_HEIGHT * (y + 1) + x - 1].e) {
        return -1;
    }
//    if (inRange(y + 1, x + 1) && !grid[y + 1][x + 1].e && !temp[y + 1][x - 1].e) {
    return 2;
}

particle_t* temp;
void UpdateGrid() {
    if (temp == NULL) {
        temp = malloc(C_WIDTH * C_HEIGHT * sizeof(particle_t));
    }
//    memcpy(temp, grid, C_WIDTH * C_HEIGHT * sizeof(particle_t));

    for (int i = 0; i < C_HEIGHT; i++) {
        for (int j = 0; j < C_WIDTH; j++) {
            int d = displace(i, j, temp);
            if (!grid[C_HEIGHT * i + j].e) {
                continue;
            }
            if (inRange(i + 1, j) && (d == -1 || d == 0 || d == 1)) {
                temp[C_HEIGHT * (i + 1) + j + d] = grid[C_HEIGHT * i + j];
                grid[C_HEIGHT * i + j] = EMPTY;
                temp[C_HEIGHT * i + j] = EMPTY;
            } else {
                temp[C_HEIGHT * i + j] = grid[C_HEIGHT * i + j];
                grid[C_HEIGHT * i + j] = EMPTY;
//                temp[C_HEIGHT * i + j] = EMPTY;
            }
        }
    }

    memcpy(grid, temp, C_WIDTH * C_HEIGHT * sizeof(particle_t));
}

int sq(int v) {
    return v * v;
}

int lerp(BYTE start, BYTE end, float t) {
    return (int) (start + (end - start) * t);
}

void interpolateColor() {
    colorPercent += COLOR_PERCENT * colorDirection;
    if (colorPercent > 1.0) {
        colorDirection = -1;
        colorPercent = 1;
    }
    if (colorPercent < 0.0) {
        colorDirection = 1;
        colorPercent = 0;
    }

    if (colorPercent <= 0.50) {
        currentColor = RGB(
                    lerp(COLOR_1.rgbtRed, COLOR_2.rgbtRed, colorPercent * 2),
                    lerp(COLOR_1.rgbtGreen, COLOR_2.rgbtGreen, colorPercent * 2),
                    lerp(COLOR_1.rgbtBlue, COLOR_2.rgbtBlue, colorPercent * 2)
                );
    } else {
        currentColor = RGB(
                lerp(COLOR_2.rgbtRed, COLOR_3.rgbtRed,    (colorPercent - 0.50) * 2),
                lerp(COLOR_2.rgbtGreen, COLOR_3.rgbtGreen,(colorPercent - 0.50) * 2),
                lerp(COLOR_2.rgbtBlue, COLOR_3.rgbtBlue,  (colorPercent - 0.50) * 2)
        );
    }
}

void DrawGrid(HDC hdc, RECT rect) {
    if (rightMouseToggle) {
        UpdateGrid();
    }
    int clientWidth = rect.right - rect.left;
    int clientHeight = rect.bottom - rect.top;
    int cellWidth = floor((double) clientWidth / C_WIDTH);
    int cellHeight = floor((double) clientHeight / C_HEIGHT);

    const RECT screen = {0, 0, S_WIDTH, S_HEIGHT};
    HBRUSH brush;
    brush = CreateSolidBrush(BACKGROUND_COLOR);
    FillRect(hdc, &screen, brush);

    for (int i = 0; i < C_WIDTH; ++i) {
        for (int j = 0; j < C_HEIGHT; ++j) {
            int x = i * cellWidth;
            int y = j * cellHeight;

            if (leftMouseDown) {
                if (sq(i - mouseLocation.x / cellWidth) + sq(j - mouseLocation.y / cellHeight) < sq(SPAWN_RADIUS)) {
                    interpolateColor();
                    grid[C_HEIGHT * j + i] = (particle_t) { currentColor, true };
                }
            }

            particle_t p = grid[C_HEIGHT * j + i];

            if (p.e) {
                brush = CreateSolidBrush(p.c);

                FillRect(hdc, &((const RECT) {x, y, x + cellWidth, y + cellHeight}), brush);
            } else {
                continue;
            }

            DeleteObject(brush);
        }
    }
}
