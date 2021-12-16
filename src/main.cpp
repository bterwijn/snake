#include "Board.h"
#include "Snake.h"

int main()
{
    cout<<"snake\n";

    Board<10,10> board;
    cout<<board;

    Snake snake;
    for (int i=0;i<10;i++)
    {
        snake.add_head(i);
        if (i%2)
        {
            auto r=snake.remove_tail();
            cout<<"remove: "<<r<<'\n';
        }
        cout<<snake<<'\n';
    }
    
    return 0;
}
