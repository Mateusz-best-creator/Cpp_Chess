#include "interface.h"
#include <cstring>
#include <vector>
#include <algorithm>

int Interface::displayAuthenticationInterface(std::vector<Player>& players)
{
    bool quit = false;
    int index = 0;
    char text[100];

    char colorName[10];
    colorName[0] = '\0';
    while (!quit)
    {
        DrawRectangle(screen, 4, 20, SCREEN_WIDTH - 8, 54, white, grey);
        sprintf_s(text, 100, "Please enter color you want to play: ");
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
        sprintf_s(text, 100, "Your color: %s", colorName);
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 42, text, charset);

        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
        SDL_RenderCopy(renderer, scrtex, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_FillRect(screen, NULL, black);
        quit = handleAuthenticationInterfaceEvents(colorName, index, true);
    }
    Colors localColor = (colorName[0] == 'W' || colorName[0] == 'w') ? WHITE : BLACK;

    index = 0;
    quit = false;
    char localName[NAME_MAX_LENGTH];
    localName[0] = '\0';

    while (!quit)
    {
        DrawRectangle(screen, 4, 20, SCREEN_WIDTH - 8, 54, white, grey);
        sprintf_s(text, 100, "Please enter your name for %s pieces, maximum length is %d characters: ", colorName, NAME_MAX_LENGTH);
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
        sprintf_s(text, 100, "Your name: %s", localName);
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 42, text, charset);

        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
        SDL_RenderCopy(renderer, scrtex, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_FillRect(screen, NULL, black);
        quit = handleAuthenticationInterfaceEvents(localName, index);
    }
    localName[index] = '\0';

    int newPlayerIndex;
    bool playerFound = false;

    // Search in vector and check if we already have that player
    for (size_t i = 0; i < players.size(); ++i) 
    {
        if (strcmp(players[i].getName(), localName) == 0)
        {
            newPlayerIndex = static_cast<int>(i);
            playerFound = true;
            break;
        }
    }

    if (!playerFound)
    {
        players.push_back(Player(localName, localColor));
        newPlayerIndex = static_cast<int>(players.size()) - 1;
        return newPlayerIndex;
    } 
    else
    {
        players[newPlayerIndex].getPlayingColor() = localColor;
    }
    return newPlayerIndex;
}

bool Interface::handleAuthenticationInterfaceEvents(char* name, int& index, bool choosingColor)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            exit(EXIT_SUCCESS);
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_RETURN && index > 0)
            {
                if (choosingColor)
                {
                    // Transform user input to lowercase 
                    std::transform(name, name + strlen(name), name, ::tolower);
                    if (strcmp(name, "white") == 0)
                        return true;
                    if (strcmp(name, "black") == 0)
                        return true;
                    return false;
                }
                return true;
            }
            else if (event.key.keysym.sym == SDLK_BACKSPACE && index > 0)
            {
                index--;
                name[index] = '\0';
            }
        }
        else if (event.type == SDL_TEXTINPUT && index < NAME_MAX_LENGTH)
        {
            if (choosingColor && index >= 5)
            {
                return false;
            }
            name[index] = *(event.text.text);
            index++;
            name[index] = '\0';
            return false;
        }
    }
    return false;
}