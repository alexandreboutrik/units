#pragma once

#include <string>
#include <tuple>
#include <unordered_map>

#include "configuration.hpp"

/*
 * Indicates an image should keep its original dimensions when loading instead
 * of being resized.
 */
#define     NO_RESIZE       -1

/* Fonts have an extra int for fontSize */
using FontData = std::tuple<Font, int>;

namespace assets {
/*
 * @class Manager
 *  Singleton class for managing the program assets.
 *  All assets have an Unique std::string identifier.
 */
class Manager {
public:
    /* Prevents copying */
    Manager(const Manager&) = delete;
    Manager& operator = (const Manager&) = delete;

    /* Singleton access */
    static Manager& Get();

    /* Unload all assets and clear storage */
    void UnloadAll();

    /* ========== Image Management ========== */
    void LoadImage(
        const std::string& name, const std::string& path,
        const int width = NO_RESIZE, const int height = NO_RESIZE);
    void DrawImage(const std::string& name, const int pos_x, const int pos_y);
    void UnloadImage(const std::string& name);
    void UnloadTexture(const std::string& name);

    /* ========== Font Management ========== */
    void LoadFont(
        const std::string& name, const std::string& path,
        const int fontSize = 128);
    FontData& GetFontData(const std::string& name);
    Font& GetFont(const std::string& name);
    int GetFontSize(const std::string& name);
    void UnloadFont(const std::string& name);


private:
    /* Constructor initializes default assets */
    Manager()
    {
        /* Images */
        Manager::LoadImage("logo", "logo.png", 128, 128);

        /* Fonts */
        Manager::LoadFont("main", MAIN_FONT_FILE);
        Manager::LoadFont("main_64", MAIN_FONT_FILE, 64);

        Manager::LoadFont("agave", "AgaveNerdFont-Regular.ttf", 64);
        Manager::LoadFont("liberation-sans", "LiberationSans-Regular.ttf", 64);
        Manager::LoadFont("marcha", "Marcha.ttf", 64);
    }

    /* Destructor */
    ~Manager() { UnloadAll(); }

    /* Assets storage */
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Image> images;
    std::unordered_map<std::string, FontData> fonts;
};

} /* assets namespace */
