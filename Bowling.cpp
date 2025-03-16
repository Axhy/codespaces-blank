//Console Application to count Bowling score for single player

#include <iostream>
#include <algorithm>

using namespace std;

//Class to hold frame score
class frame
{
    private:
    int try1;
    int try2;
    int frame_total;
    bool strike;
    bool spare;
    
    public :
    //Constructor
    frame():try1(0),try2(0),frame_total(0),strike(false),spare(false) {}

    //Dextructor
    ~frame(){}

    //first try score, set strike if score is 10
    void settry1(int val)
    {
        if(val == 10)
        {
            strike = true;
        }
        try1 = val;
    }

    //2nd try score, set spare if try 1 and try 2 total is 10
    void settry2(int val)
    {
        if(val+try1 == 10)
        {
            spare = true;
        }
        try2 = val;
    }

    //get functionalities
    int gettry1() {return try1;}
    int gettry2() {return try2;}
    int getframeTotal(){return frame_total;}
    bool isStrike(){return strike;}
    bool isSpare(){return spare;}
    void fTotal()
    {
        frame_total = try1+try2;
    }
};

//Input validation to check input is digit and return value
int inputCheck(string s)
{
    if (s.end() == std::find_if(s.begin(), s.end(),
    [](unsigned char c)->bool { return !isdigit(c); })) 
    {
       int val = stoi(s);
       return val;
    }
    else
    {
        return -1;
    }
}

//main code
int main() 
{
    string  strInput;
    int val1, val2;
    frame obj[10];
    int try3=0;
    int index;
    int grandTotal = 0;
    
    cout << "Please enter scores between 0 to 10 for each try in the frame from 1 to 10 below:" << endl;
    for(index = 0; index <10;index++)
    {
        val1=val2=0;
        cout << "======Frame "<< index+1 << "======" << endl;
        while(1)
        {
            cout << "Try1 = ";
            cin >> strInput;
            
            val1 = inputCheck(strInput);
            if((val1 < 0) || (val1 >10))
            {
                cout << "Please enter proper value" <<endl;
                continue;
            }
            else
                break;
        }
        if(val1 == 10 && index !=9)
        {
            cout<<"-----Its a strike for this frame-----"<<endl;
        }
        else
        {
            while(1)
            {
                cout << "Try2 = ";
                cin >> strInput;
        
                val2 = inputCheck(strInput);
                if((val2 < 0) || (val2 >10) && (((val1+val2) > 10) || (val1+val2) < 0))
                {
                    cout << "Please enter proper value" << endl;
                    continue;
                }
                else
                    break;
            }
        }
        
        if((index == 9) &&(val1+val2 > 9))
        {
            while(1)
            {
                cout << "Try3 = ";
                cin >> strInput;
        
                try3 = inputCheck(strInput);
                if((try3 < 0) || (try3 >10))
                {
                    cout << "Please enter proper value" << endl;
                    continue;
                }
                else
                    break;
            }
        }
        obj[index].settry1(val1);
        obj[index].settry2(val2);
        obj[index].fTotal();
    }
    
    // Start framewise Calculation 
    for(index = 0; index <10;index++)
    {
	if(index == 9)
	{
	    grandTotal += obj[index].gettry1()+obj[index].gettry2()+try3;
	}

	else if(obj[index].getframeTotal() < 10)
	{
	    grandTotal += obj[index].getframeTotal();
	}
	
	else if(obj[index].isStrike())
	{
	    grandTotal += obj[index].gettry1();
	    if(obj[index+1].isStrike())
	    {
		grandTotal += obj[index+1].gettry1();
		if(index +2 < 10)
		{
		    grandTotal+=obj[index+2].gettry1();
		}
		else
		{
		    grandTotal+= obj[index+1].gettry2();
		}
	    }
	    else
	    {
		grandTotal += obj[index+1].getframeTotal();
 	    }
	}

	else if(obj[index].isSpare())
	{
		grandTotal += obj[index+1].gettry1();
		grandTotal += obj[index].getframeTotal();
	}
	else{}

   //Enable this to check framewise score
   // cout << "Score After frame " <<index+1 << " score = " << grandTotal <<endl;
    }
    cout << "########Total score = " << grandTotal << "########"<< endl;
}
