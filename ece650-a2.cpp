/******************************************************************************
* File Name       : ece650-a2.cpp
*
* Created Date    : 10/12/2019
*
* Created By      : Somesh Gupta
*
*****************************************************************************/

/******************************************************************************
* I N C L U D  E S
******************************************************************************/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

/******************************************************************************
* G L O B A L    V A R I A B L E S
******************************************************************************/
/*Extern_variable for A3 timer concept*/
int l_value;

/*Global Variable for Storing Total Vertex */
int Total_Vertex = 0;

/*Global Variable for Storing Source */
int Source_Edge = 0;

/*Global Variable for Storing Destination */
int Destination_Edge = 0;

/* Flag to indicate */
int Print_flag = 0;

/* Vector declaration to append the string to complete the Input */
std::vector<string> BufferOf_E;

/* vector to store the Edges */
vector<int> Edges_Vector[30000];

/* Size of BufferOf_E */
int Size_E;

/* Global Array for Storing first Vertex  */
int Vertex_1[30000]={};

/* Global Array for Storing Second Vertex */
int Vertex_2[30000]={};

/* Global Buffer */
std::vector<string> Buffer;

/*Global Flag declaration*/
int Check_Flag = 0;

/******************************************************************************
* Function Name      : add_edge
*
* Description        : This function handles adding of Edges
*
* Input Parameters   : vector<int> Edges_Vector[], int *Vertex_1, int *Vertex_2
*
* Output Parameters  : None
*
* Return parameter   : void
*
******************************************************************************/
/* utility function to form edge between two vertices source and dest */
void add_edge(vector<int> Edges_Vector[], int *Vertex_1, int *Vertex_2)
{
  /* Declaring Local Variable */
  int L_index_AE =0;
  int L_source = 0;
  int L_destination = 0;

  /*Adding the edges to the Vector Edges_Vector*/
  for( L_index_AE = 0; L_index_AE < Size_E; L_index_AE++)
  {
    /* get the value of first vertex and copy to L_source */
    L_source = *Vertex_1;

    /* get the value of second vertex and copy to L_destination */
    L_destination = *Vertex_2;

    /* push the destination edge to the vector Edges_Vector */
    Edges_Vector[L_source].push_back(L_destination);

    /* push the destination edge to the vector Edges_Vector */
    Edges_Vector[L_destination].push_back(L_source);

    /*increment Vertex_1 pointer */
    Vertex_1++;

    /*increment Vertex_1 pointer */
    Vertex_2++;
  }
}

/******************************************************************************
* Function Name      : BreadthFirstSearch
*
* Description        : This function consists of Breadth First Search Algorithm
*
* Input Parameters   : vector<int> Edges_Vector[], int L_source,
*                      int L_destination, int L_vertex, int Vertex_Predecessor[]
*
* Output Parameters  : true/false
*
* Return parameter   : bool
*
******************************************************************************/

bool BreadthFirstSearch(vector<int> Edges_Vector[], int L_source, int L_destination, int L_vertex,
         int Vertex_Predecessor[])
{
  /* Variable of Integer type */
  int L_index = 0;

  /* array visited[] stores the information whether the vertex is visited
  at least once in the Breadth first search */
  bool visited[L_vertex];

  /* A Queue to maintain Queue of Vertices */
  list<int> queue;

  /* Initially none of the vertices are visited */
  for (L_index = 0; L_index < L_vertex; L_index++)
  {
    /* Initialise the array to 0 as none as visited */
    visited[L_index] = false;
    Vertex_Predecessor[L_index] = -1;
  }

  /* The Source is visited first and as the distance from source to source is 0 */
  visited[L_source] = true;
  queue.push_back(L_source);

  /* Standard BFS Algorithm */
  while (!queue.empty())
  {
    /* Store the first element of queue to the L_value */
    int L_value = queue.front();

    /*Remove the first element after storing the first element from the queue */
    queue.pop_front();

    int L_size = Edges_Vector[L_value].size();

    /* Running to check for all the vertices stored in the Edge array */
    for (L_index = 0; L_index < L_size; L_index++)
    {
      /* when the source is taken from the array */
      if (visited[Edges_Vector[L_value][L_index]] == 0)
      {
        /* Mark the source as visited in the array */
        visited[Edges_Vector[L_value][L_index]] = 1;

        /*Update the Vertex predecessor as the next value in the queue */
        Vertex_Predecessor[Edges_Vector[L_value][L_index]] = L_value;

        /* push the first value to deque */
        queue.push_back(Edges_Vector[L_value][L_index]);

        /* return True when the destination is reached */
        if (Edges_Vector[L_value][L_index] == L_destination)
        {
          return true;
        }
      }
    }
  }

  return false;
}

/******************************************************************************
* Function Name      : ShortestDistance
*
* Description        : This function calculates the shortest distance and prints
*                      it.
*
* Input Parameters   : vector<int> Edges_Vector[], int L_source,
*                      int L_destination, int Lsd_vertex
*
* Output Parameters  : None
*
* Return parameter   : void
*
******************************************************************************/

/* function to find the shortest distance between Source and Destination */
void ShortestDistance(vector<int> Edges_Vector[], int L_source,
                      int L_destination, int Lsd_vertex)
{

  /* local variable declaration */
  int Lsd_index = 0;
  int L_size_path = 0;
  int L_step =0;

  /* array to store the predecessor of the vertex */
  int Vertex_Predecessor[Lsd_vertex];

  /* To check the given edge exits in the Array */
  for(Lsd_index = 0 ; Lsd_index < Size_E; Lsd_index++)
  {
    /* if the Edge exits in the Array*/
    if((Vertex_1[Lsd_index] == L_source) || (Vertex_2[Lsd_index] == L_destination))
    {
      /*set the flag*/
      Check_Flag = 1;
    }
  }

  try
  {
    /* return error message when there is no path between source and destination*/
    if (BreadthFirstSearch(Edges_Vector, L_source, L_destination, Lsd_vertex, Vertex_Predecessor) == false)
    {
      if(Source_Edge == Destination_Edge)
      {
        if(Check_Flag == 1)
        {
          cout << L_source << "-" << L_destination << std::endl;
          /* Clear the Flag */
          Check_Flag = 0;
        }

        else
        {
          std::cerr <<"Error: No Path exists between Source and Destination"<< std::endl;
        }

      }
      else
      {
        std::cerr <<"Error: No Path exists between Source and Destination"<<std::endl;
      }
      return;
    }
  }

  catch (...)
  {
    std::cerr << "Error: No Path exists between Source and Destination" << std::endl;
  }

  /* vector path stores the shortest path*/
  vector<int> path;
  /*Copy L_destination to L_step */
  L_step = L_destination;
  /* deque the value queue */
  path.push_back(L_step);
  while (Vertex_Predecessor[L_step] != -1)
  {
    path.push_back(Vertex_Predecessor[L_step]);
    L_step = Vertex_Predecessor[L_step];
  }

  /*get the size of path vector*/
  L_size_path = path.size() - 1;

  /* get the path from the path vector */
  for (Lsd_index = L_size_path; Lsd_index >= 0; Lsd_index--)
  {
    cout << path[Lsd_index];

    /* to format the output in the required format */
    if(Lsd_index!=0)
      {
        cout << "-";
      }
  }
  cout << endl;
}

/******************************************************************************
* Function Name      : Main
*
* Description        : This function is the Main function
*
* Input Parameters   : None
*
* Output Parameters  : None
*
* Return parameter   : void
*
******************************************************************************/

int main()
{

  /* String declaration for Input String */
  std::string sentence;

  /* String declaration for Duplicating sentence */
  std::string CopyOfSentence;

  /* variable for the space delimiter */
  std::string Space_delimiter_1 = " ";

  /* variable for the Open Brace delimiter */
  std::string Brace_delimiter_2 = "{";

  /* variable for the third delimiter */
  std::string delimiter_3 = ">,<";

  /* variable for the fourth delimiter */
  std::string delimiter_4 = "<";

  /* variable for the comma delimiter */
  std::string Comma_delimiter_5 = ",";

  /* variable for gettig the position */
  size_t position = 0;

  /* variable for the space delimiter */
  int L_Vertex = 0;

  /* variable storing length */
  int L_length1 = 0;

  int L_index_E = 0;

  while(1)
  {


    /* get the Input String from the user in sentence */
    getline(cin,sentence);

    /* EOF Exception handling for Input from A3 */
    if(sentence == "")
    {
      return 0;
    }

    /* EOF Exception handling for Input */
    if(cin.eof())
    {
      return 0;
    }

    /* Copy content of Sentence to CopyOfSentence for length processing */
    CopyOfSentence = sentence;

    /* Variable for Storing a String Token */
    std::string Token_1;

    /* Varable for storing the Token of CopyOfSentence */
    std::string CoS_Token;

    /* find the position of the delimiter in the sentence */
    position = CopyOfSentence.find(Space_delimiter_1);

    /* Get the first token till the position of delimiter */
    Token_1 = sentence.substr(0, position);

    if (Token_1 == "V" || Token_1 == "E")
    {
      /*For Display only*/
      std::cout << sentence << std::endl;
    }

    /* Erase the sentence string from 0 till delimiter position */
    sentence.erase(0, position + Space_delimiter_1.length());

    /* This While loop is for getting the length of the Entire Input String \
    for Exception handling by length of the string*/
    while((position = CopyOfSentence.find(Space_delimiter_1)) != std::string::npos)
    {
      /* Get the first Token of the CopyOfSentence string for proceessing */
      CoS_Token = CopyOfSentence.substr(0, position);

      /* Push the Token into the Vector Buffer */
      Buffer.push_back(CoS_Token);

      /* Erase the CopyOfSentence string from 0 till delimiter position */
      CopyOfSentence.erase(0, position + Space_delimiter_1.length());

      /* Try and Catch block used for any exception handling input that
      is not a string */
      try
      {
        /*Don't process the next Token for Command E */
        if(Token_1 != "E")
        {
          /*Convert String to Integer and store it in Local Vertex Variable */
          L_Vertex = stoi(CopyOfSentence);
        }
      }
      catch(...)
      {
        /* Error Display */
        std::cerr << "Error: Incorrect Input Format." << std::endl;
      }
    }

    /* Get the buffer size in the L_length1 Variable */
    L_length1 = Buffer.size();

    /* Try and Catch used to handle Exception */
    try
    {

      /* If the command is V */
      if ((Token_1 == "V" || Token_1 == "v") && (L_length1 == 1))
      {
        /* copy the L_Vertex in the Total_Vertex */
        Total_Vertex = L_Vertex;

        /*Clear the arrays*/
        for(int index = 0; index < Size_E; index++)
        {
          Vertex_1[index] = 0;
          Vertex_2[index] = 0;
        }

        /*clear the Edges_Vector*/
        for(auto& c: Edges_Vector)
        {
          c.clear();
        }

        /* Clear the BufferOf_E */
        BufferOf_E.clear();

        /* Clear the Vector Buffer Variable */
        Buffer.clear();

        /*Clear the L_length1*/
        L_length1 = 0;
      }

      /* If the command is E */
      else if (Token_1 == "E" || Token_1 == "e")
      {

       /* To Parse Delimiter = "{" */
       std::string Brace_delimiter_2 = "{";

       /* find the position of the delimiter in the sentence*/
       position = sentence.find(Brace_delimiter_2);

       /* get the token till the delimiter */
       Token_1 = sentence.substr(0, position);

       /* Erase the sentence for the passed token till the delimiter */
       sentence.erase(0, position + Brace_delimiter_2.length());

       /* To Parse Delimiter = "{" */
       Brace_delimiter_2 = "}";

       /* find the position of the delimiter in the sentence*/
       position = sentence.find(Brace_delimiter_2);

       /* get the token till the delimiter */
       Token_1 = sentence.substr(0, position);

       /* Erase the sentence for the passed token till the delimiter */
       sentence.erase(0, position + Brace_delimiter_2.length());

       /* Copy the Token_1 to sentence */
       sentence = Token_1;

       int count = 0;

       /* Find the delimiter till the end of the sentence */
       while ((position = sentence.find(delimiter_3)) != std::string::npos)
       {
          /* get the token till the delimiter */
          Token_1 = sentence.substr(0, position);

          if (count)
          {
            BufferOf_E.push_back(Token_1);
          }

          /* Erase the sentence for the passed token till the delimiter */
          sentence.erase(0, position + delimiter_3.length());

          /*copy Token_1 to L_Token_E1*/
          string L_Token_E1 = Token_1;

          size_t L_position_E1;

          /* To get the delimiter "<" in the sentence */
          if (count == 0)
          {
            /*Local String declaration for holding the String */
            string L_Token_E2;

            /* find the position of the delimiter in the sentence*/
            L_position_E1 = L_Token_E1.find(delimiter_4);

            /* get the token till the delimiter */
            L_Token_E2 = L_Token_E1.substr(0, L_position_E1);

            /* Erase the sentence for the passed token till the delimiter */
            L_Token_E1.erase(0, L_position_E1 + delimiter_4.length());

            /* append the token in the vector v */
            BufferOf_E.push_back(L_Token_E1);
          }
        }
        /* Get the L_Token_E2 */
        string L_Token_E2 = sentence.substr(0, sentence.length()-1);

        /* append the L_Token_E2 in the vector v */
        BufferOf_E.push_back(L_Token_E2);

        int L_size_BoFE =  BufferOf_E.size();

        /* To get the all "," delimiter in the sentence*/
        for (L_index_E = 0; L_index_E < L_size_BoFE; L_index_E++)
        {
          /* get the size of BufferOf_E Vector in Size_E Variable */
          Size_E = BufferOf_E.size();

          /* Local String declaration */
          size_t L_position_E2 = 0;

          /* defined two Strings L_Token_E3 and L_Token_E4 */
          std::string L_Token_E3, L_Token_E4;

          /* Get the vector in the string */
          string string = BufferOf_E[L_index_E];

          L_position_E2 = string.find(Comma_delimiter_5);

          /*get the L_Token_E3 from the position */
          L_Token_E3 = string.substr(0, L_position_E2);

          /*get the Token_b from position_1 + 1*/
          L_Token_E4 = string.substr(L_position_E2 + 1, string.length()-1);

          /*Convert the Token_a string to integer*/
          int L_value1 = stoi(L_Token_E3);

          /*Convert the Token_b string to integer*/
          int L_value2 = stoi(L_Token_E4);

          /*get the value1 to the array vertex_1 */
          Vertex_1[L_index_E] = L_value1;

          /*get the value2 to the array vertex_2 */
          Vertex_2[L_index_E] = L_value2;

        }

        /*Clear the Print_flag*/
        Print_flag = 0;

        for(int index = 0 ; index <= Size_E; index++)
        {
          if ((Vertex_1[index] >= Total_Vertex) || (Vertex_2[index] >= Total_Vertex))
          {
           /* Update the flag value to one */
           Print_flag = 1;
          }
        }

        if(Print_flag == 1)
        {
          /* if Vertex is > Total_Vertex error message is printed */
          std::cerr << "Error: Edge has a Vertex greater than Vertex" << std::endl;
        }
        else
        {
          /*Function call for passing the Edges for calculating the shortest path */
          add_edge(Edges_Vector, Vertex_1, Vertex_2);
        }

        /* Clear the Buffer */
        Buffer.clear();
      }

      /* If the command is S */
      else if((Token_1 == "S" || Token_1 == "s") && (L_length1 <= 3))
      {
       /* String Token for command S */
       std::string L_Token_S1;
       std::string L_Token_S2;
       size_t position_S;

       /* get the position of the delimiter */
       position_S = sentence.find(Space_delimiter_1);

       /* get the first token in the variable */
       L_Token_S1 = sentence.substr(0,position_S);

       /* get the second token in the second variable  */
       L_Token_S2 = sentence.substr(position_S + 1, sentence.length()-1);

       /* Erase the sentence for the passed token till the delimiter */
       sentence.erase(0, position_S + Space_delimiter_1.length());

       /* convert the string to int and store it in Source_Edge */
       Source_Edge = stoi(L_Token_S1);

       /* convert the token string to int and store it in the Destination_Edge*/
       Destination_Edge = stoi(L_Token_S2);

       try
       {
         /* condition to print path only when the Vertices are < Total_Vertex */
         if (Print_flag ==1)
         {
           /* if Vertex is > Total_Vertex error message is printed */
           std::cerr << "Error: Edge has a Vertex greater than Vertex" << std::endl;
         }
         else
         {
           /* Function call */
           ShortestDistance(Edges_Vector, Source_Edge, Destination_Edge, Total_Vertex);
         }
       }

       catch(...)
       {
         std::cerr << "Error: Doesn't match the pattern of Input." << std::endl;
       }

       /* Clear the Buffer after printing the path */
        Buffer.clear();

       /* Clear the L_length1 after printing the path */
        L_length1 = 0;

       /* Clear the Print_flag */
        Print_flag = 0;

      }

      else
      {
        /* Clear the Buffer */
        Buffer.clear();
        /* Clear the L_length1 */
        L_length1 = 0;
        Token_1.clear();
        sentence.clear();

        cout << "Error: Incorrect Input Format." << std::endl;
      }

    }
    catch(...)
    {
      /* Clear the Buffer */
      Buffer.clear();
      /* Clear the L_length1 */
      L_length1 = 0;
      Token_1.clear();
      sentence.clear();
      cout << "Error: Incorrect Input Format." << std::endl;
    }

  }

  return 0;
}
