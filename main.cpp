#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric> /* iota */




using namespace std;

std::vector<std::vector<int>> win_seq{{0,1,2},{3,4,5},
                                      {6,7,8},{0,3,6},
                                      {1,4,5},{2,5,8},
                                      {0,4,8},{2,4,6}};

bool win_status=false;
bool res=false;

class Grid_Box
{


private: int len;

     //   int players=2;
     //   int player1,player2;

        std::vector<int>  poss_values;
        std::vector<char> grid_;






        Grid_Box()=delete;
        Grid_Box(Grid_Box&)=delete;
        Grid_Box(Grid_Box&&)=delete;


public:

        Grid_Box(int a):len{a}
        {

        cout<<"Creating the Grid Box"<<endl;

        grid_.resize(len*len);
        std::fill(grid_.begin(),grid_.end(),'-');


        poss_values.resize(len*len);
        std::iota(poss_values.begin(),poss_values.end(),0);



        }

        void draw_grid();
        void play_game();
        void available_free_spaces();

        bool check_win(std::vector<int>);
        bool compare_vec(std::vector<int>,std::vector<int>);

        ~Grid_Box()
        {
            cout<<"Grid object detsroyed"<<endl;

        }
};




void Grid_Box::draw_grid()
{

    cout<<endl<<endl<<endl;

    cout<<"Final Grid"<<endl<<endl<<endl;

    //   std::cout<<std::setw(20)<<"    ----------------"<<endl;

    for(int i =0;i<(len*len);i=i+3)
       {


           /*
           std::cout<<std::setw(20)<<"    |    |    |    |"<<endl;
           std::cout<<""<<grid_[i]<<"|"<<grid_[i+1]<<"|"<<grid_[i+2];
           std::cout<<"    ----------------"<<endl;

           */
            std::cout<<std::setw(31)<<" -------------"<<endl;
            std::cout<<std::setw(20)<<"| "<<grid_[i]<<" | "<<grid_[i+1]<<" | "<<grid_[i+2]<<" |"<<endl;



        }
       std::cout<<std::setw(31)<<" -------------"<<endl;
}

void Grid_Box::available_free_spaces()
{
    cout<<"Available free grid nums"<<endl;
    cout<<"{ ";
    for(auto num : poss_values)
    {
        cout<<num<<" ,";

    }

    cout<<"}";

    cout<<endl;

}


bool Grid_Box::check_win(std::vector<int> inp_seq)
{
    cout<<"Inside check win func"<<endl;


    std::sort(inp_seq.begin(),inp_seq.end());



    for(auto it =inp_seq.begin();it!=inp_seq.end();++it)
    {

        cout<<*it <<"  ";

    }



    for(size_t i =0;i < win_seq.size();++i)
    {

        cout<<win_seq[i].size()<<endl;
        cout<<i<<endl;
        if(std::includes(inp_seq.begin(),inp_seq.end(),win_seq[i].begin(),win_seq[i].end()))
            {


                cout<<"match found"<<endl;

                return true;

            }



   }







       cout<<endl;



}



void Grid_Box::play_game()
{

    cout<<"Game starts"<<endl;

    size_t markings=0;
    size_t remaining=0;

    std::vector<int> player_1_inputs;
    std::vector<int> player_2_inputs;
    size_t len_values = poss_values.size();
    size_t min_win_len = 3;



    int inp;
    bool res=false;

    /* Grid is false = empty, Grid is true= occupied*/


    cout<<"The grid nos are marked from 0 to 8"<<endl;

    cout<<" first row spans from 0 to 2"<<endl;
    cout<<" first row spans from 3 to 5"<<endl;
    cout<<" first row spans from 6 to 8"<<endl;

    std::cout<<endl<<endl;



    do{
        draw_grid();
        cout<<endl<<endl;


        if(poss_values.size()>0)
        {

            available_free_spaces();
            cout<<endl<<endl;




            cout<<"Player 1 TURN: Enter the grid num from the available nums to mark"<<endl;
            cin>>inp;

             if(std::find(poss_values.begin(),poss_values.end(),inp)!=poss_values.end())
                {


                 grid_[inp] = 'X';
                 markings++;
                 player_1_inputs.push_back(inp);

                 remaining = len_values - markings;

                 poss_values.erase(std::remove(poss_values.begin(),poss_values.end(),inp));



                 if(player_1_inputs.size()>=min_win_len)
                 {


                    cout<<"Checking for player 1 win"<<endl;

                      if(check_win(player_1_inputs))
                        {

                            cout<<"Player 1 won the game"<<endl;
                            break;
                        }

                 }




                 draw_grid();

                }
       else
            {
                cout<<"Invalid grid num :  Please choose the number from the available grid num"<<endl;

                continue;

            }
        }



          draw_grid();


          if(poss_values.size()>0)
          {

              available_free_spaces();
              cout<<endl<<endl;


              cout<<"Player 2 TURN: Enter the grid num from the available nums to mark"<<endl;
              cin>>inp;

             if(std::find(poss_values.begin(),poss_values.end(),inp)!=poss_values.end())
             {

                 grid_[inp] = 'O';
                 markings++;
                 player_2_inputs.push_back(inp);

                 cout<<"Possible Values Size = "<<poss_values.size()<<endl;

                 cout<<"Remaining entries  = "<<remaining<<endl;



                 if(player_2_inputs.size()>=min_win_len)
                 {

                    cout<<"Checking for player 2 win"<<endl;

                    res = check_win(player_2_inputs);

                    if(res)
                    {

                        cout<<"Player 2 won the game"<<endl;
                        break;
                    }

                 }




                 remaining = len_values - markings;

                 poss_values.erase(std::remove(poss_values.begin(),poss_values.end(),inp));

                 draw_grid();

             }

        else
            {
                cout<<"Invalid grid num :  Please choose the number from the available grid num"<<endl;

                continue;

            }

    }

   }while(remaining!=0);


    draw_grid();

    cout<<endl<<endl;

    cout<<"Player 1 inputs : "<<endl;

    for(auto data: player_1_inputs)
     {
       cout<<data<<"  ";


    }

    cout<<endl;

    cout<<"Player 2 inputs : "<<endl;

    for(auto data: player_2_inputs)
    {
      cout<<data<<"  ";


    }

    cout<<endl;

    draw_grid();


  }



int main()
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$  Welcoe to Tic Tac Toe Game!  $$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout<<std::endl<<std::endl;


    cout<<"There are two players: Player 1 uses X  and Player 2 uses O mark"<<endl;

    cout<<std::endl<<std::endl;



    /* the 2D Grid */

    Grid_Box a{3};
    a.play_game();


    return 0;
}
