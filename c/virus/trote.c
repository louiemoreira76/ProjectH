#include <windows.h> // Funções da API do Windows 
#include <stdio.h>
#include <commctrl.h>

#define ID_BTN1 1
#define ID_BTN2 2

HBITMAP hBitmap; // Variável global para armazenar o bitmap

void Virus(HWND hwnd);
DWORD WINAPI ProgressThread(LPVOID lpParam); // Prototipo da função do thread

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Definição da classe da janela
    const char CLASS_NAME[] = "Sample Window Class"; // Serve p referenciar as configurações da janela

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;         // Define a função de processamento de mensagens da janela
    wc.hInstance = hInstance;            // A instância da aplicação é armazenada em hInstance
    wc.lpszClassName = CLASS_NAME;       //  Define o nome da classe da janela

    RegisterClass(&wc); // Define a função de processamento de mensagens da janela

    // Criação da janela
    HWND hwnd = CreateWindowEx(
        1,                                // Estilos adicionais da janela
        CLASS_NAME,                       // Nome da classe
        "Minha Primeira Janela em C",     // Título da janela
        WS_OVERLAPPEDWINDOW,              // Estilo da janela
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300, // Posição e tamanho
        NULL,                             // Janela mãe
        NULL,                             // Menu
        hInstance,                        // Instância do aplicativo
        NULL                              // Parâmetros adicionais
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Loop de mensagens
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { // Cada vez que ocorre um evento, o Windows envia uma mensagem para esta função. 
    static HWND hwndButton1;
    static HWND hwndButton2;

    switch (uMsg) {
        case WM_CREATE: {
            // Criando um botão
            hwndButton1 = CreateWindow(
                "BUTTON",                // Classe do botão
                "Não clique Aqui!!!",    // Texto do botão
                WS_VISIBLE | WS_CHILD,   // Estilos do botão
                10, 20, 120, 30,        // Posição e tamanho do botão
                hwnd,                    // Janela mãe
                (HMENU) ID_BTN1,        // ID do botão (1)              
                (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );

            hwndButton2 = CreateWindow(
                "BUTTON",
                "Clique Aqui :)",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                120, 20, 120, 30,
                hwnd,
                (HMENU) ID_BTN2,
                (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );

            // Carregar a imagem inicial
            hBitmap = (HBITMAP) LoadImage(
                NULL,                    // Nenhum módulo de instância (imagem externa)
                "imagem.bmp",           // Nome do arquivo
                IMAGE_BITMAP,           // Tipo de imagem
                200, 200,               // Largura e altura da imagem
                LR_LOADFROMFILE         // Carregar a partir de um arquivo
            );

            if (hBitmap == NULL) {
                DWORD error = GetLastError();
                char errorMsg[256];
                sprintf(errorMsg, "Erro ao carregar a imagem! Código de erro: %lu", error);
                MessageBox(NULL, errorMsg, "Erro", MB_OK | MB_ICONERROR);
            }
            break;
        }
        case WM_COMMAND: {
            // Verifica se o botão foi clicado
            switch (LOWORD(wParam)) {
                case ID_BTN1:
                    // Carrega a nova imagem antes da barra de carregamento
                    if (hBitmap) {
                        DeleteObject(hBitmap); // Deleta a imagem anterior, se existir
                    }
                    hBitmap = (HBITMAP) LoadImage(
                        NULL,                    // Nenhum módulo de instância (imagem externa)
                        "putz.bmp",             // Nome do arquivo
                        IMAGE_BITMAP,           // Tipo de imagem
                        200, 200,               // Largura e altura da imagem
                        LR_LOADFROMFILE         // Carregar a partir de um arquivo
                    );

                    if (hBitmap == NULL) {
                        DWORD error = GetLastError();
                        char errorMsg[256];
                        sprintf(errorMsg, "Erro ao carregar a nova imagem! Código de erro: %lu", error);
                        MessageBox(NULL, errorMsg, "Erro", MB_OK | MB_ICONERROR);
                    }

                    // Inicia um novo thread para a função de loading
                    CreateThread(NULL, 0, ProgressThread, hwnd, 0, NULL);
                    InvalidateRect(hwnd, NULL, TRUE); // Atualiza a janela para mostrar a nova imagem
                    break;

                case ID_BTN2:
                    MessageBox(hwnd, "OK thau", "Mensagem", MB_OK | MB_ICONINFORMATION);
                    if (hBitmap) {
                        DeleteObject(hBitmap);
                        hBitmap = NULL; // Evita exclusões subsequentes
                    }
                    PostQuitMessage(0);
                    return 0;
            }
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Desenha a imagem bitmap na janela
            if (hBitmap != NULL) {
                HDC hdcMem = CreateCompatibleDC(hdc);
                SelectObject(hdcMem, hBitmap);
                BitBlt(hdc, 70, 70, 200, 200, hdcMem, 0, 0, SRCCOPY);
                DeleteDC(hdcMem);
            }

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY: {
            if (hBitmap) {
                DeleteObject(hBitmap);
            }
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam); // Se nenhuma das mensagens anteriores for capturada passa para win
}

// Função que será executada em um thread separado
DWORD WINAPI ProgressThread(LPVOID lpParam) {
    HWND hwnd = (HWND)lpParam;
    static HWND hwndProgress;

    InitCommonControls();
    // Cria a barra de progresso
    hwndProgress = CreateWindowEx(
        0, 
        PROGRESS_CLASS,   // Classe do controle de progresso
        NULL,             // Texto
        WS_VISIBLE | WS_CHILD | PBS_SMOOTH, // Estilos
        50, 50, 300, 30,  // Posição e tamanho
        hwnd,             // Janela mãe
        NULL,             // ID
        (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL
    );

    // Atualiza a barra de progresso
    for (int i = 0; i <= 100; i++) {
        SendMessage(hwndProgress, PBM_SETPOS, i, 0); // Define a posição da barra
        Sleep(50); // Pausa para simular trabalho
    }

    void Virus(HWND hwnd);

    // Remove a barra de progresso após a finalização
    DestroyWindow(hwndProgress);

    return 0;
}

void Virus(HWND hwnd) {

     typedef struct {
        int id;
        char name[50];
    } Person;

    const int NUM_OBJECTS = 1000000; // Aumentar o número de objetos
    const int NUM_ITERATIONS = 5000; // Aumentar o número de iterações

    // Alocação de memória para um grande número de objetos
    Person *persons = (Person *)malloc(NUM_OBJECTS * sizeof(Person));
    if (persons == NULL) {
        MessageBox(hwnd, "Falha na alocação de memória!", "Erro", MB_OK | MB_ICONERROR);
        return;
    }

    // Loop para preencher o array de objetos e realizar operações intensivas
    for (long i = 0; i < NUM_OBJECTS; i++) {
        // Atribuir ID e nome ao objeto
        persons[i].id = i + 1;
        snprintf(persons[i].name, sizeof(persons[i].name), "Pessoa %d", i + 1);
        
        // Operação intensiva
        double result = 0.0;
        for (long j = 0; j < NUM_ITERATIONS; j++) {
            result += (double)(j * j) / (j + 1);
            // Adiciona uma operação adicional para aumentar a carga
            result += (double)(j * 2) * (j % 3);
        }
        
        // Para evitar otimização do compilador
        if (i % 1000 == 0) {
            printf("Processando %d objetos...\n", i);
        }
    }

}
//gcc trote.c -o trote -mwindows -lgdi32 -lcomctl32
