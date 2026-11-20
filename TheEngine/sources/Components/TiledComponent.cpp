#include "TiledComponent.h"
#include "Engine.h"
#include "Entity.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>


TiledComponent::TiledComponent(const std::string& fichierXML, float scale)
    : m_scale(scale)
{
    m_loadMap = LoadMap(fichierXML);
}

//-----START
void TiledComponent::Start()
{
    if (!m_loadMap) return;

    for (Tileset& ts : m_tilesets)
    {
        ts.m_textureId = homer::Engine::Get()->gfx()->LoadTexture(ts.m_imagePath);
    }
}

//-----DRAW
void TiledComponent::Draw()
{
    if (!m_loadMap || m_Entity == nullptr) return;

    for (int i = 0; i < (int)m_tiles.size(); i++)
    {
        unsigned int gid = m_tiles[i];

        // Trouver le bon tileset pour ce gid
        const Tileset* ts = FindTileset(gid);
        if (ts == nullptr) continue;

        // Numéro de la tuile DANS ce tileset
        int localId = (int)gid - ts->m_firstGid;

        // Rectangle source (partie de l'image)
        RectI src{
            (localId % ts->m_columns) * ts->m_tileW,
            (localId / ts->m_columns) * ts->m_tileH,
            ts->m_tileW,
            ts->m_tileH
        };

        // Position sur la map
        int col = i % m_mapW;
        int row = i / m_mapW;

        // Rectangle destination (avec scale)
        RectF dst{
            m_Entity->GetX() + col * m_tileW * m_scale,
            m_Entity->GetY() + row * m_tileH * m_scale,
            ts->m_tileW * m_scale,
            ts->m_tileH * m_scale
        };

        // Dessin
        homer::Engine::Get()->gfx()->DrawTexture(
            ts->m_textureId,
            src,
            dst,
            0.0f,
            Flip{ false, false },
            Color{ 255, 255, 255, 255 }
        );
    }
}

//--CHARGER UN FICHIER XML
bool TiledComponent::LoadMap(const std::string& fichierXML)
{
    std::ifstream file(fichierXML);
    if (!file.is_open()) return false;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    // --- 1. Taille de la map ---
    m_mapW = FindInt(text, "width=\"");
    m_mapH = FindInt(text, "height=\"");
    m_tileW = FindInt(text, "tilewidth=\"");
    m_tileH = FindInt(text, "tileheight=\"");

    if (m_mapW <= 0 || m_mapH <= 0) return false;

    // --- 2. Charger tous les tilesets ---
    std::string folder = GetFolder(fichierXML);

    size_t pos = 0;
    while ((pos = text.find("<tileset", pos)) != std::string::npos)
    {
        // On lit la balise <tileset ...>
        size_t end = text.find('>', pos);
        if (end == std::string::npos) break;

        std::string tag = text.substr(pos, end - pos);

        Tileset ts;
        ts.m_firstGid = FindInt(tag, "firstgid=\"");

        // On récupère le nom du fichier .tsx
        std::string source = FindString(tag, "source=\"");
        if (source.empty()) return false;

        // On charge le fichier .tsx
        if (!LoadTileset(ts, folder + source))
            return false;

        m_tilesets.push_back(ts);
        pos = end;
    }

    if (m_tilesets.empty()) return false;

    // --- 3. Lire les numéros pour savoir où il y'a une tuile et pas de tuile
    size_t dataStart = text.find("<data");
    if (dataStart == std::string::npos) return false;

    dataStart = text.find('>', dataStart) + 1;
    size_t dataEnd = text.find("</data>", dataStart);
    if (dataEnd == std::string::npos) return false;

    std::string data = text.substr(dataStart, dataEnd - dataStart);

    std::stringstream ss(data);
    std::string numero;
    while (std::getline(ss, numero, ','))
    {
        // Enlever les espaces
        numero.erase(std::remove_if(numero.begin(), numero.end(),
            [](unsigned char c) { return std::isspace(c); }), numero.end());

        if (!numero.empty())
            m_tiles.push_back(std::stoul(numero));
    }

    return (int)m_tiles.size() == m_mapW * m_mapH;
}

//--CHARGER UN FICHIER TSX
bool TiledComponent::LoadTileset(Tileset& ts, const std::string& tsxPath)
{
    std::ifstream file(tsxPath);
    if (!file.is_open()) return false;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    // On lit les infos du tileset
    ts.m_columns = FindInt(text, "columns=\"");
    ts.m_tileW = FindInt(text, "tilewidth=\"");
    ts.m_tileH = FindInt(text, "tileheight=\"");

    if (ts.m_columns <= 0) return false;

    // On lit le chemin de l'image
    size_t imgPos = text.find("<image");
    if (imgPos == std::string::npos) return false;

    std::string imageName = FindString(text.substr(imgPos), "source=\"");
    if (imageName.empty()) return false;

    // Le chemin de l'image est relatif au .tsx
    ts.m_imagePath = GetFolder(tsxPath) + imageName;

    return true;
}

//--TROUVE QUEL TILESET CONTIENT SE GID
const TiledComponent::Tileset* TiledComponent::FindTileset(unsigned int gid) const
{
    const Tileset* found = nullptr;

    // On prend le dernier tileset dont firstGid <= gid
    for (const Tileset& ts : m_tilesets)
    {
        if ((unsigned int)ts.m_firstGid <= gid)
            found = &ts;
    }
    return found;
}

//--CHERCHER UN NUMERO DANS LA UNE CHAINE DE CHARACTERE
int TiledComponent::FindInt(const std::string& text, const std::string& key)
{
    size_t pos = text.find(key);
    if (pos == std::string::npos) return 0;
    pos += key.size();
    size_t end = text.find('"', pos);
    if (end == std::string::npos) return 0;
    return std::stoi(text.substr(pos, end - pos));
}

//--CHERCHER UN MOT PRECIS DANS UNE CHAINE DE CARACTERE
std::string TiledComponent::FindString(const std::string& text, const std::string& key)
{
    size_t pos = text.find(key);
    if (pos == std::string::npos) return "";
    pos += key.size();
    size_t end = text.find('"', pos);
    if (end == std::string::npos) return "";
    return text.substr(pos, end - pos);
}


//RETOURNE LE DOSSIER RACINE D'UN FICHIER
std::string TiledComponent::GetFolder(const std::string& path)
{
    size_t slash = path.find_last_of("/\\");
    return (slash == std::string::npos) ? "" : path.substr(0, slash + 1);
}