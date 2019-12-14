#include<iostream>
#include<unistd.h>
#include<string.h>
#include<fstream>
#include <bits/stdc++.h>
#define pdd pair<double, double>
using namespace std;

extern int l_vaue;

int s_value = 0;
int n_value = 0;
int l_value = 0;
int c_value = 0;
int last_s_randomvalue = 0;
int s_randomvalue = 0;
int s_randomvalue_default = 0;
int n_randomvalue = 0;
int l_randomvalue = 0;
int c_randomvalue = 0;
int c_randomvalue_x = 0;
int c_randomvalue_y = 0;
int s_defaultvalue = 10;
int n_defaultvalue = 5;
int l_defaultvalue = 5;
int c_defaultvalue = 20;
int s_flag = 0;
int n_flag = 0;
int l_flag = 0;
int c_flag = 0;
int special_index = 0;
int Check_flag1 = 0;
int count_of_copy = 0;

int street_count = 0;
int default_street_count = 0;

std::string final_coordinate_string;

std::vector<string> first_vector;

int l_coord_count_normal = 0;

std::string coordinates_string= "";

std::vector<string> coordinates_vector;
std::vector<int> temporary_Ccoordinates_vector_X;
std::vector<int> temporary_Ccoordinates_vector_Y;
std::vector<string> joined_coordinates_vector;

int C_count = 0;

double x = 0;
double y = 0;

int coordinate_array_x[100] = {};
int coordinate_array_y[100] = {};
int default_coordinate_array[100] = {};

int default_coordinate_array_x[100] = {};
int default_coordinate_array_y[100] = {};
int array_x[100] = {};
int array_y[100] = {};

std::string coordinates[100] = {};

string street_array[100] = {};
string street_coordinate_x[100] = {};
string street_coordinate_y[100] = {};

pdd A = make_pair(array_x[0], array_y[0]);
pdd B = make_pair(array_x[0], array_y[0]);
pdd C = make_pair(array_x[0], array_y[0]);
pdd D = make_pair(array_x[0], array_y[0]);


pdd SegmentIntersection(pdd A, pdd B, pdd C, pdd D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1*(A.first) + b1*(A.second);

    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2*(C.first)+ b2*(C.second);

    double determinant = a1*b2 - a2*b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return make_pair(FLT_MAX, FLT_MAX);
    }
    else
    {
        x = (b2*c1 - b1*c2)/determinant;
        y = (a1*c2 - a2*c1)/determinant;
        return make_pair(x, y);
    }
}


/* Main funtion for regen */
int main(int argc, char **argv)
{
while(1)
{
    std::string s_string;
    std::string n_string;
    std::string l_string;
    std::string c_string;

    int index = 0;
    char L_command;
    int Ls_LowerLimit = 2;
    int Ln_LowerLimit = 2;
    int Ll_LowerLimit = 5;
    int Lc_LowerLimit = 2;
    int tvX_size = 0;

    /* EOF Exception handling for Input */
    if(cin.eof())
    {
        return 0;
    }

    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    /* check that it did not fail */
    if (urandom.fail())
    {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }

    opterr = 0;

    // expected options are '-s', '-l', , '-n' and '-c value'
    while ((L_command= getopt (argc, argv, "s:n:l:c:")) != -1)
    {
        switch (L_command)
        {
        case 's':
            s_flag = 1;
            s_string = optarg;
            s_value = atoi(s_string.c_str());

            break;
        case 'n':
            n_flag = 1;
            n_string = optarg;
            n_value = atoi(n_string.c_str());

            break;
        case 'l':
            l_flag = 1;
            l_string = optarg;
            l_value = atoi(l_string.c_str());

            break;
        case 'c':
            c_flag = 1;
            c_string = optarg;
            c_value = atoi(c_string.c_str());


            break;
        case '?':
            if(optopt == 'c')
            {
                std::cerr << "Error: option -" << (char)optopt
                          << " requires an argument." << std::endl;
                exit(0);
            }

            return 1;
        default:
            return 0;
        }
    }


    if (optind < argc)
    {
        std::cerr << "Error: Found positional arguments\n";
        for (index = optind; index < argc; index++)
        {
            std::cerr << "Error: Non-option argument: " << argv[index] << "\n";
            exit(0);
        }
    }

    /* Default values of s, n, l, c, */
    if(s_flag == 0)
    {
        char ch = 'a';
        urandom.read(&ch, 1);
        s_randomvalue_default = ((unsigned int)ch % (s_defaultvalue - Ls_LowerLimit + 1)) + Ls_LowerLimit;
    }
    else
    {
            // read a random 8-bit value.
            // Have to use read() method for low-level reading
            char ch = 'a';
            urandom.read(&ch, 1);
            s_randomvalue = ((unsigned int)ch % (s_value - Ls_LowerLimit + 1)) + Ls_LowerLimit;

    }

    if(n_flag == 0)
    {
        char ch = 'b';
        urandom.read(&ch, 1);
        n_randomvalue = ((unsigned int)ch % (n_defaultvalue - Ln_LowerLimit + 1)) + Ln_LowerLimit;
    }
    else
    {
        // read a random 8-bit value.
        // Have to use read() method for low-level reading
        char ch = 'v';
        urandom.read(&ch, 1);
        n_randomvalue = ((unsigned int)ch % (n_value - Ln_LowerLimit + 1)) + Ln_LowerLimit;


    }

    if(l_flag == 0)
    {

        char ch = 'c';
        urandom.read(&ch, 1);
        l_randomvalue = ((unsigned int)ch % (l_defaultvalue - Ll_LowerLimit + 1)) + Ll_LowerLimit;


    }
    else
    {
            // read a random 8-bit value.
            // Have to use read() method for low-level reading
            char ch = 'd';
            urandom.read(&ch, 1);
            l_randomvalue = ((unsigned int)ch % (l_value - Ll_LowerLimit + 1)) + Ll_LowerLimit;

    }

    if(c_flag == 0)
    {

        coordinates_vector.clear();
        temporary_Ccoordinates_vector_X.clear();
        temporary_Ccoordinates_vector_Y.clear();
        C_count = 0;
        count_of_copy = 0;

        for(int index_s = 0; index_s < s_randomvalue_default; index_s++)
        {
            for(index = 0; index < n_randomvalue; index++)
            {
                /*Random generator for X */
                char ch = 'd';
                urandom.read(&ch, 1);
                c_randomvalue_x = ((unsigned int)ch % (c_defaultvalue - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                default_coordinate_array_x[index] = c_randomvalue_x;
                temporary_Ccoordinates_vector_X.push_back(c_randomvalue_x);

                /* Random generator for Y */
                char chd = 'g';
                urandom.read(&chd, 1);
                c_randomvalue_y = ((unsigned int)chd % (c_defaultvalue - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                default_coordinate_array_y[index] = c_randomvalue_y;
                temporary_Ccoordinates_vector_Y.push_back(c_randomvalue_y);

                /*Database for X and Y coordinates */
                coordinates_vector.push_back("(" + std:: to_string(default_coordinate_array_x[index]) + "," + std::to_string(default_coordinate_array_y[index]) + ")");

            }

        }

        tvX_size = temporary_Ccoordinates_vector_X.size();

        for (int c_index = 0; c_index < tvX_size; c_index++)
        {
            if((C_count != tvX_size) && (c_index + 3 <= tvX_size))
            {

                pdd A = make_pair(coordinate_array_x[c_index], coordinate_array_y[c_index]);
                pdd B = make_pair(coordinate_array_x[c_index + 1], coordinate_array_y[c_index + 1]);
                pdd C = make_pair(coordinate_array_x[c_index + 2], coordinate_array_y[c_index + 2]);
                pdd D = make_pair(coordinate_array_x[c_index + 3], coordinate_array_y[c_index + 3]);
                pdd intersection = SegmentIntersection(A, B, C, D);

                if (((x >= min(A.first,B.first)) && (x <= max(A.first, B.first))) &&\
                    ((min(A.second,B.second) <= y) && (y <= max(A.second, B.second))))
                {
                    for(int vx_index = 0; vx_index < temporary_Ccoordinates_vector_X.size(); vx_index++ )
                    {
                        if(count_of_copy <= temporary_Ccoordinates_vector_X.size() && (vx_index + 1 <=temporary_Ccoordinates_vector_X.size()))
                        {
                            if((temporary_Ccoordinates_vector_X[vx_index] == temporary_Ccoordinates_vector_X[vx_index + 1]) &&\
                               (temporary_Ccoordinates_vector_Y[vx_index] == temporary_Ccoordinates_vector_Y[vx_index + 1]))
                            {

                                Check_flag1 = 1;
                                coordinates_vector.clear();
                                temporary_Ccoordinates_vector_X.clear();
                                temporary_Ccoordinates_vector_Y.clear();

                                for(int index_s = 0; index_s < s_randomvalue_default; index_s++)
                                {
                                    for(index = 0; index < n_randomvalue; index++)
                                    {
                                        /*Random generator for X */
                                        char ch = 'd';
                                        urandom.read(&ch, 1);
                                        c_randomvalue_x = ((unsigned int)ch % (c_defaultvalue - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                                        default_coordinate_array_x[index] = c_randomvalue_x;
                                        temporary_Ccoordinates_vector_X.push_back(c_randomvalue_x);

                                        /* Random generator for Y */
                                        char chd = 'g';
                                        urandom.read(&chd, 1);
                                        c_randomvalue_y = ((unsigned int)chd % (c_defaultvalue - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                                        default_coordinate_array_y[index] = c_randomvalue_y;
                                        temporary_Ccoordinates_vector_Y.push_back(c_randomvalue_y);

                                        /*Database for X and Y coordinates */
                                        coordinates_vector.push_back("(" + std:: to_string(default_coordinate_array_x[index]) + "," + std::to_string(default_coordinate_array_y[index]) + ")");

                                    }
                                }
                                 count_of_copy++;
                             }
                         }
                     }

                     /*rejecting the points */
                     for(int index_s = 0; index_s < s_randomvalue_default; index_s++)
                     {
                         for(index = 0; index < n_randomvalue; index++)
                         {
                             /*Random generator for X */
                             char ch = 'd';
                             urandom.read(&ch, 1);
                             c_randomvalue_x = ((unsigned int)ch % (c_defaultvalue - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                             default_coordinate_array_x[index] = c_randomvalue_x;
                             temporary_Ccoordinates_vector_X.push_back(c_randomvalue_x);

                             /* Random generator for Y */
                             char chd = 'g';
                             urandom.read(&chd, 1);
                             c_randomvalue_y = ((unsigned int)chd % (c_defaultvalue - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                             default_coordinate_array_y[index] = c_randomvalue_y;
                             temporary_Ccoordinates_vector_Y.push_back(c_randomvalue_y);

                             /*Database for X and Y coordinates */
                             coordinates_vector.push_back("(" + std:: to_string(default_coordinate_array_x[index]) + "," + std::to_string(default_coordinate_array_y[index]) + ")");

                         }
                     }

                     C_count++;
                     c_index = 0;

                 }
                 else
                 {
                    /*Do Nothing*/;
                 }

             }

         }

         if(C_count < 80)
         {

            int l_coord_count = n_randomvalue;

            /*Automatic coordinate generator*/
            for(int l_index = 0; l_index < coordinates_vector.size(); l_index++)
            {

                l_coord_count--;

                first_vector.push_back(coordinates_vector[l_index]);

                if(l_coord_count == 0)
                {

                    for (int m_index = 0; m_index < first_vector.size(); m_index++)
                    {
                        coordinates_string = coordinates_string + first_vector[m_index];
                    }

                    joined_coordinates_vector.push_back(coordinates_string);
                    first_vector.clear();
                    coordinates_string.clear();
                    l_coord_count = n_randomvalue;
                }

            }


            if( default_street_count == 0)
            {

                /* Automatic street generator */
                for(int j_index = 0; j_index < s_randomvalue_default; j_index++)
                {
                    last_s_randomvalue = s_randomvalue_default;
                    std::string name;
                    name = "a \"Street_" + std::to_string(j_index) + "\" " + joined_coordinates_vector[j_index];
                    street_array[j_index] = name;
                    std::cout << street_array[j_index] << '\n';
                    default_street_count++;

                }

                std::cout << "g" << '\n';
                joined_coordinates_vector.clear();
            }

            else
            {
                for (int p_index = 0; p_index < last_s_randomvalue; p_index++)
                {

                    std::string remove;
                    remove = "r \"Street_" + std::to_string(p_index) + "\"";
                    cout << remove << endl;

                }

                for(int q_index = 0; q_index < s_randomvalue_default; q_index++)
                {
                    std::string after_remove;
                    after_remove = "a \"Street_" + std::to_string(q_index) + "\" " + joined_coordinates_vector[q_index];
                    street_array[q_index] = after_remove;
                    std::cout << street_array[q_index] << '\n';

                }

                std::cout << "g" << '\n';
                joined_coordinates_vector.clear();
                last_s_randomvalue = s_randomvalue_default;

            }


        }
        else
        {
            C_count = 0;
            std::cerr << "Error: failed to regenrate coordinates for 80 simultaneous times." << '\n';
            exit(0);
        }


    }
    else
    {

            coordinates_vector.clear();
            temporary_Ccoordinates_vector_X.clear();
            temporary_Ccoordinates_vector_Y.clear();
            C_count = 0;
            count_of_copy = 0;

            for(int index_s = 0; index_s < s_randomvalue; index_s++)
               {
                   for(index = 0; index < n_randomvalue; index++)
                   {
                       char ch = 'd';
                       // read a random 8-bit value.
                       // Have to use read() method for low-level reading
                       urandom.read(&ch, 1);
                       c_randomvalue_x = ((unsigned int)ch % (c_value - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                       coordinate_array_x[index] = c_randomvalue_x;
                       temporary_Ccoordinates_vector_X.push_back(c_randomvalue_x);

                       char chy = 'f';
                       // read a random 8-bit value.
                       // Have to use read() method for low-level reading
                       urandom.read(&chy, 1);
                       c_randomvalue_y = ((unsigned int)chy % (c_value - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                       // cast to integer to see the numeric value of the character
                       coordinate_array_y[index] = c_randomvalue_y;
                       temporary_Ccoordinates_vector_Y.push_back(c_randomvalue_y);

                       /*Database for X and Y coordinates */
                       coordinates_vector.push_back("(" + std:: to_string(coordinate_array_x[index]) + "," + std::to_string(coordinate_array_y[index]) + ")");
                   }
               }

            tvX_size = temporary_Ccoordinates_vector_X.size();

            for (int c_index = 0; c_index < tvX_size; c_index++)
            {
                if((C_count <= tvX_size) && c_index+3 <= tvX_size)
                {
                    pdd A = make_pair(coordinate_array_x[c_index], coordinate_array_y[c_index]);
                    pdd B = make_pair(coordinate_array_x[c_index + 1], coordinate_array_y[c_index + 1]);
                    pdd C = make_pair(coordinate_array_x[c_index + 2], coordinate_array_y[c_index + 2]);
                    pdd D = make_pair(coordinate_array_x[c_index + 3], coordinate_array_y[c_index + 3]);
                    pdd intersection = SegmentIntersection(A, B, C, D);

                    if (((x >= min(A.first,B.first)) && (x <= max(A.first, B.first))) &&\
                    ((min(A.second,B.second) <= y) && (y <= max(A.second, B.second))))
                {
                    for(int vx_index = 0; vx_index < temporary_Ccoordinates_vector_X.size(); vx_index++ )
                    {
                        if((count_of_copy <= temporary_Ccoordinates_vector_X.size()) && ( vx_index+1<= temporary_Ccoordinates_vector_X.size()))
                        {
                            if((temporary_Ccoordinates_vector_X[vx_index] == temporary_Ccoordinates_vector_X[vx_index + 1]) &&\
                               (temporary_Ccoordinates_vector_Y[vx_index] == temporary_Ccoordinates_vector_Y[vx_index + 1]))
                            {

                                Check_flag1 = 1;
                                coordinates_vector.clear();
                                temporary_Ccoordinates_vector_X.clear();
                                temporary_Ccoordinates_vector_Y.clear();

                                for(int index_s = 0; index_s < s_randomvalue; index_s++)
                                {
                                   for(int index = 0; index < n_randomvalue; index++)
                                   {
                                       char ch = 'd';
                                       // read a random 8-bit value.
                                       // Have to use read() method for low-level reading
                                       urandom.read(&ch, 1);
                                       c_randomvalue_x = ((unsigned int)ch % (c_value - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                                       coordinate_array_x[index] = c_randomvalue_x;
                                       temporary_Ccoordinates_vector_X.push_back(c_randomvalue_x);

                                       char chy = 'f';
                                       // read a random 8-bit value.
                                       // Have to use read() method for low-level reading
                                       urandom.read(&chy, 1);
                                       c_randomvalue_y = ((unsigned int)chy % (c_value - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                                       coordinate_array_y[index] = c_randomvalue_y;
                                       temporary_Ccoordinates_vector_Y.push_back(c_randomvalue_y);

                                       /*Database for X and Y coordinates */
                                       coordinates_vector.push_back("(" + std:: to_string(coordinate_array_x[index]) + "," + std::to_string(coordinate_array_y[index]) + ")");
                                   }
                               }
                                count_of_copy++;

                            }
                        }
                    }

                    /*rejecting the points */
                    for(int index_s = 0; index_s < s_randomvalue; index_s++)
                    {
                       for(int index = 0; index < n_randomvalue; index++)
                       {
                           char ch = 'd';
                           // read a random 8-bit value.
                           // Have to use read() method for low-level reading
                           urandom.read(&ch, 1);
                           c_randomvalue_x = ((unsigned int)ch % (c_value - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                           coordinate_array_x[index] = c_randomvalue_x;
                           temporary_Ccoordinates_vector_X.push_back(c_randomvalue_x);

                           char chy = 'f';
                           // read a random 8-bit value.
                           // Have to use read() method for low-level reading
                           urandom.read(&chy, 1);
                           c_randomvalue_y = ((unsigned int)chy % (c_value - Lc_LowerLimit + 1)) + Lc_LowerLimit;
                           coordinate_array_y[index] = c_randomvalue_y;
                           temporary_Ccoordinates_vector_Y.push_back(c_randomvalue_y);

                           /*Database for X and Y coordinates */
                           coordinates_vector.push_back("(" + std:: to_string(coordinate_array_x[index]) + "," + std::to_string(coordinate_array_y[index]) + ")");
                       }
                   }

                       C_count++;
                       c_index = 0;

                }
                else
                {
                    /*Do Nothing*/;
                }
            }
        }

        if(C_count < 80)
        {

            l_coord_count_normal = n_randomvalue;

            /*Automatic coordinate generator*/
            for(int l_index = 0; l_index < coordinates_vector.size(); l_index++)
            {

                l_coord_count_normal--;

                first_vector.push_back(coordinates_vector[l_index]);
                if(l_coord_count_normal == 0)
                {

                    for (int m_index = 0; m_index < first_vector.size(); m_index++)
                    {
                        coordinates_string = coordinates_string + first_vector[m_index];
                    }

                    joined_coordinates_vector.push_back(coordinates_string);
                    first_vector.clear();
                    coordinates_string.clear();
                    l_coord_count_normal = n_randomvalue;
                }

            }

            if( street_count == 0)
            {
                /* Automatic street generator */
                for(int j_index = 0; j_index < s_randomvalue; j_index++)
                {
                    last_s_randomvalue = s_randomvalue;

                        std::string name;
                        name = "a \"Street_" + std::to_string(j_index) + "\" " + joined_coordinates_vector[j_index];
                        street_array[j_index] = name;
                        std::cout << street_array[j_index] << '\n';
                        street_count++;

                }
                std::cout << "g" << '\n';
                joined_coordinates_vector.clear();
            }

            else
            {
                for (int p_index = 0; p_index < last_s_randomvalue; p_index++)
                {

                    std::string remove;
                    remove = "r \"Street_" + std::to_string(p_index) + "\"";
                    cout << remove << endl;

                }

                for(int q_index = 0; q_index < s_randomvalue; q_index++)
                {
                    std::string after_remove;
                    after_remove = "a \"Street_" + std::to_string(q_index) + "\" " + joined_coordinates_vector[q_index];
                    street_array[q_index] = after_remove;
                    std::cout << street_array[q_index] << '\n';

                }
                std::cout << "g" << '\n';
                joined_coordinates_vector.clear();
                last_s_randomvalue = s_randomvalue;

            }
        }
        else
        {
            C_count = 0;
            std::cerr << "Error: failed to regenrate coordinates for 80 simultaneous times." << '\n';
            exit(0);
        }

    }

    // close random stream
    urandom.close();

    if(l_flag == 1)
    {
        sleep(l_randomvalue);
    }
    else
    {
        sleep(l_randomvalue);
    }
}
    return 0;
}
