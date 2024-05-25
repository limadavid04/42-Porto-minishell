<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/psousa42/42_Minishell/">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/C_Programming_Language.svg/926px-C_Programming_Language.svg.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Minishell 42</h3>

  <p align="center">
    An awesome 42 project!
    <br />
    <a href="https://tailwindflex.com/public/images/thumbnails/simple-coming-soon-page-2/canvas.min.webp"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://tailwindflex.com/public/images/thumbnails/simple-coming-soon-page-2/canvas.min.webp">View Demo</a>
    ·
    <a href="https://github.com/psousa/42_Minishell/issues">Report Bug</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->



<!-- ABOUT THE PROJECT -->
## About The Project

This goal of this project is to create a simple shell.

Minishell is based on bash, and altough it is not as feature rich it has the following capabilities:

	- Lexer and parser for the input which:
		- Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
		- Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
	- Has working history which can be browsed with Up and Down arrow keys;
	- Builtin commands such as echo, cd, pwd, export, unset, env and exit;
    - It Searches and launches the right executable (based on the PATH variable or using a relative or an absolute path);
	- Signal handling for ctrl-C, ctrl-D and ctrl-\\;
	- Pipelining of commands with the pipe ("|") operator;
	- I/O Redirection 
		- ◦ < should redirect input. 
		- ◦ > should redirect output. 
		- ◦ << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history! 
		- ◦ >> should redirect output in append mode
	- Expansion of environment variables ($HOME, $PWD, etc) and exit status ($?);


<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

This Project was built using C and only some built in functions are allowed

> <a href="https://www.w3schools.com/c/c_intro.php"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/C_Programming_Language.svg/926px-C_Programming_Language.svg.png" alt="C Programming Language" width="80" height="80"> </a>

Rules of 42:
```
  * No for, do while, switch, case or goto are allowed
  * No more than 25 lines per function and 5 functions per file
  * No assigns and declarations in the same line (unless static)
  * No more than 5 variables in 1 function
```
Allowed Functions:
```
  * readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history,
  * printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4,
  * signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat,
  * unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty,
  * ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum,
  * tgetstr, tgoto, tputs
```
<p align="right">(<a href="#readme-top">back to top</a>)</p>
