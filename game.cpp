#include "game.h"
#include "player.h"
#include "castle.h"
#include "mainwindow.h"

#include <QMessageBox>

void Game::addPlayer(QString name_player, QString id_image, int number_player)
{
    Player *player = new Player;
    player->nomber_player = number_player;
    player->Name = name_player;
    player->image = QPixmap("../Game/"+id_image+".png");
    player->count_money = 500;
    switch (number_player)
    {
        case 1:
            player->castle = new Castle(this->map.scene, QPoint(this->map.scene->size_items*2,this->map.scene->size_items*2),"21");
            player->move = true;
        break;
        case 2:
            player->castle = new Castle(this->map.scene, QPoint(this->map.scene->width()-this->map.scene->size_items*3, this->map.scene->height()-this->map.scene->size_items*3), "21");
        break;
        case 3:
            player->castle = new Castle(this->map.scene, QPoint(this->map.scene->width()-this->map.scene->size_items*3,this->map.scene->size_items*2), "21");
        break;
        case 4:
            player->castle = new Castle(this->map.scene, QPoint(this->map.scene->size_items*2, this->map.scene->height()-this->map.scene->size_items*3), "21");
        break;
    }

    list_players.append(player);

}

Game* Game::GameInstance = 0;

Game* Game::GetInstance()
{
    if(!GameInstance)
        GameInstance = new Game();

    return GameInstance;
}

void Game::next_player()
{
    refresh_data_players();
    if(list_players.length()<2)
    {
        this->game_play = false;
        QMessageBox::information(MainWindow::GetInstance(),"Information", "Вот и всё");
    }
    else
    {
        for(int i=0;i<list_players.length();i++)
            if(list_players[i]->move == true)
            {
                list_players[i]->move = false;
                list_players[i]->refreshUnits();
                if(i<list_players.length()-1)
                {
                        list_players[i+1]->move = true;
                        list_players[i+1]->refreshUnits();
                }
                else
                {
                    list_players.first()->move = true;
                    list_players.first()->refreshUnits();
                    refresh_data_players();
                }
                break;
            }

        Game *game = Game::GetInstance();
        if(game->map.scene->way_drow)
        {
            for (int i=0;i<game->map.scene->line_group.length();i++)
                delete game->map.scene->line_group[i];
            game->map.scene->line_group.clear();
            game->map.scene->way_drow = false;
        }
    }
}

void Game::refresh_data_players()
{
    for (int i=0;i<list_players.length();i++)
    {
        if(list_players[i]->list_units.length() > 0 || list_players[i]->castle)
        {
            list_players[i]->count_money+=25;
            for (int j=0;j<list_players[i]->list_units.length();j++)
                list_players[i]->list_units[j]->count_steps = list_players[i]->list_units[j]->max_count_steps;
        }
        else
        {
            delete list_players[i];
            list_players.removeAt(i);
        }
    }

}
