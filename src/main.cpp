#include "Board.h"
#include "Snake.h"

int main()
{
    cout<<"snake\n";

    Board<40,40> board;
    cout<<board;

    Snake snake;
    for (int i=0;i<10;i++)
    {
        snake.add(i);
        if (i%2)
            snake.remove();
        cout<<snake<<'\n';
    }
    
    return 0;
}
