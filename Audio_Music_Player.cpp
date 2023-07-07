#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <commdlg.h>

#pragma comment(lib, "winmm.lib")

// Function to select a file
std::string selectFile()
{
    OPENFILENAME ofn;
    char szFile[MAX_PATH] = { 0 };
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = "Select an audio file";
    ofn.lpstrFilter = "Audio Files\0*.mp3;*.wav;*.ogg\0";
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFile = szFile;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        return std::string(szFile);
    }
    else
    {
        return "";
    }
}

// Function to play the selected file
void playMusic(const std::string& filePath)
{
    PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

// Function to stop the music
void stopMusic()
{
    PlaySound(NULL, NULL, SND_PURGE);
}

int main()
{
    std::string file_path;

    file_path = selectFile();
    if (!file_path.empty())
    {
        playMusic(file_path);
    }

    while (true)
    {
        std::cout << "1. Select a file" << std::endl;
        std::cout << "2. Stop music" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            file_path = selectFile();
            if (!file_path.empty())
            {
                playMusic(file_path);
            }
        }
        else if (choice == "2")
        {
            stopMusic();
        }
        else if (choice == "3")
        {
            break;
        }
    }

    return 0;
}
