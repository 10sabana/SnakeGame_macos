/* 
///////////////////////////////////////////////////////////
   SNAKE GAME FOR MACOS
            Made by Mr. Cho

    "Snake Game" only operated on the Mac OS
    If you want to compile this file, you need to use Command
                        -> gcc -o snakegame snakegame.cpp -lncurses

    * Need to revise : time count
    ** According to the score, show prize and penalty
///////////////////////////////////////////////////////////
*/

#include <cstdlib>
#include <ncurses.h> // input output
#include <unistd.h> // sleep function

//Global Variable
bool gameOver;
const int WIDTH = 20;
const int HEIGHT = 20;
int x, y; //snake head
int fruitX, fruitY;
int score;

typedef enum DIRECTION {STOP =0, LEFT, RIGHT, UP, DOWN}
Dir;
Dir dir;

// snake tail
int tailX[50], tailY[50];
int numTail=0;

void Initialize()
{
    //Shell Screen Init, functions from ncurses.h
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = WIDTH/2; // start xpos
    y = HEIGHT/2; // start ypos
    fruitX = (rand() % WIDTH)+1; 
    fruitY = (rand() % HEIGHT)+1; 
    score = 0;  
}



void Render()
{
    clear();
    //Draw map, snake head, fruit, and tail
    for (int i=0; i<HEIGHT+2; i++)
    {
        for (int j=0; j<WIDTH+2; j++)
        {
            //Draw map
            if (i==0 | i==21)
            {
                mvprintw(i, j, "0");
            }
            else if (j==0 | j==21)
            {
                mvprintw(i, j, "0");
            } 
            //Draw snake head
            else if (i==y && j==x)
            {
                mvprintw(i, j, "0");
            }
            //Draw fruit
            else if (i==fruitY && j==fruitX)
            {
                mvprintw(i, j, "@");
            }
            else
            {   //Draw Tail
                for (int k=0; k<numTail; k++)
                {
                    if (tailX[k]==j && tailY[k]==i)
                    {
                        mvprintw(i,j, "o");
                    }
                }

            }
            
        }
    }    
    //Draw Information
    mvprintw(3, 29, "------------------------------------");
    mvprintw(4, 29, "|    Snake Game Made by Mr.Cho     |");
    mvprintw(5, 29, "------------------------------------");
    mvprintw(7, 29, "Use direction keys to eat fruit");
    mvprintw(9, 43, "   ^ ");
    mvprintw(10, 43, "<  v  >");
    mvprintw(14, 29, "** If you collide with wall or tail, Snake will die");

    mvprintw(16, 29, "$$ Score = %d", score);
//  mvprintw(17, 29, "$$ Remain Time = %d", current_time);
    refresh();
}

void Poll_Input()
{
    keypad(stdscr, TRUE); // Check whether there is input, function from ncurses
    halfdelay(1); 

    int c = getch(); // Save the typed key by gamer

    switch(c)
    {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_DOWN: // definition is opposite between up and down
            dir = UP;
            break;
        case KEY_UP:
            dir = DOWN;
            break;
        case KEY_EXIT:
            gameOver = true;
            break;

    }    

}


void Update()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    // add new position and other one copy
    for (int i=1; i<numTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }


    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y++;
            break;
        case DOWN:
            y--;
            break;
        default: 
            break;
    }

// if snake goes outside from the map, game will be over    
    if (x>WIDTH || x<1 || y<1 || y>HEIGHT)
    {
        gameOver=true;
    }

// if snake eats the fruit on the map, score will increase    
    if (x==fruitX && y==fruitY)
    {
        score ++;
        fruitX = (rand() % WIDTH)+1;
        fruitY = (rand() % HEIGHT)+1;
        numTail++;
    }

    for (int i=0; i<numTail; i++)
    {
        if(tailX[i]==x && tailY[i]==y)
        {
            gameOver=true;
        }
        
    }

}


int main(void)
{
    Initialize();

   while(!gameOver)
    {
        Render();
        Poll_Input();
        Update();

    }
    getch();
    sleep(1); 
    endwin();

    return 0;
}
