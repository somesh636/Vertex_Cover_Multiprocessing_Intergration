#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <signal.h>
#include <vector>
using namespace std;


int rgen(int argc, char **argv)
{

    execv("./rgen", argv);
    return 0;
}

int a1(void)
{

    char *new_argv[4];
    new_argv[0]="/usr/bin/python2";
    new_argv[1]="-u";
    new_argv[2]="ece650-a1.py";
    new_argv[3]=0;

    int value = execvp(new_argv[0],new_argv);

    if(value == -1)
    {
        std::cerr << "Error: from a1" << '\n';
    }
    return 0;
}

int a2(void)
{
    int value2 = 0;

    char* arg_list[] = { nullptr};

    value2 = execv("./ece650-a2", arg_list);

    if(value2 == -1)
    {
        std::cerr << "Error: from a2" << '\n';
    }
    return 0;
}


int main (int argc, char **argv)
{

        std::vector<pid_t> kids;

        int RgentoA1[2];
        pipe(RgentoA1);
        int A1toA2[2];
        pipe(A1toA2);

        int status;
        string input;

        pid_t child_pid;
        child_pid = fork();

        if(child_pid < 0)
        {
            std::cout << "couldnot fork" << '\n';
        }

        /* First Child */
        else if(child_pid == 0)
        {
          /*write into the pipe RgentoA1*/
          dup2(RgentoA1[1], STDOUT_FILENO);
          close(RgentoA1[0]);
          close(RgentoA1[1]);

          /* return to rgen function */
          return rgen(argc, argv);
        }

        kids.push_back(child_pid);

        /* Forking inorder to Execute A1 */
        child_pid = fork();

        /* Second Child */
        if(child_pid == 0)
        {
            /* redirect stdin to the pipe */
            dup2(RgentoA1[0], STDIN_FILENO);
            close(RgentoA1[0]);
            close(RgentoA1[1]);

            /* redirect stdout to the pipe */
            dup2(A1toA2[1], STDOUT_FILENO);
            close(A1toA2[0]);
            close(A1toA2[1]);

            return a1();

        }
         kids.push_back(child_pid);

        /* Fork to launch A2 */
         child_pid = fork();

         /* Third Child */
         if (child_pid == 0)
         {
             /* redirect stdin to the pipe */
             dup2(A1toA2[0], STDIN_FILENO);
             close(A1toA2[0]);
             close(A1toA2[1]);

             return a2();
         }

        /* redirect stdout to the pipe */
        dup2(A1toA2[1],STDOUT_FILENO);

         while (!std::cin.eof())
         {
          // read a line of input until EOL and store in a string
          string line;
          std::getline(std::cin, line);
          std::cout << line << std::endl;

         }

          close(A1toA2[0]);
          close(A1toA2[1]);

        kids.push_back(child_pid);

        for(pid_t k : kids)
        {
            kill (k,SIGTERM);
            waitpid(k, &status, 0);

        }

    return 0;
}
