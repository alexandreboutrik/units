#include "assets.hpp"

#include "configuration.hpp"

namespace assets {

Manager&
Manager::Get()
{
    static Manager instance;
    return instance;
}

void
Manager::UnloadAll()
{
    for (auto& [name, texture] : textures)
        rl::UnloadTexture(texture);
    for (auto& [name, image] : images)
        rl::UnloadImage(image);
    for (auto& [name, fontData] : fonts)
        rl::UnloadFont(std::get<0>(fontData));

    /* Removes all elements from the maps */
    textures.clear();
    images.clear();
    fonts.clear();
}


/*****************************************
 ***          Image Management         ***
 *****************************************/

void
Manager::LoadImage(
    const std::string& name, const std::string& path,
    const int width, const int height)
{
    /* Unload existing assets if they exist */
    Manager::UnloadImage(name);
    Manager::UnloadTexture(name);

    std::string full_path = std::string(ASSETS) + "/" + path;

    Image img = rl::LoadImage(full_path.c_str());

    if (width != NO_RESIZE || height != NO_RESIZE)
        rl::ImageResize(&img, width, height);

    images[name]   = img;
    textures[name] = rl::LoadTextureFromImage(img);
}

void
Manager::DrawImage(const std::string& name, const int pos_x, const int pos_y)
{
    rl::DrawTexture(textures.at(name), pos_x, pos_y, WHITE);
}

void
Manager::UnloadImage(const std::string& name)
{
    if (images.count(name))
    {
        rl::UnloadImage(images.at(name));

        images.erase(name);
    }
}

void
Manager::UnloadTexture(const std::string& name)
{
    if (textures.count(name))
    {
        rl::UnloadTexture(textures.at(name));

        textures.erase(name);
    }
}

/***************************************
 ***          Font Management        ***
 ***************************************/

void
Manager::LoadFont(
    const std::string& name, const std::string& path, const int fontSize)
{
    Manager::UnloadFont(name);

    std::string full_path = std::string(ASSETS) + "/" + path;

    Font ft = rl::LoadFontEx(full_path.c_str(), fontSize, NULL, 0);

    fonts[name] = std::make_tuple(ft, fontSize);
}

FontData&
Manager::GetFontData(const std::string& name)
{
    return fonts.at(name);
}

Font&
Manager::GetFont(const std::string& name)
{
    return std::get<0>(fonts.at(name));
}

int
Manager::GetFontSize(const std::string& name)
{
    return std::get<1>(fonts.at(name));
}

void
Manager::UnloadFont(const std::string& name)
{
    if (fonts.count(name))
    {
        rl::UnloadFont(std::get<0>(fonts.at(name)));

        fonts.erase(name);
    }
}

} /* assets namespace */
