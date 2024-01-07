#include <Windows.h>
#include <string>

// ���������� ����������
COLORREF g_BackgroundColor = RGB(255, 255, 255); // ����� �� ���������
std::wstring g_Name; // ���������� ���������� ��� �������� ���������� �����

// �������� ������� ��������� ���������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ������� ��� ��������� ���������� ������ � ����������� �����������
void ProcessInput(HWND hwnd) {
    wchar_t buffer[256];
    GetWindowText(GetDlgItem(hwnd, 1), buffer, sizeof(buffer) / sizeof(buffer[0]));

    g_Name = buffer;

    std::wstring greeting = L"������������, " + g_Name + L"!";
    MessageBox(hwnd, greeting.c_str(), L"�����������", MB_OK);
}

// ����� ����� ��� Win32-����������
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    // ����������� ������ ����
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SimpleWinAPIApp";

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, L"�� ������� ���������������� ����� ����", L"������", MB_ICONERROR);
        return 0;
    }

    // �������� ����
    HWND hwnd = CreateWindowEx(
        0,                              // �������������� �����
        L"SimpleWinAPIApp",             // ��� ������
        L"������ ������",               // ��������� ����
        WS_OVERLAPPEDWINDOW,            // ����� ����
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // ������� � ������ ����
        NULL,                           // ������������ ����
        NULL,                           // ����
        hInstance,                      // ���������� ���������� ����������
        NULL                            // ��������� �� �������������� ������ ����
    );

    if (hwnd == NULL) {
        MessageBox(NULL, L"�� ������� ������� ����", L"������", MB_ICONERROR);
        return 0;
    }

    // �������� �������� ���������� Edit (EDIT) ��� ����� ������ (�����)
    HWND hEdit = CreateWindowEx(
        0,
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        10, 70, 200, 20,
        hwnd,
        (HMENU)1, // ������������� �������� ����������
        hInstance,
        NULL
    );

    if (hEdit == NULL) {
        MessageBox(NULL, L"�� ������� ������� ������� ���������� Edit", L"������", MB_ICONERROR);
        return 0;
    }

    // �������� �������� ���������� Button (BUTTON) � ������� "������"
    HWND hButton = CreateWindowEx(
        0,
        L"BUTTON",
        L"������",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 100, 200, 20,
        hwnd,
        (HMENU)2, // ������������� �������� ����������
        hInstance,
        NULL
    );

    if (hButton == NULL) {
        MessageBox(NULL, L"�� ������� ������� ������� ���������� Button", L"������", MB_ICONERROR);
        return 0;
    }

    // ����������� ����
    ShowWindow(hwnd, nCmdShow);

    // ������ ����� ��������� ���������
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// ������� ��������� ���������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        // ��������� ������� ������� ������
        switch (LOWORD(wParam)) {
        case 1: // ������������� �������� ���������� Edit
            // ...
            break;

        case 2: // ������������� �������� ���������� Button
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
