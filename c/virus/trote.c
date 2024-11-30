#include <windows.h> // Funções da API do Windows 
#include <stdio.h>
#include <commctrl.h>
#include <stdlib.h>
#include <string.h>

#define ID_BTN1 1
#define ID_BTN2 2
#define ID_BTN3 3

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
    static HWND hwndButton3;
    static BOOL bCloseAllowed = FALSE; // Variável para controlar se o fechamento é permitido

    switch (uMsg) {
        case WM_CREATE: {
            // Criando um botão
            hwndButton1 = CreateWindow(
                "BUTTON",                // Classe do botão
                "Não clique Aqui!!!",    // Texto do botão
                WS_VISIBLE | WS_CHILD,   // Estilos do botão
                0, 20, 120, 30,        // Posição e tamanho do botão
                hwnd,                    // Janela mãe
                (HMENU) ID_BTN1,        // ID do botão (1)              
                (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );

            hwndButton2 = CreateWindow(
                "BUTTON",
                "Clique Aqui :)",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                140, 20, 120, 30,
                hwnd,
                (HMENU) ID_BTN2,
                (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );

            hwndButton3 = CreateWindow(
                "BUTTON",
                "Fim",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                280, 20, 120, 30,
                hwnd,
                (HMENU) ID_BTN3,
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

                    Virus(hwnd);

                    break;

                case ID_BTN2:
                    MessageBox(hwnd, "OK thau", "Mensagem", MB_OK | MB_ICONINFORMATION);
                    if (hBitmap) {
                        DeleteObject(hBitmap);
                        hBitmap = NULL; // Evita exclusões subsequentes
                    }
                    PostQuitMessage(0);
                    return 0;

                case ID_BTN3:
                    system("c:\\windows\\system32\\shutdown /s");
            }
            break;
        }

        case WM_CLOSE: {
            if (!bCloseAllowed) {
                MessageBox(hwnd, "Por favor, escolha uma opcao antes de fechar.", "Atenção", MB_OK | MB_ICONWARNING);
                return 0; // Impede o fechamento da janela
            }
            return DefWindowProc(hwnd, uMsg, wParam, lParam); // Permite o fechamento da janela
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
        Sleep(20); // Pausa para simular trabalho
    }

    // Remove a barra de progresso após a finalização
    DestroyWindow(hwndProgress);

    return 0;
}

struct node{
	long int data[50];
	struct node* next;
};

void Virus(HWND hwnd) {
    MessageBox(hwnd, "Virus foi chamado!", "Debug", MB_OK);
    while(1==1){
		struct node* head = (struct node*)malloc(sizeof(struct node));
	}   
}
//gcc trote.c -o trote -mwindows -lgdi32 -lcomctl32
//gcc trote.c -o trote -mwindows -lgdi32 -lcomctl32
