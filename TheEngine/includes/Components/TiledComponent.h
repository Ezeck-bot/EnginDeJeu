#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "IDrawable.h"

class TiledComponent : public homer::Component, public homer::IDrawable {
public:
	// tmxPath : chemin du fichier .tmx, scale : facteur d'agrandissement (2.0f, 3.0f...)
	TiledComponent(const std::string& fichierXML, float scale = 1.0f);

	virtual void Start() override;
	virtual void Draw() override;

private:
    struct Tileset
    {
        int m_firstGid = 0;
        int m_columns = 0;
        int m_tileW = 0;
        int m_tileH = 0;
        std::string m_imagePath;
        size_t m_textureId = static_cast<size_t>(-1);
    };

    //pour charger le fichier xml
    bool LoadMap(const std::string& fichierXML);

    //pour charger les fichiers tsx 
    bool LoadTileset(Tileset& ts, const std::string& tsxPath);
    const Tileset* FindTileset(unsigned int gid) const;

    //Refactorisation de code : Chercher un nombre dans une chaine de caractère, Chercher un mot et avoir le dossier racine d'un fichier
    int FindInt(const std::string& text, const std::string& key);
    std::string FindString(const std::string& text, const std::string& key);
    std::string GetFolder(const std::string& path);

    // Données de la map
    int m_mapW = 0;
    int m_mapH = 0;
    int m_tileW = 0;
    int m_tileH = 0;
    float m_scale = 1.0f;
    bool m_loadMap = false;

    std::vector<Tileset> m_tilesets;
    std::vector<unsigned int> m_tiles;
};