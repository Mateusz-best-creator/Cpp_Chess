#include "interface.h"
#include <cstring>
#include <vector>

void Interface::displayAuthenticationInterface(std::vector<Player> players)
{
    SDL_Event event;
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
    std::cout << "Local color: " << localColor << std::endl;

    index = 0;
    quit = false;
    char localName[NAME_MAX_LENGTH];

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
    std::cout << "Local nme: " << localName << std::endl;
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
                    std::cout << "Color name = " << name << std::endl;
                    if (strcmp(name, "White") == 0 || strcmp(name, "white") == 0 || strcmp(name, "WHITE") == 0)
                        return true;
                    if (strcmp(name, "Black") == 0 || strcmp(name, "black") == 0 || strcmp(name, "BLACK") == 0)
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
            name[index] = *(event.text.text);
            index++;
            name[index] = '\0';
            return false;
        }
    }
    return false;
}