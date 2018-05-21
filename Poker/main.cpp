//
//  main.cpp
//  Poker
//
//  Created by 明翰  楊 on 2018/5/20.
//  Copyright c 2018年 明翰  楊. All rights reserved.
//  A game of guess number just for fun & homework
//  Notice : this project is limited by the school exam so do not have good OO architecture.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#define shuffle_time 150

class Poker{
    public :
    Poker(){
        pos=0;
        user_score=0;
        computer_score=0;
        //srand(time(NULL));
        srand( static_cast<unsigned int>(time(NULL)));
        for(int i=0;i<52;i++){
            cards[i]=i+1;
        }
        card_shuffle();
    }
    
    void card_shuffle(){
        for(int i=0;i<shuffle_time;i++){
            int ran1= rand() % 52;
            int ran2= rand() % 52;
            cards[ran1]^=cards[ran2]^=cards[ran1]^=cards[ran2];
        }
    }
    
    std::string  get_card_color(int card_color_id ){
        std::string  card_color;
        switch (card_color_id){
            case 0:
                card_color="club";
                break;
            case 1:
                card_color="diamond";
                break;
            case 2:
                card_color="heart";
                break;
            case 3:
            case 4:
                card_color="spade ";
                break;
        }
        return card_color;
    }
    
    void card_print(int id){
        //id conver to color&number
        int card_number=id%13+1;
        int card_color_id=id/13;
        std::string card_color=get_card_color(card_color_id );
        std::cout<<"{ ";
        std::cout<<"color : "<< card_color<<" ";
        std::cout<<", ";
        std::cout<<"number : "<< card_number<<" ";
        //std::cout<<", ";
        //std::cout<<"ID : "<< id<<" ";
        std::cout<<"} \n";
    }
    
    bool card_bigger(int card_first,int card_second){
        
        int card_number_first  = card_first  % 13 + 1;
        int card_number_second = card_second % 13 + 1;
        //check number
        if(card_number_first>card_number_second){
            return true;
        }
        //check color
        else if(card_number_first==card_number_second){
            int card_color_first   =  card_first   / 13;
            int card_color_second  =  card_second  / 13;
            if(card_color_first>card_color_second){
                return true;
            }else{
                return false;
            }
            
        }
        else{
            return false;
        }
    }
    
    void cards_print(){
        for(int i=0;i<52;i++){
            
            card_print(cards[i]);
        }
    }
    
    void cards_game_start(){
        
        while(true){
            if((pos+2)>52){
                std::cout<<"No more cards.System will shuffle the cards.\n";
                card_shuffle();
                std::cout<<"Game Restart! Score reset to zero\n\n";
                user_score=0;
                computer_score=0;
                pos=0;
            }
            cards_game_round();
            std::cout<<"Play next round ? (y,n)";
            char r;
            std::cin>>r;
            if(r=='n'){
                break;
            }
            std::cout<<"\n\n";
        }
        
        return ;
    }
    
    void cards_game_round(){
        bool user=false;
        bool user_win=false;
        int id_user=cards[pos];
        int id_computer=cards[pos+1];
        pos+=2;//moving cards`s ptr
        std::cout<<"Your card is:\n";
        card_print(id_user);
        std::cout<<"Please choose your guess,big or small ? Big input 1,Small input 0 :";
        int c=0;
        std::cin>>c;
        if(c==1){
            user=true;
        }else{
            user=false;
        }
        user_win=!(user^card_bigger(id_user,id_computer));//win = user nxor real
        std::cout<<"Computer`s card is:\n";
        card_print(id_computer);
        if(user_win){
            std::cout<<"You win this round!";
            user_score++;
        }else{
            std::cout<<"You lose this round!";
            computer_score++;
        }
        std::cout<<"\n-----Score Table-----\n";
        std::cout<<"User Score:"<<user_score<<"\n";
        std::cout<<"Computer Score:"<<computer_score<<"\n";
        std::cout<<"-----------------------\n";
    }
    
private:
    int cards[52];
    int pos;
    int user_score;
    int computer_score;
};
int main(int argc, const char * argv[]) {
    Poker *game=new Poker();
    game->cards_game_start();
    delete game;
    game=NULL;
    return 0;
}
