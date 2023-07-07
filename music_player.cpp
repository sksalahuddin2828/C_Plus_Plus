#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include <commdlg.h>

// Link with the Winmm.lib file
#pragma comment(lib, "Winmm.lib")

HWND playlistBox;
std::vector<std::string> playlist;
int currentIndex;
bool isPlaying;
float volume;

// Function to select a file
void selectFile()
{
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Audio/Video Files\0*.mp3;*.wav;*.ogg;*.mp4;*.avi;*.mkv;*.flv;*.mov;*.wmv;*.webm\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileName(&ofn))
    {
        addToPlaylist(fileName);
    }
}

// Function to add a file to the playlist
void addToPlaylist(const std::string& filePath)
{
    playlist.push_back(filePath);
    SendMessage(playlistBox, LB_ADDSTRING, 0, (LPARAM)filePath.c_str());
}

// Function to remove a file from the playlist
void removeFromPlaylist()
{
    int selectedIdx = SendMessage(playlistBox, LB_GETCURSEL, 0, 0);
    if (selectedIdx != LB_ERR)
    {
        playlist.erase(playlist.begin() + selectedIdx);
        SendMessage(playlistBox, LB_DELETESTRING, selectedIdx, 0);
        if (selectedIdx < currentIndex)
        {
            currentIndex--;
        }
        else if (selectedIdx == currentIndex)
        {
            stopMusic();
        }
    }
}

// Function to clear the playlist
void clearPlaylist()
{
    playlist.clear();
    SendMessage(playlistBox, LB_RESETCONTENT, 0, 0);
    stopMusic();
    currentIndex = 0;
}

// Function to play the selected file or playlist
void playMusic(const std::string& filePath = "")
{
    if (filePath.empty())
    {
        int selectedIdx = SendMessage(playlistBox, LB_GETCURSEL, 0, 0);
        if (selectedIdx == LB_ERR)
        {
            MessageBox(NULL, "No file selected.", "Error", MB_OK | MB_ICONERROR);
            return;
        }
        currentIndex = selectedIdx;
    }
    else
    {
        currentIndex = 0;
    }

    std::string fileToPlay = filePath.empty() ? playlist[currentIndex] : filePath;
    if (PlaySound(fileToPlay.c_str(), NULL, SND_ASYNC | SND_FILENAME))
    {
        isPlaying = true;
    }
    else
    {
        MessageBox(NULL, "Failed to play the selected file.", "Error", MB_OK | MB_ICONERROR);
    }
}

// Function to stop the music
void stopMusic()
{
    PlaySound(NULL, NULL, SND_ASYNC);
    isPlaying = false;
}

// Function to set the volume
void setVolume(float volumeLevel)
{
    volume = volumeLevel;
    int newVolume = static_cast<int>(volumeLevel * 100);
    int deviceVolume = newVolume | (newVolume << 16);
    waveOutSetVolume(NULL, deviceVolume);
}

// Window procedure for the main window
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        CreateWindow(TEXT("BUTTON"), TEXT("Select File"), WS_VISIBLE | WS_CHILD,
            10, 10, 100, 30, hwnd, (HMENU)1, NULL, NULL);

        playlistBox = CreateWindow(TEXT("LISTBOX"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
            10, 50, 300, 200, hwnd, NULL, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Play"), WS_VISIBLE | WS_CHILD,
            320, 50, 100, 30, hwnd, (HMENU)2, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Stop"), WS_VISIBLE | WS_CHILD,
            320, 90, 100, 30, hwnd, (HMENU)3, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Remove"), WS_VISIBLE | WS_CHILD,
            320, 130, 100, 30, hwnd, (HMENU)4, NULL, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Clear"), WS_VISIBLE | WS_CHILD,
            320, 170, 100, 30, hwnd, (HMENU)5, NULL, NULL);

        CreateWindow(TEXT("STATIC"), TEXT("Volume"), WS_VISIBLE | WS_CHILD,
            10, 270, 50, 20, hwnd, NULL, NULL, NULL);

        CreateWindow(TEXT("msctls_trackbar32"), TEXT(""), WS_VISIBLE | WS_CHILD | TBS_HORZ,
            70, 270, 200, 20, hwnd, (HMENU)6, NULL, NULL);

        break;
    }
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 1:
            selectFile();
            break;
        case 2:
            if (isPlaying)
            {
                stopMusic();
            }
            else
            {
                playMusic();
            }
            break;
        case 3:
            stopMusic();
            break;
        case 4:
            removeFromPlaylist();
            break;
        case 5:
            clearPlaylist();
            break;
        }
        break;
    }
    case WM_HSCROLL:
    {
        HWND trackbar = GetDlgItem(hwnd, 6);
        int trackbarValue = SendMessage(trackbar, TBM_GETPOS, 0, 0);
        float newVolume = trackbarValue / 100.0f;
        setVolume(newVolume);
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = TEXT("MediaPlayer");

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindow(TEXT("MediaPlayer"), TEXT("Media Player"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 450, 350, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
