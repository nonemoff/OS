#include <Windows.h>
#include <string>

// Глобальные переменные
COLORREF g_BackgroundColor = RGB(255, 255, 255); // Белый по умолчанию
std::wstring g_Name; // Глобальная переменная для хранения введенного имени

// Прототип функции обработки сообщений
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Функция для обработки введенного текста и отображения приветствия
void ProcessInput(HWND hwnd) {
    wchar_t buffer[256];
    GetWindowText(GetDlgItem(hwnd, 1), buffer, sizeof(buffer) / sizeof(buffer[0]));

    g_Name = buffer;

    std::wstring greeting = L"Здравствуйте, " + g_Name + L"!";
    MessageBox(hwnd, greeting.c_str(), L"Приветствие", MB_OK);
}

// Точка входа для Win32-приложения
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    // Регистрация класса окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SimpleWinAPIApp";

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, L"Не удалось зарегистрировать класс окна", L"Ошибка", MB_ICONERROR);
        return 0;
    }

    // Создание окна
    HWND hwnd = CreateWindowEx(
        0,                              // дополнительные стили
        L"SimpleWinAPIApp",             // имя класса
        L"Матвей Ушаков",               // заголовок окна
        WS_OVERLAPPEDWINDOW,            // стиль окна
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // позиция и размер окна
        NULL,                           // родительское окно
        NULL,                           // меню
        hInstance,                      // дескриптор экземпляра приложения
        NULL                            // указатель на дополнительные данные окна
    );

    if (hwnd == NULL) {
        MessageBox(NULL, L"Не удалось создать окно", L"Ошибка", MB_ICONERROR);
        return 0;
    }

    // Создание элемента управления Edit (EDIT) для ввода текста (имени)
    HWND hEdit = CreateWindowEx(
        0,
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        10, 70, 200, 20,
        hwnd,
        (HMENU)1, // Идентификатор элемента управления
        hInstance,
        NULL
    );

    if (hEdit == NULL) {
        MessageBox(NULL, L"Не удалось создать элемент управления Edit", L"Ошибка", MB_ICONERROR);
        return 0;
    }

    // Создание элемента управления Button (BUTTON) с текстом "Привет"
    HWND hButton = CreateWindowEx(
        0,
        L"BUTTON",
        L"Привет",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 100, 200, 20,
        hwnd,
        (HMENU)2, // Идентификатор элемента управления
        hInstance,
        NULL
    );

    if (hButton == NULL) {
        MessageBox(NULL, L"Не удалось создать элемент управления Button", L"Ошибка", MB_ICONERROR);
        return 0;
    }

    // Отображение окна
    ShowWindow(hwnd, nCmdShow);

    // Запуск цикла обработки сообщений
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Функция обработки сообщений
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        // Обработка события нажатия кнопки
        switch (LOWORD(wParam)) {
        case 1: // Идентификатор элемента управления Edit
            // ...
            break;

        case 2: // Идентификатор элемента управления Button
            ProcessInput(hwnd);
            break;
        }
        return 0;

    case WM_CTLCOLORSTATIC:
    case WM_CTLCOLORBTN:
        SetBkColor((HDC)wParam, g_BackgroundColor);
        return (INT_PTR)CreateSolidBrush(g_BackgroundColor);

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
