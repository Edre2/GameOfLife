#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <istream>
#include <ostream>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

// Une class pour modéliser le jeu de la vie de Conway
// Le jeu est représenté par un vecteur de vecteurs de
// bool. Si une case est true, il  a une cellule, si 
// elle est false, il n'y en a pas
class GameOfLife
{
    public:
        // Le constructeur
        // enVie et mort servent si l'on affiche le tableau
        GameOfLife(int size_x = 10, int size_y = 10, char enVie = 'O', char mort = ' ');

        // Pour définir la position
        void Setup(std::vector<std::vector<bool>> board);
        // Définit la cellule (i,j) comme value
        void Set(int i, int j, bool value = true);
        // Change le statut d'une cellule
        void change(int i, int j);
        // Remplit aléatoirement le tableau
        void random();
        // Vide le board
        void clear();

        // Transforme le tableau selon les règles du jeu de la vie
        void nextGen();

        // Retourne le plateau sous forme d'argument
        void board(std::vector<std::vector<bool>> & board) const;
        // Affiche le tableau dans le terminal en utilisant enVie et mort
        void afficher() const;
        // Retourne si une cellule est en vie
        bool isAlive(int i, int j);

        // Retourne si des coordonnés sont dans le tableau
        bool inboard(int i, int j) const;
        // Retourne si une celluleva survivre au prochain tour
        bool willSurvive(int i, int j) const;

        std::ostream& SaveToFile(std::ostream& outfile);
        void LoadFromFile(std::istream& file);


    private:
        // La taille du tbleau
        int m_size_x = 10;
        int m_size_y = 10;
        // Le fameux tableau
        std::vector<std::vector<bool>> m_board;
        // Les caractères pour afficher le tableau
        char m_enVie;
        char m_mort;
};

#endif